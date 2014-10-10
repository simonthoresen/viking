#include "/d/Artifact/artifact.h"

inherit ART_I_SLIVER_BASE;

private string  _type;
private string  _real_name;
private string  _base_name;
private int     _rank;
private int     _max_rank;

static void
create()
{
    int pos;
    ::create();
    _type     = 0;
    _rank     = 1;
    _max_rank = 1;

    _real_name = base_file_name();
    if ((pos = find_last('_', _real_name)) > 0 &&
        (sscanf(_real_name[pos + 1..], "%d", _rank)))
    {
        _base_name = _real_name[0..pos - 1];
        _max_rank  = _rank;
    } else {
        _base_name = _real_name;
    }
    set_name(implode(map_array(explode(_real_name, "_"),
                               "format_name"), " "));
    set_short(add_article(query_name()));
    set_long("It is " + query_short() + ".");
    set_value(1);
    set_weight(1);
    add_id("sliver");
    add_id(({ _real_name, _base_name, lower_case(query_name()), _type }));
}

static string
format_name(string str)
{
    switch (str) {
    case "0":  return 0;
    case "1":  return "I";
    case "2":  return "II";
    case "3":  return "III";
    case "4":  return "IV";
    case "5":  return "V";
    case "6":  return "VI";
    case "7":  return "VI";
    case "8":  return "VIII";
    case "9":  return "IX";
    case "10": return "X";
    default:   return capitalize(str);
    }
}

public nomask string
desc_rank()
{
    if (_max_rank == 1) {
        return "";
    }
    switch ((100 * (_rank - 1)) / (_max_rank - 1)) {
    case 0..12:
        return "some ";
    case 13..26:
        return "decent ";
    case 27..39:
        return "a lot of ";
    case 40..53:
        return "tremendous ";
    case 54..62:
        return "incredible ";
    case 63..76:
        return "unearthly ";
    case 77..89:
        return "legendary ";
    default:
        return "godlike ";
    }
}

public nomask void
set_type(string val)
{
    _type = val;
}

public nomask string
query_type()
{
    return _type;
}

public nomask string
query_real_name()
{
    return _real_name;
}

public nomask string
query_base_name()
{
    return _base_name;
}

public nomask int
query_rank()
{
    return _rank;
}

public nomask void
set_max_rank(int val)
{
    _max_rank = val;
}

public nomask int
query_max_rank()
{
    return _max_rank;
}
