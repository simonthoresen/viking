#include "/d/Empire/islands/reikland.h"

inherit RED_DIR_OBJ + "goblin";

static void
create() 
{
    ::create();
    set_name("goblin leader");
    add_long("As you look at him, he nervously edges away. You assume that " +
             "he is leader of the goblin lumberjacks.");
    scale_level(12, 15);
    add_eq(I_TORCH);
    add_money(250);
    load_a_chat(30, ({ "*yell HEEELP! I am being attacked!",
                       "*sob",
                       "*beg bgirl",
                       "*emote tries, but fails to run away." }));
}
