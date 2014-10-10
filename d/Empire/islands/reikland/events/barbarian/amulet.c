#include "/d/Empire/islands/reikland.h"

inherit EMP_I_ARMOUR;

private int _stolen;

static void
create() 
{
    ::create();
    _stolen = 0;

    set_name("collar");
    set_short("a spiked bone collar");
    set_long("A bone collar with long, protruding spikes.");
    add_id(({ "spiked collar", "bone collar" }));
    set_type("amulet");
    set_ac(1);
    set_weight(1);
    set_value(200 + random(50));
    set_wear_modifier("ac", 4);
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
    if (!silent) {
        tell_object(ply, "Suddenly everything seems so very simple.\n");
    }
    ply->add_hook("__heart_beat", store_fp("on_wearer_heart_beat"));
    _stolen = 0;
}

static void
on_remove(int silent) 
{
    object ply;
    if (!objectp(ply = query_worn_by())) {
        return;
    }
    if (!silent) {
        tell_object(ply, "Suddenly everything seems so very complex.\n");
    }
    ply->remove_hook("__heart_beat");
    ply->add_tmp_int(_stolen);
    _stolen = 0;
} 

public void
on_wearer_heart_beat()
{
    object ply;
    int val;
    if (!objectp(ply = query_worn_by()) ||
        (val = ply->query_int() - 1) == 0)
    {
        return;
    }
    ply->add_tmp_int(-val);
    _stolen += val;    
}
