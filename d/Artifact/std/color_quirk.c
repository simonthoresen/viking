#include "/d/Artifact/artifact.h"

inherit ART_I_QUIRK;

private string _color;
private string _pre_title;
private string _title;

static void
create()
{
    int pos;
    string str;
    ::create();
    str = base_file_name();
    pos = find_first('_', str);

    _color     = pos < 0 ? str : str[pos + 1..];
    _pre_title = "%^" + upper_case(str) + "%^";
    _title     = "%^END%^";

    set_info(query_name() + " colors the artifact " + _color + ".");
}

static void
setup_weapon(object wpn)
{
    ::setup_weapon(wpn);
    wpn->add_pre_title(_pre_title);
    wpn->add_title(_title);
}

static void
unset_weapon(object wpn) 
{
    ::unset_weapon(wpn);
    wpn->remove_pre_title(_pre_title);
    wpn->remove_title(_title);
}

public nomask string
query_color()
{
    return _color;
}

public nomask string
query_pre_title() 
{
    return _pre_title;
}

public nomask string
query_title()
{
    return _title;
}
