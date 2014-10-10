#include "/d/Empire/islands/altdorf.h"

inherit EMP_I_ROOM;

private string *_rewards;

static void create() {
    ::create();
    _rewards = ({ 
        "/d/Empire/islands/dragon/obj/blood",
        "/d/Empire/islands/matouci/events/jormungand_serpent/spirit",
        "/d/Empire/islands/reikland/events/ent/elixir",
    });
    set_short("Great Temple and Cathedral of Sigmar");
    set_long("You are in the Great Temple and Cathedral of Sigmar. This is " +
             "the most sacred and holiest shrine of the Cult of Sigmar, " +
             "home to the Grand Theogonist and the senior clergy. " +
             "Here ghosts may pray to Sigmar to be revived, and returning " +
             "heroes may pray to have their lost rewards restored.");
    add_property("indoors");
    add_trigger("pray", store_fp("do_pray"));
    add_hook("__heart_beat", store_fp("check_heal"));
}

static void check_heal() {
    object *arr;
    int i, len;
    for (i = 0, len = sizeof(arr = all_inventory()); i < len; ++i) {
        object ply;
        if (!objectp(ply = arr[i]) || !living(ply) || 
            objectp(ply->query_attack()) || ply->query_dead())
        {
            continue;
        }
        if (ply->query_hp() < ply->query_max_hp()) {
            tell_object(ply, "The area sooths your wounds.\n");
            ply->reduce_hit_point(-10);
        }
    }
}

public int do_pray(string arg) {
    object ply;
    if (!objectp(ply = this_player())) {
        return 0;
    }
    say(capitalize(ply->query_real_name()) + " hails Sigmar!\n");
    if (!ply->query_ghost()) {
        write("You hail Sigmar.\n");
        _rewards->claim_reward(ply);
        return 1;
    }
    write("You feel that Sigmar answers your prayers.\n");
    ply->remove_ghost();
    return 1;
}
