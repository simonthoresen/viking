#include "/d/Empire/empire.h"

inherit EMP_I_WEAPON;

private int _chance;
private int _deeds;

static void
create() 
{
    ::create();
    _chance = 0;
    _deeds  = 0;

    set_name("Tyrfing");
    set_short("a glorious broadsword");
    set_long("The sword shines and gleams like fire. It has a golden hilt. " +
             "It is said that it will never miss a stroke, will never rust " +
             "and will cut through stone and iron as easily as through " +
             "clothes.");
    set_damage_type(({ "slash", "slash", "chop" }));
    add_id(({ "sword", "glorious sword", "broadsword", 
              "glorious broadsword" }));
    set_class(19);
    set_weight(3);
    set_value(8888); 
    add_property("protected", 100);
    add_property(({ "artifact", "cursed", "magic", "metal" }));
    add_hook("__wield", store_fp("on_wield"));
    add_hook("__remove", store_fp("on_remove"));
    add_hook("__weapon_hit", store_fp("on_weapon_hit"));
    add_hook("__bwear_out", store_fp("on_bwear_out"));
    add_hook("__long", store_fp("on_long"));
}

static int
on_bwear_out(int dmg, string dtype) 
{
    return 1;
}

static string
on_long(string arg) 
{
    if (_deeds <= 0) {
        return 0;
    }
    if (_deeds == 1) {
        return "There is a mark on the hilt.";
    }
    return "There are " + convert_number(_deeds) + " marks on the hilt.";
}

static void
on_wield(object obj, string hand) 
{
    object ply;
    if (!objectp(ply = query_wield())) {
        return;
    }
    tell_object(ply, "Three marks appear on the hilt of the sword.\n");
    ply->add_hook("__damage_dealt", store_fp("on_wielder_damage_dealt"));
    ply->add_hook("__fight_beat", store_fp("on_wielder_fight_beat"));
    _deeds = 3;
}

static void
on_remove() 
{
    object ply;
    if (!objectp(ply = query_wield())) {
        return;
    }
    tell_object(ply, "The marks on the hilt of the sword disappear.\n");
    ply->remove_hook("__damage_dealt");
    ply->remove_hook("__fight_beat");
    _deeds = 0;
}

static int
on_weapon_hit(object foe) 
{
    return 44 - 10 * random(_deeds);
}

public void 
on_wielder_damage_dealt(int dmg, string dtype, object foe, 
                        string loc, object weapon) 
{
    if (weapon != this_object()) {
        return;
    }   
    EMP_D_CRITICAL->damage_dealt(query_wield(), foe, dmg, loc);
}
            
public void
on_wielder_fight_beat(object foe)
{
    object ply,obj;
    string loc;
    int val;
    if (!objectp(ply = query_wield()) || random(++_chance) < 100 || _deeds <= 0) {
        return;
    }
    _deeds--;
    _chance = 0;
    if (!stringp(loc = EMP_D_LIMB->query_random_limb(ply, 1))) {
        loc = "head";
    }
    tell_object(ply, bold("You cut yourself in the " + loc + "!\n"));
    tell_room(environment(ply), ply->query_name() + " cuts " + 
              ply->query_possessive() + "self in the " + loc + ".\n",
              ({ ply }));
    ply->set_busy_next_round();
    val = random(25) + random(25) + random(25) + random(25);
    EMP_D_COMBAT->hit_player(ply, ply, val, "slash", 0, this_object());
}

public void
set_chance(int val) 
{
    _chance = val;
}

public int
query_chance() 
{
    return _chance;
}

public void
set_deeds(int val) 
{
    _deeds = val;
}

public int
query_deeds() 
{
    return _deeds;
}
