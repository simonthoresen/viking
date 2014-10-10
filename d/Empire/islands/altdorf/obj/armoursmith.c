#include "/d/Empire/islands/altdorf.h"

inherit ALT_I_CITIZEN;

static void
create() 
{
    ::create();
    set_male();
    set_race("human");
    set_name("Dalbran Fellhammer");
    set_short("Dalbran the Armoursmith");
    set_long("This solem man has beady black eyes that are like two dark " +
             "pits. His silky, straight, ebony hair is worn in a style that " +
             "reminds you of a strange headdress. He's got stubble. He is " +
             "tall and has a wide-chested build. His skin is ruddy. He has " +
             "a domed forehead and thick eyebrows. His wardrobe is " +
             "businesslike.");
    add_id(({ "dalbran", "fellhammer", "armoursmith", "smith" }));

    set_ac(20);
    set_level(18);
    set_wc(60);
    set_hp(1000 + random(500));
    add_property("guardian");
    add_property("no_possess");

    load_chat(10, ({ "*say I have the skills to harden any armour.",
                     "*say I can repair any armour that is wearing out.",
                     "*peer",
                     "*whistle" }));
    set_greeting(({ "*say I am Dalbran, the famous armoursmith.",
		    "*say I can repair and harden your armours." }));

    EMP_D_ARMOUR->add_armour(75, "glove");
    EMP_D_ARMOUR->add_armour(75, "armour");
    EMP_D_WEAPON->add_weapon(75, "onehanded");
}
