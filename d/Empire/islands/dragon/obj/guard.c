#include "/d/Empire/islands/dragon.h"

inherit EMP_I_MONSTER;

static void
create() 
{
    ::create();
    set_name("Lair guard");
    set_short("a large dragonkin");
    set_long("This is a large crossbreed between a human and a dragon. It " +
             "has the upper body of a muscular human, and the feet and tail " +
             "of a dragon.");
    add_id(({ "guard", "dragonkin", "large dragonkin" }));
    set_log_file("dragon");
    set_level(29);
    set_hp(query_hp() * 5);
    set_str(query_str() * 5);
    set_aggressive(1);
    set_wandering_time(10);
    set_wandering_chance(50);
    load_a_chat(100, ({ store_fp("attack") }));
    EMP_D_WEAPON->add_weapon(200, "twohanded");
}

public int
is_dragon() 
{
    return 1;
}
