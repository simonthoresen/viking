#include "/d/Empire/islands/altdorf.h"

#define HEAL_COST     4000
#define HEAL_AMOUNT   400
#define HEAL_WAIT     (10 + 5 * random(10))
#define P_TIME        ("emp_nurse_heal")

inherit EMP_I_ROOM;

void create() {
    ::create();
    set_short("Hospice Priory of Shallya");
    set_long("You are in the Hospice Priory of Shallya. This is a place of " +
             "hospitality for the sick, wounded and dying. There are beds " +
             "here where you can spend your final days. There is a sign on " +
             "the wall.");
    add_item(({ "sign" }),
             "While here you may:\n\n" +
             "  - %^BOLD%^heal%^END%^, to heal your wonds (" + HEAL_COST + 
             " coins)\n\n");
    add_property("indoors");
    add_reset_object("nurse", ALT_DIR_OBJ + "nurse");
    add_trigger("heal", store_fp("do_heal"));
}

int do_heal(string arg) {
    object ply;
    if (!objectp(ply = this_player())) {
	return 0;
    }
    if (!objectp(present("nurse"))) {
	return notify_fail("There is noone here to help you.");
    }
    if (ply->query_money() < HEAL_COST) {
	return notify_fail("You can not afford that.");
    }
    if (ply->query_tmp_prop(P_TIME) > time()) {
	return notify_fail("Your body has not recovered from last time.");
    }
    write("The nurse heals your wounds.\n");
    say(ply->query_name() + " pays the nurse some money to heal " +
        ply->query_possessive() + " wounds.\n");
    
    ply->add_money(-HEAL_COST);
    ply->heal_self(HEAL_AMOUNT);
    ply->set_tmp_prop(P_TIME, time() + HEAL_WAIT);
    return 1;
}
