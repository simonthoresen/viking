#include "/d/Empire/empire.h"

inherit I_ITEM;

static void
create() 
{
    ::create();
    set_name("blood frenzy");
    set_short(0);
    set_drop(1);
    add_id(source_file_name());
    add_hook("__move", store_fp("on_move"));
    add_hook("__destroy", store_fp("on_destroy"));
}

static void
on_move(object from, object to) 
{
    object env;
    if (objectp(from) && living(from)) {
	tell_object(from, "Your rage subsides!\n");
	if (objectp(env = environment(from))) {
	    tell_room(env, from->query_name() + "'s rage subsides!\n",
		      ({ from }));
	}
        from->remove_hook("__fight_beat");
    } 
    if (objectp(to) && living(to)) {
	tell_object(to, bold("You become MAD with rage!\n"));
	if (objectp(env = environment(to))) {
	    tell_room(env, bold("\n" + to->query_name() + 
				" becomes MAD with rage!\n\n"),
		      ({ to }));
	}
        to->add_hook("__fight_beat", store_fp("on_target_fight_beat"));
    }
}

static void
on_destroy() 
{
    on_move(environment(), 0);
}

public void
on_target_fight_beat() 
{
    object ply;
    if (!objectp(ply = environment()) || 
	!objectp(ply->query_attack()) ||
	ply->query_hp() > (ply->query_max_hp() * 30) / 100)
    {
	destroy();
        return;
    }
    ply->attack();
}
