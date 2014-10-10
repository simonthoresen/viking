#include <std.h>
#include "/d/Empire/islands/matouci.h"

#define DIR_EVENT (MAT_DIR_EVENTS + "dranosh_saurfang/")
#define C_FRENZY  (DIR_EVENT + "blood_frenzy")

inherit EMP_I_WEAPON;

private mapping _spells;
private int     _blood;
private int     _blood_wc;
private int     _fury_lim;

static void
create() 
{
    ::create();
    _spells   = 0;
    _blood    = 0;
    _blood_wc = 0;
    _fury_lim = 0;
    set_info(store_fp("on_info"));
    add_hook("__weapon_hit", store_fp("on_weapon_hit"));
    add_hook("__wield", store_fp("on_wield"));
    add_hook("__remove", store_fp("on_remove"));
    add_trigger("cast", store_fp("do_cast"));
}

public void
set_fury_lim(int val) 
{
    _fury_lim = val;
}

public int
query_fury_lim() 
{
    return _fury_lim;
}

public void
set_blood_wc(int val) 
{
    _blood_wc = val;
}

public int
query_blood_wc() 
{
    return _blood_wc;
}

public void
add_spell(string name, int blood, int sp, function fnc) 
{
    if (!mapp(_spells)) {
	_spells = ([ ]);
    }
    _spells[name] = ({ blood, sp, fnc });
}

public string *
query_spells() 
{
    if (!mapp(_spells)) {
        return 0;
    }
    return filter_array(keys(_spells), "can_cast");
}

public int
can_cast(string spell) 
{
    mixed arr;
    object ply;
    return mapp(_spells) &&
           objectp(ply = query_wield()) && 
           arrayp(arr = _spells[spell]) &&
           arr[0] <= _blood &&
           arr[1] <= ply->query_sp();
}

private void
notify_blood(int prev, int next) 
{
    string *arr, key;
    int i, len, lim;
    object ply;
    if (!objectp(ply = query_wield())) {
        return;
    }
    arr = sort_array(keys(_spells), "alpha_asc", FILTER_OB);
    for (i = 0, len = sizeof(arr = keys(_spells)); i < len; ++i) {
        key = arr[i];
        lim = _spells[key][0];
        if (prev < lim && next >= lim) {
            tell_object(ply, bold("Spell enabled: ") + 
                        capitalize(key) + "\n");
        } else if (prev >= lim && next < lim) {
            tell_object(ply, bold("Spell disabled: ") + 
                        capitalize(key) + "\n");
        }
    }
}

public int
query_blood() 
{
    return _blood;
}

private string
query_blood_bar(int len) 
{
    string ret;
    int val;
    ret = "";
    val = (len * _blood) / 100;
    if (val > 0) {
        ret += "%^B_RED%^" + sprintf("%-' '*s", val, "") + "%^END%^";
    } 
    if (val < len) {
        ret += "%^B_BLUE%^" + sprintf("%-' '*s", len - val, "") + "%^END%^";
    }
    return ret;
}

public void
set_blood(int val) 
{
    object ply;
    if (val < 0 && objectp(ply = query_wield())) {
        ply->reduce_hit_point(val);
        val = 0;
    }
    if (val > 100 && objectp(ply = query_wield())) {
        ply->reduce_hit_point(-(val - 100));
        val = 100;
    }
    notify_blood(_blood, val);
    _blood = val;
}

public void
add_blood(int val) 
{
    set_blood(_blood + val);
}

static void
on_wield(object obj, string hand)
{
    object ply;
    if (objectp(ply = query_wield())) {
        ply->add_hook("__heart_beat", store_fp("on_wielder_heart_beat"));
    }
}

static void
on_remove()
{
    object ply, obj;
    if (objectp(ply = query_wield())) {
        ply->remove_hook("__heart_beat");
	if (objectp(obj = present(C_FRENZY, ply))) {
            obj->destroy();
        }
    }
    set_blood(0);
}

public void 
on_wielder_heart_beat()
{
    object ply;
    ply = previous_object();
    if (!objectp(ply->query_attack())) {
	add_blood(-1);
	return;
    } 
    if (ply->query_hp() < (ply->query_max_hp() * _fury_lim) / 100 &&
	!objectp(present(C_FRENZY, ply)))
    {
	make(C_FRENZY, ply);
    }
}

static string
on_info() 
{
    string *arr, key, ret;
    int i, len, val;
    ret = "---------------------------------------------\n";
    if (mapp(_spells)) {
	ret += "Spell name                       Blood   Mana\n"; 
	ret += "---------------------------------------------\n";
	arr = sort_array(keys(_spells), "alpha_asc", FILTER_OB);
	for (i = 0, len = sizeof(arr = keys(_spells)); i < len; ++i) {
	    key = arr[i];
	    ret += sprintf("%-30s   %5d   %4d\n", 
			   capitalize(key),
			   _spells[key][0],
			   _spells[key][1]);
	}
	ret += "---------------------------------------------\n";
    }
    ret += "Blood: " + query_blood_bar(38) + "\n";
    ret += "---------------------------------------------";
    return ret;
}

static int
on_weapon_hit(object foe) 
{
    add_blood(1);
    return (_blood * _blood_wc) / 100;
}

static int
do_cast(string arg) 
{
    object ply, foe, env;
    mixed dat;
    if (!objectp(ply = query_wield()) ||
        !objectp(env = environment(ply)))
    {
	return 0;
    }
    if (!objectp(foe = ply->query_attack())) {
	return notify_fail("You are not in combat.");
    }
    if (!arrayp(dat = _spells[arg])) {
	return notify_fail("There is no such spell.");
    }
    if (dat[0] > query_blood()) {
	return notify_fail("Not enough blood (" + 
			   dat[0] + " required).");
    }
    if (dat[1] > ply->query_sp()) {
	return notify_fail("Not enough spell points (" + 
			   dat[1] + " required).");
    }
    arg = upper_case(arg);
    write("You scream: " + arg + "!\n");
    say(ply->query_name() + " screams: " + arg + "!\n");

    catch(call_fp(dat[2], ply, foe, env));

    ply->reduce_spell_point(dat[1]);
    add_blood(-dat[0]);
    return 1;
}

