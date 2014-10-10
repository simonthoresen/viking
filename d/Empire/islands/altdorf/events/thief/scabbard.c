#include "/d/Empire/islands/altdorf.h"

inherit EMP_I_ARMOUR;

private int _value;
private int _auto_load;

private int can_save(object obj) {
    if (sscanf(source_file_name(obj), "%*sstd%*s")) {
        return 0;
    }
    if(!obj->id("blade") && !obj->id("sword") &&
       !obj->id("knife") && !obj->id("dagger"))
    {
        return 0;
    }
    if (obj->query_property("treasure_daemon") ||
        obj->query_property("unique") ||
        obj->query_property("magic") ||
        obj->query_property("artifact"))
    {
        return 0;
    }
    return 1;
}

static void
create()
{
    ::create();
    _value     = 0;
    _auto_load = 0;

    set_name("scabbard");
    set_short("a leather scabbard");
    set_long("A leather scabbard in which you may put your weapon for " +
             "safe-keeping.");
    add_id("leather scabbard");
    set_type("waist");
    set_info("This scabbard will store your blade for the next time you "+
	     "logon. It will however cost the value of the blade, not "+
	     "exceeding 1000 coins each time you logon so you better "+
	     "have the dough! Unique weapons cannot be contained.\n"+
	     "P.S: Remember to wear the scabbard!!\n");
    set_weight(1);
    set_value(0);
    set_drop(NO_DROP);

    add_trigger("sheath", store_fp("do_sheath"));
    add_trigger("draw", store_fp("do_draw"));
    add_property(({ "tagged", "leather", "protected" }));

    add_hook("__long", store_fp("on_long"));
    add_hook("__move", store_fp("on_move"));
    add_hook("__enter_inv", store_fp("on_enter_inv"));
    add_hook("__leave_inv", store_fp("on_leave_inv"));
}

static void
on_enter_inv(object obj, object from)
{
    _value = obj->query_value();
    obj->set_value(0);
}

static void
on_leave_inv(object obj, object to)
{
    obj->set_value(_value);
    _value = 0;
}

static int
do_draw(string arg)
{
    object ply, obj;
    int val;
    if(!stringp(arg)) {
	return notify_fail("Draw what?");
    }
    if (!objectp(obj = present(arg))) {
        return notify_fail("There is no " + arg + " in the scabbard.");
    }
    if ((val = _value) > 1000) {
	val = 1000;
    }
    ply = this_player();
    if (val > ply->query_money()) {
	return notify_fail("You need " + val + " coins to draw it.");
    }
    EMP_D_LOG->log("scabbard", ply->query_real_name() +
		   " got " + source_file_name(obj));
    write("You draw your " + obj->query_name() + " (" + val +
	  " coins paid).\n");
    say(ply->query_name() + " draws " + ply->query_possessive() + " " +
        obj->query_name() + ".\n");
    ply->add_money(-val);
    obj->move(ply);
    ply->command("wield " + arg);
    return 1;
}

static int
do_sheath(string arg)
{
    object ply, obj;
    if (!stringp(arg)) {
        return notify_fail("Sheath what?");
    }
    if (!objectp(ply = this_player()) || !objectp(obj = present(arg, ply)))  {
        return notify_fail("You have no " + arg + ".");
    }
    if (sizeof(all_inventory()) > 0) {
        return notify_fail("There is no room in the scabbard.");
    }
    if (!can_save(obj)) {
        return notify_fail("That does not fit in the scabbard.");
    }
    if (obj->query_wield() && !obj->unwield()) {
        return 0; /* failure notified by unwield() */
    }
    write("You sheath your " + obj->query_name() + ".\n");
    say(ply->query_name() + " sheathes " + ply->query_possessive() + " " +
        obj->query_name() + ".\n");
    obj->move(this_object());
    return 1;
}

static void
on_move(object from, object to)
{
    if (_auto_load) {
	_auto_load = 0;
	wear(1);
    }
}

static string
on_long()
{
    object *inv;
    if (sizeof(inv = all_inventory()) == 0) {
        return "\nUsage: sheath <weapon>\n";
    }
    return "It contains " + maybe_add_article(inv[0]->short()) + ".\n" +
           "Usage: draw <weapon>\n";
}

public string
query_auto_load()
{
    string arg;
    object *inv;
    arg = ":";
    if (sizeof(inv = all_inventory()) > 0) {
        arg += source_file_name(inv[0]);
    }
    return source_file_name() + arg;
}

public void
init_arg(string arg)
{
    object obj;
    _auto_load = 1;
    if (!stringp(arg) || strlen(arg) == 0 || catch(obj = make(arg))) {
        return; /* nothing created */
    }
    if (!stringp(obj->query_short())) {
        obj->destroy(); /* should never have been stored */
        return;
    }
    /* there you go */
}
