#include "/d/Empire/islands/matouci.h"

inherit MAT_DIR_EVENTS + "dranosh_saurfang/blood_weapon";

static void
create() 
{
    ::create();
    set_name("Axe of the Deathbringer");
    set_short("a war-axe of dragon's bone");
    set_long("This is a one-handed axe with double edges. It has been " + 
             "crafted from dragon's bone. It appears to drain the blood " +
             "from your hands just by holding it.");
    set_info(store_fp("on_info"));
    add_id(({ "axe", "war-axe" }));
    set_class(9);
    set_weight(1);
    set_value(16661);
    set_damage_type("chop");
    set_wield_modifier("str",  3);   
    set_wield_modifier("dex", -1);
    set_wield_modifier("con", -1);
    set_wield_modifier("int", -1);
    add_property(({ "artifact", "bone" }));

    set_fury_lim(20);
    set_blood_wc(50);
    add_spell("boiling blood",     50, 150, store_fp("do_boil"));
    add_spell("call blood beast", 100, 279, store_fp("do_call"));
}

static void
do_boil(object ply, object foe, object env) 
{
    object obj;
    if (!objectp(obj = make(resolve_path("blood_boil"), foe))) {
        return;
    }
    obj->set_caster(ply);
}

static void
do_call(object ply, object foe, object env) 
{
    object obj;
    if (!objectp(obj = make(resolve_path("blood_beast"), env))) {
        return;
    }
    obj->set_weapon(this_object());
    obj->do_attack(foe);
}
