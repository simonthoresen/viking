/*
    This is an amulet which gives you +1 int.
    You will NOT get any extra SP from this +1 int.
    All new SP gained becouse of this int will be sucked
    away by the amulet and stored for later use.
    
    The amulet can store a certain amount of SP, anything above
    will just be wasted in space.
    
    You can kiss your amulet to retreive the SP stored
    in the amulet.
    
    Removing amulet will erase all SP in storage and player
    have to start over to save up SP.
    
                                             -+ Postkasse - 2011 +-
*/

#include <mudlib.h>

inherit I_ARMOUR;

int storage;
object wearer;

void update_long_desc();

void create() {
	::create();
	set_name("amulet");
	set_short("Gemmed silver amulet");
	set_long("This amulet is made of pure silver with a transparent crystal gem covered with silver engravings.");
	set_ac(1);
	set_weight(1);
	
	set_type("amulet");
	set_value(3000);
	storage = 0;
	
	set_wear_modifier("int", 1, 2);
	add_property(({"artifact","magic","silver","crystal","metal"}));
	
	add_hook("__wear",store_fp("amulet_worn"));
	add_hook("__remove",store_fp("amulet_removed"));
	
	add_item("engravings","Beautifull shapes in awesome details.\n");
	add_item("gem","The gem has a cirular shape and is transparent.\n");
	add_trigger("kiss",store_fp("do_kiss"));
	
	set_info("This amulet will connect to your mind.\n");
}

void heart_beat() { /* Heart Beat activated when amulet is worn */
	int sp_mod;
  if(!wearer) {
  	set_heart_beat(0);
  	storage = 0;
  	return;
  }
  /* Let's calculate how much sp above your max allowed with """int minus one""" you have */
  sp_mod = wearer->query_sp() - (((wearer->query_int()-1)*wearer->query_mult_sp()) + wearer->query_base_sp());
  if(sp_mod < 0) { sp_mod = 0; }
  storage = storage + sp_mod;
  wearer->reduce_spell_point(sp_mod);
  update_long_desc();
  if(storage >= 100) storage = 100;
  else { /* Only add amulet flashing if the storage is not full */
    switch(sp_mod){
    	case 1: message("info","Amulet flicker a bit.\n",wearer);
    	break;
    	case 2: message("info","Amulet flicker.\n",wearer);
    	break;
    	case 3: message("info","Amulet flicker with light.\n",wearer);
    	break;
    	case 4: message("info","Amulet pulses.\n",wearer);
    	break;
    	case 5: message("info","Amulet pulses with light.\n",wearer);
    	break;
    	case 6: message("info","Amulet pulse brightly.\n",wearer);
    	break;
    	case 7: message("info","Amulet flashes with light.\n",wearer);
    	break;
    	case 8: message("info","Amulet flashes with pure white light.\n",wearer);
    	break;
    	default:
    	break;
    }
  }
	return;
}

void amulet_worn() { /* Wear amulet */
	set_heart_beat(1);
	wearer = query_worn_by();
	return;
}

void amulet_removed() { /* Remove Amulet */
	set_heart_beat(0);
	message("info","The amulet loses it's glow.\n",wearer);
	message("info",wearer->query_name()+"'s amulet loses it's glow.\n",environment(wearer),wearer);
  set_long("This amulet is made of pure silver with a transparent crystal gem covered with silver engravings.");
	storage = 0;
	wearer = 0;
	return;
}

void destroy() { /* When amulet is destroyed */
	set_heart_beat(0);
}

int do_kiss(string arg) { /* When kissing amulet 100% of storage will be transfered to player and all storage erased */
	if(!storage) { return 0; }
  wearer->reduce_spell_point(-storage);
  message("info","As you kiss the amulet it loses it's glow, but you feel rejuvenated.\n",wearer);
	message("info","As "+wearer->query_name()+" kisses the amulet it loses it's glow.\n",environment(wearer),wearer);
  storage = 0;
  return 1;
}

void update_long_desc() { /* Update long_desc as storage get's filled with SP */
	
	switch(storage) {
		case 0..20: set_long("This amulet is made of pure silver with a transparent crystal gem covered with silver engravings.");
		break;
		case 21..40: set_long("This amulet is made of pure silver with a transparent %^RED%^dim%^END%^ crystal gem covered with silver engravings.");
		break;
		case 41..60: set_long("This amulet is made of pure silver with a transparent %^YELLOW%^glowing%^END%^ crystal gem covered with silver engravings.");
		break;
		case 61..80: set_long("This amulet is made of pure silver with a transparent %^L_YELLOW%^bright%^END%^ crystal gem covered with silver engravings.");
		break;
		case 81..99: set_long("This amulet is made of pure silver with a transparent %^BOLD%^white%^END%^ crystal gem covered with silver engravings.");
		break;
		case 100..108:    set_long("This amulet is made of pure silver with a transparent %^BOLD%^bright white%^END%^ crystal gem covered with silver engravings.");
		break;
		default:
		break;
	}	
	return;
}

int query_storage(){ /* Paranoia in case of problems */
  return storage;
}

object query_wearer() { /* Paranoia in case of problems */
	return wearer;
}