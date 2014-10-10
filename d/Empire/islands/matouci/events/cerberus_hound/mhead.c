#include "/d/Empire/islands/matouci.h"

inherit MAT_DIR_EVENTS + "cerberus_hound/limb";

static void
create() 
{
    ::create();
    set_name("Cerberus' middle head");
    set_limb("middle head");
    set_short(0);
    set_long("It has bright yellow eyes, and teeth that are razor sharp.");
    add_id(({ "head", "middle head" }));
    set_level(29);
    set_wc(45);
    set_ac(0);
    set_hp(1000);
    set_aggressive(1);
    add_property("unarmed_damage_type", ({ "bite" }));
    load_a_chat(25, ({ store_fp("wound_player") }));
}

static void
wound_player(object ply, object foe) 
{
    object env, *arr;
    int i, len;
    if (!objectp(env = environment(ply)) || !objectp(foe)) {
        return;
    }
    tell_object(foe, "\n%^B_MAGENTA%^%^L_YELLOW%^" + ply->query_name() + 
                " crashes into you!%^END%^\n\n");
    tell_room(env, "\n%^B_MAGENTA%^%^L_YELLOW%^" + ply->query_name() + 
              " crashes into " + foe->query_name() + "!%^END%^\n\n", ({ foe }));
    if (EMP_D_COMBAT->hit_player(ply, foe, 32 + random(32), "Bite") > 0) {
        EMP_D_COMBAT->wound_player(ply, foe, 69);
    }
}
