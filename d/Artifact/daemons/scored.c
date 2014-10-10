#include "/d/Artifact/artifact.h"

inherit EMP_I_SCORED;

static void
create()
{
    ::create();
    set_save_file(ART_DIR_VAR + "scored");
    set_prefix("art_score_");
    set_num_records(10);
}

static void
notify_entry(string board, object ply, int val)
{
    ART_MASTER->broadcast(ply->query_real_name() + " took " +
                          I_GRAMMAR->convert_ordinal_number(val + 1) +
                          " place on the " + board + " leader board.");
}
