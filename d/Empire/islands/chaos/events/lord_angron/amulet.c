#include <mudlib.h>

inherit I_ARMOUR;

void warp(object ply);
void intoxicate(object ply);
void unintoxicate(object ply);
void heal(object ply);
void hurt(object ply);
void shatter(object ply);
void confuse(object ply);
void confuse_more(object ply, int val);

void create() {
    ::create();
    set_name("Amulet of Chaos");
    set_short("a bloodied amulet of bone");
    set_long("An amulet made of bloodied bone. The air around it pulsates " +
             "with magic.");
    set_type("amulet");
    add_property(({ "hidden", "tagged" }));
    set_value(2000);
    set_weight(1);
    set_ac(1);  
    add_hook("__wear", store_fp("on_wear"));
    set_wear_modifier("devotion_khorne", 10);
}  

void on_wear(int silent, object obj) {
    object ply;
    if (!objectp(ply = query_worn_by()) || !interactive(ply)) {
        return;
    }
    switch(random(8)){
    case 0:
        warp(ply);
        break;
    case 1:
        intoxicate(ply);
        break;
    case 2:
        unintoxicate(ply);
        break;
    case 3:
        hurt(ply);
        break;
    case 4:
        heal(ply);
        break;
    case 5:
        confuse(ply);
        break;
    case 6..7:
        shatter(ply);
        break;
    }
}

void warp(object ply) {
    int val;
    val = ply->query_alignment();
    if (val > 500){
        tell_object(ply, "As you put on the amulet, you feel like you turn " +
                    "your conciousness to the dark side of your " +
                    "personality.\n");
        ply->add_alignment(-2 * val);
    } else if (val < -500) {
        tell_object(ply, "Argh, the amulet draws you away from your evil " +
                    "ways, and you become a good person.\n");
        ply->add_alignment(-2 * val);
    } else {
        tell_object(ply, "You feel something changing inside you.\n");
        ply->add_alignment(random(2000) - 1000);
    }
}


void intoxicate(object ply) {
    tell_object(ply, "You scream in torment as you feel yourself becoming " +
                "filled to the utmost limits.\n");
    ply->add_stuffed(100);
    ply->add_soaked(100);
    ply->add_intoxication(100);
}

void unintoxicate(object ply) {
    tell_object(ply, "You feel empty. Very empty. Maybe you should go get " +
                "a meal?\n");
    ply->add_stuffed(-(int)ply->query_stuffed() / 3);
    ply->add_soaked(-(int)ply->query_soaked() / 3);
    ply->add_intoxication(-(int)ply->query_intoxication());
}

void heal(object ply) {
    tell_object(ply, "You feel life streaming from the amulet into you.\n");
    ply->heal_self(400);
}

void hurt(object ply) {
    tell_object(ply, "A strong force sucks your life away.\n");
    ply->reduce_hit_point(400);
    ply->reduce_spell_point(400);
}

void confuse(object ply) {
    tell_object(ply, "As you put the amulet on, you get dizzy.\n");
    confuse_more(ply, 1);
}

void confuse_more(object ply, int val) {
    string mod;
    if (!objectp(ply)) {
        return;
    }
    ply->remove_modifier("confuse:str"); 
    ply->remove_modifier("confuse:dex"); 
    ply->remove_modifier("confuse:int"); 
    ply->remove_modifier("confuse:con");
    if (!objectp(ply = query_worn_by())) {
        return;
    }
    mod = ({ "str", "dex", "con", "int" })[random(4)];
    ply->set_modifier("confuse:" + mod, mod, "special", 5 * val, 0);
    call_out("confuse_more", val > 0 ? 3 : 4, ply, val > 0 ? -1 : 1);
}

void shatter(object ply) {
    tell_object(ply, "As you wear the amulet, it shatters.\n");
    destroy(1);
}
