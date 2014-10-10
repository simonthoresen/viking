#include "/d/Empire/empire.h"

inherit EMP_I_ROOM;

static void
create()
{
    ::create();
    set_short("An arid desert");
    set_day_long(({ "The desert seems to stretch on for miles. Several " +
                    "exotic cacti puntuate the area, and desert flowers can " +
                    "be seen growing sparsely.",
                    "Exotic plants and cacti are all about. The wind picks " +
                    "up, and sand scratches against your face as you try " +
                    "not to inhale any.",
                    "You are in the middle of a small patch of cacti. As " +
                    "you look up, you see rolling dunes. The wind causes " +
                    "sand to blow over them in the distance." })[random(3)]);
    set_night_long("The stark desert moon are reflected by the sand, " +
                   "revealing cacti and other sparse vegetation.");
    add_item(({ "cactus", "cacti" }), "The cacti are exotically colored.");
    add_property("warm");
}

public void
living_heart_beat(object ply)
{
    if (!objectp(ply) ||
        !living(ply) ||
        random(100) > 10 ||
        sizeof(ply->query_worn_armour()) == 0)
    {
        return;
    }
    if (ply->query_soaked() > 0) {
        if (random(2)) {
            tell_object(ply, "The heat is unbearable.\n");
        } else {
            tell_object(ply, "You feel thirstier.\n");
        }
        ply->add_soaked(-10);
    } else {
        if (random(2)) {
            message("hityou", "You are burning up in this heat!\n", ply);
        } else {
            message("hityou", "You are thirsting in this heat!\n", ply);
        }
        if (!random(15)) {
            ply->command(({ "pant", "sweat" })[random(2)]);
        }
        catch(ply->hit_player(5 + random(5), "fire", this_object()));
        if (objectp(ply)) {
            ply->remove_attackers(this_object());
        }
    }
}
