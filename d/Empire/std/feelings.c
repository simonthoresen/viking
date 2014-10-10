#include "/d/Empire/empire.h"

inherit I_FEELINGS;

static object find_target(object actor, string arg);
static void   notify_actor(object actor, string msg);
static void   notify_target(object target, string msg);
static void   notify_audience(object actor, object target, string msg);

private string 
make_punctuation(string str) 
{
    int c;
    c = str[strlen(str) - 1];
    return (c != '!' && c != '?' && c != '.') ? "." : "";
}

private string *
format_feeling(object ply, string verb, string adverb, object who) 
{
    int i, len;    
    mixed ret;
    if (!arrayp(ret = copy(feelings[verb]))) {
        return 0;
    }
    if (!stringp(adverb)) {
        adverb = copy(adverbs[ret[0]]);
    }
    for (i = 0, len = sizeof(ret); i < len; ++i) {
    	if (!stringp(ret[i])) {
    	    continue;
        }
    	if (stringp(adverb)) {
    	    ret[i] = replace_string(ret[i], "$A", adverb);
        } else {
    	    ret[i] = replace_string(ret[i], " $A", "");
    	}
    	ret[i]  = format_message(ret[i], (who ? who : ply), ply);
    	ret[i] += make_punctuation(ret[i]) + "\n";
    }
    return ret;
}

static int
perform_feeling(object ply, string arg) 
{
    object who;
    string *ret, *args, verb, adverb;
    if (!stringp(arg)) {
    	return notify_fail("Use what feeling?");
    }
    if (!sscanf(arg, "%s %s", verb, arg)) {
        verb = arg;
        arg = "";
    }
    notify_fail("Usage: " + verb + " [abbreviated adverb] [who]");
    switch(sizeof(args = explode(arg, " "))) {
    case 2:
        if (!objectp(who = find_target(ply, args[1]))) {
            return notify_fail(capitalize(verb) + " who?");
        }
        if (!stringp(adverb = copy(adverbs[args[0]]))) {
            return notify_fail(capitalize(verb) + " how?");
        }
        break;
    case 1:
        if (!objectp(who = find_target(ply, args[0])) &&
            !stringp(adverb = copy(adverbs[args[0]]))) 
        {
            return 0;
        }
        break;
    case 0:
        break;
    default:
        return 0;
    }
    if (who == ply) {
        return 0;
    }
    if (!arrayp(ret = format_feeling(ply, verb, adverb, who))) {
        return 0;
    }
    if (stringp(ret[7]) && ret[7][0] == '#' &&
        call_other(D_MAINSOUL, ret[7][1..], who))
    {
        return 1;
    }
    if (stringp(ret[1]) && (!stringp(ret[3]) || !objectp(who))) {
        notify_actor(ply, ret[1]);
        notify_audience(ply, who, ret[2]);
    } else if (objectp(who)) {
        notify_target(who, ret[3]);
        notify_actor(ply, ret[4]);
        notify_audience(ply, who, ret[5]);
    } else {
        return notify_fail(capitalize(verb) + " who?");
    }
    if (stringp(ret[7]) && ret[7][0] != '#') {
        notify_actor(ply, ret[7] + make_punctuation(ret[7]));
    }
    return 1;
}

