#include "/d/Empire/islands/fort.h"

inherit FOR_I_WING;

private object _boss;

static void
create()
{
    ::create();
    _boss = 0;

    add_item(({ "brazier" }),
             "It is a metal receptacle holding a burning fire that heats " +
             "the room and provides lighting.");
    add_item(({ "open window", "window" }),
             "It looks out on the forest outside the fort.");
    add_item(({ "fire" }),
             "It burns in the brazier, providing heat and light.");
    add_hook("__reset", store_fp("on_reset"));
    add_property("indoors");
}

private void
clone_boss()
{
    _boss = FOR_D_BOSS->new_instance(query_wing());
    _boss->add_hook("__die", store_fp("clone_key"));
    _boss->move_player("", this_object());
}

static nomask void
clone_key(object corpse, object killer)
{
    make(FOR_C_KEY, corpse)->set_wing(query_wing());
}

static nomask void
on_reset(int not_first)
{
    if (!objectp(_boss)) {
        clone_boss();
    }
}

public void
set_wing(string val)
{
    ::set_wing(val);
    set_short("At the " + val + " throne room");
    set_long("You have arrived at the " + val + " throne room at the end of " +
             "the " + val + " gauntlet. There is a large stone dias at the " +
             "far end of the room, on which sits a dark oaken throne. There " +
             "is an open window looking out at the forest surrounding the " +
             "fort. A fire burns in a black metal brazier");
}
