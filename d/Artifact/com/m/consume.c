#include "/d/Artifact/artifact.h"

inherit CMD_MODULE;

private int
require_release(object obj)
{
    return notify_fail("You must release your " +
                       obj->query_name() + " first.");
}

private int
can_wear(object ply, object obj)
{
    string str;
    object old;
    str = obj->query_type();
    if (objectp(old = ply->query_worn_armour(str))) {
        return require_release(old);
    }
    if (objectp(old = ply->query_weapon(0)) && str == "shield") {
        return require_release(old);
    }
    return 1;
}

private int
can_wield(object ply, object obj)
{
    object lhs, rhs;
    if (!objectp(lhs = ply->query_weapon(0))) {
        lhs = ply->query_worn_armour("shield");
    }
    rhs = ply->query_weapon(1);
    if (obj->query_type() == "twohanded") {
        if (objectp(lhs)) {
            return require_release(lhs);
        }
        if (objectp(rhs)) {
            return require_release(rhs);
        }
    } else {
        if (objectp(lhs) && objectp(rhs)) {
            return require_release(rhs);
        }
    }
    return 1;
}

private int
can_consume(object obj)
{
    if (obj<-I_DRINK || obj<-I_FOOD) {
        return 1;
    }
    if (obj<-I_ARMOUR || obj<-I_WEAPON) {
        if (obj->query_property("tagged")) {
            return notify_fail("That is tagged.");
        }
        if (obj->is_used()) {
            return notify_fail("That is in use.");
        }
        return 1;
    }
    return notify_fail("You can not consume that.");
}

private int
try_consume(object ply, object obj)
{
    string str;
    if (obj->drop(1) == NO_DROP) {
        return notify_fail("You fail.");
    }
    if (obj<-I_DRINK) {
        return obj->drink(obj->query_name());
    }
    if (obj<-I_FOOD) {
        return obj->eat(obj->query_name());
    }
    if ((obj<-I_ARMOUR && !can_wear(ply, obj)) ||
        (obj<-I_WEAPON && !can_wield(ply, obj)))
    {
        return 0;
    }
    obj->move(ply);
    if (environment(obj) != ply) {
        return notify_fail("You fail.");
    }
    str = maybe_add_article(obj->short(), 1);
    write("You consume " + str + ".\n");
    if ((obj<-I_ARMOUR && obj->wear(1)) ||
        (obj<-I_WEAPON && obj->wield(objectp(ply->query_weapon(1)), 1)))
    {
        write("You trap the powers of " + str + " within yourself.\n");
        obj->add_property("unremovable");
        obj->add_property("protected");
        return 1;
    }
    write(capitalize(str) + " breaks.\n");
    obj->destroy();
    return 0;
}

private object
find_item(string arg, object env)
{
    object obj, *arr;
    int i, len;
    if (objectp(obj = present(arg, env))) {
        return obj;
    }
    if (!living(env)) {
        return 0;
    }
    for (i = 0, len = sizeof(arr = all_inventory(env)); i < len; ++i) {
        if (objectp(obj = present(arg, arr[i]))) {
            return obj;
        }
    }
    return 0;
}

static int
main(string arg)
{
    object ply, env, wpn, obj;
    string str;
    if (!objectp(ply = this_player()) ||
        !objectp(wpn = ART_C_WEAPON->get_instance(ply)) ||
        wpn->is_suspended())
    {
        write("You have no physical form.\n");
        return 1;
    }
    if (!objectp(env = environment(wpn))) {
        return notify_fail("You are not anywhere.");
    }
    if (!stringp(arg)) {
        return notify_fail("Consume what?");
    }
    if (!objectp(obj = find_item(arg, env)) &&
        !objectp(obj = present(arg, wpn->query_room())))
    {
        return notify_fail("That is not here.");
    }
    if (obj == wpn) {
        return notify_fail("You can not consume yourself.");
    }
    if (!can_consume(obj)) {
        return 0; /* can_consume() notifies fail */
    }
    str = obj->short();
    if (!try_consume(ply, obj)) {
        return 0; /* try_consume() notifies fail */
    }
    wpn->message_room(ply->query_name() + " consumes " + str + ".\n", wpn);
    return 1;
}

public string
short_help()
{
    return "Consume an item.";
}
