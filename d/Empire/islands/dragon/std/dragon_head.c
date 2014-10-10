#include "/d/Empire/islands/dragon.h"

inherit DON_I_DRAGON_MAIN;

private object _body;
private object _tail;
private string _last_dir;

static void
create() 
{
    ::create();
    _body     = 0;
    _tail     = 0;
    _last_dir = 0;

    set_name("Onyxia's head");
    set_short("the FRIGHTENING head of Onyxia");
    add_id("head");
    add_property("unarmed_damage_type", ({ "bite", "claw" }));
    add_hook("__long", store_fp("show_last_dir"));
    add_hook("__destroy", store_fp("destroy_body"));
    add_hook("__move", store_fp("pull_body"));
    add_hook("__move_player", store_fp("turn_head"));
    add_hook("__die", store_fp("release_body"));
    if (clonep(this_object())) {
        _body = new(DON_C_DRAGON_BODY);
        _body->set_head(this_object());
        _tail = new(DON_C_DRAGON_TAIL);
        _tail->set_head(this_object());
    }
}

static string
show_last_dir(string arg) 
{
    if (stringp(arg) || !stringp(_last_dir)) {
        return 0;
    }
    return "She is facing " + _last_dir + ".";
}

static void
turn_head(string dir, object from, object to) 
{
    _last_dir = dir;
}

static void
release_body() 
{
    if (objectp(_body) && objectp(environment(_body))) {
        _body = 0;
    }
    if (objectp(_tail) && objectp(environment(_tail))) {
        _tail = 0;
    }
}

static void
destroy_body() 
{
    if (objectp(_body)) {
        _body->destroy();
    }
    if (objectp(_tail)) {
        _tail->destroy();
    }
}

static void
pull_body(object from, object to) 
{
    if (!objectp(from)) {
        from = to;
    }
    if (objectp(_body)) {
        from = _body->move_to(from);
    }
    if (objectp(_tail)) {
        from = _tail->move_to(from);
    }
}

public void
set_last_dir(string val) 
{
    _last_dir = val;
}

public string
query_last_dir() 
{
    return _last_dir;
}

