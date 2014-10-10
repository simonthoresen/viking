#include "/d/Empire/islands/reikland.h"

inherit EMP_I_ARMOUR;

private string _msgin;
private string _msgout;

static void
create() 
{
    ::create();
    _msgin = 0;
    _msgout = 0;

    set_name("Boots of the Lord");
    set_short("a pair of soft leather boots");
    set_long("A pair of soft leather boots invowen with mithril threads.");
    add_id(({"boots","leather boots"}));
    set_info("These boots will make you a king.");
    set_wear_modifier("int", 3);
    set_type("boot");
    set_value(222);
    set_weight(2);
    set_ac(1);
    add_property("wear_msg", "You feel like a king in these boots!\n");
    add_property("wear_other_msg",
                 "$N looks like a king in $p new boots!\n");
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
    _msgin = ply->query_msgin();
    _msgout = ply->query_msgout();
    ply->setmin("walks in as if " + ply->query_pronoun() + " owns the place");
    ply->setmout("walks");
}

static void
on_remove(int silent) 
{
    object ply;
    if (!objectp(ply = query_worn_by())) {
        return;
    } 
    ply->setmin(_msgin);
    ply->setmout(_msgout);
}
