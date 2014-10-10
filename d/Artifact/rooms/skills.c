#include "/d/Artifact/artifact.h"

inherit EMP_I_ROOM;

private float *_costs;

private void
calc_costs()
{
    int i, sum;
    _costs = allocate(100);
    for (i = 1, sum = 0; i <= 100; ++i) {
        _costs[i - 1] = to_float(sum += i) / 171700.0;
    }
}

private int
query_cost(object skill, int prev, int next)
{
    int i, sum;
    if (prev < 0) {
        prev = 0;
    }
    sum = 0;
    for ( ; prev < next && prev < 100; ++prev) {
	sum += to_int(to_float(skill->query_train_cost()) * _costs[prev]);
    }
    return sum;
}

static void
create()
{
    ::create();
    calc_costs();

    set_light(1);
    set_short("In the room of skills");
    set_long(store_fp("do_list"));
    add_trigger("list", store_fp("do_list"));
    add_trigger("train", store_fp("do_train"));
    add_property("no_nothing");
}

static int
cmp_skill(object lhs, object rhs)
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
    arr = sort_array(ART_D_SLIVER->query_skills(), "cmp_skill");
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        object obj;
        string str;
        int val;
        if (!objectp(obj = arr[i]) || !obj->can_use(ply)) {
            continue;
        }
        if ((val = ply->query_skill(obj->query_real_name())) < 0) {
            val = 0;
        }
        if (val < 100) {
            str = sprintf("%d", query_cost(obj, val, val + 1));
        } else {
            str = "-";
        }
        ret += ({ sprintf("%-22s  %8s  %4d%%", obj->query_name(),
                          str, val) });
    }
    return ret;
}

static int
do_list()
{
    EMP_D_LIST->write("Skill name              Cost      Level",
                      create_list(this_player()));
    return 1;
}

static int
do_train(string arg)
{
    string str;
    object ply, obj;
    int prev, next, cost;
    if (!stringp(arg)) {
	return notify_fail("Train what skill to what level?");
    }
    next = 0;
    sscanf(arg, "%s to %d", arg, next);
    if (!objectp(obj = ART_D_SLIVER->query_skill(arg))) {
        return notify_fail("No such skill.");
    }
    if (!obj->can_use(ply = this_player())) {
        return 0;
    }
    prev = ply->query_skill(obj->query_real_name());
    if (prev < 0) {
	prev = 0;
    }
    if (prev > 99) {
        return notify_fail("You have already mastered that skill.");
    }
    if (next <= prev) {
	next = prev + 1;
    }
    if (next > 100) {
	next = 100;
    }
    cost = query_cost(obj, prev, next);
    if (ART_MASTER->query_free_exp(ply) < cost) {
        return notify_fail("You do not have enough experience (" + cost +
			   " required).");
    }
    write("You pay the " + cost + " training cost, and train the '" +
          obj->query_name() + "' skill to " + next + "%.\n");
    say(ply->query_name() + " trains a skill.\n");
    ply->add_exp(-cost);
    ply->add_skill(str = obj->query_real_name(), next);

    ART_D_QUEST->try_unlock(ply, str + "_25", next, 25);
    ART_D_QUEST->try_unlock(ply, str + "_50", next, 50);
    ART_D_QUEST->try_unlock(ply, str + "_75", next, 75);
    ART_D_QUEST->try_unlock(ply, str + "_100", next, 100);
    return 1;
}

public void
player_level_up(object ply)
{
    if (!objectp(ply) || !interactive(ply)) {
        return;
    }
    switch (ply->query_level()) {
    case 29..99:
        ART_D_QUEST->unlock(ply, "acid_aptitude_0");
    case 26:
        ART_D_QUEST->unlock(ply, "electricity_aptitude_0");
    case 23:
        ART_D_QUEST->unlock(ply, "magic_aptitude_0");
    case 20:
        ART_D_QUEST->unlock(ply, "cold_aptitude_0");
        ART_D_QUEST->unlock(ply, "fire_aptitude_0");
    case 15:
        ART_D_QUEST->unlock(ply, "pierce_aptitude_0");
    case 10:
        ART_D_QUEST->unlock(ply, "chop_aptitude_0");
    case 5:
        ART_D_QUEST->unlock(ply, "blunt_aptitude_0");
    case 1:
        ART_D_QUEST->unlock(ply, "slash_aptitude_0");
    }
}
