#include "/d/Empire/islands/reikland.h"

inherit armour EMP_I_ARMOUR;
inherit align  EMP_I_ALIGNED;

static void 
create() 
{
    armour::create();
    align::create();
    set_name("Heart of Kalerecent");
    set_short("a diamond ring");
    set_long("This is a shard of the heart of the Holy Warrior Kalerecent, " +
             "crystallized by a powerful alchemist after the warriors death.");
    add_id(({ "shard", "heart", "diamond ring" }));
    set_type("ring");
    set_ac(0);
    set_weight(1);
    set_value(1222);
    set_min_align(ALIGN_GOOD);
    set_wear_modifier("resist_fire", 25);
    set_wear_modifier("resist_cold", 10);
    set_wear_modifier("resist_electricity", 10);
    set_wear_modifier("devotion_good", 20);
    add_property("artifact");
}
