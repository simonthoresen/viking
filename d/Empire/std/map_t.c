#include "/d/Empire/empire.h"

inherit EMP_I_ROOM;

static void
create()
{
    ::create();
    set_short("A freezing tundra");
    set_day_long(({ "You feel you should have packed an extra jacket as you " +
                    "trudge through the deep snow here. Your breath forms " +
                    "ice crystals as you exhale. In the distance, you see " +
                    "huge mountains of ice which part the clouds.",
                    "You walk carefully along the patch of ice, taking care " +
                    "to avoid thin patches. You pause to wipe some ice " +
                    "crystals from your eyebrows and continue into the vast " +
                    "frozen wasteland.",
                    "You find it hard to breathe the freezing air as you " +
                    "scale the snow dune before you. As you reach the top, " +
                    "the view of the frozen wasteland is impressive. " +
                    "Without pausing too long to admire the awesome view, " +
                    "you continue." })[random(3)]);
    set_night_long("If you thought this place was cold during the day, you " +
                   "had another thing coming. As far as you can see, which " +
                   "isn't very, the snow is cold, flat, and unrelenting. " +
                   "Your shivers of cold are surpassed only by the " +
                   "loneliness you feel.");
    add_item("snow", "The snow is finely powdered and seems infinitely deep.");
    add_property("cold");
}

public void
living_heart_beat(object ply)
{
    if (!objectp(ply) ||
        !living(ply) ||
        random(100) > 10 ||
        sizeof(ply->query_worn_armour()) > 10)
    {
        return;
    }
    if ((string)ply->query_guild() == "/d/Frost/guild/main/master") {
        if (ply->query_hp() < ply->query_max_hp()) {
            if (random(2)) {
                tell_object(ply, "You enjoy the cold breeze.\n");
            } else {
                tell_object(ply, "You enjoy the cold air.\n");
            }
            ply->reduce_hit_point(-5);
        }
    } else {
        message("hityou", "You are freezing cold!\n", ply);
        if (!random(15)) {
            ply->command("shiver");
        }
        catch(ply->hit_player(10 + random(10), "cold", this_object()));
        if (objectp(ply)) {
            ply->remove_attackers(this_object());
        }
    }
}
