#include "/d/Empire/islands/dragon.h"

inherit DON_I_DRAGON_LIMB;

void create() {
    ::create();
    set_name("Onyxia's body");
    set_short("the ENORMOUS body of Onyxia");
    set_wc(50);
    add_id("body");
    add_hook("__damage_dealt", store_fp("crush_player"));
}

static void
crush_player(int dmg, string type, object foe, string loc) 
{
    object env;
    if (!objectp(foe) ||
        !objectp(env = environment(foe)) || 
        type != "blunt" || 
        dmg < 25) 
    {
        return;
    }
    tell_object(foe, "You are knocked to the ground by Onyxia's body.\n");
    tell_room(env, foe->query_name() + " is knocked to the ground by " +
              "Onyxia's body.\n", ({ foe }));
    foe->set_busy_next_round(foe->query_name() + " gets back on " +
                             foe->query_possessive() + " feet.\n");
}
