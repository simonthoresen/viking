#include "/d/Artifact/artifact.h"

inherit base ART_I_SPELL;
inherit util ART_I_STAT_UTIL;

static void 
create() 
{
    base::create();
    util::create();
}

public nomask string
query_info()
{
    return query_name() + " grants the artifact and " +
           "its wielder " + query_stats_desc() + ".";
}

static void
setup_player(object ply)
{
    ::setup_player(ply);
    setup_stat_bonuses(ply);
}

static void
unset_player(object ply) 
{
    ::unset_player(ply);
    unset_stat_bonuses(ply);
}

static void
setup_user(object ply)
{
    ::setup_user(ply);
    setup_stat_bonuses(ply);
}

static void
unset_user(object ply)
{
    ::unset_user(ply);
    unset_stat_bonuses(ply);
}
