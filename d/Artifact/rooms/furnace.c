#include "/d/Empire/islands/artifact.h"

#define ERR_NO_WEAPON ("You have no physical form, please cancel.")

inherit EMP_I_ROOM;

static void
create()
{
    ::create();
    set_short("In the furnace of Volund");
    set_long("Now that you have chosen your physical shape, you may " +
             "customize yourself by adding quirks. Type 'list' to see what " +
             "quirks you can choose from. There are restrictions tied to " +
             "quirks that limit what you can choose. See 'help quirks' to " +
             "read more, and 'help <quirk>' for more detailed information " +
             "about a quirk.\n" +
             "\n" +
             "To see how many slots you have available, type 'score'. To " +
             "add a quirk to your form, type 'add <quirk>'. To see what " +
             "quirks you have already chosen, type 'inventory'. To remove a " +
             "quirk that you have already chosen, type 'remove <quirk>'. To " +
             "see what your physical form looks like, just look at " +
             "yourself.\n" +
             "\n" +
             "Once you are happy with your customization, type 'complete'.");
    add_trigger(ART_D_COMMAND->query_actions("/com/m/inventory"),
                store_fp("do_inventory"));
    add_trigger("add", store_fp("do_add"));
    add_trigger("list", store_fp("do_list"));
    add_trigger("remove", store_fp("do_remove"));
    add_exit(R_VOID, "complete", store_fp("go_complete"));
    add_exit(ATI_ISLAND->find_map_type(ATI_MAP_SMITHY), "cancel",
             store_fp("go_cancel"));
    add_property(({ "no_nothing", "underground", "warm" }));
}

private int
fail_command(string str)
{
    write(str + "\n");
    return 1; // need to block replaced command
}

private string
format_slot(int val)
{
    if (val > 0) {
        return "+" + val;
    } else if (val == 0) {
        return "-";
    } else {
        return "" + val;
    }
}

private string
write_list(object *arr)
{
    string *out;
    int i, len;
    arr = sort_array(arr, "cmp_name");
    len = sizeof(arr);
    out = allocate(len);
    for (i = 0; i < len; ++i) {
        out[i] = sprintf("%-30s %8s", arr[i]->query_name(),
                         format_slot(arr[i]->query_slot("quirk")));
    }
    EMP_D_LIST->write("Quirk name                        Slots", out);
}

static int
go_cancel(string dst)
{
    object wpn;
    if (!objectp(wpn = ART_C_WEAPON->get_instance(this_player()))) {
        return 0;
    }
    wpn->destroy();
    return 0;
}

static int
go_complete(string dst)
{
    object ply, wpn;
    if (!objectp(wpn = ART_C_WEAPON->get_instance(ply = this_player()))) {
        write(ERR_NO_WEAPON + "\n");
        return 1;
    }
    if (wpn->query_slot("quirk") < 0) {
        write("Your can not complete with negative quirk slots.\n");
        return 1;
    }
    if (ply->query_sp() < COST_FURNACE) {
        write("Insufficient spell points (" +
              COST_FURNACE + " required).");
        return 1;
    }
    ply->reduce_spell_point(COST_FURNACE);

    ART_D_QUEST->add_unlock(ply, "furnace_1", 1, 1);
    ART_D_QUEST->add_unlock(ply, "furnace_10", 1, 10);
    ART_D_QUEST->add_unlock(ply, "furnace_100", 1, 100);

    wpn->move(R_SMITHY);
    wpn->message_room("The smith creates " + wpn->short() + ".\n");
    ply->move_player("into the world of men", new(ART_R_CONTROL));
    return 1;
}

static int
do_inventory(string arg)
{
    object wpn, *arr;
    if (!objectp(wpn = ART_C_WEAPON->get_instance(this_player()))) {
        return fail_command(ERR_NO_WEAPON);
    }
    if (!arrayp(arr = wpn->filter_slivers("is_quirk")) || sizeof(arr) == 0) {
        return fail_command("You have no quirks.");
    }
    write_list(arr);
    return 1;
}

static int
do_add(string arg)
{
    object ply, wpn, obj;
    if (!objectp(wpn = ART_C_WEAPON->get_instance(ply = this_player()))) {
        return notify_fail(ERR_NO_WEAPON);
    }
    if (!stringp(arg)) {
        return notify_fail(capitalize(query_verb()) + " what?");
    }
    if (!objectp(obj = ART_D_SLIVER->query_quirk(arg))) {
        return notify_fail("No such quirk.");
    }
    if (!wpn->can_add(obj)) {
        return notify_fail(wpn->query_failure_msg());
    }
    write("You add the " + obj->query_name() + " quirk.\n");
    say(ply->query_name() + " adds the " + obj->query_name() + " quirk.\n");
    clone_object(obj)->move(wpn);
    return 1;
}

static int
do_remove(string arg)
{
    object ply, wpn, obj;
    if (!objectp(wpn = ART_C_WEAPON->get_instance(ply = this_player()))) {
        return notify_fail(ERR_NO_WEAPON);
    }
    if (!stringp(arg)) {
        return notify_fail(capitalize(query_verb()) + " what?");
    }
    if (!objectp(obj = wpn->query_sliver(arg)) ||
        obj->query_type() != "quirk")
    {
        return notify_fail("No such quirk.");
    }
    write("You remove the " + obj->query_name() + " quirk.\n");
    say(ply->query_name() + " removes the " + obj->query_name() + " quirk.\n");
    obj->destroy();
    return 1;
}

static int
do_list(string arg)
{
    object *arr;
    arr = ART_D_SLIVER->filter_slivers("is_usable_quirk", this_object(),
                                       this_player());
    if (stringp(arg)) {
        arr = filter_array(arr, "name_contains", this_object(), arg);
    }
    write_list(arr);
    return 1;
}

public int
is_quirk(object obj)
{
    return obj<-ART_I_QUIRK;
}

public int
is_usable_quirk(object obj, object ply)
{
    return obj<-ART_I_QUIRK && obj->can_use(ply);
}

public int
name_contains(object obj, string arg)
{
    return sscanf(obj->query_name(), "%*s" + arg + "%*s") ||
           sscanf(obj->query_real_name(), "%*s" + arg + "%*s");
}

public int
cmp_name(object lhs, object rhs)
{
    return D_FILTER->sort_alpha_asc(lhs->query_name(), rhs->query_name());
}
