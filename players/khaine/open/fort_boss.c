#include "/d/Empire/islands/fort.h"

inherit FOR_I_MONSTER;

static void
create()
{
    ::create();
    set_race("orc");
    EMP_D_NAME->set_name(this_object()); // gets a race-appropriate name
    set_short(query_name() + " the orc chieftain");
}

static void
init_dangerlevel(int old_val, int new_val)
{
    object env;
    // this method gets called multiple times for the boss, first it gets
    // called before the boss is moved to the throne room. then it is called
    // whenever another boss is spawned or dies
    if (objectp(env = environment())) {
        if (new_val > old_val) {
            tell_room(env, query_name() + " grows stronger.\n");
        }
        if (new_val < old_val) {
            tell_room(env, query_name() + " becomes weaker.\n");
        }
    }

    // danger level scales from 0 - 100 depending on how many bosses are alive.
    // if this is the only boss, danger level will be 100, but if all bosses
    // are alive, then danger level will be 25. this does not mean that bosses
    // should be pansies at level 25, it is just a relative number that you
    // should use to scale the boss to hit harder / enrage when there are fewer
    // bosses alive. this mechanic will encourage players to engage all bosses
    // at the same time, and to make sure they die just about the same time

    // change some spell chances or stats around here. beware not to set new
    // hp, as that might cause your boss to get fully healed or something
    // similar. it is better that you set some variable that other hooks can
    // use to decide on damage or spell chances
}
