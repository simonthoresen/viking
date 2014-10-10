/*
** A little samurai girl wandering round in the forest of the goblinlands.
*/


#include <mudlib.h>
#include <std.h>
#include "/d/Samurai/include/npc.h"
#define  AMULET   "/d/Empire/islands/reikland/events/samugirl/girl-amulet"

inherit I_SAMURAI;

int friend;

void create() {
    ::create();
    
    set_short("A shy looking girl");
    set_name(({"erin","sinta","moni","gwen","ewolyn","kim","olivia","sinu"})[random(8)]);
    add_id("samurai");
    add_id("kid");
    add_id("girl");
    set_long("This is " + query_name() + " the Samurai girl. "+
             "She looks a bit shy at the first glance.");
    add_property("fast_heal", 3);
    set_offensive(0); 
    add_property("no_assist");
    set_level(15);
    set_hp(600);
    set_dex(35);
    set_str(20);
    set_gender(2);
    add_skill("samurai_chop", 200);
    add_skill("samurai_mental", 200);
    add_skill("samurai_sharp", 100);
    add_skill("samurai_slash", 200);
    add_skill("two_weapon", 100);
    add_eq("/d/Empire/islands/reikland/events/samugirl/sword",2);
    add_hook("__fight_beat",store_fp("fight"));
    new(AMULET)->move(this_object());
    command("wear all");
    
    load_chat(1, ({"*kiss amulet","*smile","*dance","*spin","Girl moves around silently.\n","Girl blushes.\n"}));
    
    friend = 0;
}

void fight() {
  object boy;
  
  if(!friend && query_hp() < 400) {
    boy = new("/players/postkasse/reikland/goblinland/monsters/samurai-boy");
    boy->move(environment(this_object()));
    message("info","Another samurai comes to the girl's rescue.\n",environment(this_object()));
    friend = 1; 
  }
  return;
}
