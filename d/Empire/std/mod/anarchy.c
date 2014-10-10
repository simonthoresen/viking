#include "/d/Empire/empire.h"

public varargs int  add_hook(string h_name, mixed hook, mixed args);
public varargs void add_property(mixed argv...);

static void create() {
    add_hook("__enter_inv", store_fp(EMP_D_ANARCHY, "enter_anarchy"));
    add_hook("__leave_inv", store_fp(EMP_D_ANARCHY, "leave_anarchy"));
    add_property("anarchy");
}

