#include "/d/Empire/islands/fort.h"

inherit FOR_I_MONSTER;

static void
create()
{
    ::create();
    set_race("orc");
    set_name("Orc");
    set_short("an orc guard");
}

static void
init_dangerlevel(int old_val, int new_val)
{
    // this method only gets called once for guards, and that is just before it
    // is moved to the room it belongs to. you can basically do whatever you
    // want here, since the npc has not yet engaged with a player

    // even at danger level 0 this guard should be hard. the danger level is a
    // mechanic to make sure noone stands in the fort for hours farming this
    // mob. guards should be hard at 0, but they should be absurd at 100

    set_level(25 + new_val / 10); /*   25 -   35 */
    set_wc(40 + new_val / 5);     /*   40 -   60 */
    set_ac(7 + new_val / 10);     /*   10 -   20 */
    set_hp(1000 + new_val * 5);   /* 1000 - 1500 */
    set_sp(1000 + new_val * 5);   /* 1000 - 1500 */
}
