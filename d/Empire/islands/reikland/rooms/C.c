#include "/d/Empire/islands/reikland.h"
#define ENT_EVENT (RED_DIR_EVENTS + "ent/event")

inherit EMP_DIR_STD + "map_f";

static void create() {
    ::create();
    set_short("A large clearing in the forest");
    set_long("You have arrived at a clearing surrounded by moisty trees. " +
             "Everything is organized in piles, and no garbage is to be seen " +
             "anywhere. It is awfully quiet here though. No birds, no insects, " +
             "no nothing. ");
    add_item(({ "forest", "moist forest", "dark forest", "trees", "grey trees",
                "barren trees", "barren grey trees", "slim grey trees",
                "slim trees" }),
             "Those slim grey trees are all around you, making it hard to see " +
             "very far. Perhaps you could chop some of them down?");
    add_item(({ "big tree", "huge tree", "tree", "slim tree", "grey tree",
                "slim grey tree" }),
             "There isn't any in particular that catches your interest. You " +
             "could just chop one of them down.");
    add_item(({ "branch", "branches", "grey branch", "grey branches",
                "grey branches with no leaves on" }),
             "As there are no really big trees around here, all you can see is " +
             "grey branches with no leaves on.");
    add_item(({ "treetops", "treetop" }), "You can't find any special one.");
    add_item(({ "funny noises", "noises", "noise" }), "Nah, it's in fact pretty " +
             "quiet here.");
    add_item(({ "grass", "ground", "wet ground", "moisty ground",
                "wet and moisty ground" }),
             "The grass makes funny noises as you walk on it: SWOSJ, SWOSJ, " +
             "SWOSJ.");
    add_item(({ "large clearing", "clearing" }),
             "The ground is soaking wet here, but otherwise this is a pretty " +
             "normal forest. You are now standing in the middle of a clearing " +
             "in it. This place looks inhabited.");
    add_item(({ "piles", "piles of lumber", "lumber" }),
             "Piles of lumber to be used to make heat.");
    add_item(({ "garbage" }),
             "Most humans dislike having garbage floating around.");

    add_trigger("chop", store_fp("do_chop"));
}

static int do_chop(string arg) {
    object ply, obj;
    if (!stringp(arg) || arg != "tree") {
        return notify_fail("Chop tree perhaps?");
    }
    ply = this_player();
    if (!(objectp(obj = ply->query_weapon(0)) && obj->id("axe")) &&
        !(objectp(obj = ply->query_weapon(1)) && obj->id("axe")))
    {
        return notify_fail("You need to wield an axe to do that.");
    }
    ply->set_busy_next_round();
    write("You start chopping away at one of the trees.\n");
    say(ply->query_name() + " chops away at one of the trees.\n");    
    if (!ENT_EVENT->run(ply, this_object()) ||
        !objectp(obj = present("ent"))) 
    {
        write("Nothing happens.");
        return 1;
    }
    obj->command("say HOW DARE YOU CHOP DOWN MY FAMILY??");
    EMP_D_COMBAT->hit_player(obj, ply, 69, "Impact", 0, "BRANCHES");
    return 1;
}
