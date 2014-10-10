#include "/d/Empire/islands/dragon.h"
#define P_BLOOD ("onyxia_blood")

inherit I_DRINK;

static void 
create() 
{
    ::create();
    set_name("dragon blood");
    set_short("a vial of dragon blood");
    set_long("A vial of potent dragon blood. This will stay with you " +
             "until you drink it all.");
    add_id(({ "vial", "vial of blood", source_file_name() }));
    set_value(9999);
    set_weight(1);
    set_empty_container("vial");
    set_drop(NO_DROP);
    add_property(({ "liquid", "artifact", "resistant" }));
    add_hook("__bwear_out", store_fp("prevent_wear"));
    add_hook("__bdrink", store_fp("on_bdrink"));
    add_hook("__drink", store_fp("on_drink"));
    add_hook("__move", store_fp("on_move"));
}

static int
prevent_wear(int val, string type) 
{
    return 1;
}

static int
on_bdrink(object obj) 
{
    object ply;
    ply = this_player();
    if (!objectp(present(DON_C_BLOOD_FX, ply))) {
        return 0;
    }
    write("You have had enough.\n");
    return 1;
}

static void
on_drink(object obj) 
{
    object ply;
    if (!objectp(ply = this_player())) {
        return;
    }
    make(DON_C_BLOOD_FX, ply);
    ply->set_tmp_prop(P_BLOOD, 1);
    ply->set_busy_next_round();
    ply->add_soaked(2000);
}

public void
claim_reward(object ply) 
{
    if (!objectp(ply) ||
        !ply->query_tmp_prop(P_BLOOD) ||
        objectp(present(DON_C_BLOOD_FX, ply)))
    {
        return;
    }
    make(DON_C_BLOOD_FX, ply);
}

public string
query_auto_load() 
{
    if (query_full() <= 0) {
	return 0;
    }
    return source_file_name() + ":";
}

public void
make_empty_drink() 
{
    ::make_empty_drink();
    set_drop(CAN_DROP);
}
