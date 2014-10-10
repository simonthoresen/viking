#include "/d/Empire/islands/matouci.h"

#define COLOR(str)   ("%^B_YELLOW%^%^RED%^" + (str) + "%^END%^")
#define P_DURATION   ("jormungand_spirit")

inherit EMP_I_ARMOUR;

private int _duration;

static void 
create() 
{
    ::create();
    _duration = 0;

    set_type("spirit");
    set_name("Spirit of Jormungand");
    set_long("The spirit of the Jormungand Serpent flows within you.");
    set_info(store_fp("on_info"));
    add_id(source_file_name());
    add_property(({ "tagged", "unremovable" }));
    add_property("protected", 100);
    add_property("wear_msg", COLOR("The serpent spirit fills you.") + "\n");
    add_property("wear_other_msg", "");
    add_property("remove_msg", COLOR("The serpent spirit leaves you.") + "\n");
    add_property("remove_other_msg", "");
    add_property("immaterial"); /* Added Oct 30th 2012  -Kralk */
    set_weight(0);
    set_value(69);    
    set_drop(NO_DROP);
    set_wear_modifier("str", 1, 1);
    set_wear_modifier("dex", 1, 1);
    set_wear_modifier("con", 1, 1);
    set_wear_modifier("int", 1, 1);
    add_hook("__destroy", store_fp("on_destroy"));
    add_hook("__move", store_fp("on_move"));
}

public string
on_info() 
{
    string str;
    if (_duration < 60 * 30) {
        str = "in less than an hour";
    } else {
        str = "after " + (_duration / (60 * 30)) + " hours";
    }
    return "It will fade " + str + " of combat.";
}

public string
extra_look() 
{
    return capitalize(environment()->query_pronoun() +
		      " bears the mark of the Jormungand Serpent");
}

public string
query_auto_load() 
{
    object ply;
    if (objectp(ply = environment())) {
        EMP_LOG("jormungand.load", sprintf("query_auto_load(%d) for %s",
                                           _duration, ply->query_real_name()));
    }
    return MAT_C_SPIRIT + ":" + _duration;
}

public void
init_arg(string arg) 
{
    if (!sscanf(arg, "%d", _duration)) {
	_duration = 0;
    }
}

static void
on_move(object from, object to) 
{
    if (objectp(from) && living(from)) {
        if (_duration > 0) {
            from->add_property(P_DURATION, _duration);
        }
        from->remove_hook("__fight_beat");
    }
    if (objectp(to) && living(to)) {
        map_array(all_inventory(to), "consume_spirit");
        _duration += to->query_property(P_DURATION);
        to->remove_property(P_DURATION);
        to->add_hook("__fight_beat", store_fp("on_fight_beat"));
        wear(0);
    } else if (objectp(to) && !living(to)) {
	call_out("destroy", 0); /* item too good not to be paranoid */
    }
}

static void
consume_spirit(object obj) 
{
    if (!objectp(obj) || obj == this_object() ||
        !obj->id(MAT_C_SPIRIT)) 
    {
        return;
    }
    obj->remove(1, 1);
    obj->destroy();
}

static void
on_destroy() 
{
    on_move(environment(), 0);
}

public void
on_fight_beat() 
{
    object ply;
    if (!objectp(ply = previous_object())) {
        return;
    }
    if (--_duration < 0) {
        destroy();
    } else {
        ply->heal_self(2);
    }
}

public void
set_duration(int val) 
{
    object ply;
    if (objectp(ply = environment()) && living(ply)) {
        EMP_LOG("jormungand", sprintf("set_duration(%d) called by %O for %s",
                                      val, previous_object(),
                                      ply->query_real_name()));
    }
    _duration = val;
}

public void
add_duration(int val) 
{
    object ply;
    if (objectp(ply = environment()) && living(ply)) {
        EMP_LOG("jormungand", sprintf("add_duration(%d) called by %O for %s",
                                      val, previous_object(),
                                      ply->query_real_name()));
    }
    _duration += val;
}

public varargs int
query_duration(object ply) 
{
    return objectp(ply) ? ply->query_property(P_DURATION) : _duration;
}

public void
claim_reward(object ply) 
{
    object obj;
    if (!objectp(ply) || 
        !query_duration(ply) ||
        objectp(present(MAT_C_SPIRIT, ply)))
    {
        return;
    }
    obj = new(MAT_C_SPIRIT);
    obj->set_duration(0);
    obj->move(ply);
}
