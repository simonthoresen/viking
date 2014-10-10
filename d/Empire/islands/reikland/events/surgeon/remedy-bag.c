#include <mudlib.h>

inherit I_CONTAINER;

static void create() {
  object pill;
  ::create();

  set_name("remedy bag");
  set_short("A remedy bag");
  add_id("bag");
  set_weight(1);
  set_max_weight(7);
  set_value(110);
  add_property("tagged");
    
  pill=new(I_FOOD);
	pill->set_name("red pill");
	pill->add_id("pill");
	pill->set_short("A red pill");
	pill->set_eater_mess("Crunch crunch.\n");
	pill->set_strength(50+random(20));
	pill->set_value(10);
	pill->set_weight(1);
	pill->add_property("hidden"); 
  pill->move(this_object());
  
  pill=new(I_FOOD);
	pill->set_name("blue pill");
	pill->add_id("pill");
	pill->set_short("A blue pill");
	pill->set_eater_mess("Crunch crunch.\n");
	pill->set_strength(30+random(40));
	pill->set_value(10);
	pill->set_weight(1);
	pill->add_property("hidden"); 
  pill->move(this_object());
  
  pill=new(I_FOOD);
	pill->set_name("green pill");
	pill->add_id("pill");
	pill->set_short("A toxic green pill");
	pill->set_eater_mess("You feel dizzy.\n");
	pill->set_strength(-100);
	pill->set_value(10);
	pill->set_weight(1);
	pill->add_property("hidden"); 
  pill->move(this_object());
}
