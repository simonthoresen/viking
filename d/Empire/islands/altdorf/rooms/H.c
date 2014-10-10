#include "/d/Empire/islands/altdorf.h"

inherit EMP_I_ROOM;

void create() {
    ::create();
    set_light(1);
    set_short("The People's Hall");
    set_long("You are standing inside the People's Hall. Marble covers " +
             "the floor and walls. A big statue is standing in the center " +
             "of the hall, adorned with various gems and precious metals. " +
             "There is a bounty board with WANTED posters on the wall.");
    add_item(({ "hall", "large hall" }), 
             "This hall is quite large, and has several lights in the roof " +
             "to light it up.");
    add_item(({ "roof" }),
             "The roof consists of several lights.");
    add_item(({ "light", "lights" }),
             "The lights keeps the hall from becoming dark at night. They " +
             "seem to be magical.");
    add_item(({ "floor", "wall", "walls", "ground" }),
             "It is covered with marble. Very nice craftmanship.");
    add_item(({ "statue", "big statue", "a big statue" }),
             "The statue represents a tall figure. He looks kinda familiar " +
             "but you cannot quite make out where you have seen him before. " +
             "There is an inscription here as well.");
    add_item(({ "inscription", "text" }),
             "The inscription says: He fought long and hard, but in the end " +
             "there was no hope of victory.\nKarl-Franz Emperor.");
    add_item(({ "gems", "gem", "metal", "metals" }),
             "They look very valuable, too bad you'll never be able to pry " +
             "them off since they are magically fastened.");
    add_item(({ "marble" }), 
             "It is top-quality marble from the southern part of The Empire.");
    add_item(({ "bounty board", "wanted posters", "posters", "poster" }),
             store_fp("exa_bounty"));
    add_property("indoors");
    
    add_reset_object("board", ALT_DIR_OBJ + "board", 1);
}

void exa_bounty() {
    int i, len;
    string *arr;
    mapping dat;
    if (!mapp(dat = ALT_D_BOUNTY->query_bounties()) ||
        (len = sizeof(arr = keys(dat))) == 0) 
    {
        write("There are no posters up right now.\n");
        return;
    }
    write("----------------------------------------\n");
    for (i = 0; i < len; ++i) {
        printf("%-30s%10d\n", capitalize(arr[i]), dat[arr[i]]);
    }
    write("----------------------------------------\n");
}
