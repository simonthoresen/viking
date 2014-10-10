#include "/d/Empire/islands/altdorf.h"

inherit ALT_I_CITIZEN;

static void
create() 
{
    ::create();
    set_male();
    set_name("Betty");
    set_short("a tired-looking nurse");
    set_long("This boorish woman has slitted blue eyes that are like two " +
             "turquoises. Her thick, curly, gray hair is very long and is " +
             "worn in an impractacal, carefully-crafted style. She is tall " +
             "and has an amazonian build. Her skin is nut-brown. She has " +
             "thin lips and large hands. Her wardrobe is unusual.");
    add_id(({ "woman", "nurse" }));
    add_property("guardian");
    add_property("no_possess");
    set_level(12);
    set_hp(200);
    set_sp(50);
    set_wc(10);
    set_ac(3);
    load_a_chat(10, ({ "*say Cut it out, will you?",
                       "*say I am too tired for this!" }));
    set_greeting(({ "*say I am Betty, one of the nurses here.",
		    "*say I can treat your wounds from time to time." }));
}
