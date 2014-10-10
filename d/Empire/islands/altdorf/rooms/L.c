#include "/d/Empire/islands/altdorf.h"

inherit EMP_I_SHOP;

static int _prev;

void create() {
    ::create();
    _prev = EMP_D_TIME->query_hour_of_day();

    set_short("Hart's Lodge");
    set_long("You have entered Hart's Lodge. This inn seems as a " +
             "good place to stay the night for those who do not seek out " +
             "the adventures of the wilderness at night. In here, you can " +
             "be sure no monsters will come, and there is always room for " +
             "more people here. " +
             "There is an old clock on the wall.");
    add_property("indoors");
    add_item(({ "clock", "old clock" }), store_fp("exa_clock"));
    add_for_sale(ALT_DIR_OBJ + "drink_acider");
    add_for_sale(ALT_DIR_OBJ + "drink_ale");
    add_for_sale(ALT_DIR_OBJ + "drink_clausthaler");
    add_for_sale(ALT_DIR_OBJ + "drink_firebreather");
    add_for_sale(ALT_DIR_OBJ + "drink_heineken");
    add_for_sale(ALT_DIR_OBJ + "drink_juice");
    add_for_sale(ALT_DIR_OBJ + "drink_nutradrink");
    add_for_sale(ALT_DIR_OBJ + "drink_schnaps");
    add_for_sale(ALT_DIR_OBJ + "drink_wine");
    add_for_sale(ALT_DIR_OBJ + "food_cake");
    add_for_sale(ALT_DIR_OBJ + "food_donut");
    add_for_sale(ALT_DIR_OBJ + "food_loaf");
    add_for_sale(ALT_DIR_OBJ + "food_pizza");
    add_for_sale(ALT_DIR_OBJ + "bag");
    add_for_sale("/obj/torch");
    add_hook("__heart_beat", store_fp("on_heart_beat"));
    add_reset_object("egil", ALT_DIR_OBJ + "egil", 1);
}

string exa_clock() {
    return "This old clock was bought by Hart to help adventurers know " +
        "what time it is.\nIt shows " + EMP_D_TIME->query_stime() + ".";
}

void on_heart_beat() {
    int next;
    if ((next = EMP_D_TIME->query_hour_of_day()) == _prev) {
        return;
    }
    _prev = next;
    next = next % 12;
    if (next == 0) {
        next = 12;
    }
    tell_room(this_object(), "The clock strikes " + convert_number(next) + 
              ".\nDING DONG, DING DONG.\n");
}
    
