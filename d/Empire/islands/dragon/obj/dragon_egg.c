#include "/d/Empire/empire.h"

inherit I_ITEM;

static void
create() 
{
    ::create();
    set_name("Dragon's egg");
    set_short("a small dragon's egg");
    set_long("It is a small yellow egg that was stolen from the still-warm " +
             "corpse of the dragon queen Onyxia. It feels hot.");
    add_id(({ "egg", "dragon egg", "small egg" }));
    set_value(1);
    set_weight(1);
    set_drop(NO_DROP);
    add_property(({ "artifact", "resistant", "fragile", "tagged", "warm" }));
    set_heart_beat(1);
    add_hook("__move", store_fp("apply_bonus"));
    add_hook("__destroy", store_fp("clear_bonus"));
}

static void
apply_bonus(object from, object to) 
{
    if (objectp(from)) {
        from->remove_modifier("onyxia:egg");
    }
    if (objectp(to)) {
        to->set_modifier("onyxia:egg", "resist_fire", "magic", 5);
    }
}

static void
clear_bonus() 
{
    apply_bonus(environment(), 0);
}

private string
query_random_noise() 
{
    switch (random(5)) {
    case 0: return "Something moves inside your dragon's egg.\n";
    case 1: return "There is movement inside your dragon's egg.\n";
    case 2: return "There is a faint *thud* from within your dragon's egg.\n";
    case 3: return "The temperature of your dragon's egg changes.\n";
    case 4: return "A tiny crack appears on your dragon's egg.\n";
    }
}
public void
heart_beat() 
{
    object env;
    if (!objectp(env = environment()) ||
        random(10000) > 1) 
    {
        return;
    }
    message("", query_random_noise(), env);
}

public string
query_auto_load() 
{
    return source_file_name() + ":";
}
