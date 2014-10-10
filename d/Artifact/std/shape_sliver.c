#include "/d/Artifact/artifact.h"

inherit ART_I_SLIVER;

private string  _wpn_shape;
private string  _wpn_long;
private string *_wpn_ids;
private mapping _wpn_props;
private int     _wpn_class;
private int     _wpn_weight;
private string *_wpn_dtypes;
private string  _wpn_type;

static void
create()
{
    ::create();
    _wpn_shape  = lower_case(query_name());
    _wpn_long   = "#R is " + add_article(_wpn_shape) + ".";
    _wpn_ids    = ({ });
    _wpn_props  = ([ ]);
    _wpn_class  = 0;
    _wpn_weight = 1;
    _wpn_dtypes = ({ });
    _wpn_type   = "onehanded";

    set_type("shape");
    set_slot("shape", -1);
}

static void
setup_weapon(object obj)
{
    int i, len;
    string *arr;
    ::setup_weapon(obj);
    obj->set_shape(_wpn_shape);
    obj->set_short(_wpn_shape);
    obj->set_long(_wpn_long);
    obj->add_id(_wpn_ids);
    obj->add_id(_wpn_shape);
    obj->set_class(_wpn_class);
    obj->set_weight(_wpn_weight);
    obj->set_damage_type(_wpn_dtypes);
    obj->set_type(_wpn_type);
    for (i = 0, len = sizeof(arr = keys(_wpn_props)); i < len; ++i) {
        obj->add_property(arr[i], _wpn_props[arr[i]]);
    }
}

public string
query_info()
{
    return format_message(_wpn_long, this_player());
}

public void
set_weapon_shape(string val)
{
    _wpn_shape = val;
}

public string
query_weapon_shape()
{
    return _wpn_shape;
}

public void
set_weapon_long(string val)
{
    _wpn_long = val;
}

public string
query_weapon_long()
{
    return _wpn_long;
}

public void
add_weapon_id(string val)
{
    _wpn_ids |= ({ val });
}

public void
add_weapon_ids(string *val)
{
    _wpn_ids |= val;
}

public void
set_weapon_ids(string *val)
{
    _wpn_ids = val;
}

public string *
query_weapon_ids()
{
    return _wpn_ids;
}

public varargs void
add_weapon_prop(string key, mixed val)
{
    _wpn_props[key] = val != 0 ? val : 1;
}

public void
add_weapon_props(string *val)
{
    int i, len;
    for (i = 0, len = sizeof(val); i < len; ++i) {
        _wpn_props[val[i]] = 1;
    }
}

public void
set_weapon_props(mapping val)
{
    _wpn_props = val;
}

public mapping
query_weapon_props()
{
    return _wpn_props;
}

public void
set_weapon_class(int val)
{
    _wpn_class = val;
}

public int
query_weapon_class()
{
    return _wpn_class;
}

public void
set_weapon_weight(int val)
{
    _wpn_weight = val;
}

public int
query_weapon_weight()
{
    return _wpn_weight;
}

public void
add_weapon_dtype(string val)
{
    _wpn_dtypes += ({ val });
}

public void
set_weapon_dtype(string val)
{
    _wpn_dtypes = ({ val });
}

public void
set_weapon_dtypes(string *val)
{
    _wpn_dtypes = val;
}

public string *
query_weapon_dtypes()
{
    return _wpn_dtypes;
}

public void
set_weapon_type(string val)
{
    _wpn_type = val;
}

public string
query_weapon_type()
{
    return _wpn_type;
}
