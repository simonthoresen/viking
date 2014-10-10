/*
Surgeon
Mengelin the infamous battelfield butcher.
he has a scar on his ,head ,arm ,osv
He does not look like the healer type.
he is wearing a apron splatterd in blood.
he is wielding a bloodletting knife in his right hand.
A remedy bag.

says They where dying annyway, no harm in me taking a little for myself.
says What battles ive seen.
says Scum dying in drowes
says I can stich you up in no time, if i bother.
says who cares about prisoners annyway
says my work must continue, imortalility is just a few steps away
says There is true power in blood and fear.
says A mans fear is as sweet as his blood is salty.
says A little pain will do you good.
says you will feel a little prick. 
says Pain or Extasy is it realy that much of a difference

emotes licks his blade

emotes cuts his hand swiftly
emotes cuts his chin absentmindedly
emotes cuts his thigh slowly
emotes cuts his ear silently
emotes cuts his left nipple gracefully
emotes cuts his sholder deeply
emotes cuts his palm painfully  

Ruler - 2011
*/

#include <mudlib.h>

inherit I_MONSTER;

void create() {
  ::create();
  set_name("surgeon");
  add_id("mengelin");
  add_id("butcher");
  set_short("Mengelin the infamous battlefield surgeon");
  set_long("Mengelin the infamous battelfield surgeon.\n"+
           "He has a scar on her left leg, right leg, nose, left arm, right arm,\nleft hand, right hand, forehead, left cheek and right cheek.\n"+
           "He does not look like the healer type'o guy.");
  set_level(50);
  set_hp(2000);
 
  load_chat(10,({"Mengelin says 'They where dying anyway, no harm in me taking a little for myself'.\n",
                 "Mengelin says 'What battles ive seen'.\n",
                 "Mengelin says 'Scum dying in drowes'.\n",
                 "Mengelin says 'I can stich you up in no time, if i bother'.\n",
                 "Mengelin says 'Who cares about prisoners annyway'.\n",
                 "Mengelin says 'My work must continue, imortalility is just a few steps away'.\n",
                 "Mengelin says 'There is true power in blood and fear'.\n",
                 "Mengelin says 'A mans fear is as sweet as his blood is salty'.\n",
                 "Mengelin says 'A little pain will do you good'.\n",
                 "Mengelin says 'You will feel a little prick'.\n",
                 "Mengelin says 'Pain or Extasy is it realy that much of a difference'.\n",
                 "Mengelin licks his blade.\n",
                 "Mengelin cuts his hand swiftly.\n",
                 "Mengelin cuts his chin absentmindedly.\n",
                 "Mengelin cuts his thigh slowly.\n",
                 "Mengelin cuts his ear silently.\n",
                 "Mengelin cuts his left nipple gracefully.\n",
                 "Mengelin cuts his sholder deeply.\n",
                 "Mengelin cuts his palm painfully.\n" }));
                 
  new("/d/Empire/islands/reikland/events/surgeon/surgeon-knife")->move(this_object());
  new("/d/Empire/islands/reikland/events/surgeon/surgeon-apron")->move(this_object());
  new("/d/Empire/islands/reikland/events/surgeon/remedy-bag")->move(this_object());                 
  command("wear all");
  command("wield all");
}
	