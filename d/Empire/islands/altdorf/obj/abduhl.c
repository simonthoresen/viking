#include "/d/Empire/islands/altdorf.h"

inherit ALT_I_CITIZEN;
 
static void
create() 
{
    ::create();
    set_name("Abduhl");
    set_short("Artificer Abduhl Al'Haraz");
    set_long("Abduhl Al'Haraz is in the artifact trading business. He is " +
             "rather cunning in the arts of trading. He is carrying all " +
             "sorts of jewelry showing how rich he is. He looks you over " +
             "for things he could sell for you."); 
    set_race("human");
    add_id(({ "man", "shopkeeper", "keeper", "artificer", "al'haraz",
              "abduhl al'haraz" }));
    add_property("guardian");
    set_male();
    set_level(29);
    set_hp(2000);
    set_al(400);
    set_wc(50);
    set_ac(20); 
    set_greeting(({ "*smile", "*say Welcome to my humble shop, sahib." }));
}
