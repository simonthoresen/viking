#include "/d/Empire/empire.h"

inherit EMP_I_MONSTER;

static void
create() 
{
    ::create();    
    set_name("jotunn");
    set_short("a GIANT jotunn");
    set_long("A large monster, well over ten feet tall. It is a dirty " +
             "and disgustingly smelly creature, with a variety of " +
             "fungi growing on its body.\n");
    add_id(({ "giant", "giant jotunn" }));
    set_level(29);
    set_str(90);
    set_hp(2000);
    set_al(-500);
    set_ac(10);
    set_wc(50);
    set_aggressive(1);
    set_random_pick(90);
    set_scary(1);
    set_bored_secs(300);
    add_property("vuln_cold", 100);
    add_money(random(1500));
    add_hook("__damage_done", store_fp("on_damage_done"));
    add_hook("__die", store_fp("on_die"));
    load_chat(75, ({ store_fp("do_regenerate"),
                     store_fp("do_eat") }));
    load_a_chat(25, ({ store_fp("do_bite"), 
                       store_fp("do_eat"),
                       store_fp("do_regenerate") }));    
    add_eq(resolve_path("trunk"));
}

public void
init() 
{
    object ply;
    ::init();
    if (!objectp(ply = this_player()) || 
        interactive(ply)) 
    {
        return;
    }
    do_attack(ply);
}

static void 
do_eat(object ply, object foe) 
{
    if (ply->query_hp() >= ply->query_max_hp()) {
        return;
    }
    if (!objectp(present("roast"))) {
        return;
    }
    command("eat roast");
}

static void 
do_bite(object ply, object foe) 
{
    string limb;
    if (!objectp(foe)) {
        return;
    }
    if (!stringp(limb = EMP_D_LIMB->query_random_limb(foe))) {
        return;
    }
    tell_object(foe, "%^BOLD%^The jotunn sinks its teeth into your " + 
                limb + ".%^END%^\n");
    tell_room(environment(), "The jotunn sinks its teeth into " + 
              foe->query_name() + "'s " + limb + ".\n", ({ foe }));
    EMP_D_COMBAT->hit_player(ply, foe, 40 + random(40), "bite", limb, "teeth");
}

static void 
do_regenerate()
{ 
    heal_self(10 + random(50)); 
}

static void 
on_damage_done(int dmg, string dtype, object foe, string loc) 
{
    if (!objectp(foe) || dmg < 30 || random(4)) {
        return;
    }
    message("hityou", "Acidic blood sprays from the wounds of the " +
            "jotunn and scorches you terribly.\n", foe);
    message("visual", "Acidic blood sprays from the wounds of the " +
            "jotunn, scorching " + foe->query_name() + " terribly.\n", 
            environment(foe), foe);
    foe->hit_player(5 + random(20), "Acid", this_object());
}

static void
on_die(object corpse, object foe) 
{
    object env, obj, *arr;
    int i, len;
    arr = filter_array(all_inventory(env = environment()), 
                       "isliving", FILTER_OB);
    arr -= ({ this_object() });
    message("visual", "Acidic blood sprays from the fatal wound " +
            "of the jotunn.\n", env);
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        message("visual", arr[i]->query_name() + " is scorched by " +
                "the blood.\n", env, arr[i]);
        message("hityou", "You are scorched by the blood.\n", arr[i]);
        arr[i]->hit_player(20 + random(40), "Acid", this_object());
    }
    if (objectp(corpse) &&
        objectp(obj = D_TREASURE->get_unique(resolve_path("ring")))) 
    {
        obj->move(corpse);
    }
    if (objectp(foe)) {
	EMP_D_ACHIEVEMENT->unlock(foe, "jotunn_giant");
    }
}
