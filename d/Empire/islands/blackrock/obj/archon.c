#include "/d/Empire/islands/blackrock.h"

inherit BRD_I_CRITTER;

static void
init_dangerlevel(int val) 
{
    string mtype, dtype;
    int idx;
    if (random(2)) {
        mtype = "fire";
        dtype = "fire";
        switch (val / 40) {
        case 0:
            set_name("Fire archon emberguard");
            add_id(({ "emberguard", "guard" }));
            break;
        case 1:
            set_name("Fire archon blazesteel");
            add_id("blazesteel");
            break;
        case 2:
            set_name("Fire archon ash disciple");
            add_id(({ "ash disciple", "disciple" }));
            break;
        }
        load_a_chat(25, ({ 
            "*emote blazes with fire!",
            "It is unbearably hot near the " + query_name() + "!\n",
            "Your clothes almost catch fire!\n", 
        }));
    } else {
        mtype = "ice";
        dtype = "cold";
        switch (val / 40) {
        case 0:
            set_name("Ice archon hailscourge");
            add_id("hailscourge");
            break;
        case 1:
            set_name("Ice archon rimehammer");
            add_id("rimehammer");
            break;
        case 2:
            set_name("Ice archon frostshaper");
            add_id("frostshaper");
            break;
        } 
        load_a_chat(25, ({ 
            "*emote makes the room freezing cold!",
            "It is unbearably cold near the " + query_name() + "!\n",
            "Your breath turns to droplets of ice!\n", 
        }));
    }
    set_long("It resembles a man, but made completely of " + mtype + ".");
    add_skill("prot_" + dtype, 100);
    add_property("unarmed_damage_type", dtype);    
    add_tmp_con(11);
    add_tmp_int(11);
    EMP_D_ARMOUR->add_armour(75 + random(val), "legging");
}
