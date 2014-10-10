#include "/d/Empire/empire.h"

inherit I_MONSTER;

private object _weapon;

static void
create() 
{
    ::create();
    _weapon = 0;

    set_name("blood beast");
    set_short("a traslucent bear spirit");
    set_long("A traslucent red bear with sharp teeth.");
    add_property("unarmed_damage_type", ({ "claw", "bite" }));
    add_property("ghost");
    add_property("prot_bite", 100);
    add_property("prot_blunt", 100);
    add_property("prot_chop", 100);
    add_property("prot_claw", 100);
    add_property("prot_impact", 100);
    add_property("prot_pierce", 100);
    add_property("prot_slash", 100);
    add_property("vuln_magic", 100);
    add_id(({ "beast", "bear", "translucent bear",
              "bear spirit", "spirit" }));
    set_level(19);
    destroy(30);
    add_hook("__destroy", store_fp("on_destroy"));
    add_hook("__attack", store_fp("blood_link"));
    add_hook("__bkill", store_fp("yield_kill"));
}

static void
on_destroy() 
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    tell_room(env, "The beast leaves in a puff of blood.\n");
}

static void
blood_link(object foe) 
{
    if (!objectp(_weapon)) {
        return;
    }
    _weapon->add_blood(1);
}

static int
yield_kill(object victim, object killer) 
{
    return 1;
}

public object
query_weapon() 
{
    return _weapon;
}

public void
set_weapon(object val) 
{
    _weapon = val;
}
