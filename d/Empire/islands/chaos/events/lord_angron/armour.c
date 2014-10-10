#include <mudlib.h>

inherit I_ARMOUR;

void create() {
    ::create();
    set_name("Armour of Khorne");
    set_short("a completely smooth, and pitch black steel-platemail");
    set_long("This frightening looking body armour is used by the followers " +
             "of Khorne. It is known to become a part of the wearer if " +
             "worn.");
    add_id(({ "platemail", "steel-platemail", "plate", "chaos armour" }));
    add_property(({ "steel", "hidden", "tagged"}));
    add_property("protected", 99);
    set_value(5000);
    set_weight(3);
    set_ac(4);  
    set_type("armour");
    add_hook("__wear", store_fp("on_wear"));
    add_hook("__bremove", store_fp("on_bremove"));
    set_wear_modifier("devotion_khorne", 10);
    set_wear_modifier("resist_slash", 10);
    set_wear_modifier("resist_blunt", 10);
    set_wear_modifier("resist_pierce", 10);
    set_wear_modifier("resist_chop", 10);
    set_wear_modifier("resist_claw", 10);
    set_wear_modifier("resist_bite", 10);
    set_wear_modifier("resist_fire", 10);
    set_wear_modifier("resist_cold", 10);
    set_wear_modifier("resist_electricity", 10);
    set_wear_modifier("resist_impact", 10);
    set_wear_modifier("resist_drain", 10);
    set_wear_modifier("resist_acid", 10);
    set_wear_modifier("resist_magic", 10);
}  

void on_wear(int silent, object obj) {
    object ply;
    if (!objectp(ply = query_worn_by()) ||
        !interactive(ply)) 
    {
        return;
    }
    tell_object(ply, "As you put the armour on, you feel enormous pain as " +
                "the armour grows stuck to you!\n");
}

int on_bremove(int silent) {
    object ply;
    if (!objectp(ply = query_worn_by()) ||
        !interactive(ply)) 
    {
        return 0;
    }
    tell_object(ply, "You fail.\n");
    return 1;
}
