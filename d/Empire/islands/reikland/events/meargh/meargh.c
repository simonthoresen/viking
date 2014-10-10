#include "/d/Empire/islands/reikland.h"

inherit RED_DIR_OBJ + "fimir";

static void
create() 
{
    ::create();
    set_name("Meargh");
    set_short("a fimir meargh");
    set_long("She is roughly humanoid, with a great barrel-like chest, short " +
             "powerful legs ending in three-toed clawed feet, and long " +
             "sinewy arms which reach almost to the ground. She has " +
             "three small horns growing from the side of her head that is " +
             "otherwise covered in lank, greasy blue-black hair.");
    add_id("fimir meargh");
    set_female();
    set_level(27);
    set_str(50);
    set_dex(50);  
    set_con(100);  
    set_int(100);  
    set_al(-500);
    set_hp(3750);
    set_sp(1500);
    set_wc(30);     
    set_ac(19);     
    set_aggressive(1);
    set_scary(1);
    set_bored_secs(300);
    load_a_chat(66, ({
        store_fp("tail_attack"),
        store_fp("do_cloud"),
        store_fp("do_coldball"),
        store_fp("do_darkball"),
        store_fp("do_fireball"),
        store_fp("do_frenzy"),
        store_fp("do_regen"),
    }));
    EMP_D_WEAPON->add_unique(parse_path("hammer"), 150);
    EMP_D_ARMOUR->add_armour(75 + random(25));
    EMP_D_ARMOUR->add_armour(50 + random(25));
}

static void
do_cloud(object ply, object foe) 
{
    object *arr, env;
    int i, len;
    if (!objectp(env = environment()) ||
        !arrayp(arr = query_attackers())) 
    {
	return;
    }
    tell_room(env, "%^B_BLUE%^%^BOLD%^THE MEARGH " +
              "CALLS FORTH A LIGHTNING STORM!%^END%^\n");
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        EMP_D_COMBAT->hit_player(ply, arr[i], 35 + random(35), 
                                 "electricity", 0, "spell");
    }
}

static void
do_coldball(object ply, object foe) 
{
    object env;
    if (!objectp(env = environment(ply))) {
	return;
    }
    tell_room(env, "%^B_BLUE%^The meargh casts a cold-ball!%^END%^\n");
    EMP_D_COMBAT->hit_player(ply, foe, 20 + random(80), "Cold");
}

static void
do_darkball(object ply, object foe) 
{
    object env;
    if (!objectp(env = environment(ply))) {
	return;
    }
    tell_room(env, "%^B_GREY%^%^BLACK%^The meargh casts a dark-ball!%^END%^\n");
    EMP_D_COMBAT->hit_player(ply, foe, 25 + random(50), "drain");
}

static void
do_fireball(object ply, object foe) 
{
    object env;
    if (!objectp(env = environment(ply))) {
	return;
    }
    tell_room(env, "%^B_RED%^%^L_YELLOW%^The meargh casts a " +
              "fire-ball!%^END%^\n");
    EMP_D_COMBAT->hit_player(ply, foe, 20 + random(80), "Fire");
}

static void
do_frenzy(object ply, object foe) 
{
    object env;
    int i, len;
    if (!objectp(env = environment(ply))) {
	return;
    }
    tell_room(env, bold("The meargh suddenly attacks with great speed!\n"));
    for (i = 0, len = 2 + random(3); i < len; ++i) {
        attack();
    }
}

static void
do_regen(object ply, object foe) 
{
    object env;
    if (!objectp(env = environment(ply))) {
	return;
    }
    tell_room(env,"The fimir's wounds mend.\n");
    heal_self(25 + random(25));
}

