#include "/d/Empire/islands/altdorf.h"

inherit EMP_I_ROOM;

void create() {
    ::create();
    set_light(1);
    set_short("Tots Blatter's Weapon Smithy");
    set_long("You are in the smithy of the renowned weaponsmith Tots " +
             "Blatter. The ground is covered with gravel and trampled hay. " +
             "Against the west wall stands a big furnace that keeps this " +
             "place warm even on the coldest of nights. A heavy anvil " +
             "stands near the exit. " +
             "There is a sign on the wall.");
    add_item(({ "sign" }),
             "While here you may:\n\n" +
             "  - %^BOLD%^cost <item>%^END%^, to evaluate an item\n" +
             "  - %^BOLD%^sharpen or improve <item>%^END%^, to sharpen an item\n" +
             "  - %^BOLD%^repair <item>%^END%^, to repair an item\n\n");
    add_item(({ "anvil", "black anvil", "heavy anvil" }), 
             "It is black and very heavy.");
    add_item(({ "furnace", "warm furnace", "big furnace" }), 
             "It is warm.");
    add_item(({ "west wall" }), 
             "There is nothing there but a warm furnace.");
    add_item(({ "gravel", "hay", "trampled hay" }), 
             "It is scattered on the ground, very uninteresting.");
    add_property(({ "hot", "indoors" }));

    add_reset_object("weaponsmith", ALT_DIR_OBJ + "weaponsmith");
    add_trigger("cost", store_fp("do_cost"));
    add_trigger("sharpen", store_fp("do_sharpen"));
    add_trigger("improve", store_fp("do_sharpen"));
    add_trigger("repair", store_fp("do_repair"));
}

int query_repair_cost(object obj) {
    int val;
    if (!objectp(obj)) {
        return 0;
    }
    if (!obj->query_property("weapon")) {
        return 0;
    }
    if (!obj->query_broken()) {
        return 0;
    }
    if ((val = obj->query_value()) == 0) {
        val = 100;
    }
    return val;
}

int query_sharpen_cost(object obj) {
    int ret;
    if (!objectp(obj)) {
        return 0;
    }
    if (!obj->query_property("weapon")) {
        return 0;
    }
    if ((int)obj->weapon_class() >= 20) {
        return 0;
    }
    if((ret = obj->query_value()) <= 0) {
        ret = 100;
    }
    if (obj->query_property("sharpened")) {
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
    if (!ret->query_property("weapon")) {
        notify_fail("That is not a weapon.");
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
    if ((val = query_sharpen_cost(obj)) > 0) {
        write("It will cost " + val + " coins to sharpen.\n");
    } else {
        write("It can not be sharpened.\n");
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
    if (objectp(obj->query_wield()) && !obj->unwield(1)) {
        return notify_fail("You fail to unwield it.");
    }
    if (!obj->repair()) {
        return notify_fail("That can not be repaired.");
    }
    write("The smith takes your weapon and repairs it.\n");
    say(ply->query_name() + " pays the smith some money to repair " +
        ply->query_possessive() + " " + obj->short() + ".\n");

    ply->add_money(-val);
    return 1;
}

int do_sharpen(string arg) {
    int val;
    object obj, ply;
    if (!objectp(obj = find_item(ply = this_player(), query_verb(), arg))) {
        return 0;
    }
    if ((val = query_sharpen_cost(obj)) <= 0) {
        return notify_fail("That can not be sharpened.");
    }
    if (ply->query_money() < val) {
        return notify_fail("You can not afford that.");
    }
    if (objectp(obj->query_wield()) && !obj->unwield(1)) {
        return notify_fail("You fail to unwield it.");
    }
    write("The smith takes your weapon and sharpens it.\n");
    say(ply->query_name() + " pays the smith some money to sharpen " +
        ply->query_possessive() + " " + obj->short() + ".\n");

    ply->add_money(-val);
    obj->set_class((val = (int)obj->weapon_class() + 5) < 20 ? val : 20);
    obj->add_property("sharpened");
    if (!obj->query_hook("__short")) {
        obj->add_hook("__short", store_fp("on_short"));
    }
    return 1;
}

string on_short() {
    return "[sharpened]";
}
