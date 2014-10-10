#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_SPELL;

static int
do_cast(object ply, object foe) 
{
    int val;
    if ((val = ply->query_hp()) >= ply->query_max_hp() ||
        ply->query_tmp_prop("last_heal_time") + 20 > time()) 
    {
        return 0;
    }
    ply->set_tmp_prop("last_heal_time", time());
    if (is_caster(ply)) {
        ply->command("emote casts a healing spell!");
    } else {
        ply->command("emote mends " + ply->query_possessive() + " wounds.");
    }
    ply->reduce_hit_point(-ply->query_max_hp() / 5);
    if (ply->query_hp() > val) {
        ply->command("emote looks healthier.");
    }
    return 1;
}
