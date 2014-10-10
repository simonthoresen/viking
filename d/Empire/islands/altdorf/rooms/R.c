#include "/d/Empire/islands/altdorf.h"
#include "/d/Empire/islands/dragon.h"

#define MAXPOTIONS 20

inherit EMP_I_SHOP;

private int _num_sold;

static void create() {
    ::create();
    _num_sold = 0;

    set_short("Krank's Potions and Remedies");
    set_long("You are in the Krank's Potions and Remedies apothecary. The " +
             "walls are lined with cabinets full of unlabeled bottles and " +
             "jars. There is a sign on the wall.");
    add_item(({ "sign" }),
             "While here you may:\n\n" +
             "  - %^BOLD%^list%^END%^, to list all items for sale\n" +
             "  - %^BOLD%^buy <item>%^END%^, to buy an item\n\n");
    add_property("indoors");
    add_for_sale(ALT_DIR_OBJ + "potion_blood");
    add_for_sale(ALT_DIR_OBJ + "potion_full");
    add_for_sale(ALT_DIR_OBJ + "potion_hp");
    add_for_sale(ALT_DIR_OBJ + "potion_sp");
}

public void reset(int flag) {
    ::reset(flag);
    if (flag) {
        tell_room(this_object(), "Krank mixes up a new batch of potions.\n");
    }
    _num_sold = 0;
}

public int do_buy(string arg) {
    if (_num_sold > MAXPOTIONS) { 
        if (sizeof(DON_D_DRAGON->query_dragons()) == 0) {
            return notify_fail("There are no more in stock.");
        }  
        tell_room(this_object(), "Since the dragon has returned, Krank " +
                  "mixes up extra potions from his reserve.\n");
    } 
    if (!::do_buy(arg)) {
        return 0;
    }
    ++_num_sold;
    return 1;
}
