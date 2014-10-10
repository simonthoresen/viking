#include "/d/Empire/islands/ruins.h"

#define P_VULNERABILITY ("runestone_vulnerability")

inherit RUN_I_MONSTER;

private void  do_count();
private void  do_shout(string str);
private void  maybe_spawn_shade();
private void  randomize_vulnerability();
private void  schedule_remove_vulnerability();
public  void  healed_by_shade();
public  void  remove_vulnerability();
public  void  runestone_destroyed();
public  void  spawn_shade(string *runestones, int runestone_idx);
static  mixed follow_crumbs();
static  void  on_die(object corpse, object killer);
static  void  on_heart_beat();
static  void  try_stun(object ply);

private int   _has_shades;
private int   _last_heal;
private int   _stun_countdown;

static void
create()
{
    ::create();
    _has_shades     = 1;
    _last_heal      = 0;
    _stun_countdown = FORNJOT_STUN_COUNTDOWN_BEATS;

    set_name("Fornjot");
    set_short("the ancient giant Fornjot");
    set_long("");
    set_level(66);
    set_bored_secs(300);
    set_wandering_chance(100);
    set_wandering_time(1);
    set_wandering_hook(store_fp("follow_crumbs"));
    add_property("unarmed_damage_type", "claw");
    add_hook("__heart_beat", store_fp("on_heart_beat"));
    add_hook("__hit_player", store_fp("on_hit_player"));
    add_hook("__die", store_fp("on_die"));
}

public void
healed_by_shade()
{
    _last_heal = time();
}

private void
do_count()
{
    --_stun_countdown;
    if (_stun_countdown >= 0 && _stun_countdown % 5 == 0) {
        do_shout(upper_case(convert_number(_stun_countdown)) + "!!");
    }
    if (_stun_countdown <= 0) {
        _stun_countdown = FORNJOT_STUN_COUNTDOWN_BEATS;
        map_array(RUN_ISLAND->query_livings(), "try_stun");
    }
}

static void
try_stun(object ply)
{
    if (!objectp(ply) || ply<-RUN_I_MONSTER) {
        return;
    }
    EMP_D_COMBAT->stun_player(ply, FORNJOT_STUN_DURATION_SECS,
                              this_object(), 1);
}

private void
do_shout(string str)
{
    command("shout %^B_MAGENTA%^%^L_YELLOW%^" +
            upper_case(str) + "%^END%^");
}

private void
maybe_spawn_shade()
{
    if (_has_shades && query_hp() < (10 * query_max_hp()) / 100) {
        _has_shades = 0;
        call_out("spawn_shade", FORNJOT_SHADE_SPAWN_DELAY,
                 RUN_ISLAND->find_all_map_type(RUN_MAP_RUNESTONE));
    }
}

public void
spawn_shade(string *runestones, int runestone_idx)
{
    if (runestone_idx >= sizeof(runestones)) {
        return;
    }
    make(RUN_C_FORNJOT_SHADE, runestones[runestone_idx]);
    call_out("spawn_shade", FORNJOT_SHADE_SPAWN_DELAY,
             runestones, runestone_idx + 1);
}

static void
on_heart_beat()
{
    do_count();
    maybe_spawn_shade();
}

static void
on_hit_player(int dmg, string type, object foe, string loc,
              int prot, int res, int vuln, int ac, object wpn)
{
    if (dmg <= 0 || _last_heal + FORNJOT_SHADE_INVULN_SECS < time()) {
        return 0;
    }
    tell_room(environment(), query_name() + " does not seem to be affected " +
              "by the " + WEAR_D->prot_message(lower_case(type)) + ".\n");
    return -dmg;
}

static void
on_die(object corpse, object killer)
{
    make(EMP_I_TOKEN, corpse)->add_amount(19);
}

static mixed
follow_crumbs()
{
    object env;
    string str, dst;
    if (objectp(env = environment()) &&
        stringp(str = env->query_crumb()) &&
        stringp(dst = env->query_exit(str)) &&
        !dst->query_property("no_wander"))
    {
        return str; /* follow player */
    }
    do_count();
    return "growl men"; /* stay put */
}

public void
runestone_destroyed()
{
    do_shout("UNNGGH!!! WHAT WAS THAT?");
    _stun_countdown = FORNJOT_STUN_COUNTDOWN_BEATS;
    randomize_vulnerability();
}

private void
randomize_vulnerability()
{
    string type;
    remove_vulnerability();
    type = ({ "slash", "pierce", "chop", "fire", "cold" })[random(5)];
    set_modifier("runestone_vulnerability", "vuln_" + type,
                 "magic", 100, 100);
    tell_room(environment(),
              bold("\n" + query_name() + " becomes vulnerable to " +
                   type + ".\n\n"));
    schedule_remove_vulnerability();
}

private void
schedule_remove_vulnerability()
{
    call_out_unique("remove_vulnerability", FORNJOT_VULNERABILITY_SECS);
}

public void
remove_vulnerability()
{
    mixed mod;
    string type;
    if (!arrayp(mod = query_modifier(P_VULNERABILITY)) ||
        !sscanf(mod[0], "vuln_%s", type))
    {
        return;
    }
    remove_modifier(P_VULNERABILITY);
    tell_room(environment(), query_name() + " is no longer " +
              "vulnerable to " + type + ".\n");
}
