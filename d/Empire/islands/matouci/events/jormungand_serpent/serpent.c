#include "/d/Empire/islands/matouci.h"

#define REQUIRED_PLAYERS   (3)
#define REWARD_DURATION    (24 * 60 * 30)
#define GLOB_COUNT         (10)
#define MAX_HP             (100000)

inherit EMP_I_MONSTER;

private int _num_globs;

static void 
create() 
{
    ::create();
    _num_globs = GLOB_COUNT;

    set_name("Jormungand's head");
    set_short("the HEAD of Jormungand");
    set_long("The head of the serpent is as big as a house, its jaws lined " +
             "with fangs the size of a man. The serpent's maw is an opening " +
             "into an insatiable dread, bellowing balls of hellfire and " +
             "burning aether.");
    add_id(({ "head of jormungand", "head" }));
    set_log_file("jormungand");
    set_no_corpse(1);
    set_level(29);
    set_aggressive(1);
    set_hp(MAX_HP);
    set_wc(66);
    set_scary(1);
    set_bored_secs(300);
    set_wandering_time(10);
    set_wandering_chance(75);
    add_property("unarmed_damage_type", ({ "bite", "pierce", "slash" }));

    add_hook("__damage_dealt", store_fp("on_damage_dealt"));
    add_hook("__destroy", store_fp("on_destroy"));
    add_hook("__die", store_fp("on_die"));
    add_hook("__hit_player", store_fp("on_hit_player"));
    add_hook("__move", store_fp("on_move"));

    load_a_chat(50, ({ store_fp("do_aether"),
                       store_fp("do_eat"),
                       store_fp("do_hellfire"),
                       store_fp("do_stun"),
                       store_fp("do_throw"),
                       store_fp("do_wound") }));
}

static void
do_aether(object ply, object foe) 
{
    object env, *arr;
    int i, len;
    if (!objectp(foe) || !objectp(env = environment())) {
        return;
    }
    tell_room(env, "%^B_MAGENTA%^%^YELLOW%^Jormungand bathes the room in " +
              "aether!\n%^END%^");
    for (i = 0, len = sizeof(arr = all_inventory(env)); i < len; ++i) {
        object obj;
        if (!objectp(obj = arr[i]) || !living(obj) || obj->is_jormungand()) {
            continue;
        }
        EMP_D_COMBAT->hit_player(ply, obj, 25 + random(25), "acid");
        EMP_D_COMBAT->hit_player(ply, obj, 25 + random(25), "drain");
        EMP_D_COMBAT->hit_player(ply, obj, 25 + random(25), "magic");
    }
}

static void
do_eat(object ply, object foe) 
{
    object env;
    string limb;
    if (!objectp(foe) || !objectp(env = environment()) ||
        !stringp(limb = EMP_D_LIMB->query_random_limb(foe, 0)) ||
        EMP_D_COMBAT->hit_player(ply, foe, 25 + random(25), "bite") < 25) 
    {
        return;
    }
    foe->command("scream ago");
    if (!EMP_D_LIMB->cut_limb(foe, limb)) {
        return;
    }
    EMP_D_COMBAT->wound_player(ply, foe, 25 + random(25)); 
}

static void
do_hellfire(object ply, object foe) 
{
    object env, *arr;
    int i, len;
    if (!objectp(foe) || !objectp(env = environment())) {
        return;
    }
    tell_room(env, "%^B_RED%^%^YELLOW%^Jormungand bathes the room in " +
              "hellfire!\n%^END%^");
    for (i = 0, len = sizeof(arr = all_inventory(env)); i < len; ++i) {
        object obj;
        if (!objectp(obj = arr[i]) || !living(obj) || obj->is_jormungand()) {
            continue;
        }
        EMP_D_COMBAT->hit_player(ply, obj, 25 + random(25), "acid");
        EMP_D_COMBAT->hit_player(ply, obj, 25 + random(25), "electricity");
        EMP_D_COMBAT->hit_player(ply, obj, 25 + random(25), "fire");
    }
}

static void
do_stun(object ply, object foe) 
{
    object env;
    if (!objectp(foe) || !objectp(env = environment())) {
        return;
    }
    tell_room(env, "Jormungand SLAMS its head down on " + foe->query_name() + 
              ".\n", ({ foe }));
    tell_object(foe, "\n\nOOOOOOOOOOOOUCH!\n\n\nJormungand SLAMS its head " +
		"down on you.\n");
    if (EMP_D_COMBAT->hit_player(ply, foe, 25 + random(25), "impact") < 25) {
        return;
    }
    EMP_D_COMBAT->stun_player(foe, 2 + random(4));
}

static void
do_throw(object ply, object foe) 
{
    object env;
    if (!objectp(foe) || !objectp(env = environment())) {
        return;
    }
    tell_room(env, "Jormungand RAMS its head into " + foe->query_name() + 
              ".\n", ({ foe }));
    tell_object(foe, "\n\nOOOOOOOOOOOOUCH!\n\n\nJormungand RAMS its head " +
                "into you.\n");
    if (EMP_D_COMBAT->hit_player(ply, foe, 25 + random(25), "impact") < 25) {
        return;
    }
    EMP_D_COMBAT->throw_player(foe, 1 + random(3));
}

static void
do_wound(object ply, object foe) 
{
    object env;
    if (!objectp(foe) || !objectp(env = environment())) {
        return;
    }
    tell_room(env, "Jormungand's jaws open wide..\n");
    if (EMP_D_COMBAT->hit_player(ply, foe, 50 + random(50), "Bite") < 50) {
        return;
    }
    EMP_D_COMBAT->wound_player(ply, foe, 50 + random(50));
}

private int
create_globs(object env) 
{
    object *arr;
    int i;
    if (!objectp(env) || _num_globs < 2) {
        return 0;
    }
    tell_room(env, "%^B_RED%^%^L_YELLOW%^Jormungand explodes in an orgy of " +
	      "blood and gore!%^END%^\n");
    EMP_D_COMBAT->spray_blood(env, 69, ({ this_object() }));
    arr = ({ });
    for (i = 0; i < _num_globs; ++i) {
	arr += ({ make(resolve_path("glob"), env) });
    }
    arr->set_globs(arr);
    return 1;
}

static void
reward_killer(object ply, int val) 
{
    object obj;
    string err;
    if (!objectp(ply) || !interactive(ply)) {
        return;
    }
    EMP_LOG("jormungand", "reward " + ply->query_real_name());
    obj = new(resolve_path("spirit"));
    obj->add_duration(val);
    if (stringp(err = catch(obj->move(ply)))) {
	EMP_LOG("jormungand", "error: " + err);
    }
}

private void
reward_kill(object *arr) 
{
    int len, val;
    EMP_LOG("jormungand", sprintf("reward %O", arr->query_real_name()));
    if ((len = sizeof(arr)) == 0) {
        return;
    }
    val = (REQUIRED_PLAYERS * REWARD_DURATION) / len;
    map_array(arr, "reward_killer", this_object(), val);
              
}

static void
on_damage_dealt(int dmg, string dtype, object foe, string loc) 
{
    int val;
    if (!objectp(foe) || !objectp(present(foe, environment()))) {
        return;
    }
    if (dtype == "bite") {
        EMP_D_COMBAT->wound_player(this_object(), foe, dmg);
    }
    EMP_D_CRITICAL->damage_dealt(this_object(), foe, dmg);
}

static void
on_die(object corpse, object foe) 
{
    object env, obj;
    if (!objectp(foe) || !objectp(env = environment(foe))) {
	return;
    }
    EMP_LOG("jormungand", sprintf("%O killed by %s, _num_globs = %d",
                                  this_object(), foe->query_real_name(),
                                  _num_globs));
    if (create_globs(env)) {
        return; /* not done yet */
    }
    EMP_LOG("jormungand", sprintf("%O deaded by %s", this_object(), 
                                  foe->query_real_name()));
    catch(resolve_path("event")->set_next_time(time() + 7 * 24 * 60 * 60));
    if (env != environment()) {
        return; /* no loot unless the head was killed */
    }
    reward_kill(filter_array(all_inventory(env), "isplayer", FILTER_OB));
    if (objectp(obj = D_TREASURE->get_unique(resolve_path("amulet")))) {
	obj->move(env);
    }
    if (objectp(obj = D_TREASURE->get_unique(resolve_path("con_ring")))) {
	obj->move(env);
    }
    if (objectp(obj = D_TREASURE->get_unique(resolve_path("dex_ring")))) {
	obj->move(env);
    }
    if (objectp(obj = D_TREASURE->get_unique(resolve_path("int_ring")))) {
	obj->move(env);
    }
    if (objectp(obj = D_TREASURE->get_unique(resolve_path("str_ring")))) {
	obj->move(env);
    }
    if (objectp(foe)) {
	EMP_D_ACHIEVEMENT->unlock(foe, "jormungand_serpent");
    }
}

static void
on_move(object from, object to) 
{
    string file;
    object obj;
    if (!objectp(to)) {
	return;
    }
    file = resolve_path("tail");
    if (objectp(obj = present(file, to))) {
	/* tail might be from previous phase, retag to avoid dest */
	obj->set_head(this_object()); 
	return;
    }
    obj = new(file);
    obj->set_head(this_object());
    obj->set_scary_id(source_file_name());
    obj->move_player(0, to);
}

static int
on_hit_player(int dmg, string dtype, object foe, string loc, 
              int prot, int res, int vuln, int ac, object wpn) 
{
    if (!objectp(foe) || environment(foe) != environment()) {
        return 0;
    }
    return dmg * 24;
}

public void
set_num_globs(int val) 
{
    _num_globs = val > GLOB_COUNT ? GLOB_COUNT : (val < 1 ? 1 : val);
    set_hp(MAX_HP);
    reduce_hit_point(((GLOB_COUNT - _num_globs) * MAX_HP) / GLOB_COUNT);
}

public int
query_num_globs() 
{
    return _num_globs;
}

public int
is_jormungand_head() 
{
    return 1;
}

public int
is_jormungand() 
{
    return 1;
}
