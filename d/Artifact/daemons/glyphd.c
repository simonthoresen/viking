#include "/d/Artifact/artifact.h"

inherit EMP_I_DAEMON;

private int _bias;

static void
create()
{
    ::create();
    _bias = 0;

    set_heart_beat(1);
    add_hook("__heart_beat", store_fp("on_heart_beat"));
    add_hook("__destroy", store_fp("on_destroy"));
}

public void
on_heart_beat()
{
    map_array(users(), "ensure_kill_hook");
}

public void
on_destroy()
{
    map_array(users(), "remove_kill_hook");
}

static void
ensure_kill_hook(object ply)
{
    if (!objectp(ply) || wizardp(ply)) {
        return;
    }
    if (ply->query_hook("__kill")) {
        return; // already hooked
    }
    ply->add_hook("__kill", store_fp("maybe_drop_glyph"));
}

static void
remove_kill_hook(object ply)
{
    if (!objectp(ply)) {
        return;
    }
    ply->remove_hook("__kill");
}

private object
random_glyph()
{
    object *arr;
    int len;
    arr = ART_D_SLIVER->query_glyphs();
    if (!arrayp(arr)) {
        return 0;
    }
    len = sizeof(arr);
    if (len == 0) {
        return 0;
    }
    return arr[random(len)];
}

public void
maybe_drop_glyph(object victim, object killer)
{
    object obj;
    if (!objectp(victim) || !objectp(killer)) {
        // mudlib bug
        return;
    }
    if (random(100000) > 100 + (++_bias)) {
        // Base chance for a glyph drop is 1%%. For every 100th kill without a
        // glyph, the chance increases with an additional 1%%. This gives:
        // 900 => 1%, 9900 => 10%, 99900 => 100%
        return;
    } else {
        // reset bias before trying to create a glyph to avoid having a guild
        // bug trigger on every kill across the mud once the bias is large
        _bias = 0;
    }
    if (!objectp(obj = random_glyph())) {
        // guild bug
        return;
    }
    ART_LOGX("glyphs", "%s got %s from %O (%s)",
             killer->query_real_name(),
             obj->query_real_name(),
             victim, victim->query_real_name());
    clone_object(obj)->move(victim);
}
