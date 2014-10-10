#include "/d/Empire/islands/altdorf.h"

inherit ALT_I_CITIZEN;

static void
create() 
{
    ::create();    
    set_male();
    set_race("human");
    set_name("Tots Blatter");
    set_short("Tots the Weaponsmith");
    set_long("This guy puts you in mind of a sneaky serpent. He has round " +
             "green eyes that are like two clumps of moss. He is bald, but " +
             "used to have thick, straight, night-black hair. He is short " +
             "and has a masculine build. His skin is nut-brown. He has a " +
             "low forehead. His wardrobe is strange and professional, with " +
             "a completely green and yellow color scheme.");
    add_id(({ "tots", "blatter", "weaponsmith", "smith" }));

    set_ac(20);
    set_level(18);
    set_wc(60);
    set_hp(1000+random(500));
    add_property("guardian");
    add_property("no_possess");

    load_chat(10, ({ "*say I have the skills to sharpen any weapon.",
                     "*say I can repair any weapon that is wearing out.",
                     "*peer",
                     "*whistle" }));
    set_greeting(({ "*say I am Tots, the famous weaponsmith.", 
		    "*say I can repair and sharpen your weapons." }));

    EMP_D_ARMOUR->add_armour(75, "glove");
    EMP_D_ARMOUR->add_armour(75, "armour");
    EMP_D_WEAPON->add_weapon(75, "onehanded");
}
