#include "/d/Artifact/artifact.h"

inherit ART_I_SLIVER;

private int _train_cost;

static void
create() 
{
    ::create();
    _train_cost = 0;
    set_type("skill");
}

public nomask void 
set_train_cost(int val) 
{
    _train_cost = val;
}

public nomask int 
query_train_cost() 
{
    return _train_cost;
}
