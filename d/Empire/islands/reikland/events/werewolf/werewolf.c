#include "/d/Empire/islands/reikland.h"

inherit EMP_I_MONSTER;

static void
create()
{
    ::create();
    set_race("wolf");
    set_name("Werewolf");
    set_short("a fierce werewolf");
    set_long("A most fierce werewolf wearing some torn, filthy rags. " +
             "Slime drips from its grinning jaws, and a spark of evil " +
             "flashes in its red eyes as you look at it.");
    add_id("fierce werewolf");
    set_level(25);
    set_hp(1000);
    set_str(36);
    set_dex(36);
    set_con(36);
    set_int(20);
    set_wc(36);
    set_ac(15);
    set_al(-250);
    add_property("unarmed_damage_type", ({ "bite", "claw" }));
    add_hook("__bkill", store_fp("maybe_infect"));
    add_hook("__heart_beat", store_fp("fast_heal"));
    load_a_chat(100, ({ store_fp("attack") }));
}

static void
fast_heal()
{
    reduce_hit_point(-5);
}

static int
maybe_infect(object victim, object killer)
{
    string file;
    if (!objectp(victim) ||
        !interactive(victim) ||
        objectp(present(file = resolve_path("disease"), victim)) ||
        random(100) > 50)
    {
        return 0;
    }
    make(file, victim);
    victim->run_away();
    return 1;
}
