#include "/d/Empire/islands/altdorf.h"

inherit I_SHOP;

void create() {
    ::create();
    set_short("Reik-Talabec Trading Company");
    set_long("You are in a shop of the Reik-Talabec Trading Company. You " +
             "can buy or sell things here. To the north is a counter. There " +
             "is a sign on the wall.");
    add_item("sign", "Something is written on it in huge white letters");
    add_item("letters", "Why not simply read the sign");
    add_item("counter", "Type 'list' to see what is on display");
    add_property("indoors");
    add_reset_object("trashcan","/obj/trashcan");
    add_reset_object("guard", ALT_C_SENTRY, 2);
}
