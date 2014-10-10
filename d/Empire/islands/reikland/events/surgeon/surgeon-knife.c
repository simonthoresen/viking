/* -----------------------------------------------------
    Simple but good knife that gives the wielder a 
    certain chance of stealing hp from the enemy.
    
                 Idea - Ruler / Code - Postkasse     
----------------------------------------------------- */

#include <mudlib.h>

inherit I_WEAPON;

static void create() {
  ::create();
  set_name("a bloodletting knife");
  add_id("knife");
  set_long("A surgeon knife drenched in blood.");
  set_class(11);
  set_value(866);
  set_damage_type("pierce");
  set_weight(1);
  add_property("metal");
  add_hook("__wield",store_fp("do_wield"));
  add_hook("__remove",store_fp("do_unwield"));
}

void do_wield() {
	object who;
	who = query_wield();
	if(!who) return;
	who->add_hook("__attack",store_fp("do_steal"));
	return;
}

void do_unwield() {
	object who;
	who = query_wield();
	if(!who) return;
  who->remove_hook("__attack");
  return;
}

void do_steal(object foe) {
	object who;
	int chance;
	who = this_player();

  chance = 5 + random(10);
  if(!random(chance)) {
  	foe->reduce_hit_point(chance);
  	who->reduce_hit_point(-chance);
  	message("hityou",who->query_name()+" draws blood from you.\n",foe);
  	message("youhit","You draw blood from "+foe->query_name()+".\n",who);
  }
	return;
}

