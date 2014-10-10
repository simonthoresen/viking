#include "/d/Empire/islands/reikland.h"

inherit EMP_I_ITEM;

private int _duration;
private int _last_sp;

static void 
create() 
{
    ::create();
    _duration = 0;
    _last_sp  = 0;

    set_name("Sap of the Ent");
    set_short(0);
    set_get(NO_GET);
    set_drop(NO_DROP);
    add_id(source_file_name());
    add_hook("__move", store_fp("on_move"));
    add_hook("__destroy", store_fp("on_destroy"));
}

static void
on_move(object from, object to) 
{
    if (objectp(from) && living(from)) {
        tell_object(from, "You stop growing.\n");
	from->remove_modifier("ent:str");
	from->remove_modifier("ent:dex");
	from->remove_modifier("ent:con");
	from->remove_modifier("ent:int");
	from->remove_modifier("ent:ac");
	from->remove_hook("__heart_beat");
	from->remove_hook("__fight_beat");
    }
    if (objectp(to) && living(to)) {
        tell_object(to, "You feel a wonderful sensation within yourself, as " +
                    "if you are growing.\n");
	to->add_hook("__heart_beat", store_fp("maybe_grow"));
	to->add_hook("__fight_beat", store_fp("maybe_attack"));
        to->heal_self(25);
    } 
    if (objectp(to) && !living(to)) {
	call_out("destroy", 0); /* item too good not to be paranoid */
    }
}

static void
on_destroy() 
{
    on_move(environment(), 0);
}

public string
extra_look() 
{
    return capitalize(environment()->query_pronoun())+" is growing";
}

public void
maybe_attack(object foe) 
{
    object ply, env;
    if (!objectp(ply = environment()) ||
	!objectp(env = environment(ply)) ||
        ply->query_property("last_speed_attack") == time() ||
        ply->query_busy_next_round() ||
        ply->query_sp() < _last_sp ||
        ply->query_wimpy() > 0 ||
        random(100) > 10)
    {
        _last_sp = ply->query_sp();
        return;
    }
    switch (random(4)) {
    case 0: 
        tell_object(ply, "You feel determined for an attack!\n"); 
        break;
    case 1:
        tell_object(ply, "You boldly rush out to attack!\n"); 
        break;
    case 2:
        tell_object(ply, "You force yourself to attack!\n"); 
        break;
    case 3:
        tell_object(ply, "You move onward out of sheer determination!\n"); 
        break;
    }
    ply->add_property("last_speed_attack", time());
    catch(ply->attack());
}

public void
maybe_grow() 
{
    object ply, env;
    if (!objectp(ply = environment()) ||
	!objectp(env = environment(ply)))
    {
	return;
    }
    if (_duration > 500) {
        _duration = 400;
    }
    switch (++_duration) {
    case 25:
        tell_object(ply, "You continue growing...\n");
        ply->heal_self(50);
        break;
    case 50:
        tell_object(ply, "You feel more determined.\n");
        tell_room(env, ply->query_name() + " seems more determined all of a " +
                  "sudden.\n", ({ ply }));
        ply->heal_self(75);
        catch(ply->attack());
        catch(ply->attack());
        catch(ply->attack());
        catch(ply->attack());
        break;
    case 100:
        tell_object(ply, "You feel bolder.\n");
        ply->set_wimpy_hp(0);
        ply->heal_self(100);
        break;
    case 150:
        tell_object(ply, "You grow stronger.\n");
        ply->set_modifier("ent:str", "str", "magic", 2);
        ply->heal_self(125);
        break;
    case 200:
        tell_object(ply, "You feel wiser.\n");
        ply->set_modifier("ent:int", "int", "magic", 2);
        ply->heal_self(150);
        break;
    case 250:
        tell_object(ply, "You feel healthier.\n");
        ply->set_modifier("ent:con", "con", "magic", 2);
        ply->heal_self(175);
        break;
    case 300:
        tell_object(ply, "You grow more agile.\n");
        ply->set_modifier("ent:dex", "dex", "magic", 2);
        ply->heal_self(200);
        break;
    case 400:
        tell_object(ply, "Your skin grows tougher!\n");
        ply->set_modifier("ent:ac", "ac", "magic", 2);
        ply->heal_self(225);
        break;
    case 500:
        tell_object(ply, "You grow a little.\n");
        tell_room(env, ply->query_name() + " seems to grow a little.\n", 
                  ({ ply }));
        ply->heal_self(250);
        break;
    default:
        ply->heal_self(1);
        break;
    }
}
