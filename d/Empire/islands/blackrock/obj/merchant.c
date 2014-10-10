#include "/d/Empire/islands/blackrock.h"

#define LINE        ("--------------------------------------   " + \
                     "--------------------------------------\n")
#define ITEM_TYPE   ("type")
#define ITEM_CMIN   ("cmin")
#define ITEM_CMAX   ("cmax")

inherit EMP_I_MONSTER;

private mapping _armours;
private mapping _weapons;
private string  _table;

private string
create_table() 
{
    string *lhs_arr, *rhs_arr, ret;
    int i, lhs_len, rhs_len;
    ret  = LINE;
    ret += "Armours                    Black coins   ";
    ret += "Weapons                    Black coins\n";
    ret += LINE;
    lhs_len = sizeof(lhs_arr = keys(_armours));
    rhs_len = sizeof(rhs_arr = keys(_weapons));
    for (i = 0; i < lhs_len || i < rhs_len; ++i) {
        mapping dat;
        string lhs, rhs;
        if (i < lhs_len) {
            dat = _armours[lhs_arr[i]];
            lhs = sprintf("%-26s %4d - %4d", capitalize(lhs_arr[i]),
                          dat[ITEM_CMIN], dat[ITEM_CMAX]);
        } else {
            lhs = "";
        } 
        if (i < rhs_len) {
            dat = _weapons[rhs_arr[i]];
            rhs = sprintf("%-26s %4d - %4d", capitalize(rhs_arr[i]),
                          dat[ITEM_CMIN], dat[ITEM_CMAX]);
        } else {
            rhs = "";
        } 
        ret += sprintf("%-38s   %-38s\n", lhs, rhs);
    }
    ret += LINE;
    return ret;
}

static void
store_armour(string name, string type, int qmin, int qmax) 
{
    _armours[name] = ([ 
        ITEM_TYPE : type, 
        ITEM_CMIN : qmin * BRD_COIN_PER_QLTY, 
        ITEM_CMAX : qmax * BRD_COIN_PER_QLTY, 
    ]);
}

static void
store_weapon(string name, string type, int qmin, int qmax) 
{
    _weapons[name] = ([ 
        ITEM_TYPE : type, 
        ITEM_CMIN : qmin * BRD_COIN_PER_QLTY, 
        ITEM_CMAX : qmax * BRD_COIN_PER_QLTY, 
    ]);
}

static void
create() 
{
    ::create();
    _armours = ([ ]);
    store_armour("amulet", "amulet", 100, 150);
    store_armour("belt", "belt", 100, 175);
    store_armour("cloak", "cloak", 100, 175);
    store_armour("helmet", "helmet", 100, 175);
    store_armour("jacket", "armour", 100, 175);
    store_armour("pair of boots", "boot", 100, 175);
    store_armour("pair of gloves","glove", 100, 175);
    store_armour("pair of leggings", "legging", 100, 175);
    store_armour("ring", "ring", 100, 150);
    store_armour("shield", "shield", 100, 175);
    store_armour("tabard", "tabard", 100, 150);
    
    _weapons = ([ ]);
    store_weapon("axe", "axe", 100, 175);
    store_weapon("curved sword", "curved sword", 100, 175);
    store_weapon("dagger", "dagger", 100, 150);
    store_weapon("hammer", "hammer", 100, 175);
    store_weapon("piercing sword", "piercing sword", 100, 175);
    store_weapon("sword", "sword", 100, 175);
    store_weapon("twohanded axe", "greataxe", 100, 200);
    store_weapon("twohanded halberd", "halberd", 100, 200);
    store_weapon("twohanded hammer", "greathammer", 100, 200);
    store_weapon("twohanded katana", "katana", 100, 200);
    store_weapon("twohanded spear", "spear", 100, 200);
    store_weapon("twohanded sword", "greatsword", 100, 200);

    _table = create_table();

    set_male();
    set_name("Antonio");
    set_short("the merchant of Blackrock");
    set_long("He is a middle-aged bachelor and merchant by trade who has " +
             "his financial interests tied up in overseas shipments. He is " +
             "loved and revered by all the Christians who know him.");
    add_id(({ "merchant", "bachelor", "man" }));
    set_level(10);
    add_trigger("list", store_fp("do_list"));
    add_trigger("buy", store_fp("do_buy"));
    set_greeting(({ "*say I am Antonio, the merchant of Blackrock.",
                    "*say You may buy items off of me for black coins.",
                    "*say I respond to 'list' and 'buy <what> for <cost>'.",
                    store_fp("explain_render") }));
}

static void
explain_render(object this, object ply) 
{
    if (!objectp(ply)) {
        return;
    }
    command("tell " + ply->query_real_name() + " When you are down there, " +
            "try 'render on' for a different look on things.");
}

public int
do_list(string arg) 
{
    if (stringp(arg)) {
        return 0;
    }
    say("Antonio shows " + this_player()->query_name() + 
        " what is for sale.\n");
    write(_table);
    return 1;
}

private int
validate_cost(int cost, int min, int max) 
{
    if (cost < min) {
        return notify_fail("You must spend at least " + min + " coins.");
    }
    if (cost > max) {
        return notify_fail("You can spend at most " + max + " coins.");
    }
    return 1;
}

public int
do_buy(string arg) 
{
    mapping dat;
    object coin, item;
    string what;
    int cost, qlty;
    if (!stringp(arg)) {
        return notify_fail("Buy what?");
    }
    if (sscanf(arg, "%s for %d", what, cost) != 2) {
        return notify_fail("Buy <item> for <cost>.");
    }
    if (!objectp(coin = present(BRD_C_COIN, this_player())) ||
        coin->query_amount() < cost) 
    {
        return notify_fail("You do not have " + cost + " black coins.");
    }
    qlty = cost / BRD_COIN_PER_QLTY;
    if (mapp(dat = _armours[what])) {
        if (!validate_cost(cost, dat[ITEM_CMIN], dat[ITEM_CMAX])) {
            return 0;
        }
        catch(item = EMP_D_ARMOUR->create_armour(qlty, dat[ITEM_TYPE]));
    } else if (mapp(dat = _weapons[what])) {
        if (!validate_cost(cost, dat[ITEM_CMIN], dat[ITEM_CMAX])) {
            return 0;
        }
        catch(item = EMP_D_WEAPON->create_weapon(qlty, dat[ITEM_TYPE]));
    } else {
        return notify_fail("That is not for sale.");
    }
    if (!objectp(item)) {
        return notify_fail("There are none in stock right now.");
    }
    write("You pay " + cost + " black coins for " + item->short() + ".\n");
    say(this_player()->query_name() + " buys " + item->short() + ".\n");
    item->move(this_player());
    item->set_drop(NO_DROP);
    coin->add_amount(-cost);

    EMP_LOG("blackrock", this_player()->query_real_name() + " bought " + arg);
    return 1;
}
