#include "/d/Empire/islands/matouci.h"

inherit MAT_DIR_EVENTS + "fenrir_wolf/claw";

static void
create() 
{
    ::create();
    set_name("Fenrir's right claw");
    set_short("the right claw of Fenrir");
    set_wield_modifier("str", 2, 11);
}
