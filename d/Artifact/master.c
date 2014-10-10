#include <chardata.h>
#include "/d/Empire/islands/artifact.h"

inherit I_GUILD;

private string *_titles;

private void
push_titles()
{
    int i, len;
    neut_title_str = allocate(20);
    for (i = 0, len = sizeof(_titles); i < len; ++i) {
        neut_title_str[i] = "the " + _titles[i];
    }
    male_title_str = neut_title_str;
    fem_title_str = neut_title_str;
}

static void
create()
{
    ::create();
    _titles = allocate(19);
    _titles[ 0] = "residue";
    _titles[ 1] = "fragment";
    _titles[ 2] = "scrap";
    _titles[ 3] = "curio";
    _titles[ 4] = "hogwash";
    _titles[ 5] = "forgery";
    _titles[ 6] = "remnant";
    _titles[ 7] = "curiosity";
    _titles[ 8] = "rarity";
    _titles[ 9] = "vestige";
    _titles[10] = "handiwork";
    _titles[11] = "keepsake";
    _titles[12] = "souvenir";
    _titles[13] = "objet d\'art";
    _titles[14] = "trophy";
    _titles[15] = "antique";
    _titles[16] = "relic";
    _titles[17] = "antiquity";
    _titles[18] = "artifact";
    push_titles();

    set_light(1);
    set_short("In the hut of enlightenment");
    set_long("You have to come here when you want to advance your level.\n" +
             "Commands: cost, advance [level, str, dex, int, con], " +
             "explored.\n" +
	     "Eternals have two additional branches: trade and twoweapon.");
    add_property("no_nothing");
    add_trigger("add_member", store_fp("do_add_member"));
    add_trigger("remove_member", store_fp("do_remove_member"));
    add_reset_object("board", ART_DIR_OBJ + "board", 1);
    add_exit(ATI_ISLAND->find_map_type(ATI_MAP_GUILD), "out");
}

public void
init()
{
    ::init();
    add_action("do_nothing", "quest");
    add_action("do_nothing", "quests");
}

public int
do_nothing(string dst)
{
    return 0;
}

public void
clean_member(object ply)
{
    object *arr, obj;
    int i, len;
    if (!objectp(ply)) {
        return;
    }
    arr = all_inventory(ply);
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        if (!objectp(obj = arr[i]) || obj<-ART_C_SOULSTONE) {
            continue;
        }
        //obj->destroy();
    }
}

public mixed
skill_name(string str)
{
    object obj;
    if (!objectp(obj = ART_D_SLIVER->query_skill(str))) {
        return 0;
    }
    return obj->query_name();
}

public int
valid_skill(string str)
{
    return objectp(ART_D_SLIVER->query_skill(str));
}

public object *
query_members()
{
    return filter_array(users(), "is_member", this_object());
}

public string
query_cmdpaths()
{
    return ART_DIR_COM_M;
}

public int
is_member(object ply)
{
    if (!objectp(ply)) {
        return 0;
    }
    if ((string)ply->query_guild() != ART_MASTER) {
        return 0;
    }
    return 1;
}

public varargs void
broadcast(string msg, mixed pre)
{
    string str;
    if (stringp(pre)) {
        str = pre + " ";
    } else if (objectp(pre)) {
        str = pre->query_name() + " ";
    } else {
        str = "";
    }
    str += "[Artifact]: " + msg + "\n";
    message("channels", str, query_members());
}

public void
member_enters(object ply)
{
    if (environment(ply) != this_object()) {
        ply->move_player("Z", this_object());
    }
    clean_member(ply);
    ART_C_SOULSTONE->get_instance(ply); // ensures instance
}

public void
member_reenters(object ply)
{
    if (!objectp(ART_C_WEAPON->get_instance(ply))) {
        return; // nothing to resume control of
    }
    if (objectp(ply->query_ld_room())) {
        return; // has somewhere to go
    }
    ply->move_player("X", new(ART_R_CONTROL));
}

public string
member_finger_info(string name)
{
    object ply;
    string ret;
    int level, gender, num_scores, num_titles;
    if (objectp(ply = find_player(name))) {
        level = ply->query_level() - 1;
        gender = ply->query_gender();
    } else {
        level = lookup_chardata(name, VAR_LEVEL) - 1;
        gender = lookup_chardata(name, VAR_GENDER);
    }
    if (level >= (num_titles = sizeof(_titles))) {
        level = num_titles - 1;
    }
    ret = "is " + add_article(_titles[level]) + ".";
    num_scores = ART_D_SCORE->query_num_highscores(name);
    if (num_scores > 0) {
        ret += "\n";
        ret += ({ "It", "He", "She" })[gender];
        ret += " holds " + convert_number(num_scores) +
               " guild highscores.";
    }
    return ret;
}

static varargs int
can_wiz(object obj)
{
    return 1; // bypass quest point requirement
}

static void
even_bigger_advance(string arg)
{
    ::even_bigger_advance(arg);
    ART_R_SKILLS->player_level_up(this_player());
}

private int
query_quests_req(int level)
{
    switch (level) {
    case 1..5:
        return 0;
    case 6..10:
        return level;
    case 11..20:
        return level * 2;
    case 21..29:
        return level * 3;
    default:
        return 9999;
    }
}

public int
advance(string arg)
{
    object ply;
    ply = this_player();
    if (!stringp(arg) || arg == "level") {
        int lev, val, req;
        lev = ply->query_level() + 1;
        req = query_quests_req(lev);
        val = ART_D_QUEST->query_num_unlocked(ply);
        if (val < req) {
            write("You need to complete " + (req - val) + " more quests " +
                  "before you can advance to level " + lev + ".\n");
            return 1;
        }
    }
    if (!::advance(arg)) {
        return 0;
    }
    ART_R_SKILLS->player_level_up(ply);
    return 1;
}

public int
add_member(object ply)
{
    if (!D_GUILD->into_guild(ply, "artifact")) {
        return 0;
    }
    member_enters(ply);
    ART_R_SKILLS->player_level_up(ply);
    return 1;
}

public int
remove_member(object ply)
{
    object obj;
    if (!D_GUILD->remove_from_guild(ply)) {
        return 0;
    }
    if (objectp(obj = present(ART_C_SOULSTONE, ply))) {
        obj->destroy();
    }
    return 1;
}

public int
try_join(object ply)
{
    if (!ART_CAN_JOIN) {
        return 0;
    }
    if (!objectp(ply) || !interactive(ply) || ply->query_level() > 1) {
        return 0;
    }
    return add_member(ply);
}

static int
do_add_member(string arg)
{
    object ply;
    if (!wizardp(ply = this_player())) {
        return notify_fail("You need to be a wizard to add a member.");
    }
    if (!stringp(arg)) {
        return notify_fail("Add who?");
    }
    if (!objectp(ply = find_player(arg))) {
        return notify_fail("No such player.");
    }
    if (!add_member(ply)) {
        return notify_fail("You fail.");
    }
    write("Ok.\n");
    return 1;
}

static int
do_remove_member(string arg)
{
    object ply;
    if (!wizardp(ply = this_player())) {
        return notify_fail("You need to be a wizard to remove a member.");
    }
    if (!stringp(arg)) {
        return notify_fail("Remove who?");
    }
    if (!objectp(ply = find_player(arg))) {
        return notify_fail("No such player.");
    }
    if (!remove_member(ply)) {
        return notify_fail("You fail.");
    }
    write("Ok.\n");
    return 1;
}

public int
member_present(object member, object other)
{
    object member_wpn, member_usr;
    object other_wpn, other_usr;
    if (objectp(member_wpn = ART_C_WEAPON->get_instance(member)) &&
        objectp(member_usr = member_wpn->query_user()) &&
        !member_wpn->is_suspended())
    {
        member = member_usr;
    }
    if (objectp(other_wpn = ART_C_WEAPON->get_instance(other)) &&
        objectp(other_usr = other_wpn->query_user()) &&
        !other_wpn->is_suspended())
    {
        other = other_usr;
    }
    return environment(member) == environment(other);
}

public int
query_free_exp(object ply)
{
    if (!objectp(ply)) {
        return 0;
    }
    return ply->query_exp() - get_next_exp(ply->query_level() - 1);
}
