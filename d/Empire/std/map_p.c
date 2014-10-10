#include "/d/Empire/empire.h"

inherit EMP_I_ROOM;

static void create() {
    ::create();
    set_short("Beautiful plains");
    set_day_long(({ "You are in the middle of a beautiful grassy plain. The " +
                    "cool wind blows through the dark purple grass, making " +
                    "a comforting rustling sound. The sun is bright, and " +
                    "you can see various critters scampering through the " +
                    "grass.",
                    "The sky is slightly overcast and shadows move quickly " +
                    "over the plains, giving the odd sensation of motion. " +
                    "The wind picks up, and you feel as though rain might " +
                    "be in the future.",
                    "The grass of the peaceful, dark plain is punctuated by " +
                    "a few large rocks lying about. A few large insects and " +
                    "small, black reptiles scamper about." })[random(3)]);
    set_night_long("At night, you can barely see that dark grass in the " +
                   "moonlight, giving you the sensation of floating in " +
                   "space. Your only idea that you are on solid ground is " +
                   "given by the faint rustling of the wind through the " +
                   "vegetation.");
    add_item(({ "grass", "fresh grass" }), 
             "Wide open area with fresh grass in front of you.");
}
