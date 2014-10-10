
#include "/d/Artifact/artifact.h"

inherit EMP_I_ITEM;

static void setup_weapon(object obj) { }
static void unset_weapon(object obj) { }
static void setup_player(object obj) { }
static void unset_player(object obj) { }
static void setup_owner(object obj)  { }
static void unset_owner(object obj)  { }
static void setup_user(object obj)   { }
static void unset_user(object obj)   { }

private mapping _slots;
private mapping _skill_reqs;
private string *_spell_reqs;
private string *_quest_reqs;
private int     _level_req;
private int     _str_req;
private int     _dex_req;
private int     _con_req;
private int     _int_req;

static void
create()
{
    ::create();
    _slots      = ([ ]);
    _skill_reqs = ([ ]);
    _spell_reqs = ({ });
    _quest_reqs = ({ });
    _level_req  = 0;
    _con_req    = 0;
    _dex_req    = 0;
    _int_req    = 0;
    _str_req    = 0;
}

public varargs nomask void
leave_env(object from, object to)
{
    object obj;
    if (!objectp(from) || !from<-ART_C_WEAPON) {
        return;
    }
    unset_weapon(from);
    if (objectp(obj = from->query_player())) {
        unset_player(obj);
    }
    if (objectp(obj = from->query_owner())) {
        unset_owner(obj);
    }
    if (objectp(obj = from->query_user())) {
        unset_user(obj);
    }
    from->remove_hook("__move");
    from->remove_hook("__wield");
    from->remove_hook("__remove");
    from->release_slots(_slots);
}

public varargs nomask void
enter_env(object to, object from)
{
    object obj;
    if (!objectp(to) || !to<-ART_C_WEAPON) {
        return;
    }
    setup_weapon(to);
    if (objectp(obj = to->query_player())) {
        setup_player(obj);
    }
    if (objectp(obj = to->query_owner())) {
        setup_owner(obj);
    }
    if (objectp(obj = to->query_user())) {
        setup_user(obj);
    }
    to->add_hook("__move", store_fp("update_owner"));
    to->add_hook("__wield", store_fp("setup_user_on_wield"));
    to->add_hook("__remove", store_fp("unset_user_on_remove"));
    to->retain_slots(_slots);
}

public nomask object
query_weapon()
{
    object wpn;
    if (!objectp(wpn = environment()) ||
        !wpn<-ART_C_WEAPON)
    {
        return 0;
    }
    return wpn;
}

static varargs nomask mixed
call_weapon(string fnc, mixed args...)
{
    object wpn;
    if (!objectp(wpn = query_weapon())) {
        return 0;
    }
    return call_other(wpn, fnc, args...);
}

public nomask object
query_player()
{
    return call_weapon("query_player");
}

public nomask object
query_control()
{
    return call_weapon("query_control");
}

public nomask object
query_owner()
{
    return call_weapon("query_owner");
}

public nomask object
query_user()
{
    return call_weapon("query_user");
}

public nomask object
query_room()
{
    return call_weapon("query_room");
}

static nomask void
update_owner(object from, object to)
{
    if (objectp(from) && living(from)) {
        unset_owner(from);
    }
    if (objectp(to) && living(to)) {
        setup_owner(to);
    }
}

static nomask void
setup_user_on_wield()
{
    object usr;
    if (objectp(usr = query_user())) {
        return;
    }
    setup_user(usr);
}

static nomask void
unset_user_on_remove()
{
    object usr;
    if (!objectp(usr = query_user())) {
        return;
    }
    unset_user(usr);
}

public nomask string
desc_slots_short()
{
    string *arr, *ret;
    int i, len, val;
    ret = ({ });
    arr = sort_array(keys(_slots), "sort_alpha_asc", FILTER_OB);
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        val = _slots[arr[i]];
        ret += ({ (val > 0 ? "+" : "") + val + " " + arr[i] });
    }
    return implode(ret, " ");
}

public nomask string
desc_slots_long()
{
    string *arr, *out, *ret;
    int i, len, val;
    ret = ({ });
    arr = sort_array(keys(_slots), "sort_alpha_asc", FILTER_OB);
    out = ({ });
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        if ((val = _slots[arr[i]]) < 0) {
            out += ({ (-val) + " " + arr[i] });
        }
    }
    if (sizeof(out) > 0) {
        ret += ({ "requires " + make_list(out) });
    }
    out = ({ });
    for (i = 0; i < len; ++i) {
        if ((val = _slots[arr[i]]) > 0) {
            out += ({ val + " " + arr[i] });
        }
    }
    if (sizeof(out) > 0) {
        ret += ({ "provides " + make_list(out) });
    }
    if (sizeof(ret) == 0) {
        return "No slots.";
    }
    return capitalize(make_list(ret)) + " slots.";
}

public nomask void
set_slots(mapping val)
{
    _slots = val;
}

public nomask mapping
query_slots()
{
    return _slots;
}

public nomask void
set_slot(string key, int val)
{
    _slots[key] = val;
}

public nomask int
query_slot(string key)
{
    return _slots[key];
}

public varargs int
can_use(object ply, object wpn)
{
    string *arr;
    int i, len;
    if (!objectp(ply)) {
        return 0;
    }
    for (i = 0, len = sizeof(arr = keys(_skill_reqs)); i < len; ++i) {
        int req;
        req = _skill_reqs[arr[i]];
        if (ply->query_skill(arr[i]) >= req) {
            continue;
        }
        return notify_fail("Insufficient " + ART_MASTER->skill_name(arr[i]) +
                           " skill (" + req + " required).");
    }
    for (i = 0, len = sizeof(_spell_reqs); i < len; ++i) {
        object obj;
        obj = ART_D_SLIVER->query_sliver(_spell_reqs[i]); // never null
        if (ply->query_property(ART_P_SPELL(obj))) {
            continue;
        }
        return notify_fail("Required spell '" + obj->query_name() +
                           "' not trained.");
    }
    for (i = 0, len = sizeof(_quest_reqs); i < len; ++i) {
        if (ART_D_QUEST->is_unlocked(ply, _quest_reqs[i])) {
            continue;
        }
        return notify_fail("Required quest '" +
                           ART_D_QUEST->query_title(_quest_reqs[i]) +
                           "' not unlocked.");
    }
    if (ply->query_level() < _level_req) {
        return notify_fail("Insufficient level (" + _level_req +
                           " required).");
    }
    if (ply->query_con() < _con_req) {
        return notify_fail("Insufficient constitution (" + _con_req +
                           " required).");
    }
    if (ply->query_dex() < _dex_req) {
        return notify_fail("Insufficient dexterity (" + _dex_req +
                           " required).");
    }
    if (ply->query_int() < _int_req) {
        return notify_fail("Insufficient intelligence (" + _int_req +
                           " required).");
    }
    if (ply->query_str() < _str_req) {
        return notify_fail("Insufficient strength (" + _str_req +
                           " required).");
    }
    return 1;
}

public nomask string
desc_reqs_short()
{
    string *arr, *ret;
    int i, len;
    ret = ({ });
    if (_level_req > 0) {
        ret += ({ "level " + _level_req });
    }
    if (_str_req > 0) {
        ret += ({ "str " + _str_req });
    }
    if (_dex_req > 0) {
        ret += ({ "dex " + _dex_req });
    }
    if (_con_req > 0) {
        ret += ({ "con " + _con_req });
    }
    if (_int_req > 0) {
        ret += ({ "int " + _int_req });
    }
    for (i = 0, len = sizeof(arr = keys(_skill_reqs)); i < len; ++i) {
        ret += ({ ART_MASTER->skill_name(arr[i]) + " " +
                  _skill_reqs[arr[i]] });
    }
    for (i = 0, len = sizeof(arr = _spell_reqs); i < len; ++i) {
        ret += ({ ART_D_SLIVER->query_sliver(arr[i])->query_name() });
    }
    for (i = 0, len = sizeof(arr = _quest_reqs); i < len; ++i) {
        ret += ({ ART_D_QUEST->query_title(arr[i]) });
    }
    ret = sort_array(ret, "sort_alpha_asc", FILTER_OB);
    return implode(ret, ", ");
}

public nomask string
desc_reqs_long()
{
    string *arr, *ret;
    int i, len;
    ret = ({ });
    if (_level_req > 0) {
        ret += ({ "level " + _level_req });
    }
    if (_str_req > 0) {
        ret += ({ "strength " + _str_req });
    }
    if (_dex_req > 0) {
        ret += ({ "dexterity " + _dex_req });
    }
    if (_con_req > 0) {
        ret += ({ "constitution " + _con_req });
    }
    if (_int_req > 0) {
        ret += ({ "intelligence " + _int_req });
    }
    for (i = 0, len = sizeof(arr = keys(_skill_reqs)); i < len; ++i) {
        ret += ({ ART_MASTER->skill_name(arr[i]) + " " +
                  _skill_reqs[arr[i]] });
    }
    for (i = 0, len = sizeof(arr = _spell_reqs); i < len; ++i) {
        ret += ({ ART_D_SLIVER->query_sliver(arr[i])->query_name() });
    }
    for (i = 0, len = sizeof(arr = _quest_reqs); i < len; ++i) {
        ret += ({ ART_D_QUEST->query_title(arr[i]) });
    }
    if (sizeof(ret) == 0) {
        return "No requirements.";
    }
    ret = sort_array(ret, "sort_alpha_asc", FILTER_OB);
    return "Requires " + make_list(ret) + ".";
}

public nomask void
set_skill_reqs(mapping val)
{
    _skill_reqs = val;
}

public nomask mapping
query_skill_reqs()
{
    return _skill_reqs;
}

public nomask void
add_skill_req(string key)
{
    _skill_reqs[key] = 100;
}

public nomask void
set_skill_req(string key, int val)
{
    _skill_reqs[key] = val;
}

public nomask int
query_skill_req(string key)
{
    return _skill_reqs[key];
}

public nomask void
set_spell_reqs(string *val)
{
    _spell_reqs = val;
}

public nomask string *
query_spell_reqs()
{
    return _spell_reqs;
}

public nomask void
add_spell_req(string val)
{
    _spell_reqs |= ({ val });
}

public nomask int
query_spell_req(string val)
{
    return sizeof(_spell_reqs & ({ val }));
}

public nomask void
set_quest_reqs(string *val)
{
    _quest_reqs = val;
}

public nomask string *
query_quest_reqs()
{
    return _quest_reqs;
}

public nomask void
add_quest_req(string val)
{
    _quest_reqs |= ({ val });
}

public nomask int
query_quest_req(string val)
{
    return sizeof(_quest_reqs & ({ val }));
}

public nomask void
set_level_req(int val)
{
    _level_req = val;
}

public nomask int
query_level_req()
{
    return _level_req;
}

public nomask void
set_con_req(int val)
{
    _con_req = val;
}

public nomask int
query_con_req()
{
    return _con_req;
}

public nomask void
set_dex_req(int val)
{
    _dex_req = val;
}

public nomask int
query_dex_req()
{
    return _dex_req;
}

public nomask void
set_int_req(int val)
{
    _int_req = val;
}

public nomask int
query_int_req()
{
    return _int_req;
}

public nomask void
set_str_req(int val)
{
    _str_req = val;
}

public nomask int
query_str_req()
{
    return _str_req;
}
