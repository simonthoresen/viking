#include "/d/Empire/empire.h"

inherit EMP_I_MONSTER;

private object _partner;
private string _liquid;
private int    _gland;
private string _art;

static void
create() 
{
    ::create();
    _partner = 0;
    _liquid  = 0;
    _gland   = 500;
    _art     = 0;
    set_scary(1);
    set_bored_secs(300);
    add_id("serpent");
    add_hook("__damage_done", store_fp("on_damage_done"));
    add_hook("__destroy", store_fp("on_destroy"));
}

static int
has_gland() 
{
    return stringp(_liquid) && _gland > 0;
}

static object 
create_liquid(int amount) 
{
    object obj;
    if (!has_gland()) {
        return 0;
    }
    obj = new(resolve_path(_liquid));
    obj->set_amount(amount);
    obj->set_hitter(this_object());
    return obj;
}

static void
on_damage_done(int dmg, string type, object foe, string loc) 
{
    object env;
    if (!objectp(env = environment()) ||
        !has_gland() ||
        !stringp(type) || 
        lower_case(type) != "pierce")
    {
        return;
    }
    if (dmg > _gland) {
        tell_room(env, query_name() + "'s " + _liquid + "-gland ruptures!\n");
        map_array(all_inventory(env), "show_art");
        EMP_D_COMBAT->spray_liquid(env, create_liquid(50 + random(50)));
    } else if (dmg > 25) {
        tell_object(foe, query_name() + " cringes from the pierce.\n");
    }
    _gland -= dmg;
}

public void 
on_partner_die(object corpse, object killer) 
{
    object env;
    if (!objectp(env = environment())) {
        return;
    }
    tell_room(env, bold("\n" + query_name() + " goes into a MAD rage!\n\n"));
}

public void
set_partner(object val) 
{
    if (objectp(_partner)) {
        _partner->remove_hook("__die");
    }
    _partner = val;
    if (objectp(_partner)) {
        _partner->add_hook("__die", store_fp("on_partner_die"));
    }
}

public object
query_partner() 
{
    return _partner;
}

public void
set_liquid(string val) 
{
    _liquid = val;
}

public string
query_liquid() 
{
    return _liquid;
}

public void
set_gland(int val) 
{
    _gland = val;
}

public int
query_gland() 
{
    return _gland;
}

static int
scale_damage(int dmg) 
{
    return (dmg * (objectp(_partner) ? 100 : 150)) / 100;
}

static void
on_destroy() 
{
    set_partner(0);
}

static void
show_art(object obj) 
{
    if (!objectp(obj) || !interactive(obj)) {
        return;
    }
    if (!stringp(_art)) {
        _art = read_file(resolve_path(_liquid + ".art"));
    }
    tell_ansi(obj, _art);
}

