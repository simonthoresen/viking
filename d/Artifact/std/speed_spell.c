#include "/d/Artifact/artifact.h"

inherit ART_I_SPELL;

private int _num_attacks;

static void 
create() 
{
    ::create();
    _num_attacks = 0;
}

public nomask string
query_info() 
{
    return query_name() + " grants the wielder of the artifact " +
           convert_number(_num_attacks) + " additional attacks.";
}

static void
setup_user(object ply)
{
    int i;
    ::setup_user(ply);
    ply->add_property("last_speed_attack", time());
    for (i = 0; i < _num_attacks; ++i) {
        if (!objectp(ply) || !objectp(ply->query_attack())) {
            break;
        }
        ply->attack();
    }
}

public nomask void 
set_num_attacks(int val) 
{
    _num_attacks = val;
}

public nomask int
query_num_attacks()
{
    return _num_attacks;
}
