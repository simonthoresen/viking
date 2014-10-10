#include "/d/Empire/islands/altdorf.h"

inherit ALT_I_CITIZEN;

static void
create()
{
    ::create();
    set_name("Weissmann");
    set_short("Weissmann the wiseman");
    set_long("An extremely old man. If there is something he hasn't seen, " +
             "then you probably will never see it.");
    set_male();
    set_race("human");
    add_id(({ "wiseman", "weissmann", "man", "old man" }));
    set_ac(20);
    set_level(25);
    set_int(50);
    set_al(600);
    set_bored_secs(300);
    set_hp(1000 + random(500));
    set_greeting(({ "*say I am Weissmann, the famous scribe.",
		    "*say Just give me an item you want me to identify." }));
    add_response("identify", "*say Just give me the item, $N.");
    load_chat(10, ({ "*say I have studied magical items and special items " +
                     "for as long as I've lived here.",
                     "*say I can appraise items for you.",
                     "*think",
                     "*ponder" }));
    add_eq(resolve_path("shard"));
    add_hook("__enter_inv", store_fp("maybe_identify"));
}

private string
query_how_much(int val)
{
    if (val < -90) {
	return "unnaturally less";
    }
    if (val > 90) {
	return "unnaturally more";
    }
    switch (val) {
    case -90..-71: return "a whole lot less";
    case -70..-51: return "alot less";
    case -50..-31: return "even less";
    case -30..-11: return "somewhat less";
    case -10..-1:  return "a bit less";
    case 0:        return "no more, nor less";
    case 1..10:    return "a bit";
    case 11..30:   return "somewhat";
    case 31..50:   return "even more";
    case 51..70:   return "alot more";
    case 71..90:   return "a whole lot more";
    }
}

private mapping
query_modifier_flat()
{
    mapping dat, ret;
    string *arr, key;
    int i, len;
    if (!mapp(dat = query_modifier())) {
	return ([ ]);
    }
    ret = ([ ]);
    for (i = 0, len = sizeof(arr = keys(dat)); i < len; ++i) {
	key = dat[arr[i]][0];
	ret[key] = ret[key] + dat[arr[i]][2];
    }
    return ret;
}

private mapping
query_modifier_diff(mapping prev)
{
    mapping next;
    string *arr;
    int i, len;
    next = query_modifier_flat();
    for (i = 0, len = sizeof(arr = keys(next)); i < len; ++i) {
	next[arr[i]] = next[arr[i]] - prev[arr[i]];
    }
    return next;
}

private string
desc_modifier(string key, int val)
{
    string str;
    switch (key) {
    case "str":
        return "it will make you " + query_how_much(val * 20) +
               " stronger";
    case "dex":
        return "it will make you " + query_how_much(val * 20) +
               " nimbler";
    case "con":
        return "it will make you " + query_how_much(val * 20) +
               " tougher";
    case "int":
	return "it will make you " + query_how_much(val * 20) +
               " smarter";
    }
    if (sscanf(key, "prot_%s", str)) {
	return "it will make you " + query_how_much(val) +
   	       " protected from " + str;
    }
    if (sscanf(key, "resist_%s", str)) {
	return "it will make you " + query_how_much(val) +
  	       " resistant to " + str;
    }
    if (sscanf(key, "vuln_%s", str)) {
	return "it will make you " + query_how_much(val) +
  	       " vulnerable to " + str;
    }
    return 0;
}

private string *
identify_modifier(object obj, string cmd)
{
    mapping dat;
    string *arr, *ret;
    int i, len;
    dat = query_modifier_flat();
    command(cmd + " " + obj->query_name());
    dat = query_modifier_diff(dat);
    ret = ({ });
    for (i = 0, len = sizeof(arr = keys(dat)); i < len; ++i) {
	string key, tmp;
	key = arr[i];
	ret += ({ desc_modifier(arr[i], dat[arr[i]]) });
    }
    return ret;
}

private string
identify_weight(int val)
{
    switch (val) {
    case 0:      return "it weighs nothing";
    case 1..2:   return "it's lightweight";
    case 3..4:   return "it weighs somewhat much";
    case 5..6:   return "it's heavy";
    case 7..9:   return "it'is very heavy";
    case 10..15: return "it's extremely heavy";
    case 16..40: return "it weighs a tremedous lot";
    default:     return "it looks impossible to lift";
    }
}

private string
identify_wear(int val)
{
    switch (val) {
    case 0:       return "it's undamaged";
    case 1..10:   return "it's barely damaged";
    case 11..20:  return "it is in good condition";
    case 21..40:  return "it seems a to be a little damaged";
    case 41..60:  return "it seems to be in need of repair soon";
    case 61..80:  return "it's very worn out, it will be broken soon";
    case 81..100: return "it looks almost ready to break in pieces";
    default:      return "it's a miracle it hasn't been broken yet";
    }
}

private string
identify_weapon(int val)
{
    switch (val) {
    case 0:      return 0;
    case 1..3:   return "it does pathetic damage";
    case 4..6:   return "it does a little bit of damage";
    case 7..10:  return "it can inflict some damage";
    case 11..13: return "it can inflict decent damage";
    case 14..17: return "it can inflict alot of damage";
    case 18..20: return "it can inflict tremendous amounts of damage";
    case 21..25: return "it does incredible damage";
    case 26..35: return "it does unearthly damage";
    case 36..50: return "it can inflict legendary damage";
    default:     return "it does godlike damage";
    }
}

private string
identify_armour(int val)
{
    switch (val) {
    case 0:  return 0;
    case 1:  return "it offers a little protection";
    case 2:  return "it offers good protection";
    case 3:  return "it offers very good protection";
    case 4:  return "it offers as good protection as it gets";
    default: return "it offers godlike protection";
    }
}

static void
maybe_identify(object obj, object ply)
{
    if (!objectp(obj) || !objectp(ply) || !living(ply)) {
        return;
    }
    call_out("try_identify", 0, obj, ply);
}

public void
try_identify(object obj, object ply)
{
    int val;
    if (!objectp(obj) || !objectp(ply) || !living(ply)) {
        return;
    }
    val = obj->query_value() / 2;
    if (val < 200) {
        val = 200;
    } else if (val > 500 && obj->query_info() == 0) {
        val = 500;
    } else if (val > 1000) {
        val = 1000;
    }
    if (ply->query_money() < val) {
        command("say You do not have the " + val + " coins I require " +
                "to identify that.");
    } else {
        string *arr, str;
	arr = ({ });
	if (obj->query_property("armour")) {
	    arr += identify_modifier(obj, "wear");
	}
	if (obj->query_property("weapon")) {
	    arr += identify_modifier(obj, "wield");
	}
        arr += ({
            identify_weight(obj->query_weight()),
            identify_armour(obj->query_ac()),
            identify_weapon(obj->weapon_class()),
            identify_wear(obj->query_property("worn_out"))
        });
	command("say " + capitalize(make_list(arr - ({ 0 }))) + ".");
	if (stringp(str = obj->query_info())) {
	    command("say " + replace_string(str, "\n", " "));
	}
    }
    command("give " + obj->query_name() + " to " + ply->query_real_name());
}
