#include "/d/Empire/islands/matouci.h"

inherit monster EMP_I_MONSTER;

private object *_parts;

static void
create() 
{
    ::create();
    set_name("Cerberus");
    set_short("the THREE-HEADED Cerberus hound");
    set_long("A menacing monster of a hound, big as a house and radiating " +
             "danger. You feel as if you are about to die.");
    add_id(({ "hound", "cerebrus hound" }));
    set_level(29);
    set_wc(30);
    set_ac(10);
    set_hp(2000);
    set_aggressive(1);
    set_scary(1);
    set_bored_secs(300);
    add_property("no_possess");
    add_property("unarmed_damage_type", "claw");
    add_property(EMP_P_NOREGEN);
    add_property(EMP_P_LIMBS, ([ "left head"   : ({ }),
                                 "middle head" : ({ }),
                                 "right head"  : ({ }),
                                 "tail"        : ({ }) ]));
    add_hook("__bnotify_attack", store_fp("on_bnotify_attack"));
    add_hook("__move", store_fp("on_move"));
    add_hook("__destroy", store_fp("on_destroy"));
    add_hook("__die", store_fp("on_die"));
    load_a_chat(100, ({ store_fp("attack") }));

    _parts = ({ new(resolve_path("lhead")),
                new(resolve_path("mhead")),
                new(resolve_path("rhead")),
                new(resolve_path("tail")) });
    _parts->set_hound(this_object());
    _parts->set_scary_id(query_scary_id());
}

public object *
query_parts() 
{
    return _parts - ({ 0 });
}

static void
on_die(object corpse, object foe) 
{
    object obj;
    if (objectp(corpse)) {
        if (objectp(obj = D_TREASURE->get_unique(resolve_path("shield")))) {
            obj->move(corpse);
        } else {
            EMP_D_TREASURE->add_treasure(10000, corpse);
        }
    }
    if (objectp(foe)) {
	EMP_D_ACHIEVEMENT->unlock(foe, "cerberus_hound");
    }
}

static void
on_bnotify_attack(object foe) 
{
    query_parts()->do_attack(foe);
}

static void
on_move(object from, object to) 
{
    if (objectp(from) && !objectp(to)) {
        query_parts()->move(this_object());
    }
    if (objectp(to)) {
        query_parts()->move(to);
    }
}

static void
on_destroy() 
{
    query_parts()->destroy();
}

public int
is_cerberus() 
{
    return 1;
}
