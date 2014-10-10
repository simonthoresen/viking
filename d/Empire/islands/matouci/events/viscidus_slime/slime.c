#include "/d/Empire/empire.h"

#define DTYPE_MUNDANE   (({ "slash", "blunt", "pierce", \
                            "chop", "claw", "bite" }))
#define FROZEN_SLOW     1
#define FROZEN_FREEZE   16
#define FROZEN_SOLID    32
#define THAWED_BEATS    10
#define GLOB_COUNT      10
#define MAX_HP          1000

#define BONE_VOLLEY     5
#define POISON_SHOCK    3
#define TOXIN_CLOUDS    7

inherit EMP_I_MONSTER;

private int _frozen;
private int _thawed;
private int _shock;
private int _volley;
private int _clouds;
private int _num_globs;

static void
create() 
{
    ::create();
    _frozen    = 0;
    _thawed    = 0;
    _shock     = 0;
    _volley    = 0;
    _clouds    = 0;
    _num_globs = GLOB_COUNT;

    set_name("Viscidus");
    set_short("the DEADLY Viscidus slime");
    set_long("Apart from the skull face and glaring red eyes, this monster " +
             "resembles a thick, viscous lump of green sludge.");
    add_id(({ "slime", "deadly slime" }));

    set_no_corpse(1);
    set_level(29);
    set_aggressive(1);
    set_hp(MAX_HP);
    set_wc(66);
    set_scary(1);
    set_bored_secs(300);
    add_property("unarmed_damage_type", ({ "acid", "bite" }));

    add_hook("__heart_beat", store_fp("on_heart_beat"));
    add_hook("__hit_player", store_fp("on_hit_player"));
    add_hook("__short", store_fp("on_short"));
    add_hook("__die", store_fp("on_die"));
}

private object
create_slime() 
{
    object obj;
    obj = new(EMP_C_LIQUID);
    obj->set_name("slime");
    obj->set_long("It smells of rotten eggs!");
    obj->set_color("%^B_GREEN%^%^BLACK%^");
    obj->set_amount(25);
    return obj;
}

private int
create_globs(object env) 
{
    object *arr;
    int i;
    if (!objectp(env) || _num_globs < 2) {
        return 0;
    }
    tell_room(env, "%^B_GREEN%^%^BLACK%^Viscidus explodes in an orgy of " +
	      "ooze and slime!%^END%^\n");
    EMP_D_COMBAT->spray_liquid(env, create_slime(), ({ this_object() }));
    arr = ({ });
    for (i = 0; i < _num_globs; ++i) {
	arr += ({ make(resolve_path("glob"), env) });
    }
    arr->set_globs(arr);
    return 1;
}

static string
on_short() 
{
    if (_frozen < FROZEN_SOLID) {
        return 0;
    }
    return "(frozen solid)";
}

static void 
bone_volley(object env, object foe) 
{
    if (!objectp(env) || !objectp(foe)) {
        return;
    }
    tell_room(env, "%^B_RED%^%^L_YELLOW%^Viscidus releases a " +
              "volley of bone fragments.%^END%^\n");
    map_array(filter_array(all_inventory(env), "isplayer", FILTER_OB),
              "apply_volley", this_object());
}

public void
apply_volley(object foe) 
{
    object ply;
    if (!objectp(ply = this_object()) || !objectp(foe) ||
        EMP_D_COMBAT->hit_player(ply, foe, 10 + random(25),
                                 "pierce", 0, "bone fragment") <= 0)
    {
        return;
    }
    EMP_D_COMBAT->wound_player(ply, foe, 25 + random(50));
}

static void
poison_shock(object env, object foe) 
{
    if (!objectp(env) || !objectp(foe)) {
        return;
    }
    tell_room(env, "%^B_YELLOW%^%^RED%^Viscidus blasts the " +
              "room with a poisonous shockwave.%^END%^\n");
    map_array(filter_array(all_inventory(env), "isplayer", FILTER_OB),
              "apply_shock", this_object());
}

public void
apply_shock(object foe) 
{
    object ply;
    if (!objectp(ply = this_object()) || !objectp(foe)) {
        return;
    }
    EMP_D_COMBAT->hit_player(ply, foe, 35 + random(35), 
                             "acid", 0, "poison shock"); 
}

static void
toxin_clouds(object env, object foe) 
{
    if (!objectp(env) || !objectp(foe)) {
        return;
    }
    tell_room(env, "%^B_MAGENTA%^%^YELLOW%^Viscidus coughs " +
              "up toxin clouds!%^END%^\n");
    map_array(filter_array(all_inventory(env), "isplayer", FILTER_OB),
              "apply_clouds", this_object());
}

public void
apply_clouds(object foe) 
{
    object ply;
    if (!objectp(ply = this_object()) || !objectp(foe) ||
        EMP_D_COMBAT->hit_player(ply, foe, 25 + random(25), 
                                 "drain", 0, "toxin clouds") <= 0) 
    {
        return;
    }
    ply->set_busy_next_round();
}

private void
on_fight_beat(object env, object foe) 
{
    if (!objectp(env) || !objectp(foe)) {
        return;
    }
    if (_frozen < FROZEN_SLOW) {
        if (++_volley >= BONE_VOLLEY) {
            bone_volley(env, foe);
            _volley = 0;
        }
        attack();
        attack();
    } 
    if (_frozen < FROZEN_FREEZE) {
        if (++_shock >= POISON_SHOCK) {
            poison_shock(env, foe);
            _shock = 0;
        }
        attack();
        attack();
    }
    if (_frozen < FROZEN_SOLID) {
        if (++_clouds >= TOXIN_CLOUDS) {
            toxin_clouds(env, foe);
            _clouds = 0;
        }
        attack();
    } 
}

private void 
on_frozen_beat(object env) 
{
    if (!objectp(env)) {
        return;
    }
    ++_thawed;
    if (_thawed < THAWED_BEATS) {
        set_busy_next_round("Viscidus is thawing.\n");
    } else {
        tell_room(env, "%^BOLD%^Viscidus comes back to life!%^END%^\n");
        _frozen = 0;
        _thawed = 0;
    }
}

static void
on_heart_beat() 
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    if (_frozen < FROZEN_SOLID) {
        object foe;
        if (objectp(foe = query_attack())) {
            on_fight_beat(env, foe);
        }
    } else {
        on_frozen_beat(env);
    }
}

static int 
on_hit_player(int dmg, string dtype, object foe, string loc, int prot,
              int resist, int vuln, int ac, object weapon) 
{
    object env;
    if (!objectp(env = environment()) || dmg <= 0) {
        return 0;
    }
    dtype = lower_case(dtype);
    if ((_frozen >= FROZEN_SOLID && member_array(dtype, DTYPE_MUNDANE) < 0) ||
        (_frozen <  FROZEN_SOLID && dtype != "cold")) 
    {
        tell_room(env, "Viscidus is not affected by the " + dtype + ".\n");
        return -dmg;
    }
    if (_frozen >= FROZEN_SOLID) {
        return 0;
    }
    ++_frozen;
    if (_frozen == FROZEN_SLOW) {
        tell_room(env, "%^BOLD%^Viscidus begins to slow!%^END%^\n");
    } else if (_frozen == FROZEN_FREEZE) {
        tell_room(env, "%^BOLD%^Viscidus begins to freeze!%^END%^\n");
    } else if (_frozen == FROZEN_SOLID) {
        tell_room(env, "%^B_BLUE%^%^WHITE%^Viscidus is frozen solid!%^END%^\n");
    }
    return -(dmg * 9) / 10;
}


static void
on_die(object corpse, object foe) 
{
    object env, obj;
    if (!objectp(foe) || !objectp(env = environment(foe))) {
	return;
    }
    if (create_globs(env)) {
        return; /* not done yet */
    }
    if (objectp(obj = D_TREASURE->get_unique(resolve_path("ring")))) {
        obj->move(env);
    } else {
        EMP_D_TREASURE->add_treasure(10000, env);
    }
    if (objectp(foe)) {
	EMP_D_ACHIEVEMENT->unlock(foe, "viscidus_slime");
    }
}

public void
set_frozen(int val) 
{
    _frozen = val;
}

public int
query_frozen() 
{
    return _frozen;
}

public void
set_thawed(int val) 
{
    _thawed = val;
}

public int
query_thawed() 
{
    return _thawed;
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
