#include "/d/Empire/islands/reikland.h"

inherit EMP_I_ITEM;

static void
create() 
{
    ::create();
    set_name("curse");
    set_short(0);
    set_long("You have been cursed by Huldra.");
    add_hook("__move", store_fp("on_move"));
    add_hook("__destroy", store_fp("on_destroy"));
    destroy(180);
}

static void
on_move(object from, object to) 
{
    if (objectp(from) && living(from)) {
	tell_object(from, "You feel less clumsy.\n");
	from->remove_modifier("huldra:dex");
    }
    if (objectp(to) && living(to)) {
	tell_object(to, bold("You feel clumsy!\n"));
	to->set_modifier("huldra:dex", "dex", "special", -3);
    }
}

static void
on_destroy() 
{
    on_move(environment(), 0);
}
