#include "/d/Empire/empire.h"

inherit EMP_I_MONSTER;

private int _roast;

static void
create() 
{
    ::create();
    _roast = 0;

    set_name(({ "smelly", "pink", "stinky", "cute", "hairy", 
                "dirty", "small", "fat", "ugly", "mean" })[random(10)] + " pig");
    add_id(({ "pig" }));
    set_short(add_article(lower_case(query_name())));
    set_long("The pig has a wet snout, small eyes, and a small, curly " +
             "tail. It has a thick body, short legs, and coarse hair.");
    set_level(15);
    set_aggressivity(75);
    set_bored_secs(300);
    set_corpse_object(store_fp("create_corpse"));
    add_hook("__hit_player", store_fp("on_hit_player"));
}

private string
query_roasting_msg() 
{
    switch (random(4)) {
    case 0:  return "The fire makes the pig's skin sizzle and roast.\n";
    case 1:  return "The pig squeals as you burn its skin to a crisp crust.\n";
    case 2:  return "The fire sears the pig's skin.\n";
    case 3:  return "The pig's skin is becoming caramelized and tasty.\n";
    default: return 0;
    }
}

private string
query_shout_msg() 
{
    switch (random(3)) {
    case 0:  return "It smells of a barbeque to the #d.";
    case 1:  return "The sweet smell of bacon fills the air.";
    case 2:  return "Someone is roasting meat #d of here, it smells delicious.";
    default: return 0;
    }
}

static int
on_hit_player(int dmg, string dtype, object foe, string loc, int prot,
              int resist, int vuln, int ac, object weapon)
{
    object env;
    if (dtype != "fire") {
        return 0;
    }
    _roast += dmg;
    if (dmg > 15 && objectp(foe)) {
        tell_object(foe, query_roasting_msg());
    } 
    if (dmg > 30 && objectp(env = environment())) {
        env->shout(query_shout_msg(), 2);
    }
    return dmg;
}

static object 
create_corpse(string foe) 
{
    object obj;
    if (_roast < 50) {
        return new(C_CORPSE);
    }
    obj = new(I_FOOD);
    obj->set_name("roast");
    obj->set_short("a roasted pig");
    obj->set_long("A whole roasted pig. It smells delicious.");
    obj->add_id(({ "roast", "pig", "roasted pig" }));
    obj->set_eater_mess("You pig yourself on the roast.\n");
    obj->set_doses(_roast / 35);
    obj->set_strength(35);
    obj->set_value(_roast);
    obj->set_weight(1);
    return obj;
}
