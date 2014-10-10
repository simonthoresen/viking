#include "/d/Empire/empire.h"

inherit EMP_I_MONSTER_MESSAGE;

private mapping _responses;
private string  _res_msg;
private object  _res_actor;
private string  _res_trigger;

static void
create()
{
    ::create();
    _responses   = ([ ]);
    _res_msg     = 0;
    _res_actor   = 0;
    _res_trigger = 0;
}

public void
create_done()
{
    ::create_done();
    if (map_sizeof(_responses) == 0) {
        return;
    }
    add_hook("__catch_tell", store_fp("check_responses"));
    add_hook("__peace_beat", store_fp("maybe_respond"));
}

static nomask void
check_responses(string msg)
{
    string who, *arr;
    int i, len;
    if (objectp(_res_actor) && stringp(_res_trigger)) {
	return; /* busy */
    }
    if (!stringp(msg) || sscanf(msg, "%s says: %s?", who, _res_msg) != 2) {
	return; /* not a trigger */
    }
    if (!objectp(_res_actor = present(lower_case(who), environment()))) {
        return; /* no actor */
    }
    for (i = 0, len = sizeof(arr = explode(_res_msg, " ")); i < len; ++i) {
        _res_trigger = lower_case(arr[i]);
	if (_responses[_res_trigger]) {
	    return;
	}
    }
}

static nomask void
maybe_respond()
{
    object env;
    mixed val;
    if (!stringp(_res_msg) ||
	!objectp(_res_actor) ||
        !stringp(_res_trigger) ||
        !objectp(env = environment()) ||
        !objectp(_res_actor = present(_res_actor, env)))
    {
        return;
    }
    val = _responses[_res_trigger];
    if (functionp(val)) {
	catch(val = call_fp(val, this_object(), _res_msg,
			    _res_actor, _res_trigger));
    }
    if (stringp(val) && strlen(val) > 0) {
        int len;
	if (val[0] != '*') {
	    val = "*say " + val;
        }
        val = format_message(val, this_object(), _res_actor);
        if ((len = strlen(val)) > 1) {
            catch(command(val[1..len - 1]));
        }
    }
    _res_actor = 0;
}

public nomask void
set_responses(mapping val)
{
    if (is_create_done()) {
        error("set_responses() must be called in create()");
    }
    _responses = val;
}

public nomask mapping
query_responses()
{
    return _responses;
}

public nomask mixed
query_response(string val)
{
    return _responses[val];
}

public nomask void
add_response(mixed trigger, mixed response)
{
    int i, len;
    if (is_create_done()) {
        error("add_response() must be called in create()");
    }
    if (!arrayp(trigger)) {
        trigger = ({ trigger });
    }
    for (i = 0, len = sizeof(trigger); i < len; ++i) {
        _responses[trigger[i]] = response;
    }
}
