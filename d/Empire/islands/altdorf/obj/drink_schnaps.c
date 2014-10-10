#include "/d/Empire/islands/altdorf.h"

inherit I_DRINK;

static void
create() 
{
    ::create();
    set_name("schnaps");
    set_short("a small cup of schnaps");
    set_drinking_mess(" puts a cup to his mouth, then pours it down in one " +
                      "split-second.\n");
    set_drinker_mess("You put the cup to your mouth, then rapidly pour it " +
                     "down. Ahhh.\n");
    set_strength(20);
    set_heal(30);
    set_value(110);
    set_weight(1);
    set_full(1);
    set_empty_container("cup");
    set_soft_strength(0);
    add_id(({ "schnaps", "cup" }));
    add_property("hidden");
}
