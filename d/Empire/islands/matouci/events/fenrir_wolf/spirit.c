#include "/d/Empire/empire.h"

inherit I_MONSTER;

static void
create() 
{
    ::create();
    set_name("spirit wolf");
    set_short("a translucent wolf spirit");
    set_long("A translucent blue wolf with sharp teeth.");
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
    add_id(({ "wolf", "translucent wolf",
              "wolf spirit", "spirit" }));
    set_level(19);
    destroy(30);
    add_hook("__destroy", store_fp("on_destroy"));
    add_hook("__bkill", store_fp("yield_kill"));
}

static void
on_destroy() 
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    tell_room(env, "The spirit wolf leaves in a puff of smoke.\n");
}

static int
yield_kill(object victim, object killer) 
{
    return 1;
}

