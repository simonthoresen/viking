#include "/d/Artifact/artifact.h"

inherit EMP_I_ROOM;

static void
create()
{
    ::create();
    set_short("At the great anvil of Volund");
    set_long("You are on a small island swimming in a lake of boiling lava. " +
             "Here lies the great anvil of Volund the smith. This is where " +
             "you take on a physical form and enter the world of men.\n\n" +
             "Type 'list' to see what shapes you can choose from. See " +
             "'help shapes' to see the complete list of shapes, and " +
             "'help <shape>' for more detailed information about a shape. " +
             "Once you have decided on a shape, do 'select <shape>'.\n\n");
    add_item(({ "mold", "molds" }), store_fp("do_list"));
    add_property("no_nothing");
    add_reset_object("smith", ART_DIR_OBJ + "smith", 1);
    add_trigger("list", store_fp("do_list"));
    add_trigger("select", store_fp("do_select"));
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

static int
do_list(string arg)
{
    int i, len;
    object *arr;
    string *out;
    out = ({ });
    for (i = 0, len = sizeof(arr = ART_D_SLIVER->query_shapes());
         i < len; ++i)
    {
        object obj;
        if (!objectp(obj = arr[i]) || !obj->can_use(this_player())) {
            continue;
        }
        out += ({ sprintf("%-18s  %5s  %5s  %5s",
                          obj->query_name(),
                          format_slot(obj->query_slot("glyph")),
                          format_slot(obj->query_slot("quirk")),
                          format_slot(obj->query_slot("spell"))) });
    }
    EMP_D_LIST->write("Shape               Glyph  Quirk  Spell", out);
    return 1;
}

static int
do_select(string arg)
{
    object ply, obj;
    ply = this_player();
    if (!ART_CAN_PLAY) {
        return notify_fail("The furnace has been disabled by the guild " +
                           "maintainer.");
    }
    if (!ART_MASTER->is_member(ply)) {
        return notify_fail("You need to be a guild member to do this.");
    }
    if (!ART_D_QUEST->is_unlocked(ply = this_player(), "help_guild")) {
        return notify_fail("You need to read the 'guild' help before you " +
                           "can select a shape.");
    }
    if (!stringp(arg)) {
        return notify_fail(capitalize(query_verb()) + " what?");
    }
    if (!objectp(obj = ART_D_SLIVER->query_shape(arg))) {
        return notify_fail("No such shape.");
    }
    if (!obj->can_use(ply)) {
        return notify_fail(obj->query_failure_msg());
    }
    if (objectp(ART_C_WEAPON->get_instance(ply))) {
        return notify_fail("You already have a physical form to resume.");
    }
    if (!objectp(ART_C_WEAPON->new_instance(ply, obj))) {
        return 0; // new_instance() should notify fail
    }
    write("You select the " + obj->query_name() + " mold.\n");
    ply->move_player("into " + add_article(obj->query_name()) + " mold",
                     ART_R_FURNACE);
    return 1;
}
