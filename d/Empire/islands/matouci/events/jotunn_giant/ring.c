#include "/d/Empire/empire.h"

inherit EMP_I_ARMOUR;

static void
create() 
{
    ::create();
    set_name("jotunn ring");
    set_short("a heavy metal ring");
    set_long("This is a ring made out of a dark and beaten metal. " +
             "It is so large that you need to put several fingers " + 
             "through to prevent it from falling off. It is heavy.");
    add_id(({ "ring", "metal ring", "heavy ring" }));
    set_type("ring");
    set_value(1234);
    set_ac(1);
    set_weight(2);
    set_wear_modifier("ac", 3, 666);
    set_wear_modifier("str", 4, 11); 
    add_property("wear_msg", "You feel stronger and more protected.");
    add_property("magic");
    set_heart_beat(1);
}

public void
heart_beat() 
{
    object ply;
    if (!objectp(ply = query_worn_by()) || !interactive(ply) ||
        !objectp(ply->query_attack()))
    {
        return;
    }
    if (random(20)) {
        return;
    }
    tell_object(ply, "%^BOLD%^The lose your grip on the ring.%^END%^\n");
    ply->set_busy_next_round();
    remove(1);
}
