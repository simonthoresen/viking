#include "/d/Empire/islands/altdorf.h"

inherit I_DAEMON;

private mapping _bounties;

static void create() {
    ::create();
    _bounties = ([ ]);
}

public mapping query_bounties() {
    return _bounties;
}

public int query_bounty(object ply) {
    string str;
    if (!objectp(ply) || !interactive(ply) || 
        !stringp(str = ply->query_real_name()))
    {
        return 0;
    }
    return _bounties[str];
}

public void set_bounty(object ply, int val) {
    string str;
    if (!objectp(ply) || !interactive(ply) || 
        !stringp(str = ply->query_real_name()))
    {
        return;
    }
    _bounties[str] = val;
}

public void add_bounty(object ply, int val) {
    set_bounty(ply, query_bounty(ply) + val);
}
