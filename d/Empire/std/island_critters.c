#include "/d/Empire/empire.h"

inherit EMP_I_ISLAND_WANDER;

private int    *_entries;
private string *_critters;
private int     _num_critters;

static void 
create() 
{
    ::create();
    _entries      = 0;
    _critters     = 0;
    _num_critters = 0;
    add_hook("__heart_beat", store_fp("check_critters"));
}

public object *
find_critters() 
{
    return filter_array(query_livings(), "call_other_true",
			FILTER_OB, ({ "query_property", EMP_P_CRITTER }));
}

public string 
query_random_entry() 
{
    int len, pos;
    if (!arrayp(_entries)) {
	mapping dat;
	if (!mapp(dat = create_road_map())) {
	    return 0;
	}
	_entries = keys(dat);
    }
    if ((len = sizeof(_entries)) == 0) {
        return 0;
    }
    pos = _entries[random(len)];
    return query_room(to_row(pos), to_col(pos));
}

public object 
load_random_entry() 
{
    string str;
    object env;
    if (!stringp(str = query_random_entry())) {
	return 0;
    }
    if (catch(env = str->__bootstrap())) {
        return 0;
    }
    return env;
}

public string 
query_random_critter(object env) 
{
    int len;
    if (!arrayp(_critters) || 
        (len = sizeof(_critters)) == 0) 
    {
        return 0;
    }
    return _critters[random(len)];
}

public object 
create_random_critter(object env) 
{
    string str;
    if (!stringp(str = query_random_critter(env))) {
	return 0;
    }
    return new(str);
}

static nomask void 
check_critters() 
{
    object env, obj;
    if (_num_critters <= 0 ||
        sizeof(find_critters()) >= _num_critters ||
        !objectp(env = load_random_entry()) || 
	!objectp(obj = create_random_critter(env)))
    {
	return;
    }
    obj->add_property(EMP_P_CRITTER);
    obj->move_player("", env);
}

public void 
set_critters(string *val) 
{
    _critters = val;
}

public void 
add_critter(string val) 
{
    if (arrayp(_critters)) {
	_critters += ({ val });
    } else {
	_critters  = ({ val });
    }
}

public string *
query_critters() 
{
    return _critters;
}

public void 
set_num_critters(int val) 
{
    _num_critters = val;
}

public int 
query_num_critters() 
{
    return _num_critters;
}
    
