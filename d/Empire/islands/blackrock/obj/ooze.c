#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_CRITTER;

static void
init_dangerlevel(int val) 
{
    switch (val / 40) {
    case 0:
        set_name("Ochre jelly");
        add_id("jelly");
        break;
    case 1:
        set_name("Green slime");
        add_id("slime");
        break;
    case 2:
        set_name("Black pudding");
        add_id("pudding");
        break;
    }
    set_long("It resembles a giant amoeba, consisting of a thick, porous, " +
             "golden sludge stiffly built up into the amoeba shape. It " +
             "lurks in dungeons, slowly sludging its way along floors, " +
             "walls and ceilings alike, under doors and through cracks, " +
             "looking for victims.");
    add_property("unarmed_damage_type", "acid");
    add_property("resistant", 100);
    add_hook("__hit_player", store_fp("weapon_stuck"));
    EMP_D_TREASURE->add_treasure(750 + random(10 * val));
}

static int
weapon_stuck(int dmg, string type, object foe, string loc,
             int prot, int resist, int vuln, int ac, object wpn)
{
    if (!objectp(foe) || !objectp(wpn) || random(100) > 20) {
        return 0;
    }
    tell_object(foe, "You fumble with your " + wpn->query_name() + " as it " +
                "hits the sludgy " + query_name() + ".");
    foe->set_busy_next_round();
}
