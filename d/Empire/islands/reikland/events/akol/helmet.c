#include "/d/Empire/empire.h"

inherit armour EMP_I_ARMOUR;
inherit align  EMP_I_ALIGNED;

private string *_blockable;

static void
create()
{
    armour::create();
    align::create();
    _blockable = ({ "blunt", "chop", "pierce", "slash" });

    set_name("Helm of Akol");
    set_short("an eog-alloyed helm");
    set_long("This is an eog alloyed open helm.");
    add_id(({ "helm", "eog helm", "alloyed helm" }));
    set_info("It is the very protective helm of the holy knight Akol.");
    set_type("helmet");
    set_value(1222);
    set_weight(1);
    set_ac(1);
    set_min_align(ALIGN_GOOD);
    set_wear_modifier("ac", 2);
    set_wear_modifier("devotion_good", 20);
    add_property("artifact");
    add_property("wear_msg",
                 "You feel the protection of the holy knight.\n");
    add_property("remove_msg",
                 "You feel the protection of the holy knight slip away.\n");
    add_hook("__wear", store_fp("on_wear"));
    add_hook("__remove", store_fp("on_remove"));
}

static void
on_wear(int silent, object obj)
{
    object ply;
    if (!objectp(ply = query_worn_by())) {
        return;
    }
    ply->add_hook("__hit_player", store_fp("on_hit_player"));
}

static void
on_remove(int silent)
{
    object ply;
    if (!objectp(ply = query_worn_by())) {
        return;
    }
    ply->remove_hook("__hit_player");
}

public int
on_hit_player(int dmg, string type, object hitter, string loc,
              int prot, int res, int vuln, int ac, object wpn)
{
    object ply;
    if (!objectp(ply = query_worn_by()) ||
        loc != "head" ||
        random(100) > ply->query_tmp_prop("devotion_good") ||
        sizeof(({ lower_case(type) }) & _blockable) == 0)
    {
        return 0;
    }
    tell_object(ply, bold("Your helmet absorbs some of the damage.\n"));
    return -random(dmg/2);
}
