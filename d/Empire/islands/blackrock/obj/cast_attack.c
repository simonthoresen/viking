#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_SPELL;

static int
do_cast(object ply, object foe)
{
    if (ply->query_tmp_prop("last_speed_attack") == time()) {
        return 0;
    }
    if (is_caster(ply)) {
        ply->command("emote casts a swiftness spell.");
    } else {
        ply->command("emote makes some fast footwork and makes an extra " +
                     "attack.");
    }    
    ply->attack();
    return 1;
}
