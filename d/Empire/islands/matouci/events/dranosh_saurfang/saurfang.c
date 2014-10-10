#include "/d/Empire/islands/matouci.h"

#define SPELL_TIME 20

inherit EMP_I_MONSTER;

private mapping _cast;

static void
create() 
{
    object obj;
    ::create();
    _cast = ([ ]);

    set_name("Dranosh Saurfang");
    set_short("Dranosh Saurfang the Deathbringer");
    set_long("Dranosh Saurfang, often called Saurfang the Younger, was the " +
             "son of Varok Saurfang and nephew of Broxigar the Red. He has " +
             "fallen to the undead, risen as a champion deathbringer.");
    add_id(({ "dranosh", "saurfang", "deathbringer" }));
    add_property("no_disarm");
    set_aggressive(1);
    set_gender(1);
    set_level(29);
    set_hp(6666);
    set_sp(6666);
    set_wc(66);
    set_ac(22);
    set_scary(1);
    set_bored_secs(300);
    
    load_chat(10, ({
        "*say I believe that my destiny lies elsewhere - that I will serve " +
            "a greater purpose someday.",
        "*say My father has gifted me with his battle armor and axe. Soon I " +
            "put it to good use.",
        "*say Rise up, sons of the Horde! Blood and glory await us! Lok'tar " +
            "ogar! For the Horde!",
    }));

    add_hook("__die", store_fp("on_die"));
    add_hook("__fight_beat", store_fp("on_fight_beat"));
    add_hook("__wield", store_fp("on_wield"));
    add_hook("__remove", store_fp("on_remove"));
    add_hook("__choose_target", store_fp("on_choose_target"));

    if (!clonep(this_object())) {
        return;
    }
    if (objectp(obj = D_TREASURE->get_unique(resolve_path("sword")))) {
        obj->move();
        obj->wield();
    } else {
        make(resolve_path("axe"), this_object())->wield();
        EMP_D_ARMOUR->add_armour(200, "shield");
    }
}

static object
on_choose_target(object *arr) 
{
    int len;
    if (!arrayp(arr) || (len = sizeof(arr)) == 0) {
	return 0;
    }
    return arr[random(len)];
}

private string
select_spell(string *spells) 
{
    int i, len;
    if (!arrayp(spells)) {
        return 0;
    }
    for (i = 0, len = sizeof(spells); i < len; ++i) {
        if (_cast[spells[i]] < time()) {
            return spells[i];
        }
    }
    return 0;
}

static void
on_fight_beat(object foe) 
{ 
    object weapon;
    string spell;
    if (!objectp(weapon = query_weapon(1))) {
        return;
    }
    weapon->add_blood(33, 1); /* cheat */ 
    if (!stringp(spell = select_spell(weapon->query_spells()))) {
        return;
    }
    if (command("cast " + spell)) {
        _cast[spell] = time() + SPELL_TIME + random(SPELL_TIME);
    }
}

static void
on_die(object corpse, object foe) 
{
    if (objectp(foe)) {
	EMP_D_ACHIEVEMENT->unlock(foe, "dranosh_saurfang");
    }
}

static void
on_wield(object weapon, string hands) 
{
    weapon->add_hook("__weapon_hit", store_fp("more_damage"));
}

static void
on_remove(object weapon, int silent) 
{
    weapon->remove_hook("__weapon_hit");
}

public int
more_damage(object foe) 
{
    return 69;
}
