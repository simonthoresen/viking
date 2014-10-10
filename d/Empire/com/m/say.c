#include "/d/Empire/empire.h"

inherit CMD_MODULE;

int query_range(object ply, string verb) {
    switch (verb) {
    case "say":  return 1;
    case "yell": return (int)ply->query_con() / 5;
    default:     return 0;
    }
}
    
int main(string arg) {
    object ply, env, *arr;
    string name, verb;
    mapping dat;
    int i, len;
    if (!stringp(arg) || 
        !objectp(ply = this_player()) ||
	!objectp(env = environment(ply)) ||
	!env->is_empire()) 
    {
	return 0;
    }
    verb = query_verb();
    write("You " + verb + ": " + arg + "\n");
    say((name = ply->query_name()) + " " + verb + "s: " + arg + "\n");
    env->tell_nearby(name + " " + verb + "s from the #d: " + arg + "\n",
                     query_range(ply, verb));
    return 1;
}

string short_help() {
    return "Exclaim something to the surrounding area.";
}

string *query_action() {
    return ({ "say", "yell" });
}
