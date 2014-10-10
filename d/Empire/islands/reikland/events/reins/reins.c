#include "/d/Empire/islands/reikland.h"

#define LEGAL_MOUNTS (({ "/players/knubo/open/hurtme", \
                         "/players/bigdog/monsters/hydra", \
                         "/players/grumble/sea/theserpent", \
                         "/players/artemis/area/monsters/hellhound", \
                         "/d/Dlord/monster/d_warningguard" }))

inherit EMP_C_REINS;

private int _charges;

static void
create() 
{
    ::create();
    _charges = 3;
    add_trigger(({ "mount", "ride" }), store_fp("do_mount"));
    add_trigger(({ "dismount", "unmount" }), store_fp("do_dismount"));
}

static int 
is_legal(object mob) 
{
    string src;
    if (!stringp(src = source_file_name(mob))) {
        return 0;
    }
    if (sscanf(src, "/room/monster/%*s")) {
        return 1;
    }
    if (member_array(src, LEGAL_MOUNTS) >= 0) {
        return 1;
    }
    return 0;
}

static int
can_mount(object ply, object mob) 
{
    if (!interactive(ply)) {
        return 1;
    }
    if (mob->query_level() > ply->query_level() ||
        mob->query_level() > 5 ||
        mob->query_max_hp() > 500 ||
        mob->query_wc() > 20) 
    {
        return 0;
    }
    return 1;
}

public int
mount(object mob) 
{
    if (!::mount(mob)) {
        return 0;
    }
    mob->add_hook("__heart_beat", store_fp("check_can_mount"));
    return 1;
}

public void
unmount() 
{
    object mob;
    if (objectp(mob = query_mount())) {
        mob->remove_hook("__heart_beat");
    }
    ::unmount();
}

public void 
check_can_mount() 
{
    object rider, mount;
    if (!objectp(rider = query_rider()) || 
        !objectp(mount = query_mount()) ||
        can_mount(rider, mount)) 
    {
        return;
    }
    tell_object(rider, mount->query_name() + " throws you off " +
                mount->query_possessive() + " back.\n");
    unmount();
}

public int
do_mount(string arg) 
{
    object ply, mob;
    if (!living(ply = environment())) {
        return 0;
    }
    if (!stringp(arg)) {
        return notify_fail("Mount what?");
    }
    if (!objectp(mob = present(arg, environment(ply)))) {
        return notify_fail("There is no '" + arg + "' here.");
    }
    if (ply->query_busy_next_round()) {
        return notify_fail("You are too busy to do that.");
    }
    if (mob->query_property("no_mount") || 
        mob->query_property("no_special")) 
    {
        return notify_fail("You can not mount that.");
    }
    if (environment(mob)->query_property("no_special")) {
        return notify_fail("You can not do that here.");
    }
    if (interactive(ply) && !is_legal(mob)) {
        return notify_fail("Urd, Skuld and Verdande do not allow it.");
    }
    if (!can_mount(ply, mob)) {
        return notify_fail(capitalize(mob->query_pronoun()) + " resists you.");
    }
    if (!mount(mob)) {
        return notify_fail("You can not mount that.");
    }
    if (--_charges < 0) {
        tell_object(ply, "SNAP! " + mob->query_name() + " bites through your " +
                    "reins, destroying them completely.\n");
        destroy();
    }
    mob->remove_attackers(ply);
    ply->remove_attackers(mob);
    return 1;
}

public int
do_dismount(string arg) 
{
    object rider, mount;
    if (!living(environment())) {
        return 0;
    }
    if (!objectp(rider = query_rider()) ||
        !objectp(mount = query_mount()))
    {
        return notify_fail("You are not mounted.");
    }
    if (environment(mount)->query_property("no_special")) {
        return notify_fail("You can not do that here.");
    }
    if (stringp(arg) && !mount->id(arg)) {
        return notify_fail("You are not mounting '" + arg + "'.");
    }
    unmount();
    return 1;
}

public int
query_charges() 
{
    return _charges;
}
