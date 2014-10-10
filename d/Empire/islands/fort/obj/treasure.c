#include "/d/Empire/islands/fort.h"

inherit I_CONTAINER;

private string *_keys;

static void
create()
{
    ::create();
    _keys = ({ });

    set_name("chest");
    set_short("a large wooden chest");
    set_long("This large wooden chest is very dirty, as if it has been " +
             "buried in the ground for some time.");
    add_id(({ "large wooden chest", "large chest", "wooden chest" }));
    add_property("wood");
    set_max_weight(30);
    set_can_open(1);
    set_value(500);
    set_weight(3);
    add_hook("__long", store_fp("desc_locks"));
    add_hook("__bopen", store_fp("require_unlocked"));
    add_trigger("unlock", store_fp("do_unlock"));

    if (clonep(this_object())) {
        make(C_MONEY)->add_money(75000 + random(25000));
        EMP_D_TREASURE->add_treasure(10000);
    }
}

public int
is_locked()
{
    return sizeof(_keys) < FOR_NUM_WINGS;
}

static string
desc_locks()
{
    int cnt;
    switch(cnt = FOR_NUM_WINGS - sizeof(_keys)) {
    case 0:
        return 0;
    case 1:
        return "There is a lock on it.";
    default:
        return "There are " + convert_number(cnt) + " locks on it.";
    }
}

static int
do_unlock(string arg)
{
    object ply, *arr;
    ply = this_player();
    if (!is_locked()) {
        return notify_fail("It is not locked.");
    }
    if (!sizeof(map_array(all_inventory(ply), "try_unlock") - ({ 0 }))) {
        return notify_fail("You do not have a key that fits.");
    }
    if (!is_locked() && !ply->query_quests("treasure_of_fort_dumbarton")) {
        ply->set_quest("treasure_of_fort_dumbarton");
        write("Congratulations! You solved the quest to find the treasure " +
              "of Fort Dumbarton.\n");
    }
    return 1;
}

static int
try_unlock(object obj)
{
    string key;
    if (!objectp(obj) || !obj<-FOR_C_KEY) {
        return 0;
    }
    key = obj->query_keycode();
    if (sizeof(_keys & ({ key }))) {
        return 0;
    }
    _keys += ({ key });
    write("Your " + obj->query_name() + " breaks as you open the lock.\n");
    say(this_player()->query_name() + " opens a lock on the " +
        query_name() + ".\n");
    obj->destroy();
    return 1;
}

static int
require_unlocked(int is_open)
{
    if (is_locked()) {
        write("It is locked.\n");
        return 1;
    }
    return 0;
}
