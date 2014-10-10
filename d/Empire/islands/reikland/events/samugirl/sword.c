#include <mudlib.h>

inherit I_WEAPON;

static void create() {
    ::create();

    set_name("sword");
    set_short("shortsword");
    set_long("This is a well forged lightweigth shortsword.\n");
    set_class(10);
    set_weight(2);
    set_value(300);
    set_damage_type("slash");
    add_property("steel");
}

