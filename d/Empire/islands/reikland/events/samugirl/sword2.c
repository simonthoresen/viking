#include <mudlib.h>

inherit I_WEAPON;

static void create() {
    ::create();

    set_name("sword");
    set_short("katana");
    add_id("sword");
    set_long("This is a well forged twohanded katana.\n");
    set_class(20);
    set_weight(7);
    set_type("twohanded");
    set_value(600);
    set_damage_type("slash");
    add_property("steel");
}

