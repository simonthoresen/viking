#include "/d/Empire/empire.h"

inherit EMP_I_ITEM;

private string _color;
private int    _amount;

static void
create()
{
    ::create();
    _color  = 0;
    _amount = 1;

    set_name("liquid");
    set_long("It is an unknown liquid.");
    add_id(source_file_name());
    set_heart_beat(1);
    set_get(NO_GET);
    set_drop(NO_DROP);
    add_hook("__move", store_fp("liquid_moved"));
    add_hook("__destroy", store_fp("liquid_destroyed"));
}

public int
equals(object obj)
{
    if (!objectp(obj) || !obj->is_liquid()) {
	return 0;
    }
    if ((string)obj->query_name() != query_name()) {
	return 0;
    }
    return 1;
}

public object
clone()
{
    object obj;
    obj = clone_object(this_object());
    obj->set_name(query_name());
    obj->set_long(query_long());
    obj->set_color(_color);
    return obj;
}

private object
find_liquid(object env)
{
    int i, len;
    object *arr;
    if (!objectp(env)) {
	return 0;
    }
    for (i = 0, len = sizeof(arr = all_inventory(env)); i < len; ++i) {
	object obj;
	if (equals(obj = arr[i]) && obj != this_object()) {
	    return obj;
	}
    }
    return 0;
}

public void
heart_beat()
{
    object ply, env, obj;
    catch(hook("__heart_beat"));
    if (!objectp(this_object())) {
        return; /* destroyed by hook */
    }
    if (!objectp(env = environment()) || _amount < 0) {
        destroy();
        return;
    }
    if (env->query_property("room")) {
	--_amount;
	return; /* live until dried up */
    }
    if (!living(ply = env)) {
	destroy();
	return; /* only splash creatures */
    }
    if (!objectp(env = environment(ply))) {
	return; /* yikes */
    }
    if (!objectp(obj = find_liquid(env))) {
	obj = clone();
        obj->move(env);
        if (!objectp(obj)) {
            return; /* dested by move */
        }
    }
    if (!random(10)) {
	tell_object(ply, capitalize(query_name()) + " drips from you.\n");
        tell_room(env, capitalize(query_name()) + " drips from " +
		  ply->query_name() +  ".\n", ({ ply }));
    }
    obj->add_amount(10);
    _amount -= 10;
}

public string
short()
{
    object env;
    string str;
    if (!objectp(env = environment()) ||
        !env->query_property("room"))
    {
        return 0;
    }
    if (stringp(_color)) {
	str = _color + query_name() + "%^END%^";
    } else {
	str = query_name();
    }
    if (_amount < 200) {
        return "a few drops of " + str;
    } else if (_amount < 400) {
        return "a very small puddle of " + str;
    } else if (_amount < 800) {
        return "a small puddle of " + str;
    } else if (_amount < 1600) {
        return "a puddle of " + str;
    } else if (_amount < 3200) {
        return "a large puddle of " + str;
    } else if (_amount < 6400) {
        return "a very large puddle of " + str;
    } else {
	str = "an ocean of " + query_name();
	if (stringp(_color)) {
	    str = _color + str + "%^END%^";
	}
	return str;
    }
}

public string
query_desc()
{
    if (_amount < 10) {
        return "freckled with " + query_name();
    } else if (_amount < 20) {
        return "speckled with " + query_name();
    } else if (_amount < 40) {
        return "stained with " + query_name();
    } else if (_amount < 80) {
        return "smeared with " + query_name();
    } else if (_amount < 160) {
        return "smudged with " + query_name();
    } else if (_amount < 320) {
        return "wet with " + query_name();
    } else if (_amount < 640) {
        return "dripping with " + query_name();
    } else if (_amount < 1280) {
        return "drenched in " + query_name();
    } else {
        return "soaked in " + query_name();
    }
}

public string
liquid_desc()
{
    object ply;
    if (!interactive(ply = previous_object()) && !stringp(ply->query_short())) {
	return 0;
    }
    return "(" + query_desc() + ")";
}

static nomask void
liquid_moved(object from, object to)
{
    if (objectp(from)) {
        from->remove_hook("__short");
    }
    if (objectp(to)) {
        object obj;
        if (living(to)) {
            to->add_hook("__short", store_fp("liquid_desc"));
        }
	if (objectp(obj = find_liquid(to))) {
            _amount += obj->query_amount();
	    obj->destroy();
	}
    }
}

static nomask void
liquid_destroyed()
{
    liquid_moved(environment(), 0);
}

public void
set_amount(int val)
{
    _amount = val;
}

public void
add_amount(int val)
{
    _amount += val;
}

public int
query_amount()
{
    return _amount;
}

public void
set_color(string val)
{
    _color = val;
}

public string
query_color()
{
    return _color;
}

public int
is_liquid()
{
    return 1;
}
