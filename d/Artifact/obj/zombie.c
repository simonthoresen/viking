#include "/d/Artifact/artifact.h"

inherit EMP_I_MONSTER;

private object _master;

static void
create()
{
    ::create();
    _master = 0;

    set_name("Zombie");
    add_property("undead");
    add_hook("__bkill", store_fp("yield_kill"));
    add_hook("__destroy", store_fp("notify_destroy"));
    add_hook("__heart_beat", store_fp("help_master"));
}

static int
yield_kill(object victim, object killer)
{
    return 1;
}

static void
notify_destroy()
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    tell_room(env, query_name() + " crumbles to dust.\n");
}

static void
help_master()
{
    object foe;
    if (!objectp(_master)) {
        destroy_later();
        return; // destroy later
    }
    if (objectp(query_attack())) {
        return; // already busy
    }
    if (!objectp(present(_master)) ||
        !objectp(foe = _master->query_attack()))
    {
        return; // noone to help
    }
    if (foe != this_object()) {
        do_attack(foe);
    } else {
        _master = 0;
    }
}

public object
query_master()
{
    return _master;
}

public void
set_master(object val)
{
    _master = val;
}

public object
raise_corpse(object corpse)
{
    object obj;
    if (!objectp(corpse) || !corpse<-I_CORPSE) {
        return 0;
    }
    obj = new(source_file_name());
    obj->set_short("an undead " + corpse->query_name());
    obj->set_long("It is " + obj->short() + ".");
    obj->set_level(corpse->query_level());
    obj->set_gender(corpse->query_gender());
    obj->set_alignment(corpse->query_alignment());
    obj->set_race(corpse->query_race());
    obj->add_id(corpse->query_old_ids());
    obj->add_intoxication(corpse->query_property("intoxicated"));

    filter_array(all_inventory(corpse), "can_drop")->move(obj);
    obj->move_player("", environment(corpse));

    corpse->empty(1);
    corpse->destroy();
    return obj;
}

static int
can_drop(object obj)
{
    return objectp(obj) && !obj->drop(1);
}
