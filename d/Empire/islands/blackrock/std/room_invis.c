#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_ROOM_DLEVEL;

static void create() {
    ::create();
    add_hook("__init", store_fp("drain_invis"));
}

static void drain_invis() {
    object ply;
    if (!objectp(ply = this_player()) || !interactive(ply) || !ply->query_invis()) {
        return;
    }
    tell_object(ply, bold("The magic of Blackrock tears at your soul.\n"));
    EMP_D_COMBAT->hit_player(ply, ply, max(25, ply->query_hp() / 5), "drain");
}
