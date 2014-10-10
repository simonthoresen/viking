#include "/d/Artifact/artifact.h"

inherit EMP_I_ROOM;

static void
create()
{
    ::create();

    set_light(1);
    set_short("In the room of spells");
    set_long(store_fp("do_list"));
    add_trigger("list", store_fp("do_list"));
    add_trigger("train", store_fp("do_train"));
    add_property("no_nothing");
}

static int
cmp_spell(object lhs, object rhs)
{
    return strcmp(lhs->query_name(), rhs->query_name());
}

private string *
create_list(object ply)
{
    string *ret;
    object *arr;
    int i, len;
    ret = ({ });
    arr = sort_array(ART_D_SLIVER->query_spells(), "cmp_spell");
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        object obj;
        if (!objectp(obj = arr[i]) ||
            !obj->can_use(ply) ||
            ply->query_property(ART_P_SPELL(obj)))
        {
            continue;
        }
        ret += ({ sprintf("%-29s  %8d",
                          obj->query_name(),
                          obj->query_train_cost()) });
    }
    return ret;
}

static int
do_list()
{
    EMP_D_LIST->write("Spell name                     Cost    ",
                      create_list(this_player()));
    return 1;
}

static int
do_train(string arg)
{
    object ply, spell;
    int cost;
    if (!stringp(arg)) {
	return notify_fail("Train what?");
    }
    if (!objectp(spell = ART_D_SLIVER->query_spell(arg))) {
        return notify_fail("No such spell.");
    }
    ply = this_player();
    if (ply->query_property(ART_P_SPELL(spell))) {
        return notify_fail("You already know that spell.");
    }
    cost = spell->query_train_cost();
    if (ART_MASTER->query_free_exp(ply) < cost) {
        return notify_fail("You do not have enough experience (" + cost +
			   " required).");
    }
    ART_D_QUEST->add_unlock(ply, "spell_1", 1, 1);
    ART_D_QUEST->add_unlock(ply, "spell_10", 1, 10);
    ART_D_QUEST->add_unlock(ply, "spell_100", 1, 100);
    ART_D_QUEST->add_unlock(ply, "spell_all", 1,
                            ART_D_SLIVER->query_num_spells());

    write("You pay the " + cost + " training cost, and learn the '" +
          capitalize(spell->query_name()) + "' spell.\n");
    say(ply->query_name() + " learns a new spell.\n");
    ply->add_exp(-cost);
    ply->add_property(ART_P_SPELL(spell));
    return 1;
}
