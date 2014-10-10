#include "/d/Empire/empire.h"

inherit EMP_I_WEAPON;

static void
create() 
{
    ::create();
    set_name("claw");
    set_long("This is one of the claws of the dreaded Fenrir wolf. " +
             "It looks REALLY sharp. ");
    set_class(17);
    set_damage_type(({ "Claw", "claw", "claw", "claw" }));
    set_weight(3);
    set_value(6699);   
    add_property(({ "fur", "bone" }));
    add_hook("__long", store_fp("on_long"));
    add_hook("__remove", store_fp("on_remove"));
    add_hook("__weapon_hit", store_fp("on_weapon_hit"));
    add_hook("__wield", store_fp("on_wield"));
}

static void
on_long(string arg) 
{
    object ply, env;
    if (!objectp(ply = this_player()) ||
        !objectp(env = environment(ply))) 
    {
        return;
    }
    tell_object(ply, "It is so sharp, in fact, that you cut yourself " +
                "just by looking at it!\n");
    EMP_D_COMBAT->wound_player(ply, ply, 10);
}
 
static int
on_weapon_hit(object foe) 
{
    return 23;
}

static void
on_wield(object obj, string hand) 
{
    object ply;
    if (!objectp(ply = query_wield())) {
        return;
    }
    ply->add_hook("__damage_dealt", store_fp("on_wielder_damage_dealt"));
}

static void
on_remove(object obj) 
{
    object ply;
    if (!objectp(ply = query_wield())) {
        return;
    }
    ply->remove_hook("__damage_dealt");
}

public void
on_wielder_damage_dealt(int dmg, string dtype, object foe, 
                        string loc, object weapon) 
{
    object ply;
    if (!objectp(ply = query_wield()) ||
        !objectp(foe) || dmg < 15 ||
        weapon != this_object()) 
    {
        return;
    }
    EMP_D_COMBAT->wound_player(ply, foe, (dmg * 2) / 3);
}

public int
is_fenrir_claw() 
{
    return 1;
}
