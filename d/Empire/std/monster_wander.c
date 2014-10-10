#include "/d/Empire/empire.h"

inherit EMP_I_MONSTER_SCARY;

private string _goal_name;
private int    _goal_row;
private int    _goal_col;

static void
create() 
{
    ::create();
    _goal_name = 0;
    _goal_row  = 0;
    _goal_col  = 0;
}

public void
create_done()
{
    ::create_done();
    if (!stringp(query_short())) {
        return;
    }
    add_hook("__short", store_fp("append_goal"));
}

static nomask string
append_goal() 
{
    object ply;
    if (!objectp(ply = this_object()) || 
        !stringp(ply->query_short()) ||
        !stringp(_goal_name)) 
    {
	return 0;
    }
    return "on " + ply->query_possessive() + " way to the " + _goal_name;
}

public nomask int
set_goal(int row, int col) 
{
    string *arr;
    object env;
    if (!objectp(env = environment()) || 
        !arrayp(arr = env->find_route(row, col)) ||
        !sizeof(arr)) 
    {
	return 0;
    }
    _goal_name = env->query_island()->query_name_at(row, col);
    _goal_row  = row;
    _goal_col  = col;
    set_wandering_route(arr);
    set_wandering_hook(0);
    return 1;
}

public nomask void
clear_goal() 
{
    _goal_name = 0;
    _goal_row  = 0;
    _goal_col  = 0;
}

public nomask string
query_goal_name() 
{
    return _goal_name;
}

public nomask int
query_goal_row() 
{
    return _goal_row;
}

public nomask int
query_goal_col() 
{
    return _goal_col;
}
