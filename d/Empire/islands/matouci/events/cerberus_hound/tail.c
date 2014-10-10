#include "/d/Empire/islands/matouci.h"

inherit MAT_DIR_EVENTS + "cerberus_hound/limb";

static void 
create() 
{
    ::create();
    set_name("Cerberus' tail");
    set_limb("tail");
    set_short(0);
    set_long("It is as large as the trunk of a tree, and it is " +
             "flailing around dangerously.");
    add_id(({ "tail" }));
    set_level(29);
    set_wc(45);
    set_ac(0);
    set_hp(500);
    set_aggressive(1);
    load_a_chat(10, ({ store_fp("throw_player") }));
}

static void
throw_player(object ply, object foe) 
{
    object env;
    if (!objectp(env = environment(ply))) {
        return;
    }
    tell_room(env, "%^BOLD%^Cerberus swings its tail around.%^END%^\n");
    tell_object(foe, "\n\nS M A C K !\n\n\n");
    tell_room(env, foe->query_name() + " is hit by Cerberus' tail.\n", 
              ({ foe }));
    if (!EMP_D_COMBAT->throw_player(foe, 1)) {
        EMP_D_COMBAT->hit_player(ply, foe, 25 + random(25), "blunt");
    }
}
