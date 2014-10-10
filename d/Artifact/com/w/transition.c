#include "/d/Artifact/artifact.h"

#define OLD_MASTER   ("/d/Artifacts/master")
#define OLD_FURNACE  ("/d/Artifacts/furnace")
#define OLD_TALENT   ("/d/Artifacts/com/talent")

inherit CMD_MODULE;

private int
calc_skill_cost(int val, int max, int cost)
{
    int i, sum;
    for (i = 0, sum = 0; i <= val; i += 5) {
        sum += OLD_TALENT->query_skill_cost(cost, i, max);
    }
    return sum;
}

public int
calc_exp(object ply)
{
    int i, len, sum;
    string *arr;
    mapping dat;
    sum = OLD_MASTER->query_exp(ply);
    printf("Current exp: %d\n", sum);

    dat = OLD_FURNACE->query_skills(ply);
    for (i = 0, len = sizeof(arr = keys(dat)); i < len; ++i) {
        int val, exp;
        string skill;
        skill = arr[i];
        val = ply->query_skill(skill);
        exp = calc_skill_cost(val, dat[skill][2], dat[skill][1]);
        printf("- %s (%d): %d\n", skill, val, exp);

        sum += exp;
    }
    printf("Total exp: %d\n", sum);
    return sum;
}

static int
main(string arg)
{
    object ply;
    if (!stringp(arg)) {
        return notify_fail("Transition who?");
    }
    if (!objectp(ply = find_player(arg))) {
        return notify_fail("No such player.");
    }
    if (!OLD_MASTER->query_member(ply)) {
        return notify_fail(ply->query_name() + " is not a retired artifact.");
    }
    ply->add_property(ART_P_RESTED_EXP, calc_exp(ply));
    if (!OLD_MASTER->do_leave(arg)) {
        return notify_fail("Failed to remove " + ply->query_name() +
                           " from old guild.");
    }
    ply->add_exp(1 - ply->query_exp());
    ply->set_level(1);
    ply->set_str(1);
    ply->set_dex(1);
    ply->set_con(1);
    ply->set_int(1);
    if (!ART_MASTER->add_member(ply)) {
        return notify_fail("Failed to add " + ply->query_name() +
                           " to new guild.");
    }
    ply->save_me();
    write("Ok.\n");
    return 1;
}
