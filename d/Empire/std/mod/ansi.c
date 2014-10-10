#include "/d/Empire/empire.h"

static void
create()
{
    /* empty */
}

public string
escape(string str)
{
    return "%" + "^" + str + "%" + "^";
}

public int
has_ansi(object ply)
{
    return ply->query_property("TERM") == "ansi";
}

public void
tell_ansi(object ply, string str)
{
    int can, val;
    can = !ply<-I_PLAYER || interactive(ply);
    if (can) {
        val = ply->query_width();
        ply->set_width(0x7fffffff);
    }
    tell_object(ply, str);
    if (can) {
        ply->set_width(val);
    }
}

public void
write_ansi(string str)
{
    tell_ansi(this_player(), str);
}
