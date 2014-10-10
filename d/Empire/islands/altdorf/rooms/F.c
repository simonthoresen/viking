#include "/d/Empire/islands/altdorf.h"

inherit EMP_I_ROOM;

void create() {
    ::create();
    set_short("Association of Financiers and Moneylenders");
    set_long("You are in the house of the Association of Financiers and " +
             "Moneylenders. This marble hall echoes as you walk across it " +
             "towards the counter. Behind the counter you can see a clerk. " +
             "On the wall behind him there is a sign.");
    add_item("clerk", "You try to catch the clerk's eye, and he responds " +
                      "immediately. 'What can I do for you?' he says " +
                      "in a businesslike manner.");
    add_item("sign", "The sign reads:\nYou can deposit or withdraw money " +
             "from your account here.");
    add_item("counter", "You see nothing of interest, except from an " +
                        "hourglass.");
    add_item("hourglass", store_fp("exa_hourglass"));
    add_property("indoors");
    set_light(1);

    add_trigger("balance", store_fp("do_balance"));
    add_trigger("deposit", store_fp("do_deposit"));
    add_trigger("withdraw", store_fp("do_withdraw"));
    add_reset_object("guard", ALT_C_SENTRY, 2);
}

string exa_hourglass() {
    return "It rests on the counter, and currently shows " + 
        EMP_D_TIME->query_stime() + ".";
}

int do_balance(string arg) {
    object ply;
    if (!objectp(ply = this_player())) {
        return 0;
    }
    write("Your balance is " + ply->query_account() + " coins.\n");
    say(ply->query_name() + " checks " + ply->query_possessive() + 
        " account.\n");
    return 1;
}

int do_deposit(string arg) {
    object ply;
    int val;
    if (!objectp(ply = this_player())) {
        return 0;
    }
    if (!stringp(arg) || !sscanf(arg, "%d", val)) {
        return notify_fail("Deposit how much?");
    }
    if (val > ply->query_money()) {
        return notify_fail("You do not have that much money.");
    }
    ply->add_money(-val);
    ply->set_account(ply->query_account() + val);
    ply->save_me();

    write("You deposit " + val + " coins. Your current balance is " +
          ply->query_account() + ".\n");
    say(ply->query_name() + " deposits some money.\n");
    return 1;
}

int do_withdraw(string arg) {
    object ply;
    int val;
    if (!objectp(ply = this_player())) {
        return 0;
    }
    if (!stringp(arg) || !sscanf(arg, "%d", val)) {
        return notify_fail("Deposit how much?");
    }
    if (val > ply->query_account()) {
        return notify_fail("You do not have that much money.");
    }
    ply->add_money(val);
    ply->set_account(ply->query_account() - val);
    ply->save_me();

    write("You withdraw " + val + " coins. Your current balance is " +
          ply->query_account() + ".\n");
    say(ply->query_name() + " deposits some money.\n");
    return 1;
}
