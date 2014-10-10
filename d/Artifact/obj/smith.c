#include "/d/Artifact/artifact.h"

inherit I_MONSTER;

static void
create()
{
    ::create();
    set_name("Volund");
    set_short("Volund the Smith");
    set_long("A really huge blacksmith boosting enormous muscles with " +
             "protruding bloodveins.");
    add_id(({ "blacksmith", "smith", "man" }));
    load_chat(1, ({ store_fp("make_noise") }));
}

static void
make_noise()
{
    string msg;
    msg = "Volund hammers at you. ";
    msg += "*";
    msg += ({ "K","B","T" })[random(3)];
    msg += ({ "L","" })[random(2)];
    msg += ({ "O","I","A" })[random(3)];
    msg += ({ "I","" })[random(2)];
    msg += ({ "NK","KK" })[random(2)];
    msg += "*\n";
    tell_room(environment(), msg);
}
