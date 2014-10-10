#include "/d/Empire/islands/altdorf.h"
#include "/d/Empire/islands/chaos.h"
#include "/d/Empire/islands/matouci.h"
#include "/d/Empire/islands/reikland.h"

inherit weapon EMP_I_WEAPON;
inherit align  EMP_I_ALIGNED;

private mapping _events;
private int     _bias;

static void
create() 
{
    weapon::create();
    align::create();
    _events = 0;
    _bias   = 0;

    set_name("Grimoire of Kalis Pathon");
    set_short("a thick leather-bound book");
    set_long("It is a very thick, leather-bound book of magic. You may wield " +
             "it to use its magic as a weapon.");
    set_info("This is the grimoire of the magician Kalis Pathon.");
    add_id(({ "book", "thick book", "leather-bound book",
              "book of magic", "grimoire" }));
    set_class(0);
    set_weight(1);
    set_value(1000);
    set_min_align(ALIGN_GOOD);
    set_hit_func(this_object());
    set_read(store_fp("read_index"));
    set_wield_modifier("devotion_good", 20);
    add_property("artifact");
    add_trigger("study", store_fp("do_study"));
    add_hook("__destroy", store_fp("on_destroy"));
}

private string
pretty_name(string file) 
{
    string *arr;
    int i, len;
    file = replace_string(file, "_", " ");
    for (i = 0, len = sizeof(arr = explode(file, " ")); i < len; ++i) {
        arr[i] = capitalize(arr[i]);
    }
    return implode(arr, " ");
}

private string
event_name(string file) 
{
    string *arr;
    arr = explode(lower_case(file), "/");
    return pretty_name(arr[sizeof(arr) - 2]);
}

private string
island_name(string file) 
{
    string *arr;
    arr = explode(lower_case(file), "/");
    return pretty_name(arr[3]);
}

private void
store_event(string file) 
{
    object obj;
    if (stringp(catch(obj = file->__bootstrap()))) {
        return;
    }
    obj->add_hook("__open", store_fp("notify_event"));
    _events[event_name(file)] = file;
}

private void
store_events(string dir) 
{
    string *arr;
    int i, len;
    for (i = 0, len = sizeof(arr = get_files(dir)); i < len; ++i) {
        if (file_size(dir + arr[i] + "/ENABLED") < 0) {
            continue;
        }
        store_event(dir + arr[i] + "/event");
    }
}

private void
ensure_events() 
{
    if (mapp(_events)) {
        return;
    }
    _events = ([ ]);
    store_events(ALT_DIR_EVENTS);
    store_events(CAS_DIR_EVENTS);
    store_events(MAT_DIR_EVENTS);
    store_events(RED_DIR_EVENTS);
}

static void
on_destroy() 
{
    string *arr;
    int i, len;
    if (!mapp(_events)) {
        return;
    }
    for (i = 0, len = sizeof(arr = map_values(_events)); i < len; ++i) {
        catch(arr[i]->remove_hook("__open"));
    }
}

static int
read_index(string arg) 
{
    ensure_events();
    write("Herein lies the knowledge of " + make_list(keys(_events)) + ".\n" +
          "Usage: study <topic>\n");
    return 1;
}

public int
do_study(string arg) 
{
    object ply;
    string event, info, last_ply, last_env;
    int last_time, next_time;
    if (!objectp(ply = this_player())) {
        return 0;
    }
    if (!stringp(arg)) {
        return notify_fail("Study what?");
    }
    ensure_events();
    if (!stringp(event = _events[pretty_name(arg)])) {
        return notify_fail("The book does not cover that.");
    }
    say(ply->query_name() + " reads in " + ply->query_possessive() + "'s " +
        query_name() + ".\n");
    if (stringp(catch(event->__bootstrap()))) {
        return notify_fail("The pages for that are missing.");
    }
    write("You study the pages that describe the " + event_name(event) + 
          " event in " + island_name(event) + ".\n");

    info      = event->query_info();
    last_ply  = event->query_last_ply();
    last_env  = event->query_last_env();
    last_time = event->query_last_time();
    next_time = event->query_next_time();

    if (!stringp(info) && last_time == 0 && next_time == 0) {
        write("You fail to understand the symbols.\n");
        return 1;
    }
    if (stringp(info)) {
        write(info); 
    }
    if (last_time > 0 && stringp(last_ply) && stringp(last_env)) {
        string *map, str;
        if (ply->query_property("TERM") == "ansi") {
            map = last_env->query_ansi_map();
        } else {
            map = last_env->query_dumb_map();
        } 
        str = "It last occured " + ctime(last_time) + " for " + 
              capitalize(last_ply);
        if (arrayp(map)) {
            str += " here:\n\n" + implode(map, "\n") + "\n\n";
        } else {
            str += ".\n";
        }
        tell_ansi(ply, str);
    }
    if (next_time - 60 > time()) {
        write("The symbols foresay that it may occur in " + 
              format_time(((next_time - time()) / 60) * 60) + ".\n");
    } else if (next_time > 0) {
        write("The symbols foresay that it may occur at any moment.\n");
    }
    return 1;
}

public void
notify_event(object ply, object env) 
{
    if (!objectp(env = environment())) {
        return;
    }
    message("", "The pages on the " +
            event_name(source_file_name(previous_object())) + 
            " event change.\n", env);
}

public mixed
weapon_hit(object foe) 
{
    object ply;
    if (objectp(ply = query_wield()) &&
        (random(100) < 25 + (++_bias)))
    {
        int dmg;
        string type;
        tell_object(ply, "You cast a spell from your grimoire!\n");
        dmg  = 50 + random(ply->query_tmp_prop("devotion_good") / 2);
        type = ({ "cold", "fire", "electricity", "magic" })[random(4)];
        EMP_D_COMBAT->hit_players(ply, ply->query_attackers(), dmg, type,
                                  0, this_object());

        _bias = 0; 
    }
    return "miss";
}
