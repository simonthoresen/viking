#include "/d/Empire/empire.h"

inherit I_ITEM;

private object _rider;
private object _mount;
private string _short;
private string _min;
private string _mout;

static void create() {
    ::create();
    _rider = 0;
    _mount = 0;
    _short = 0;
    _min   = 0;
    _mout  = 0;

    set_name("leather reins");
    set_short("a set of leather reins");
    set_long("A leather strap, fastened to each end of the " +
             "bit of a bridle, by which a rider can control " +
             "a horse or other animal by pulling so as to " +
             "exert pressure on the bit. This is your ticket " +
             "to ride!");
    add_id(({ "rein", "reins", "strap", "leather strap" }));
    set_weight(1);
    set_value(666);
    set_drop(NO_DROP);

    add_hook("__short", store_fp("on_short"));
    add_hook("__move", store_fp("on_move"));
    add_hook("__destroy", store_fp("on_destroy"));
}

public string extra_look() {
    object ply;
    if (!objectp(ply = environment())) {
        return 0;
    }
    if (!objectp(_mount)) {
        return 0;
    }
    return capitalize(ply->query_pronoun()) +
        " is riding " + _short;
}

public void unmount() {
    if (objectp(_rider) && objectp(_mount)) {
        EMP_D_LOG->log("reins", sprintf("%s (%d) unmounted %s (%d) in %O.",
                                        _rider->query_real_name(),
                                        _rider->query_level(),
                                        source_file_name(_mount),
                                        _mount->query_level(),
                                        environment(_mount)));
    }
    if (objectp(_rider)) {
        object env;
        _rider->remove_hook("__battack");
        _rider->remove_hook("__destroy");
        _rider->remove_hook("__move");
        _rider->remove_hook("__short");
        _rider->setmout(stringp(_mout) ? _mout : "leaves");
        _rider->setmin(stringp(_min) ? _min : "arrives");

        tell_object(_rider, "You dismount " + _mount->query_name() + ".\n");
        if (objectp(env = environment(_rider))) {
            tell_room(env, _rider->query_name() + " dismounts " +
                      _mount->query_name() + ".\n", ({ _rider }));
        }
    }
    if (objectp(_mount)) {
        _mount->set_short(_short);
        _mount->remove_hook("__destroy");
    }
    _rider = 0;
    _mount = 0;
    _short = 0;
    _mout  = 0;
    _min   = 0;
}

public int mount(object mob) {
    object ply, env;
    unmount(); /* _P_A_R_A_N_O_I_A_ */
    if (!objectp(ply = environment()) || !living(ply) ||
        !objectp(mob) || !living(mob) || interactive(mob) || mob == ply)
    {
        return 0;
    }
    EMP_D_LOG->log("reins", sprintf("%s (%d) mounted %s (%d) in %O.",
                                    ply->query_real_name(), ply->query_level(),
                                    source_file_name(mob), mob->query_level(),
                                    environment(mob)));
    _rider = ply;
    _mount = mob;
    _short = _mount->short();
    _mount->set_short(0);
    _mount->set_aggressive(0);
    _mount->set_wandering_chance(0);
    _mount->add_hook("__destroy", store_fp("on_mount_destroy"));
    _rider->add_hook("__battack", store_fp("on_rider_battack"));
    _rider->add_hook("__destroy", store_fp("on_rider_destroy"));
    _rider->add_hook("__move", store_fp("on_rider_move"));
    _rider->add_hook("__short", store_fp("on_rider_short"));
    _mout = _rider->query_msgout();
    _min  = _rider->query_msgin();
    _rider->setmout("rides " + _short);
    _rider->setmin("rides in on " + _short);

    tell_object(_rider, "You mount " + _mount->query_name() + ".\n");
    if (objectp(env = environment(_rider))) {
        tell_room(env, _rider->query_name() + " mounts " +
                  _mount->query_name() + ".\n", ({ _rider }));
    }
    return 1;
}

static void on_move(object from, object to) {
    unmount();
}

static string on_short() {
    if (!objectp(_mount)) {
        return 0;
    }
    return "[on " + _short + "]";
}

static void on_destroy() {
    unmount();
}

public void on_rider_battack(object foe) {
    if (objectp(_mount) && !objectp(_mount->query_attack())) {
        _mount->do_attack(foe);
    }
}

public void on_rider_destroy() {
    unmount();
}

public void on_rider_move(object from, object to) {
    if (objectp(_mount)) {
        _mount->move(to);
    }
}

public string on_rider_short() {
    if (!objectp(_mount)) {
        return 0;
    }
    return "riding " + _short;
}

public void on_mount_destroy() {
    unmount();
}

public object query_rider() {
    return _rider;
}

public object query_mount() {
    return _mount;
}
