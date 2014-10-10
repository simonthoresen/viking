#include "/d/Artifact/artifact.h"

inherit ART_I_SPELL;

private string _summon_item;
private int    _item_level;
private int    _num_items;

static void 
create() 
{
    ::create();
    _summon_item = 0;
    _item_level  = 0;
    _num_items   = 1;
}

public nomask string
query_info()
{
    string name, str;
    name = _summon_item->query_name();
    str  = query_name() + " summons " + convert_number(_num_items) + " ";
    str += _num_items > 1 ? I_GRAMMAR->pluralize(name) : name;
    str += ".";
    return str;
}

static void
setup_player(object ply)
{
    int i;
    object *arr, env;
    ::setup_player(ply);
    arr = allocate(_num_items);
    for (i = 0; i < _num_items; ++i) {
        arr[i] = new(_summon_item);
        arr[i]->set_item_level(_item_level);
    }
    env = query_room();
    tell_room(env, capitalize(I_GRAMMAR->composite_list(arr)) + " arrive" +
              (_num_items > 1 ? "" : "s") + " in a puff of smoke.\n");
    arr->move(env);
}

public nomask void 
set_summon_item(string val) 
{
    _summon_item = val;
}

public nomask string
query_summon_item()
{
    return _summon_item;
}

public nomask void 
set_item_level(int val) 
{
    _item_level = val;
}

public nomask int
query_item_level()
{
    return _item_level;
}

public nomask void 
set_num_items(int val) 
{
    _num_items = val;
}

public nomask int
query_num_items()
{
    return _num_items;
}
