#include "/d/Empire/islands/reikland.h"

inherit EMP_I_MONSTER;

static void
create() 
{
    ::create();
    ::create();
    set_male();
    set_name("Lord Random");
    set_short("a peculiar looking man");
    set_long("A peculiar looking man. He is the infamous Lord Random, a " +
             "dreaded wizard that have long ago mastered the ancient powers " +
             "of magic.");
    add_id(({ "lord", "random","man"}));
    set_level(20 + random(10));
    set_str(10 + random(20));
    set_dex(10 + random(20));
    set_con(10 + random(20));
    set_int(10 + random(20));
    set_al(random(4000) - 2000);
    set_ac(random(30));
    set_wc(10 + random(20));
    set_hp(30 * query_level() + random(30 * query_level()));  
    set_scary(1);
    set_bored_secs(300);
    add_money(3000 + random(4000));
    add_property("unarmed_weapon_name", "magic");
    add_property("unarmed_damage_type", ({ "fire", "cold", "electricity",
                                           "drain", "acid", "magic" }));
    load_a_chat(25, ({ 
        store_fp("cast_heal"),
        store_fp("cast_bolt"), 
        store_fp("cast_storm"),
        store_fp("cast_meteor"),
        store_fp("cast_stun"),
        store_fp("cast_throw"),
        store_fp("cast_wound"),
        store_fp("cast_tear"),
    }));

    EMP_D_ARMOUR->add_unique(parse_path("boot"), 150);
    EMP_D_ARMOUR->add_unique(parse_path("cloak"), 150);
    EMP_D_WEAPON->add_weapon(150);
}

private string 
random_chant() 
{
    string str;
    str  = "Lord Random starts to ";
    str += ({ "gesture", "chant", "speak" })[random(3)] + " ";
    str += ({ "magically", "wildly", "an ancient ritual",
              "something unfamiliar"})[random(4)] + ".\n";
    str += "During the " + convert_ordinal_number(2 + random(5)) + " "; 
    str += ({ "movement", "strofe", "syllable" })[random(3)];
    return str;
}

private string
random_dtype() 
{
    return ({ "fire", "cold", "electricity", "acid", "magic" })[random(5)];
}

static void
cast_heal(object ply, object foe) 
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    tell_room(env, random_chant() + " he becomes healthier.\n");
    heal_self(50 + random(50));
}

static void
cast_bolt(object ply, object foe) 
{
    object env;
    string type;
    if (!objectp(foe) ||
        !objectp(env = environment())) 
    {
        return;
    }
    type = random_dtype();
    if (random(100) < 75) {
        tell_room(env, random_chant() + " he casts a " + type + "-bolt!\n");
    } else {
        tell_room(env, random_chant() + " he casts a " + type + "-ball!\n");
        type = capitalize(type);
    }
    EMP_D_COMBAT->hit_player(ply, foe, 25 + random(50), type);
}

static void
cast_storm(object ply, object foe) 
{
    object env, *arr;
    string type;
    int i, len;
    if (!objectp(env = environment()) ||
        !arrayp(arr = ply->query_attackers()) ||
        (len = sizeof(arr)) == 0) 
    {
        return;
    }
    type = random_dtype();
    tell_room(env, random_chant() + " he summons a " + type + "-storm!\n");
    for (i = 0; i < len; ++i) {
        EMP_D_COMBAT->hit_player(ply, arr[i], 25 + random(50), type);
    }
}

static void
cast_meteor(object ply, object foe) 
{
    object env, *arr;
    int i, len;
    if (!objectp(env = environment()) ||
        !arrayp(arr = ply->query_attackers()) ||
        (len = sizeof(arr)) == 0) 
    {
        return;
    }
    tell_room(env, random_chant() + " a METEOR crashes into the ground!\n");
    for (i = 0; i < len; ++i) {
        EMP_D_COMBAT->hit_player(ply, arr[i], 25 + random(25), "Impact");
        EMP_D_COMBAT->hit_player(ply, arr[i], 25 + random(25), "impact");
        EMP_D_COMBAT->hit_player(ply, arr[i], 25 + random(25), "impact");
        EMP_D_COMBAT->hit_player(ply, arr[i], 25 + random(25), "fire");
        EMP_D_COMBAT->hit_player(ply, arr[i], 25 + random(25), "fire");
    }
    for (i = 0; i < 5 + random(5); ++i) {
        make(parse_path("stone"), env);
    }
}

static void
cast_tear(object ply, object foe) 
{
    object env, *arr;
    int len;
    if (!objectp(foe) ||
        !objectp(env = environment()) || 
        !arrayp(arr = foe->query_worn_armour()) ||
        (len = sizeof(arr)) == 0) 
    {
        return;
    }
    tell_room(env, random_chant() + " pieces of shrapnel fly everywhere!\n");
    arr[random(len)]->wear_out(6699, "pierce");
}

static void 
cast_stun(object ply, object foe) 
{
    object env, *arr;
    int i, len;
    if (!objectp(env = environment()) ||
        !arrayp(arr = ply->query_attackers()) ||
        (len = sizeof(arr)) == 0) 
    {
        return;
    }
    tell_room(env, random_chant() + " he summons a BLINDING flash of light!\n");
    for (i = 0; i < len; ++i) {
        EMP_D_COMBAT->stun_player(arr[i], 1 + random(4));
    }
}

static void
cast_throw(object ply, object foe) 
{
    object env, *arr;
    int i, len;
    if (!objectp(env = environment()) ||
        !arrayp(arr = ply->query_attackers()) ||
        (len = sizeof(arr)) == 0) 
    {
        return;
    }
    tell_room(env, random_chant() + " the room is hit by a strong wind!\n");
    for (i = 0; i < len; ++i) {
        EMP_D_COMBAT->throw_player(arr[i], 1 + random(4));
    }
}

static void
cast_wound(object ply, object foe) 
{
    object env, *arr;
    int i, len;
    if (!objectp(env = environment()) ||
        !arrayp(arr = ply->query_attackers()) ||
        (len = sizeof(arr)) == 0) 
    {
        return;
    }
    tell_room(env, random_chant() + " razorblades shoot around the room!\n");
    for (i = 0; i < len; ++i) {
        EMP_D_COMBAT->wound_player(ply, arr[i], 50 + random(100));
    }
}
