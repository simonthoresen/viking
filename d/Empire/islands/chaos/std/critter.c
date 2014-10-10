#include "/d/Empire/islands/chaos.h"

inherit EMP_I_MONSTER;

static void
create() {
    ::create();
    set_wandering_chance(25);
    set_wandering_time(10);
    set_al(ALIGN_EVIL - 6 - 6 -6);
    add_hook("__die", store_fp("on_die"));
    add_hook("__init", store_fp("on_init"));
}

static void
on_die(object corpse, object killer) 
{
    EMP_D_ACHIEVEMENT->add_unlock(killer, "hero_to_the_downtrodden", 1, 10);
    EMP_D_ACHIEVEMENT->add_unlock(killer, "vanquisher_of_evil", 1, 25);
    EMP_D_ACHIEVEMENT->add_unlock(killer, "dispenser_of_justice", 1, 100);
}

static void
on_init() 
{
    object ply;
    if (!objectp(ply = this_player()) ||
        ply->is_chaos() ||
        ply->query_invis()) 
    {
        return;
    }
    do_attack(ply);
}

public int
is_chaos() 
{
    return 1;
}
