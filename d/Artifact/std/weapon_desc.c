#include "/d/Artifact/artifact.h"

inherit ART_I_WEAPON_BASE;

public nomask string query_pre_title();
public nomask string query_title();

private mapping _pre_titles;
private string  _pre_title_cache;
private mapping _titles;
private string  _title_cache;
private string  _shape;

static void
create()
{
    ::create();
    _pre_titles      = ([ ]);
    _pre_title_cache = 0;
    _titles          = ([ ]);
    _title_cache     = 0;
    _shape           = 0;

    add_id("artifact");
    add_property("artifact");
    remove_property("prot_acid");
    remove_property("prot_bite");
    remove_property("prot_blunt");
    remove_property("prot_chop");
    remove_property("prot_claw");
    remove_property("prot_cold");
    remove_property("prot_electricity");
    remove_property("prot_fire");
    remove_property("prot_impact");
    remove_property("prot_magic");
    remove_property("prot_pierce");
    remove_property("prot_slash");
}

public int
id(string arg)
{
    object ply;
    if (::id(arg)) {
        return 1;
    }
    if (objectp(ply = query_player()) && ply->id(arg)) {
        return 1;
    }
    return 0;
}

public nomask string
query_name()
{
    object ply;
    if (!objectp(ply = query_player())) {
        return ::query_name();
    }
    return ply->query_name();
}

public nomask string
query_real_name()
{
    object ply;
    if (!objectp(ply = query_player())) {
        return ::query_name();
    }
    return ply->query_real_name();
}

public nomask string
short()
{
    object ply;
    string str, out;
    out = "";
    if (stringp(str = query_pre_title())) {
        out += str;
    }
    out += ::short();
    if (stringp(str = query_title())) {
        out += str;
    }
    if (objectp(ply = query_player()) &&
        stringp(str = ply->short()) &&
        !ply->query_invis())
    {
        out += " named " + str;
    }
    if (is_suspended()) {
        out += " (limp)";
    } else if (is_idle()) {
        out += " (idle)";
    }
    return add_article(out);
}

public nomask
set_long(string arg)
{
    object ply;
    if (objectp(ply = query_player())) {
        arg = format_message(arg, ply);
    }
    ::set_long(arg);
}

private string
desc_scars(object ply)
{
    int i, cnt, scar;
    if ((scar = ply->query_scar()) == 0) {
        return "#R is in mint condition.";
    }
    for (i = 0, cnt = 0; i < 32; ++i) {
        if (scar & (1 << i)) {
            ++cnt;
        }
    }
    if (cnt == 1) {
        return "#R has a single dent.";
    }
    return "#R has " + cnt + " dents.";
}

public nomask varargs void
long(string arg, int nonl)
{
    object ply;
    string str, *arr;
    if (!objectp(ply = query_player())) {
        ::long(0, nonl);
        return;
    }
    write(ply->short() + ".\n");
    ::long(0, nonl);
    str = desc_scars(ply);
    if (sizeof(arr = all_inventory()->extra_look() - ({ 0 }))) {
        str += "\n" + implode(filter_unique(arr), ".\n") + ".";
    }
    write((nonl ? "\n" : "") + format_message(str, query_player()) +
          (nonl ? "" : "\n"));
}

public nomask int
query_cursed()
{
    return ART_D_QUEST->is_unlocked(query_player(), "usr_die_10");
}

private string
calc_title(mapping dat)
{
    /* by using a mapping for titles we are able to track how many times
       a title has been added, so that removal of that title only occurs
       once all instances have been removed. */
    if (map_sizeof(dat) == 0) {
        return 0;
    }
    return implode(keys(dat), "");
}

public nomask mapping
query_pre_titles()
{
    return _pre_titles;
}

public nomask void
set_pre_titles(mapping val)
{
    _pre_titles = val;
    _pre_title_cache = 0;
}

public nomask void
add_pre_title(string val)
{
    _pre_titles[val] = _pre_titles[val] + 1;
    _pre_title_cache = 0;
}

public nomask void
remove_pre_title(string val)
{
    _pre_titles[val] = _pre_titles[val] - 1;
    _pre_title_cache = 0;
}

public nomask string
query_pre_title()
{
    if (!stringp(_pre_title_cache)) {
        _pre_title_cache = calc_title(_pre_titles);
    }
    return _pre_title_cache;
}

public nomask mapping
query_titles()
{
    return _titles;
}

public nomask void
set_titles(mapping val)
{
    _titles = val;
    _title_cache = 0;
}

public nomask void
add_title(string val)
{
    _titles[val] = _titles[val] + 1;
    _title_cache = 0;
}

public nomask void
remove_title(string val)
{
    _titles[val] = _titles[val] - 1;
    _title_cache = 0;
}

public nomask string
query_title()
{
    if (!stringp(_title_cache)) {
        _title_cache = calc_title(_titles);
    }
    return _title_cache;
}

public nomask void
set_shape(string val)
{
    _shape = val;
}

public nomask string
query_shape()
{
    return _shape;
}
