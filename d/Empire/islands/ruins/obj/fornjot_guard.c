#include "/d/Empire/islands/ruins.h"

inherit RUN_I_MONSTER;

static void
create()
{
    ::create();
    set_name("Critter");
    set_short("some undecided critter");
    set_long("");
    set_level(29);
    add_property("unarmed_damage_type", "cold");
    add_hook("__heart_beat", store_fp("on_heart_beat"));
}
