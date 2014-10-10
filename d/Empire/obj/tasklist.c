#include "/d/Empire/empire.h"
#define LINE              ("-------------------------" + \
                           "-------------------------\n")
#define STATE_CREATED     (0)
#define STATE_SUBMITTED   (1)
#define STATE_EXECUTING   (2)
#define STATE_COMPLETED   (3)
#define STATE_ABORTED     (4)

inherit EMP_I_ITEM;

private int       _state;
private string    _error;
private int       _task_idx;
private function *_task_arr;
private int      *_tick_arr;

static void
create()
{
    ::create();
    _state    = STATE_CREATED;
    _error    = 0;
    _task_idx = 0;
    _task_arr = ({ });
    _tick_arr = ({ });

    set_name(base_file_name());
    set_short(store_fp("my_short"));
    set_long(store_fp("my_long"));
    add_id(({ "tasklist", "task", "list" }));
    set_drop(NO_DROP);
    add_trigger("execute", store_fp("do_execute"));
    add_trigger("abort", store_fp("do_abort"));
}

static string
my_short()
{
    string str;
    int len;
    str = add_article(query_name()) + " list [";
    if (_state == STATE_COMPLETED) {
        str += "%^B_GREEN%^";
    } else if (_state == STATE_ABORTED) {
        str += "%^B_RED%^";
    } else if (_state != STATE_CREATED) {
        str += "%^B_YELLOW%^";
    }
    str += _task_idx + "/" + sizeof(_task_arr);
    str += "%^END%^]";
    return str;
}

public int
query_ticks()
{
    int i, len, ret;
    ret = 0;
    for (i = 0, len = sizeof(_tick_arr); i < len; ++i) {
	ret += _tick_arr[i];
    }
    return ret;
}

private string
desc_state()
{
    switch (_state) {
    case STATE_CREATED:   return "CREATED";
    case STATE_SUBMITTED: return "SUBMITTED";
    case STATE_EXECUTING: return "EXECUTING";
    case STATE_COMPLETED: return "COMPLETED";
    case STATE_ABORTED:   return "ABORTED";
    }
}

private string
desc_index(int val)
{
    if (val > _task_idx || _state == STATE_CREATED) {
	return sprintf("[ %4d ]", val + 1);
    }
    if (val < _task_idx) {
	return "[ %^L_GREEN%^DONE%^END%^ ]";
    }
    if (_state != STATE_ABORTED) {
	return "[ %^L_YELLOW%^NEXT%^END%^ ]";
    }
    return "[ %^RED%^FAIL%^END%^ ]";
}

private string
desc_task(int val)
{
    return replace_string(retrieve_fp(_task_arr[val])[1], "_", " ");
}

private string
desc_info()
{
    string ret;
    if (!stringp(ret = query_info())) {
        return "";
    }
    return ret;
}

static void
my_long()
{
    int i, len;
    printf(LINE + "Name   : %-21s State  : %10s\n" +
	   "Info   : %-21s Ticks  : %10d\n" + LINE,
	   query_name(), desc_state(), desc_info(), query_ticks());
    for (i = 0, len = sizeof(_task_arr); i < len; ++i) {
	printf("%s %-30s %10d\n", desc_index(i), desc_task(i), _tick_arr[i]);
    }
    write(LINE);
    if (stringp(_error)) {
        write("ERROR: " + _error + "\n" + LINE);
    }
}

static void
do_notify(string str)
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    message("", "[Task]: " + str + "\n", env);
}

public nomask void
notify(mixed args...)
{
    string str;
    if (sizeof(args) > 1) {
        str = sprintf(args...);
    } else if (!stringp(args[0])) {
        str = sprintf("%O", args[0]);
    } else {
        str = args[0];
    }
    do_notify(str);
}

public nomask int
run()
{
    int val, cpu;
    if (_state >= STATE_COMPLETED) {
	return 1;
    }
    _state = STATE_EXECUTING;
    if (_task_idx >= sizeof(_task_arr)) {
	_state = STATE_COMPLETED;
	notify("Ignored.");
	return 1;
    }
    notify(capitalize(desc_task(_task_idx)) + ".");
    cpu = status()[ST_TICKS];
    _error = catch(val = call_fp(_task_arr[_task_idx]));
    cpu -= status()[ST_TICKS];
    _tick_arr[_task_idx] += cpu;
    if (stringp(_error)) {
	_state = STATE_ABORTED;
	notify("Aborted.");
	return 1;
    }
    if (val != 0 && ++_task_idx >= sizeof(_task_arr)) {
	_state = STATE_COMPLETED;
	notify("Done.");
	return 1;
    }
    call_out("run", 2);
    return 0;
}

public int
execute()
{
    if (_state > STATE_CREATED) {
	return 0;
    }
    _state = STATE_SUBMITTED;
    call_out("run", 0);
    return 1;
}

public int
do_execute(string arg)
{
    if (!stringp(arg) || !id(arg)) {
        return notify_fail("Execute what?");
    }
    if (!execute()) {
        return notify_fail("Task was not accepted.");
    }
    write("Ok.\n");
    return 1;
}

public void
abort(string err)
{
    _error = stringp(err) ? err : "Error.";
    _state = STATE_ABORTED;
    notify(_error);
}

public int
do_abort(string arg)
{
    if (!stringp(arg) || !id(arg)) {
        return notify_fail("Abort what?");
    }
    abort("Aborted by user.");
    write("Ok.\n");
    return 1;
}

public void
insert_before(int idx, function fnc)
{
    _task_arr = _task_arr[0..idx - 1] + ({ fnc }) + _task_arr[idx..];
    _tick_arr = _tick_arr[0..idx - 1] + ({   0 }) + _tick_arr[idx..];
}

public void
insert_after(int idx, function fnc)
{
    _task_arr = _task_arr[0..idx] + ({ fnc }) + _task_arr[idx + 1..];
    _tick_arr = _tick_arr[0..idx] + ({   0 }) + _tick_arr[idx + 1..];
}

public void
push_front(function fnc)
{
    _task_arr = ({ fnc }) + _task_arr;
    _tick_arr = ({   0 }) + _tick_arr;
}

public void
push_back(function fnc)
{
    _task_arr = _task_arr + ({ fnc });
    _tick_arr = _tick_arr + ({   0 });
}

public int
is_submitted()
{
    return _state >= STATE_SUBMITTED;
}

public int
is_completed()
{
    return _state == STATE_COMPLETED;
}

public int
is_aborted()
{
    return _state == STATE_ABORTED;
}

public string
query_error()
{
    return _error;
}
