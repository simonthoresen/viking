#include <mudlib.h>

inherit I_ARMOUR;

void create() {
    ::create();
    set_name("Cloak of Devotion");
    set_short("a cloak with the mark of Khorne");
    set_long("The cloak has a large red mark embroided on it's back."); 
    add_property(({ "tagged", "hidden" }));
    set_value(10000);
    set_weight(1);
    set_ac(1);  
    set_type("cloak");
    add_hook("__wear", store_fp("on_wear"));
    add_hook("__bremove", store_fp("on_bremove"));
    set_wear_modifier("con", -4);
    set_wear_modifier("int", -4);
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
	tell_object(ply, "You do not want to remove the cloak.\n");
    }
    return 1;
}
