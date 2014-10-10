#include "/d/Artifact/artifact.h"

inherit ART_I_SPELL;

private int _did_invis;

static void
create()
{
    ::create();
    _did_invis = 0;
    set_info(query_name() + " turns the wielder of the artifact invisible " +
             "for a short period of time.");
}

static void 
setup_user(object ply)
{
    ::setup_user(ply);
    if (ply->query_invis()) {
        fizzle_spell(ply->query_name() + " is already invisible.");
        return;
    }
    _did_invis = 1;
    ply->invis();
}

static void
unset_user(object ply)
{
    ::unset_user(ply);
    if (_did_invis) {
        ply->vis();
    }
}
