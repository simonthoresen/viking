#include "/d/Empire/islands/blackrock.h"

inherit I_CONTAINER;

static void
create() 
{
    ::create();
    set_name("chest");
    set_short("a heavy black chest");
    set_long("This is the Blackrock chest that contains the treasure of the " +
	     "labyrinth.");
    add_id(({ "heavy chest", "blackrock chest" }));
    add_property(({ "artifact", "stone" }));
    set_get(0);
    set_weight(666);
    set_max_weight(666);
    set_value(666);
    set_can_open(1);
    add_hook("__open", store_fp("reward_open"));
}

static void
reward_open(int flag) 
{
    object ply, obj;
    if (!objectp(ply = this_player())) {
        return;
    }
    if (!BRD_ISLAND->try_recreate(300)) {
        write("To your great disappointment, you discover that the chest is " +
              "empty. Someone must have beat you to it.\n");
        return;
    }
    remove_hook("__open");
    ply->add_exp(25000);
    EMP_D_TREASURE->add_treasure(25000);
    EMP_D_ACHIEVEMENT->unlock(ply, "random_mouse");
    EMP_D_ACHIEVEMENT->add_unlock(ply, "tremaux", 1, 25);
    EMP_D_ACHIEVEMENT->add_unlock(ply, "theseus", 1, 100);
    if (interactive(ply) && !wizardp(ply)) {
	BRD_D_SCORE->add_solve_count(ply, 1);
	BRD_D_SCORE->set_last_solve(ply, time());
    }
    make(BRD_C_COIN)->add_amount(BRD_COIN_TREASURE - 1);
    EMP_LOG("blackrock", ply->query_real_name() + " found the treasure");
}
