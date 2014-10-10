#include "/d/Empire/islands/matouci.h"

inherit MAT_DIR_EVENTS + "fenrir_wolf/claw";

static void
create() 
{
    ::create();
    set_name("Fenrir's left claw");
    set_short("the left claw of Fenrir");
    set_wield_modifier("dex", 2, 11);
}
