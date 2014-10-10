#include "/d/Empire/empire.h"

inherit EMP_I_MONSTER;

private string *_mirror;
private mapping _glitch;

static void
create() 
{
    object obj;
    ::create();
    _mirror = ({ });
    _glitch = ([ ]);

    set_male();
    set_race("human");
    set_name("Krugan");
    set_short("a strangely malformed man");
    set_long("A strangely malformed man. Something gives you a very creepy " +
             "feeling about this being. You feel that he is not an ordinary " +
             "man, but rather some strange, perverted creation of the powers " +
             "of evil. He has pitch black eyes.");
    add_id(({ "man", "malformed man" }));
    set_level(29);
    set_hp(2222);
    set_al(0);
    load_a_chat(25, ({ store_fp("do_regen") }));
    add_hook("__bnotify_attack", store_fp("mirror_foe"));
    add_hook("__battack", store_fp("select_dtype"));
    add_hook("__hit_player", store_fp("improve_self"));
    if (objectp(obj = EMP_D_WEAPON->add_unique(parse_path("knife"), 150, 
                                               "onehanded"))) 
    {
        command("unwield all");
        command("wield " + obj->query_name() + " in left hand");
    }
}

static void
do_regen(object ply, object foe) 
{
    heal_self(22);
}

private int
try_glitch(object foe, string next) 
{
    string prev, name, type;
    if (!objectp(foe) || 
        !stringp(name = foe->query_real_name()) ||
        !stringp(next) || 
        !sscanf(next, "vuln_%s", type)) 
    {
        return 0;
    }
    if (!stringp(prev = _glitch[name]) ||
        foe->query_skill(next) > foe->query_skill("vuln_" + prev)) 
    {
        _glitch[name] = type;
    }
    return 1;
}

static void
mirror_foe(object foe) 
{
    string name, key, *arr;
    mapping dat;
    object env;
    int i, len;
    if (!objectp(foe) || 
        !objectp(env = environment(foe)) ||
        !stringp(name = foe->query_real_name()) ||
        member_array(name, _mirror) >= 0)
    {
        return;
    }
    tell_object(foe, "\n\n\nKRUGAN'S BODY ALTERS TO MIRROR YOU!\n\n\n\n");
    tell_room(env, "Krugan's body alters to mirror " + 
              foe->query_name() + "!\n", ({ foe }));
    
    _mirror |= ({ name });
    set_str(query_str() + foe->query_str());
    set_dex(query_dex() + foe->query_dex());
    set_con(query_con() + foe->query_con());
    set_int(query_int() + foe->query_int());
    dat = foe->query_skill();
    for (i = 0, len = sizeof(arr = keys(dat)); i < len; ++i) {
        if (try_glitch(foe, key = arr[i])) {
            continue;
        }
        add_skill(key, max(0, query_skill(key) + dat[key]));
    }
    dat = foe->query_tmp_prop();
    for (i = 0, len = sizeof(arr = keys(dat)); i < len; ++i) {
        if (try_glitch(foe, key = arr[i])) {
            continue;
        }
        add_tmp_prop(key, dat[key]);
    }
    if (stringp(_glitch[name])) {
        command("tell " + name + " I know your weakness, mortal!");
    }
}

static void 
select_dtype(object foe) 
{
    object env;
    string val;
    if (!objectp(foe) ||
        !objectp(env = environment()) ||
        !stringp(val = _glitch[foe->query_real_name()]) ||
        val == query_property("unarmed_damage_type")) 
    {
        return;
    }
    tell_room(env, bold("Krugan's hands begin to radiate " + val + "!\n")); 
    add_property("unarmed_damage_type", val);
}

static int
improve_self(int dmg, string type, object foe, string loc, 
             int prot, int res, int vuln, int ac, object wpn) 
{
    object env;
    if (!objectp(foe) || !objectp(env = environment()) || dmg < 10) {
        return 0;
    }
    if (objectp(wpn) && random(100) < 20 && dmg < random(query_dex())) {
        tell_room(env, "Krugan's body splits apart at the point of impact " +
                  "as he is hit, making " + wpn->query_name() + " glide " +
                  "through empty space, inflicting no damage!\n");
        return -dmg;
    }
    if (ac < -10 && objectp(wpn)) {
        tell_object(foe, "Your " + wpn->query_name() + " gets a crack as it " +
                    "hits Krugan's tough skin!\n");
        wpn->wear_out(5);
    }
    if (ac > -10 && objectp(wpn)) {
        tell_room(env, "Krugan's skin becomes more rigid!\n");
        add_tmp_prop("ac", 1);
    }
    add_tmp_prop("resist_" + type, 5);
    add_tmp_prop("prot_" + type, 1);
    return 0;
}
