#include "/d/Empire/islands/matouci.h"

inherit MAT_DIR_EVENTS + "cerberus_hound/limb";

static void
create() 
{
    ::create();
    set_name("Cerberus' left head");
    set_limb("left head");
    set_short(0);
    set_long("It has eyes lit with fire, and brimstone drips from " +
             "its roaring mouth.");
    add_id(({ "head", "left head" }));
    set_level(29);
    set_wc(45);
    set_ac(0);
    set_hp(1000);
    set_aggressive(1);
    add_property("unarmed_damage_type", ({ "bite", "fire", "Fire" }));
    load_a_chat(25, ({ store_fp("breath_fire") }));
}

static void
breath_fire(object ply, object foe) 
{
    object env, *arr;
    int i, len;
    if (!objectp(env = environment(ply)) || !objectp(foe)) {
        return;
    }
    tell_room(env, "\n%^B_RED%^%^L_YELLOW%^" + ply->query_name() + 
              " breathes fire!%^END%^\n\n");
    for (i = 0, len = sizeof(arr = all_inventory(env)); i < len; ++i) {
        if (!objectp(foe = arr[i]) || !living(foe) || foe->is_cerberus()) {
            continue;
        }
        EMP_D_COMBAT->hit_player(ply, foe, 69 + random(69), "fire");
    }
}
