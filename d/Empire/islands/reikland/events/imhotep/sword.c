#include "/d/Empire/islands/reikland.h"

inherit weapon EMP_I_WEAPON;
inherit align  EMP_I_ALIGNED;

private int _bias;

static void
create() 
{
    weapon::create();
    align::create();
    _bias = 0;

    set_name("Kirae Shang");
    set_short("a black laen blade");
    set_long("A bastard sword whose blade is composed of silver laen, " +
             "tinted black. The pommel is forged of the finest steel and " +
             "the grip is wrapped in brown leather. There are fine runes " +
             "engraved in the blade.");
    add_id(({ "sword", "blade", "laen blade", "black blade" }));
    set_info("This is Kirae Shang, Drinker of Souls, forged by Akasnu in " +
             "the depths of Sakath Shrenar, empowered by Akasnu to slay " +
             "the immortal forces of good.");
    set_class(19);
    set_weight(3);
    set_value(2222);
    set_damage_type(({ "drain", "slash" }));
    set_max_align(ALIGN_EVIL);
    set_hit_func(this_object());
    set_wield_modifier("devotion_evil", 20);
    add_property(({ "artifact", "evil" }));
    add_property("wield_msg", "You feel malevolent and cruel.\n");
    add_property("remove_msg", "You feel remorse.\n");
    add_hook("__wield", store_fp("on_wield"));
    add_hook("__remove", store_fp("on_remove"));
}

static void
on_wield(object obj, string hands) 
{
    object ply;
    if (!objectp(ply = query_wield())) {
        return;
    }
    ply->add_hook("__hit_player", store_fp("deflect_magic"));
}

static void
on_remove() 
{
    object ply;
    if (!objectp(ply = query_wield())) {
        return;
    }
    ply->remove_hook("__hit_player");
}

static int
deflect_magic(int dmg, string type, object foe, string loc, 
              int prot, int resist, int vuln, int ac, object wpn) 
{
    object ply, env;
    if (!objectp(foe) ||
        !objectp(ply = previous_object()) ||
        !objectp(env = environment(ply)) ||
        env->query_property("no_mdefence") ||
        lower_case(type) != "magic" ||
        random(100) > 25 ||
        ply == foe)
    {
        return 0;
    }
    tell_object(ply, "You raise your sword and reflect the magic attack " +
                "back at " + foe->query_name() + ".\n");
    tell_object(foe, ply->query_name() + " raises " + ply->query_possessive() +
                " sword and reflects your attack back at you.\n");
    EMP_D_COMBAT->hit_player(ply, foe, dmg - prot - resist - vuln - ac, 
                             type, loc, this_object());
    return -dmg;
}

public mixed 
weapon_hit(object foe) 
{
    object ply;
    int val;
    if ((!objectp(ply = query_wield()) || !objectp(foe)) || 
        (interactive(ply) && ply->query_alignment() > foe->query_alignment()))
    {
        return "miss";
    }
    val = ply->query_tmp_prop("devotion_evil");
    if ((_bias += val / 4 + random(val / 2)) >= 100) {
        _bias = 0; /* by devotion 10-50% chance */
        tell_object(ply, "Your hands are guided by the demon lord!\n");
        return 90; 
    }
    return 40; 
}

