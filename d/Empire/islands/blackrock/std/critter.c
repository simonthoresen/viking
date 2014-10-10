#include "/d/Empire/islands/blackrock.h"

inherit EMP_I_MONSTER;

private int _dlevel;
private int _guard;

static void
init_dangerlevel(int val)
{
    /* inherit and implement */
}

static void
create()
{
    ::create();
    _dlevel = -1;
    _guard  = 0;

    set_name(replace_string(base_file_name(this_object()), "_", " "));
    set_aggressive(1);
    set_wandering_time(5);
    set_wandering_chance(25);
    set_wandering_hook(store_fp("follow_crumbs"));
    add_property("no_hero_quest");
    add_hook("__fight_beat", store_fp("maybe_cast"));
}

public void
set_name(string arg)
{
    ::set_name(capitalize(arg));
    set_short(add_article(lower_case(arg)));
}

public void
set_short(string arg)
{
    ::set_short(arg);
    set_long("This is " + arg + ".");
}

public void
set_dangerlevel(int val)
{
    if (_dlevel >= 0) {
        error("Danger level already set!");
    }
    if (val < 0) {
        val = 0;
    }
    if (val > 100) {
        val = 100;
    }
    set_level(25 + val / 10); /*   25 -   35 */
    set_wc(40 + val / 5);     /*   40 -   60 */
    set_ac(7 + val / 10);     /*   10 -   20 */
    set_hp(1000 + val * 5);   /* 1000 - 1500 */
    set_sp(1000 + val * 5);   /* 1000 - 1500 */

    add_property("dangerlevel", val);
    init_dangerlevel(val);
    _dlevel = val;
}

public int
query_dangerlevel()
{
    return _dlevel;
}

static mixed
follow_crumbs()
{
    int len;
    object env;
    string str, dst, *arr;
    if (!objectp(env = environment())) {
        return "scratch";
    }
    if (stringp(str = env->query_crumb()) &&
        stringp(dst = env->query_exit(str)) &&
        !dst->query_property("no_wander"))
    {
        _guard = 0;
        return str; /* follow player */
    }
    if (!_guard &&
        arrayp(arr = env->query_visible_exits()) &&
        (len = sizeof(arr)) > 0)
    {
        _guard = 1;
        return "guard " + arr[random(len)];
    }
    return "idle"; /* stay put */
}

static string
random_spell()
{
    if (random(100) > 25 + _dlevel / 4) {
        return 0;
    }
    switch (random(25 + _dlevel)) {
    case   0..  9: return "cast_heal";
    case  10.. 19: return "cast_attack";
    case  20.. 29: return "cast_dmg";
    case  30.. 39: return "cast_dot";
    case  40.. 49: return "cast_stun";
    case  50.. 54: return "cast_throw";
    case  55.. 69: return "cast_dmg_all";
    case  70.. 79: return "cast_dot_all";
    case  80.. 89: return "cast_stun_all";
    case  90.. 94: return "cast_throw_all";
    case  95..109: return "cast_dmg";
    case 110..119: return "cast_dot";
    case 120..124: return "cast_dmg_cap";
    default:       return 0;
    }
}

static void
maybe_cast(object foe)
{
    string str;
    if (!stringp(str = random_spell())) {
        return;
    }
    (BRD_DIR_OBJ + str)->main(this_object(), query_attack());
}
