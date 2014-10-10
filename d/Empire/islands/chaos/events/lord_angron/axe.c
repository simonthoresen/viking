#include "/d/Empire/empire.h"

inherit I_WEAPON;

void create() {
    ::create();
    set_name("Axe of Khorne");  
    set_short("a huge axe covered with runes");
    set_long("The Axe of Khorne is only used by the most devoted and " +
             "powerful of Khornes champions. It has runes engraved all " +
             "over its surface, and you can barely hold it in your hands " +
             "due to the power it contains.");
    add_id("axe");
    set_class(20);
    set_value(10000); 
    set_weight(6);
    set_damage_type("chop");
    set_type("twohanded");
    set_break_chance(1);
    set_break_msg("The axe explodes in an inferno of flames.\n");
    set_broken_desc("This was once a truly amazing weapon."); 
    add_property(({ "tagged", "hidden" }));
    add_hook("__wield", store_fp("on_wield"));  
    add_hook("__remove", store_fp("on_remove"));
    add_hook("__weapon_hit", store_fp("on_weapon_hit"));
    set_wield_modifier("devotion_khorne", 10);
    set_wield_modifier("str", 3);
}

void on_wield(object obj, string hands) { 
    object ply;
    if (!objectp(ply = query_wield())) {
        return;
    }
    tell_object(ply, "You feel an awesome power going through your veins " +
                "as you wield the axe.\n");
}

void on_remove() {
    object ply;
    if (!objectp(ply = query_wield())) {
        return;
    }
    tell_object(ply, "What a shame it is to let this weapon slip away from " +
                "you.\n");
}

int on_weapon_hit(object foe) {
    object ply;
    int val;
    if (!objectp(ply = query_wield())) {
        return 0;
    }
    val = random(ply->query_tmp_prop("devotion_khorne"));
    switch (random(100) - (val / 4)) {
    case 0:
        EMP_D_CRITICAL->damage_dealt(ply, foe, 666);
        return 666;
    case 1..5:
        tell_object(ply, foe->query_name() + " screams as you almost chop a " +
                    "limb off!\n");
        tell_object(foe, ply->query_name() + " almost chops one of your " +
                    "limbs off!\n");
        tell_room(environment(ply), ply->query_name() + " almost chops one " + 
                  "of " + foe->query_name() + "'s limbs off!\n", 
                  ({ ply, foe }));
        return (200 * val) / (val + 10); /* 100 - 180 */
    case 6..10:
        tell_object(ply, "You scream: 'DIE DIE DIE!' as you swing the axe " +
                    "into " + foe->query_name() + "!\n");
        tell_object(foe, ply->query_name() + " screams: 'DIE DIE DIE!' and " +
                    "swings the axe into you!\n");
        tell_room(environment(ply), ply->query_name() +
                  " screams: 'DIE DIE DIE!' and swings the axe into " +
                  foe->query_name() + ".\n", ({ ply, foe }));
        return (100 * val) / (val + 10); /* 50 - 90 */
    default:
        return (50 * val) / (val + 10); /* 25 - 45 */
    }
}


