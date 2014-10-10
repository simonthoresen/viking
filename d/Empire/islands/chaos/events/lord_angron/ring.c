#include <mudlib.h>

inherit I_ARMOUR;

void create() {
    ::create();
    set_name("Ring of Devotion");
    set_short("a ring with the mark of Khorne");
    set_long("The ring has a large red mark on it's front."); 
    add_property(({ "tagged", "hidden" }));
    set_value(5000);
    set_weight(1);
    set_ac(1);  
    set_type("ring");
    add_hook("__wear", store_fp("on_wear"));
    add_hook("__bremove", store_fp("on_bremove"));
    set_wear_modifier("str", -4);
    set_wear_modifier("dex", -4);
    set_wear_modifier("devotion_khorne", 25);
}  

void on_wear(int silent, object obj) {
    if (silent) {
        return;
    }
    tell_object(query_worn_by(), 
                "You feel your devotion to Khorne growing.\n");
}

int on_bremove(int silent) {
    object ply;
    if (!objectp(ply = query_worn_by()) ||
	!interactive(ply)) 
    {
	return 0;
    }
    if (!silent) {
	tell_object(ply, "You do not want to remove the ring.\n");
    }
    return 1;
}
