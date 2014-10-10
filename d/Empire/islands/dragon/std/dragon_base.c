#include "/d/Empire/islands/dragon.h"

#define REQUIRED_RAID_SIZE    (10)
#define REQUIRED_PLAYER_DPS   (100)
#define EXPECTED_FIGHT_TIME   (15 * 30) 

inherit EMP_I_MONSTER;

static void
create() 
{
    ::create();
    set_female();
    set_race("dragon");
    set_name("Onyxia");
    set_short("an ENORMOUS dragon");
    set_long("It has a serpentine shape, with a broad, low head adorned with " +
             "a fringe of golden whiskers on the chin and along the rear " +
             "portions of the skull. Pairs of horns rise from behind the " +
             "eyes, and a pair of barbules descend from beneath the " +
             "pronounced nasal region. Scaly armour covers the iridicent " +
             "red body, neck and tail, which are surrounded by a ridge of " +
             "membrane-connected spines. The highly dexterous paws are " +
             "four-fingered, with each digit ending in a large claw.");
    add_id(({ "dragon", "enormous dragon" }));
    set_scary_id("onyxia");
    set_log_file("dragon");
    set_level(66);
    set_hp(REQUIRED_RAID_SIZE * 
           REQUIRED_PLAYER_DPS * 
           EXPECTED_FIGHT_TIME);
    set_sp(16661);
    set_aggressive(1);
    add_property("no_crit");
    add_property("no_disarm");
    add_property("no_glaze");
    add_property("no_headchop");
    add_property("no_stun");
    add_hook("__hit_player", store_fp("block_megahits"));
}

static int
block_megahits(int dmg, string type, object foe, string loc, int prot, 
               int resist, int vuln, int ac, object weapon) 
{
    if (objectp(foe) && wizardp(foe)) {
        return 0;
    }
    return dmg < 666 ? dmg : 666;
}

public int
is_dragon() 
{
    return 1;
}

public int
is_onyxia() 
{
    return 1;
}
