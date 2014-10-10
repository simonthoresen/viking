#include "/d/Empire/islands/reikland.h"

inherit EMP_I_ITEM;

private int _magic;

static void 
create() 
{
    ::create();
    _magic = 1;

    set_name("scroll");
    set_short("an old %^L_YELLOW%^glowing%^END%^ scroll");
    set_long("It appears to be glowing with a faint enhancing glow. You " +
             "can not make out any visible letters on it.");
    add_id(({ "old scroll", "glowing scroll" }));
    set_info("This is a scroll of enchantment.");
    set_weight(0);
    set_value(3333);
    set_read(store_fp("do_read"));
    add_property(({ "magic", "paper", "tagged" }));
}

static int
do_read(string arg) 
{
    object ply;
    if (!objectp(ply = this_player()) ||
        !interactive(ply) ||
        !_magic)
    {
        return notify_fail("Nothing happens.");
    }
    say(ply->query_name() + " reads an old glowing scroll.\n");
    write("Use the scroll on which item? ");
    input_to("enchant_item");
    return 1;
}

public void
enchant_item(string arg)
{
    object ply, obj;
    ply = this_player();
    if (!_magic) {
        tell_object(ply, "Nothing happens.\n");
        return;
    }
    if (!objectp(obj = present(arg, ply))) {
        tell_object(ply, "You do not have " + maybe_add_article(arg) + ".\n");
        return;
    }
    tell_object(ply, "Rays of light shoot from the scroll in every " +
                "direction!\n");
    if (!EMP_D_ENCHANT->add_enchant(obj, 100)) {
        tell_object(ply, "The magic fizzles and dies.\n");
        return;
    }
    tell_object(ply, "The magic leaves the scroll.\n");

    remove_id(query_id_array());
    set_name("scroll");
    set_short("an old scroll");
    set_long("It appears to be an old scroll with no letter on it.");
    set_info("The scroll is discharged.");
    add_id("old scroll");
    _magic = 0;
}
