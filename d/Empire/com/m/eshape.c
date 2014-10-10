#include "/d/Empire/empire.h"

#define P_ENABLE ("emp_shape")

inherit base CMD_MODULE;
inherit util EMP_I_UTIL;

static void create() {
    base::create();
    util::create();
}

private string query_color(int val) {
    switch (val) {
    case 0..30:  return "%^B_RED%^"; 
    case 31..60: return "%^B_YELLOW%^"; 
    default:     return "%^B_GREEN%^"; 
    }
}

private string query_bar(int val) {
    string ret;
    int cnt;
    ret = "";
    val = max(0, min(100, val));
    if ((cnt = (val * 30) / 100) > 0) {
	ret += query_color(val) + sprintf("%-' '*s", cnt, "");
    }
    if ((cnt = ((100 - val) * 30) / 100) > 0) {
	ret += "%^END%^%^B_BLUE%^" + sprintf("%-' '*s", cnt, "");
    }
    ret += "%^END%^";
    return ret;
}

static int main(string arg) {
    object ply, foe, env;
    int val;
    if (!objectp(ply = this_player()) || 
	!objectp(env = environment(ply)))
    {
	return 0;
    }
    if (!stringp(arg)) {
	if (!objectp(foe = ply->query_attack())) {
            return notify_fail("Check whose shape?");
        }
    } else if (!objectp(foe = present(arg, env))) {
        return notify_fail("You do not see that here!");
    }
    if (ply->test_dark(1)) {
        return notify_fail("It is too dark!");
    }
    if (foe->query_property("no_shape")) {
	return notify_fail("You fail!");
    }
    val = ((int)foe->query_hp() * 100) / max(1, (int)foe->query_max_hp());
    write(bold(foe->query_name()) + " " + 
	  query_bar(val) + " (" + val + "%)\n");
    return 1;
}

public string short_help() {
    return "Prints the condition of a monster.\n";
}
