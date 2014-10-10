#include "/d/Artifact/artifact.h"

inherit ART_I_SLIVER;

static void
create()
{
    ::create();
    set_long("It is " + short() + ". You may inscribe this on an artifact " +
             "to imbue it with additional powers. You may also trade it at " +
             "Abduhl Al'Haraz's shop in New Altdorf for a fair sum of gold.");
    add_id("glyph");
    set_type("glyph");
    set_slot("glyph", -1);
    add_trigger("inscribe", store_fp("do_inscribe"));
}

static void
setup_player(object ply)
{
    ::setup_player(ply);
    ART_D_QUEST->add_unlock(ply, "glyph_10", 1, 10);
    ART_D_QUEST->add_unlock(ply, "glyph_100", 1, 100);
    ART_D_QUEST->add_unlock(ply, "glyph_1000", 1, 1000);
}

static int
do_inscribe(string arg)
{
    string what, where;
    object ply, obj;
    if (!stringp(arg) || sscanf(arg, "%s on %s", what, where) != 2) {
        return notify_fail("Inscribe what on where?");
    }
    if (!id(what)) {
        return notify_fail("You do not have that glyph.");
    }
    if (!objectp(obj = present(where, ply = this_player()))) {
        return notify_fail("You do not have that artifact.");
    }
    if (!obj<-ART_C_WEAPON) {
        return notify_fail("The glyph only works on artifacts.");
    }
    if (!obj->can_add(this_object())) {
        return notify_fail("There is no room for that glyph.");
    }
    ART_LOG("glyphs", ply->query_real_name() + " inscribed " +
            query_real_name() + " on " + obj->query_real_name());
    move(obj);
    message_player(bold(ply->query_name() + " inscribes " +
                        add_article(query_name()) + " glyph on you!\n"));
    message_owner("You inscribe the " + query_name() + " glyph on your " +
                  obj->query_shape() + ".\n");
    message_room(ply->query_name() + " inscribes " +
                 add_article(query_name()) + " glyph on " +
                 ply->query_possessive() + " " + obj->query_shape() + ".\n",
                 ({ ply, obj }));
    return 1;
}

public string
extra_look()
{
    return "#R is inscribed with " + add_article(query_name());
}
