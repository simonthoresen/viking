#include "/d/Artifact/artifact.h"

inherit base EMP_I_WEAPON;
inherit util ART_I_DAMAGE_BASE;

private object  _player;
private mapping _slots;

static void
create()
{
    base::create();
    util::create();
    _player = 0;
    _slots  = ([ "glyph" : 1, "shape" : 1, "spell" : 2 ]);

    add_hook("__destroy", store_fp("destroy_control"));
}

public nomask object
query_weapon()
{
    return this_object();
}

public nomask object
query_control()
{
    object env;
    if (!objectp(_player) ||
        !objectp(env = environment(_player)) ||
        !env<-ART_R_CONTROL)
    {
        return 0;
    }
    return env;
}

public nomask int
is_idle()
{
    return objectp(_player) && query_idle(_player) > MAX_COMBAT_IDLE;
}

public nomask int
is_suspended()
{
    return objectp(_player) && !objectp(query_control());
}

public nomask void
set_player(object val)
{
    if (origin() != ORIGIN_CALL_OTHER ||
        source_file_name(previous_object()) != ART_C_WEAPON)
    {
        error(sprintf("expected %O, got %O", ART_C_WEAPON, previous_object()));
    }
    _player = val;
    hook("__Artifact_player_set", ({ _player }));
}

public nomask object
query_player()
{
    return _player;
}

public nomask object
query_owner()
{
    object ply;
    if (!objectp(ply = environment()) || !living(ply)) {
        return 0;
    }
    return ply;
}

public nomask object
query_user()
{
    return query_wield();
}

public nomask varargs object
query_room(object env)
{
    if (!objectp(env)) {
        env = environment();
    }
    while (objectp(env) && !env->query_property("room")) {
        env = environment(env);
    }
    return env;
}

public nomask void
add_sliver(object obj)
{
    if (!objectp(obj) || !obj<-ART_I_SLIVER) {
        return;
    }
    if (environment(obj) == this_object()) {
        return; // already added
    }
    if (!clonep(obj)) {
        obj = clone_object(obj);
    }
    obj->move();
}

public nomask object
query_sliver(string name)
{
    object obj, *arr;
    int i, len;
    for (i = 0, len = sizeof(arr = all_inventory()); i < len; ++i) {
        obj = arr[i];
        if (objectp(obj) && obj<-ART_I_SLIVER && obj->id(name)) {
            return obj;
        }
    }
    return 0;
}

public nomask mapping
query_slots()
{
    return copy(_slots);
}

public nomask int
query_slot(string key)
{
    return _slots[key];
}

public int
can_add(object obj)
{
    mapping dat;
    string *arr;
    int i, len;
    if (!objectp(obj) || !obj<-ART_I_SLIVER) {
        return notify_fail("That is not a sliver.");
    }
    if (!obj->can_use(_player, this_object())) {
        return notify_fail(obj->query_failure_msg());
    }
    if (objectp(query_sliver(obj->query_real_name()))) {
        return notify_fail("Can not have multiple " + query_name() +
                           " slivers.");
    }
    dat = obj->query_slots();
    for (i = 0, len = sizeof(arr = keys(dat)); i < len; ++i) {
        int num;
        num = _slots[arr[i]] + dat[arr[i]];
        if (num >= 0) {
            continue;
        }
        return notify_fail("Insufficient " + arr[i] + " slots (" + (-num) +
                           " required).");
    }
    return 1;
}

static nomask void
destroy_control()
{
    object env;
    if (!objectp(env = query_control())) {
        return;
    }
    env->destroy_later();
}

public nomask void
retain_slots(mapping dat)
{
    int i, len;
    string *arr;
    for (i = 0, len = sizeof(arr = keys(dat));
         i < len; ++i)
    {
        _slots[arr[i]] = _slots[arr[i]] + dat[arr[i]];
    }
}

public nomask void
release_slots(mapping dat)
{
    int i, len;
    string *arr;
    for (i = 0, len = sizeof(arr = keys(dat));
         i < len; ++i)
    {
        _slots[arr[i]] = _slots[arr[i]] - dat[arr[i]];
    }
}
