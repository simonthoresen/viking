#include "/d/Empire/empire.h"

inherit EMP_I_MONSTER;

private object _head;

static void
create() 
{
    ::create();
    _head = 0;
    
    set_name("Jormungand");
    set_short("the INFERNAL Jormungand serpent");
    set_long("The serpent is larger than anything you have ever seen before. " +
             "It towers before and all around you, stretching out in every " +
             "direction. It is covered in scales as impenetrable as steel, " +
             "and studded with razor-sharp spikes covered in acid.");
    add_id(({ "infernal jormungand", "jormungand serpent", "serpent" }));
    add_id(source_file_name());
    set_log_file("jormungand");
    set_no_corpse(1);
    set_level(29);
    set_aggressive(1);
    set_hp(666);
    set_ac(10);
    set_wc(66);
    add_property("prot_slash", 25);
    add_property("prot_blunt", 25);
    add_property("prot_pierce", 25);
    add_property("prot_chop", 25);
    add_property("prot_claw", 25);
    add_property("prot_bite", 25);
    add_property("unarmed_damage_type", ({ "acid", "pierce" }));

    add_hook("__bdie", store_fp("on_bdie"));
    add_hook("__damage_dealt", store_fp("on_damage_dealt"));
    add_hook("__damage_done", store_fp("on_damage_done"));
    add_hook("__destroy", store_fp("on_destroy"));
    add_hook("__heart_beat", store_fp("on_heart_beat"));
}

private void
do_thrash() 
{
    object env, *arr;
    int i, len;
    if (!objectp(env = environment())) {
        return;
    }
    for (i = 0, len = sizeof(arr = all_inventory(env)); i < len; ++i) {
        object obj;
        if (!objectp(obj = arr[i]) || !living(obj) || obj->is_jormungand()) {
            continue;
        }
        EMP_D_COMBAT->hit_player(this_object(), obj, 25 + random(25), 
                                 "impact", 0, "body");
    }
}

static int
on_bdie(object foe) 
{
    return 1; /* must kill the head */
}

static void
on_damage_dealt(int dmg, string dtype, object foe, string loc) 
{
    if (dtype != "pierce") {
        return;
    }
    EMP_D_COMBAT->wound_player(this_object(), foe, dmg / 4);
}

static void
on_damage_done(int dmg, string dtype, object foe, string loc) 
{
    if (!objectp(_head)) {
        return;
    }
    _head->hit_player(dmg, "Drain", foe);
}

static void
on_destroy() 
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    tell_room(env, capitalize(short()) + " withers to dust.\n");
}

static void
on_heart_beat() 
{
    object env, room;
    string file;
    if (!objectp(env = environment()) || !objectp(_head)) {
        destroy(0);
        return;
    }
    do_thrash();
}

public int
query_hp() 
{
    return objectp(_head) ? _head->query_hp() : 1;
}

public int
query_max_hp()
{
    return objectp(_head) ? _head->query_max_hp() : 1;
}

public void
set_head(object val) 
{
    _head = val;
}

public object
query_head() 
{
    return _head;
}

public int
is_jormungand_tail() 
{
    return 1;
}

public int
is_jormungand() 
{
    return 1;
}

