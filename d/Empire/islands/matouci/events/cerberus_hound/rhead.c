#include "/d/Empire/islands/matouci.h"

inherit MAT_DIR_EVENTS + "cerberus_hound/limb";

static void
create() 
{
    ::create();
    set_name("Cerberus' right head");
    set_limb("right head");
    set_short(0);
    set_long("It has glowing white eyes, and lightning spews from its mouth.");
    add_id(({ "head", "right head" }));
    set_level(29);
    set_wc(45);
    set_ac(0);
    set_hp(1000);
    set_aggressive(1);
    add_property("unarmed_damage_type", ({ "bite", "electricity" }));
    load_a_chat(25, ({ store_fp("shock_player") }));
}

static void 
shock_player(object ply, object foe) 
{
    object env, *arr;
    int i, len;
    if (!objectp(env = environment(ply)) || !objectp(foe)) {
        return;
    }
    tell_room(env, "\n%^B_BLUE%^%^BOLD%^%^WHITE%^" + ply->query_name() + 
              " spews lightning!%^END%^\n\n");
    for (i = 0, len = sizeof(arr = all_inventory(env)); i < len; ++i) {
        if (!objectp(foe = arr[i]) || !living(foe) || foe->is_cerberus()) {
            continue;
        }
        if (EMP_D_COMBAT->hit_player(ply, foe, 16 + random(16), "electricity") > 10) {
            EMP_D_COMBAT->stun_player(foe, 1 + random(2));
        }
    }
}
