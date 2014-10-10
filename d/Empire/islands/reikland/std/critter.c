#include "/d/Empire/empire.h"

inherit EMP_I_MONSTER;

private int _size;

static void
create() 
{
    ::create();
    _size = random(100);
}

static string
query_size_desc() 
{
    switch (_size) {
    case 0..4:   return "petite";
    case 5..9:   return "baby";
    case 10..14: return "little";
    case 15..19: return "young";
    case 20..24: return "immature";
    case 25..29: return "small";
    case 30..34: return "scanty";
    case 35..39: return "humble";
    case 40..44: return "meager";
    case 45..49: return "modest";
    case 50..54: return "fat";
    case 55..59: return "bulky";
    case 60..64: return "big";
    case 65..69: return "hefty";
    case 70..74: return "huge";
    case 75..79: return "hulking";
    case 80..84: return "massive";
    case 85..89: return "gigantic";
    case 90..94: return "enormous";
    case 95..99: return "colossal";
    default:     return 0;
    }
}

static int
scale_to_size(int min, int max) 
{
    if (min < max) {
        return min + ((max - min) * _size) / 100;
    } else {
        return min - ((min - max) * _size) / 100;
    }
}

public void
add_long(string val) 
{
    ::set_long(("It is " + query_short() + ".") + 
               (stringp(val) ? " " + val : ""));
}

public void
set_name(string val) 
{
    string desc;
    ::set_name(val);
    if (stringp(desc = query_size_desc())) {
        desc += " " + val;
    } else {
        desc = val;
    }
    set_short(add_article(desc));
    add_long(0);
    add_id(desc);
}

public void
scale_level(int min, int max) 
{
    set_level(scale_to_size(min, max));
}

public void
scale_str(int min, int max) 
{
    set_str(scale_to_size(min, max));
}

public void
scale_dex(int min, int max) 
{
    set_dex(scale_to_size(min, max));
}

public void
scale_con(int min, int max) 
{
    set_con(scale_to_size(min, max));
}

public void
scale_int(int min, int max) 
{
    set_int(scale_to_size(min, max));
}

public void
scale_wc(int min, int max) 
{
    set_wc(scale_to_size(min, max));
}

public void
scale_ac(int min, int max) 
{
    set_ac(scale_to_size(min, max));
}

public void
scale_hp(int min, int max) 
{
    set_hp(scale_to_size(min, max));
}

public void
scale_sp(int min, int max) 
{
    set_sp(scale_to_size(min, max));
}

public void
scale_skill(string name, int min, int max) 
{
    add_skill(name, scale_to_size(min, max));
}

public int
query_size() 
{
    return _size;
}
