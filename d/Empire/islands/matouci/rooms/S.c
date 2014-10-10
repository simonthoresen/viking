#include "/d/Empire/islands/matouci.h"
#define JORMUNGAND_EVENT (MAT_DIR_EVENTS + "jormungand_serpent/event")

inherit EMP_DIR_STD + "map_f";

void create() {
    ::create();
    set_long("You have arrived at an abrupt clearing in the forest. " +
             "The trees lie broken and torn around a dark and intimidating " +
             "bottomless pit. The ground is beat and trampled, and there " +
             "are obvious signs of struggle and death here.");
    add_item(({ "clearing" }), "The trees around the pit have been uprooted " +
             "and broken, as if the pit was dug from underneath.");
    add_item(({ "tree", "trees" }), "They lie torn and broken around the pit.");
    add_item(({ "broken tree" }), "It is as if some incredible force had " +
             "snapped them like toothpicks.");
    add_item(({ "uprooted tree" }), 
             "Its roots have been torn from the ground.");
    add_item(({ "sign", "death", "struggle" }),
             "There is blood and human remains scattered about.");
    add_item(({ "blood" }), "It seems human.");
    add_item(({ "human", "remains", "human remains" }),
             "There is not much left. They must not have stood a chance.");
    add_item(({ "pit", "bottomless pit", "hole" }), store_fp("exa_pit"));
    add_exit(R_VOID, "pit", store_fp("prevent_enter"));
    add_hook("__enter_inv", store_fp("check_blood"));
    set_heart_beat(1);
}

private int can_trigger() {
    return JORMUNGAND_EVENT->query_next_time() < time();
}

private int is_lamb(object ply) {
    return 
        objectp(ply) &&
        objectp(present(ply)) &&
        interactive(ply) &&
        ply->query_alignment() >= ALIGN_SAINTLY && 
        ply->query_gender() == 2 &&                
        !stringp(ply->query_spouse()) &&
        ply->query_level() >= ETERNAL_LAST;        
}

private string query_random_noise() {
    switch (random(8)) {
    case 0:  return "The ground trembles beneath your feet.\n";
    case 1:  return "Smoke rises from the bottomless pit.\n";
    case 2:  return "There is a sinister growl from the pit.\n";
    case 3:  return "You feel a chill run down your spine.\n";
    case 4:  return "What?\n";
    case 5:  return "What was that?\n";
    case 6:  return "There it was again!\n";
    default: return "You are afraid!\n";
    }
}

public void heart_beat() {
    if (random(100) > 1 || !can_trigger()) {
        return;
    }
    tell_room(this_object(), query_random_noise());
}

public string exa_pit() {
    if (can_trigger()) {
        return "You think you see some movement down there..";
    }
    return "It is pitch black and bottomless.";
}

public void check_blood(object obj, object from) {
    object ply; 
    if (!objectp(obj) || !obj<-EMP_C_BLOOD ||
        !objectp(ply = obj->query_victim()))
    {
        return;
    }
    if (!can_trigger() || !is_lamb(ply)) {
        return;
    }
    call_out("notify_trigger", 1, ply);
}

public void notify_trigger(object ply) {
    if (!can_trigger() || !is_lamb(ply)) {
        return;
    }
    tell_room(this_object(), bold("There is a sudden movement in the pit!\n"));
    call_out("consume_victim", 2, ply);
}

public void consume_victim(object ply) {
    object obj;
    if (!can_trigger() || !is_lamb(ply) || 
        !JORMUNGAND_EVENT->run(ply, this_object()) ||
        !objectp(obj = present("jormungand"))) 
    {
        return;
    }
    EMP_D_COMBAT->hit_player(obj, ply, 6666, "Bite", "head", "TEETH");
}

public int prevent_enter() {
    write("NO WAY!\n");
    return 1;
}
