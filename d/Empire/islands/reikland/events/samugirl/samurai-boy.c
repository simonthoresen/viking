/*
** A little samurai girl wandering round in the forest of the goblinlands.
*/


#include <mudlib.h>
#include <std.h>
#include "/d/Samurai/include/npc.h"

inherit I_SAMURAI;

void create() {
    ::create();
    
    set_short("A dextrous samurai boy");
    set_name(({"amo","erik","quin","girm","giha","zork","moain","shant"})[random(8)]);
    add_id("samurai");
    add_id("kid");
    add_id("boy");
    set_long("This is " + query_name() + " the Samurai boy. "+
             "He looks confident and strong.");
    add_property("fast_heal", 3);
    set_offensive(100); 
    set_level(18);
    set_hp(800);
    set_dex(30);
    set_str(40);
    set_gender(1);
    add_skill("samurai_chop", 200);
    add_skill("samurai_mental", 200);
    add_skill("samurai_sharp", 100);
    add_skill("samurai_slash", 200);
    add_skill("two_weapon", 100);
    add_eq("/d/Empire/islands/reikland/events/samugirl/sword2");
}
