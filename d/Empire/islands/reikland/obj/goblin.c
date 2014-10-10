#include "/d/Empire/islands/reikland.h"

inherit RED_I_CRITTER;

static void
create() {
    ::create();
    set_faction("goblins");
    set_race("goblin");
    set_name("goblin");
    add_id(({ "labouring goblin", "goblin lumberjack", "lumberjack" }));
    add_long("This fellow is working hard, in his own pace. If you so " +
             "inclined, you might have found this sort of hard working " +
             "individual attractive. Has has really bad B.O., though.");
    set_male();
    scale_level(7, 9);
    scale_str(12, 14);
    scale_dex(12, 14);
    scale_wc(12, 14);
    scale_ac(8, 10);
    set_al(-75);
    set_aggressivity(20);

    EMP_D_WEAPON->add_weapon(35);
    add_money(40 + random(10));
    
    load_a_chat(15, ({ "*yell Don't let the enemy rob us.",
                       "*emote goes berserk and charges!",
                       "*emote tries to hide behind a tree, but fails.",
                       "*yell CHARGE!" }));
}
