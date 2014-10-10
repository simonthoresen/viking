#include "/d/Empire/islands/fort.h"

#define TIME_OPEN       (30)
#define TIME_NOTIFY     (3)
#define TIME_COOLDOWN   (300)

inherit I_DAEMON;

private int *_call_guard;
private int  _close_at;

static void
create()
{
    ::create();
    _call_guard = ({ });
    _close_at   = 0;
}

public int
is_open()
{
    return _close_at > time();
}

public int
can_open()
{
    return _close_at + TIME_COOLDOWN < time();
}

public int
open_gauntlet()
{
    if (is_open() || !can_open()) {
        return 0;
    }
    FOR_ISLAND->tell_island(bold("\nTHE GAUNTLET OF FORT DUMBARTON " +
                                 "IS NOW OPEN!\n\n"));
    _close_at = time() + TIME_OPEN;
    call_out("check_time", TIME_NOTIFY, _call_guard);
    return 1;
}

public void
close_gauntlet()
{
    FOR_ISLAND->tell_island(bold("\nTHE GAUNTLET OF FORT DUMBARTON " +
                                 "IS NOW CLOSED!\n\n"));
    _close_at = time();
    remove_call_out("check_time");
}

public void
check_time(int *call_guard)
{
    int val;
    if (call_guard != _call_guard) {
        error("Illegal call to check_time().");
    }
    if ((val = _close_at - time()) <= 0) {
        close_gauntlet();
        return;
    }
    FOR_ISLAND->tell_island("The gauntlet closes in " +
                            format_time(val) + "..\n");
    if (val > TIME_NOTIFY) {
        val = TIME_NOTIFY;
    }
    call_out("check_time", val, _call_guard);
}
