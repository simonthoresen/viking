#include "/d/Empire/islands/reikland.h"

inherit EMP_I_MONSTER;

static void 
create() 
{
    ::create();
    set_name("wolf");
    set_short("a fierce wolf");
    set_long("A grey furred wolf with sharp teeth.");
    set_level(22);
    set_hp(666);
    set_wc(22);
    set_ac(11);
    set_aggressive(1);
    add_property("unarmed_damage_type", ({ "claw", "bite" }));
    add_property("unarmed_weapon_class", 20);
    load_a_chat(100, ({ store_fp("attack") }));
}
