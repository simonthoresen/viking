#include "/d/Empire/islands/dragon.h"

inherit EMP_I_MONSTER;

static void
create() 
{
    ::create();
    set_name("Whelp");
    set_short("a dragon whelp");
    set_long("This is a small flying dragon whelp. Although small, it can " + 
             "still put up quite the fight.");
    add_id("dragon whelp");
    set_log_file("dragon");
    set_level(29);
    set_sp(query_sp() * 2);
    set_hp(query_hp() / 2);
    set_aggressive(1);
    set_wandering_time(10);
    set_wandering_chance(50);
    add_property("unarmed_damage_type", ({ "bite", "claw" }));
    add_property("flying");
    load_a_chat(75, ({ store_fp(parse_path("cast_elembolt"), "main") }));
}

public int
is_dragon() 
{
    return 1;
}
