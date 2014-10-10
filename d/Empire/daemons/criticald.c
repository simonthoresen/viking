#include "/d/Empire/empire.h"

#define MIN_DAMAGE      25
#define CRIT_CHANCE     20
#define MAX_HP_PERCENT  80
#define YOUHIT_DELAY     1
#define HITYOU_DELAY     0

inherit I_DAEMON;

private mapping _arm;
private mapping _body;
private mapping _head;
private mapping _leg;

private mapping
read_table(string file)
{
    string str, *arr, *hitter, *victim, *others;
    int i, len;
    if (!stringp(str = read_file(file))) {
        return 0;
    }
    hitter = ({ });
    victim = ({ });
    others = ({ });
    arr = explode(str, "\n");
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        hitter += ({ arr[i++] });
        victim += ({ arr[i++] });
        others += ({ arr[i++] });
    }
    return ([ "hitter" : hitter,
              "victim" : victim,
              "others" : others ]);
}

private mapping
query_table(string loc)
{
    string *arr;
    if (!stringp(loc) || !arrayp(arr = explode(loc, " "))) {
        return _body;
    }
    switch (arr[sizeof(arr) - 1]) {
    case "cheek":
    case "chin":
    case "eye":
    case "head":
    case "neck":
    case "nose":
        return _head;

    case "body":
    case "torso":
    case "back":
    case "stomach":
    case "waist":
        return _body;

    case "arm":
    case "shoulder":
    case "arms":
    case "hand":
    case "hands":
    case "finger":
    case "fingers":
    case "thumb":
    case "forearm":
        return _arm;

    case "calf":
    case "feet":
    case "foot":
    case "leg":
    case "legs":
    case "thigh":
    case "toe":
    case "toes":
        return _leg;

    default:
        return _body;
    }
}

static void
create()
{
    ::create();
    _arm  = read_table(EMP_DIR_ETC + "criticals.arm");
    _body = read_table(EMP_DIR_ETC + "criticals.body");
    _head = read_table(EMP_DIR_ETC + "criticals.head");
    _leg  = read_table(EMP_DIR_ETC + "criticals.leg");
}

private string
query_cut_limb(object victim, string cut)
{
    string *arr;
    int i, len;
    if (!objectp(victim) || !stringp(cut)) {
        return 0;
    }
    if (!arrayp(arr = EMP_D_LIMB->query_limbs(victim))) {
        return 0;
    }
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        if (sscanf(arr[i], "%*s" + cut)) {
            return arr[i];
        }
    }
    return 0;
}

private int
perform_cut(object hitter, object victim, string arg)
{
    if (!objectp(hitter) || !objectp(victim) || !stringp(arg)) {
        return 0;
    }
    if (!stringp(arg = query_cut_limb(victim, arg))) {
        return 0;
    }
    if (!EMP_D_LIMB->cut_limb(victim, arg, hitter)) {
        return 0;
    }
    return 1;
}

private int
perform_die(object hitter, object victim)
{
    if (!objectp(hitter) || !objectp(victim)) {
        return 0;
    }
    if (!victim->query_dead()) {
        victim->hit_player(victim->query_hp() + 1, "Drain", hitter);
    }
    return 1;
}

private int
perform_wound(object hitter, object victim, int val)
{
    if (!objectp(hitter) || !objectp(victim)) {
        return 0;
    }
    if (!EMP_D_COMBAT->wound_player(hitter, victim, val)) {
        return 0;
    }
    return 1;
}

private int
perform_stun(object hitter, object victim, int val)
{
    if (!objectp(hitter) || !objectp(victim)) {
        return 0;
    }
    if (!EMP_D_COMBAT->stun_player(victim, val, hitter)) {
        return 0;
    }
    return 1;
}

private int
perform_drop(object hitter, object victim, int arg)
{
    int i, dmg;
    if (!objectp(hitter) || !objectp(victim)) {
        return 0;
    }
    if (arg < 0) {
        arg = -arg;
        dmg = 1;
    } else {
        dmg = 0;
    }
    for (i = 0; i < arg; ++i) {
        object obj;
        if (!objectp(obj = victim->query_weapon(i))) {
            continue;
        }
        if (dmg) {
            obj->wear_out(666, "blunt");
        }
        if (!objectp(obj) || !obj->unwield(1)) {
            continue;
        }
        victim->drop_one_item(obj);
    }
    return 1;
}

private int
perform_critical(object hitter, object victim, string *arr)
{
    int i, len;
    if (!objectp(hitter) || !objectp(victim) || !arrayp(arr)) {
        return 0;
    }
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        string str;
        mixed arg;
        str = arr[i];
        if (sscanf(str, "CUT(%s)", arg)) {
            perform_cut(hitter, victim, (string)arg);
        } else if (str == "DIE") {
            perform_die(hitter, victim);
        } else if (sscanf(str, "DROP(%d)", arg)) {
            perform_drop(hitter, victim, (int)arg);
        } else if (sscanf(str, "STUN(%d)", arg)) {
            perform_stun(hitter, victim, (int)arg);
        } else if (sscanf(str, "WOUND(%d)", arg)) {
            perform_wound(hitter, victim, (int)arg);
        }
    }
    return i;
}

static int
can_perform(string arg, object victim)
{
    string str;
    if (sscanf(arg, "CUT(%s)", str)) {
        return EMP_D_LIMB->can_cut(victim, str);
    }
    if (sscanf(arg, "DROP(%*s)") &&
        victim->query_property("no_disarm"))
    {
        return 0;
    }
    return 1;
}

public int
hit_player(object hitter, object victim, int val, string loc)
{
    int idx;
    mapping dat;
    object env;
    string *arr;
    if (!objectp(hitter) || !mapp(dat = query_table(loc)) ||
        !objectp(victim) || !objectp(env = environment(hitter)))
    {
        return 0;
    }
    if (env->query_property("no_special_attack") ||
        victim->query_property(EMP_P_NOCRIT))
    {
        return 0;
    }
    val = (val < 0 ? 0 : (val > 99 ? 99 : val));
    idx = (sizeof(dat["victim"]) * val) / 100;
    arr = explode(dat["victim"][idx], "@");
    arr = filter_array(arr, "can_perform", this_object(), victim);
    if (sizeof(arr) <= 1) {
        return 0;
    }
    hitter->set_tmp_prop("last_crit_youhit", time());
    victim->set_tmp_prop("last_crit_hityou", time());
    if (hitter != victim) {
        message("youhit", format_message(dat["hitter"][idx] + "\n",
                                         hitter, victim), hitter);
    }
    message("combat", format_message(dat["others"][idx] + "\n",
                                     hitter, victim),
            env, ({ hitter, victim }));
    message("hityou", format_message(arr[0] + "\n", hitter, victim,
                                     hitter == victim), victim);
    perform_critical(hitter, victim, arr);
    return 1;
}

public int
damage_dealt(object hitter, object victim, int dmg, string loc)
{
    int hp, hpp, max, val;
    if (!objectp(victim) ||
        !objectp(present(hitter, environment(victim))) ||
        (victim->query_dead()) ||
        (dmg < MIN_DAMAGE) ||
        (random(100) > CRIT_CHANCE) ||
        (hp = victim->query_hp()) <= 0 ||
        (max = victim->query_max_hp()) <= 0 ||
        (hpp = (hp * 100) / max) > MAX_HP_PERCENT ||
        (hitter->query_tmp_prop("last_crit_youhit")) > time() - YOUHIT_DELAY ||
        (victim->query_tmp_prop("last_crit_hityou")) > time() - HITYOU_DELAY)
    {
        return 0;
    }
    if (!stringp(loc)) {
        loc = EMP_D_LIMB->query_random_limb(victim);
    }
    /* transform hpp from hp percentage left, to a 0-100 range */
    hpp = (hpp * 100) / MAX_HP_PERCENT;

    /* now calculate a badness value in 0-100 range, where 100 is death */
    val = ( 50 * dmg) / max + /* how much dmg in hit compared to max hp */
          (100 - hpp) / 2;    /* the more wounded, the worse the crit   */
    return hit_player(hitter, victim, val / 2 + random(val / 2), loc);
}
