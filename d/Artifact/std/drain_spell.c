#include "/d/Artifact/artifact.h"

inherit base ART_I_SPELL;
inherit util ART_I_DAMAGE_UTIL;

private int _drain_sp;
private int _conversion_rate;

static void
create()
{
    base::create();
    util::create();
    _drain_sp        = 0;
    _conversion_rate = 100;

    set_dtype("drain");
}

public nomask string
query_info() 
{
    return query_name() + " drains " +
           make_list((query_damage() > 0 ? ({ "hit points" }) : ({ })) +
                     (_drain_sp > 0 ? ({ "spell points" }) : ({ }))) +
           " from whoever the wielder of the artifact is attacking.";
}

private int
convert(int val)
{
    return (val * 100) / _conversion_rate;
}

static void
setup_user(object usr)
{
    int val;
    object ply, foe;
    ::setup_user(usr);
    if (query_room()->query_property("no_mattack")) {
        fizzle_spell("The area prevents it.");
        return;
    }
    if (!objectp(foe = usr->query_attack())) {
        fizzle_spell(usr->query_name() + " is not attacking anyone.");
        return;
    }
    ply = query_player();
    if (objectp(foe) && query_damage() > 0) {
        val = apply_damage(ply, usr, foe);
        val = convert(val);
        if (val < 0) {
            tell_object(ply, bold("\nYOUR SPELL BACKFIRES!!!\n\n"));
        }
        ply->reduce_hit_point(-val);
    } 
    if (objectp(foe) && _drain_sp > 0) {
        val = foe->query_sp();
        foe->reduce_spell_point(_drain_sp);
        if (objectp(foe) && !foe->query_dead()) {
            val = val - foe->query_sp();
        }
        val = convert(val);
        if (val < 0) {
            tell_object(ply, bold("\nYOUR SPELL BACKFIRES!!!\n\n"));
            MESSAGE_D->weapon_noise(ply, -val, "drain", foe);
        } else {
            MESSAGE_D->weapon_noise(foe, val, "drain", ply);
        }
        ply->reduce_spell_point(-val);
    }
}

public nomask int
query_drain_hp() 
{
    return query_damage();
}

public nomask void
set_drain_hp(int val) 
{
    set_damage(val);
}

public nomask int
query_drain_sp() 
{
    return _drain_sp;
}

public nomask void
set_drain_sp(int val) 
{
    _drain_sp = val;
}

public nomask int
query_conversion_rate() 
{
    return _conversion_rate;
}

public nomask void
set_conversion_rate(int val) 
{
    _conversion_rate = val;
}
