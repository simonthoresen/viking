#include "/d/Empire/islands/ruins.h"

inherit RUN_I_MONSTER;

static void
create()
{
    ::create();
    set_name("runestone");
    set_level(10);
    set_hp(100);
    set_no_corpse(1);
    add_skill("prot_slash", 100);
    add_skill("prot_pierce", 100);
    add_skill("prot_chop", 100);
    add_skill("prot_claw", 100);
    add_skill("prot_bite", 100);
    add_skill("prot_fire", 100);
    add_skill("prot_cold", 100);
    add_skill("prot_electricity", 100);
    add_skill("prot_drain", 100);
    add_skill("prot_acid", 100);
    add_skill("prot_magic", 100);
    add_hook("__battack", store_fp("on_battack"));
    add_hook("__bnotify_attack", store_fp("on_bnotify_attack"));
    add_hook("__die", store_fp("on_die"));
    add_trigger("break", store_fp("do_break"));
}

static int
do_break(string arg)
{
    if (!stringp(arg) || !id(arg)) {
        return notify_fail("Break what?");
    }
    write("Ok.\n");
    this_player()->do_attack(this_object());
    return 1;
}

static int
on_battack(object foe)
{
    return 1;
}

static int
on_bnotify_attack(object foe)
{
    object npc;
    if (!objectp(npc = present(RUN_C_FORNJOT_GUARD))) {
        return 0;
    }
    write(npc->query_name() + " blocks your way.\n");
    npc->do_attack(foe);
}

static void
on_die(object corpse, object killer)
{
    object npc;
    if (!objectp(npc = RUN_D_RUINS->query_npc(RUN_C_FORNJOT))) {
        return;
    }
    npc->runestone_destroyed();
}
