#include "/d/Empire/empire.h"

static void
create()
{
    // empty
}

static int
call_out_unique(string fnc, mixed delay, mixed args...)
{
    while (remove_call_out(fnc) >= 0) {
        // empty
    }
    call_out(fnc, delay, args...);
}
