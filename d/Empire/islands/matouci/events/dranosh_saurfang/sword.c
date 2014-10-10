#include "/d/Empire/islands/matouci.h"

inherit MAT_DIR_EVENTS + "dranosh_saurfang/blood_weapon";

static void
create() 
{
    ::create();
    set_name("Sword of the Deathbringer");
    set_short("a great-sword of dragon's bone");
    set_long("This is a heavy two-handed sword crafted from dragon's bone. " +
             "There a series of intricate marks of blood running along its " +
             "blade. It appears to drain the blood from your hands just by " +
             "holding it.");
    add_id(({ "sword", "great-sword" }));
    set_class(20);
    set_weight(10);
    set_value(16661);
    set_type("twohanded");
    set_damage_type("chop");
    set_wield_modifier("str",  6);   
    set_wield_modifier("dex", -2);
    set_wield_modifier("con", -2);
    set_wield_modifier("int", -2);
    add_property(({ "artifact", "bone" }));

    set_fury_lim(20);
    set_blood_wc(75);
    add_spell("rune of blood",     20, 100, store_fp("do_rune"));
    add_spell("boiling blood",     40, 150, store_fp("do_boil"));
    add_spell("blood nova",        60, 200, store_fp("do_nova"));
    add_spell("call blood beast",  80, 279, store_fp("do_call"));
    add_spell("mark of death",    100, 362, store_fp("do_mark"));
}

static string
colour(string str) 
{
    return "%^B_RED%^%^L_YELLOW%^" + str + "%^END%^";
}

static void
do_nova(object ply, object foe, object env) 
{
    object *arr;
    int i, len; 
    tell_room(env, colour("Shrapnel of frozen blood shoot from " + 
                          ply->query_name() + ".") + "\n", ({ ply }));
    arr = ply->query_attackers();
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        if (!objectp(foe = present(arr[i], env))) {
            continue;
        }
        EMP_D_COMBAT->hit_player(ply, foe, 70 + random(80), 
                                 "magic", 0, this_object());
    }
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

static void
do_mark(object ply, object foe, object env) 
{
    object obj;
    if (!objectp(obj = make(resolve_path("death_mark"), foe))) {
        return;
    }
    obj->set_caster(ply);
}

static void
do_rune(object ply, object foe, object env) 
{
    object obj;
    if (!objectp(obj = make(resolve_path("blood_rune"), foe))) {
        return;
    }
    obj->set_caster(ply);
}
