#include "/d/Empire/islands/ruins.h"

inherit RUN_I_MONSTER;

static void
create()
{
    ::create();
    set_name("Acolyte");
    set_short("acolyte of the god of wind");
    set_long("");
    set_level(29);
    add_hook("__heart_beat", store_fp("on_heart_beat"));
    add_hook("__die", store_fp("on_die"));
}

static void
on_die(object corpse, object killer)
{
    map_array(RUN_ISLAND->query_livings(), "destroy_tornado");
}

static void
destroy_tornado(object ply)
{
    if (!objectp(ply) || !ply<-RUN_C_KARI_TORNADO) {
        return;
    }
    ply->destroy();
}
