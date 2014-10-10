#include <armour.h>
#include "/d/Empire/islands/altdorf.h"

inherit EMP_I_ROOM;

void create() {
    ::create();
    set_light(1);
    set_short("Dalbran Fellhammer's Armour Smithy");
    set_long("You are in the smithy of the renowned armoursmith Dalbran " +
             "Fellhammer. Apart from the anvil and furnace used to forge "+
             "armours, there is sign on the wall.");
    add_item(({ "sign" }),
             "While here you may:\n\n" +
             "  - %^BOLD%^cost <item>%^END%^, to evaluate an item\n" +
             "  - %^BOLD%^harden <item>%^END%^, to harden an item\n" +
             "  - %^BOLD%^repair <item>%^END%^, to repair an item\n\n");
    add_item(({ "anvil", "black anvil" }), 
             "It is black and very heavy.");
    add_item(({ "furnace", "warm furnace" }), 
             "It is warm.");
    add_property(({ "hot", "indoors" }));
    
    add_reset_object("armoursmith", ALT_DIR_OBJ + "armoursmith");
    add_trigger("cost", store_fp("do_cost"));
    add_trigger("harden", store_fp("do_harden"));
    add_trigger("repair", store_fp("do_repair"));
}

int query_repair_cost(object obj) {
    int val, worn;
    if (!objectp(obj)) {
        return 0;
    }
    if (!obj->query_property("armour")) {
        return 0;
    }
    if ((worn = obj->query_property("worn_out")) == 0) {
        return 0;
    }
    if ((val = obj->query_value()) == 0) {
        val = 100;
    }

    return (val * worn) / 100;
}

int query_harden_cost(object obj) {
    int ret;
    if (!objectp(obj)) {
        return 0;
    }
    if (!obj->query_property("armour")) {
        return 0;
    }
    if ((obj->query_ac()) >= ARMOUR_MAXES[obj->query_type()]) {
        return 0;
    }
    if ((ret = obj->query_value()) <= 0) {
        ret = 100;
    }
    if (obj->query_property("hardened")) {
        ret *= 500;
    } else {
        ret *= 2;
    }
    return ret;
}

object find_item(object ply, string verb, string arg) {
    object ret;
    if (!objectp(ply)) {
        return 0;
    }
    if (!stringp(arg)) {
        notify_fail(capitalize(verb) + " what?");
        return 0;
    }
    if (!objectp(ret = present(arg, ply))) {
        notify_fail("You do not have that.");
        return 0;
    }
    if (!ret->query_property("armour")) {
        notify_fail("That is not a piece of armour.");
        return 0;
    }
    if (!objectp(present("smith"))) {
        notify_fail("There is noone here to help you.");
        return 0;
    }
    return ret;
}

int do_cost(string arg) {
    int val;
    object obj, ply;
    if (!objectp(obj = find_item(ply = this_player(), query_verb(), arg))) {
        return 0;
    }
    if ((val = query_repair_cost(obj)) > 0) {
        write("It will cost " + val + " coins to repair.\n");
    } else {
        write("It does not need to be repaired.\n");
    }
    if ((val = query_harden_cost(obj)) > 0) {
        write("It will cost " + val + " coins to harden.\n");
    } else {
        write("It can not be hardened.\n");
    }
    return 1;
}

int do_repair(string arg) {
    int val;
    object obj, ply;
    if (!objectp(obj = find_item(ply = this_player(), query_verb(), arg))) {
        return 0;
    }
    if ((val = query_repair_cost(obj)) <= 0) {
        return notify_fail("That can not be repaired.");
    }
    if (ply->query_money() < val) {
        return notify_fail("You can not afford that.");
    }
    if (objectp(obj->query_worn_by()) && !obj->remove()) {
        return notify_fail("You fail to remove it.");
    }
    write("The smith takes your armour and repairs it.\n");
    say(ply->query_name() + " pays the smith some money to repair " +
        ply->query_possessive() + " " + obj->short() + ".\n");

    ply->add_money(-val);
    obj->add_property("worn_out", 0);
    return 1;
}

int do_harden(string arg) {
    int val;
    object obj, ply;
    if (!objectp(obj = find_item(ply = this_player(), query_verb(), arg))) {
        return 0;
    }
    if ((val = query_harden_cost(obj)) <= 0) {
        return notify_fail("That can not be hardened.");
    }
    if (ply->query_money() < val) {
        return notify_fail("You can not afford that.");
    }
    if (objectp(obj->query_worn_by()) && !obj->remove()) {
        return notify_fail("You fail to remove it.");
    }
    write("The smith takes your armour and hardens it.\n");
    say(ply->query_name() + " pays the smith some money to harden " +
        ply->query_possessive() + " " + obj->short() + ".\n");

    ply->add_money(-val);
    obj->set_ac((int)obj->query_ac() + 1);
    obj->add_property("hardened");
    if (!obj->query_hook("__short")) {
        obj->add_hook("__short", store_fp("on_short"));
    }
    return 1;
}

string on_short() {
    return "[hardened]";
}
