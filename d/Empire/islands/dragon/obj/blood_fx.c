#include "/d/Empire/empire.h"

#define MOD_NAME(x)   ("onyxia:" + (x))
#define DMG_TYPES     (({ "acid", "bite", "blunt", "chop", "claw", "cold",    \
                          "electricity", "fire", "impact", "magic", "pierce", \
                          "pierce", "slash" }))

inherit I_ITEM;

private int _bias;

static void
create() 
{
    ::create();
    _bias = 0;

    set_name("Blood of Onyxia");
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
    int i, len;
    if (objectp(from) && living(from)) {
        tell_object(from, bold("The powers of the dragon leave you.\n"));
        for (i = 0, len = sizeof(DMG_TYPES); i < len; ++i) {
            from->remove_modifier(MOD_NAME(DMG_TYPES[i]));
        }
	from->remove_hook("__heart_beat");
    }
    if (objectp(to) && living(to)) {
        tell_object(to, bold("Your blood surges with the powers " +
                             "of the dragon!\n"));
        for (i = 0, len = sizeof(DMG_TYPES); i < len; ++i) {
            to->set_modifier(MOD_NAME(DMG_TYPES[i]), "resist_" + 
                             DMG_TYPES[i], "magic", 35);
        }
	to->add_hook("__heart_beat", store_fp("on_heart_beat"));
    } else if (objectp(to) && !living(to)) {
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
    return capitalize(environment()->query_pronoun() + " is empowered by the " +
                      "blood of the dragon queen");
}

public void
on_heart_beat() 
{
    object ply, env, foe;
    if (!objectp(ply = previous_object()) ||
        !objectp(env = environment(ply)))
    {
        return;
    }
    ply->heal_self(5);
    if (!objectp(foe = ply->query_attack()) ||
        random(100) > ++_bias + 25)
    {
        return;
    }
    _bias = 0;
    message("", "You breath the fire of the dragon queen!\n", ply);
    message("", ply->query_name() + " spews fire and brimstone!\n", env, ply);
    EMP_D_COMBAT->hit_players(ply, ply->query_attackers(), 10 + random(20), 
                              "fire", 0, "breath");
}
