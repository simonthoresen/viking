#include "/d/Empire/empire.h"

private string _failure_msg;

static void
create()
{
    _failure_msg = 0;
}

static nomask int
notify_fail(string arg)
{
    _failure_msg = arg;
    return ::notify_fail(arg);
}

public nomask string
query_failure_msg(string arg)
{
    return _failure_msg;
}
