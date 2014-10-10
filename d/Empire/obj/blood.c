#include "/d/Empire/empire.h"

inherit EMP_C_LIQUID;

private object _victim;

static void create() {
    ::create();
    set_name("blood");
    set_color("%^RED%^");
    set_long("It is the blood of some poor bastard.");
}

public object clone() {
    object obj;
    obj = ::clone();
    obj->set_victim(_victim);
    return obj;
}

public void set_victim(object val) {
    _victim = val;
}

public object query_victim() {
    return _victim;
}

public void set_blood(int val) {
    set_amount(val);
}

public void add_blood(int val) {
    add_amount(val);
}

public int query_blood() {
    return query_amount();
}
