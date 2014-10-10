#include "/d/Empire/islands/chaos.h"

inherit I_ROOM;

private int    _chance;
private string _landing;
private string _splash;

static void create() {
    ::create();
    _chance  = 0;
    _landing = 0;
    _splash  = read_file(CAS_DIR_ETC + "splash.art");

    set_short("The void");
    set_long("You are falling through the void.");
    set_light(1);
    add_property("no_telein");
    add_hook("__enter_inv", store_fp("on_enter_inv"));
    add_exit(R_VOID, "down", store_fp("block_exit"));
}

public int block_exit() {
    write("Yes, yes!\n");
    return 1;
}

static void on_enter_inv(object obj, object from) {
    call_out("maybe_land", 0.1);
}

public void set_splash(string val) {
    _splash = val;
}

public string query_splash() {
    return _splash;
}

public void set_landing(string val) {
    _landing = val;
}

public string query_landing() {
    if (stringp(_landing)) {
        return _landing;
    }
    return sprintf("%saltdorf/%d/%d", EMP_DIR_VAR_ISLANDS,
                   17 + random(3), 39 + random(10));
}

public void maybe_land() {
    if (100 + random(100) < ++_chance) {
        map_array(all_inventory(), "perform_land");
        destroy();
    } else {
        map_array(all_inventory(), "echo_falling");
        call_out("maybe_land", 0.1);
    }
}

static void echo_falling(object obj) {
    if (!objectp(obj) || !interactive(obj)) {
        return;
    }
    if (!random(5)) {
        tell_object(obj, sprintf("%*c", random(obj->query_width()), '?'));
    }
    tell_object(obj, "\n\n");
}

static void perform_land(object obj) {
    string str;
    object env;
    if (!stringp(str = query_landing()) ||
        !objectp(env = str->__bootstrap()))
    {
        env = R_CHURCH->__bootstrap();
    }
    if (living(obj)) {
        if (stringp(_splash)) {
            tell_object(obj, _splash);
        }
        obj->move_player("down", env);
    } else {
        obj->move(env);
    }
}
