#include "/d/Empire/islands/reikland.h"

#define WIELD_COST     200
#define UNWIELD_COST   25
#define BEAT_COST      1
#define SOUL_LIMIT     10

inherit EMP_I_WEAPON;

private int _souls;

static void 
create() 
{
    ::create();
    _souls = 10 + random(25);
    
    set_name("The Nexus Blade");
    set_short("a burning laen sword");
    set_long("A bastard sword whose blade is composed of burning gold laen, " +
             "outlines tinted black. The pommel is forged of the finest " +
             "steel and the grip is wrapped in brown leather. There are fine " +
             "runes engraved in the blade.");
    set_info("This is The Nexus Blade - The Burning Blade of Souls.\n" +
             "Stay mentally strong while using this blade, or The Nexus " +
             "Blade might just eat your soul.");
    add_id(({ "nexus", "nexus blade", "burning laen sword", "burning sword",
              "laen sword", "bastard sword", "sword", "blade" }));
    add_item(({ "rune", "runes" }), store_fp("exa_runes"));
    add_property("silver");
    set_class(17);
    set_value(7777);
    set_weight(7);
    set_damage_type(({ "slash", "slash", "fire" }));
    set_hit_func(this_object());
    set_heart_beat(1);
    add_hook("__bdrop", store_fp("on_bdrop"));
    add_hook("__wield", store_fp("on_wield"));
    add_hook("__remove", store_fp("on_remove"));
}

static string
exa_runes() 
{
    return ("Etched on the burning laen surface of The Nexus Blade you see " +
            _souls + " markings.\n");
}

private void
kill_player(object ply) 
{
    if (!objectp(ply) || ply->query_dead() || !interactive(ply)) {
        return;
    }
    if (ply->query_level() > ETERNAL_LAST) {
        tell_object(ply, "Your wizardhood protects you from the will of " +
                    "The Nexus Blade.\n");
        return;
    }
    EMP_D_COMBAT->hit_player(ply, ply, 6666, "drain", "head", this_object());
}

private int
drain_sp(object ply, int val) 
{
    if (!objectp(ply) || !interactive(ply)) {
        return 1;
    }
    if (ply->query_sp() < val) {
        return 0;
    }
    ply->reduce_spell_point(val);
    return 1;
}

private int
try_cost(object ply, int val) 
{
    object env;
    if (!objectp(ply) ||
        !objectp(env = environment(ply)))
    {
        return 1;
    }
    tell_object(ply, "The entire sword shivers as the spirit of The " +
                "Nexus Blade struggles the will of its oppressor.\n"); 
    tell_room(env, ply->query_name() + "'s sword shivers in " + 
              ply->query_possessive()+ " hand.\n", ({ ply }));
    if (!drain_sp(ply, val)) {
        tell_object(ply, "Your mental power is too weak to control it!\n");
        tell_room(env, ply->query_name()+"'s eyes open wide as " + 
                  ply->query_pronoun() + " stares in despair at " + 
                  ply->query_possessive() + " sword.\n", ({ ply }));
        return 0;
    }
    tell_object(ply, "The spirit of The Nexus Blade surrenders its will " +
                "to you - but for how long?\n");
    return 1;
}

public void
heart_beat() 
{
    object ply;
    if (!objectp(ply = query_wield()) || 
        objectp(ply->query_attack()) ||
        !interactive(ply)) 
    {
        return;
    }
    if (!drain_sp(ply, BEAT_COST)) {
        tell_object(ply, "Mentally exhausted, you lose control over the " +
                    "spirit of your sword.\n");
        kill_player(ply);
    }
}

static void
on_wield(object obj, string hands) 
{
    object ply;
    if (!objectp(ply = query_wield())) {
        return;
    }
    ply->add_hook("__kill",store_fp("drain_soul"));
    ply->add_hook("__damage_dealt", store_fp("maybe_crit"));
    if (!try_cost(ply, WIELD_COST)) {
        call_out("kill_player", 0, ply);
    }
}

static void
on_remove() 
{
    object ply;
    if (!objectp(ply = query_wield())) {
        return;
    }
    ply->remove_hook("__kill");
    ply->remove_hook("__damage_dealt");
    if (!try_cost(ply, UNWIELD_COST)) {
        call_out("kill_player", 0, ply);
    }
}

static int
on_bdrop(int silent) 
{
    object ply;
    if (!objectp(ply) || !interactive(ply)) {
        return 0;
    }
    if (!silent) {
        tell_object(ply, "The Nexus Blade refuses to be dropped.\n");
    }
    return 1;
}

public void
maybe_crit(int dmg, string dtype, object foe, string loc) 
{
    object ply;
    if (!objectp(ply = previous_object()) || !objectp(foe)) {
        return; 
    }
    EMP_D_CRITICAL->damage_dealt(ply, foe, (dmg * 150) / 100, loc);
}

public void
drain_soul(object victim, object killer) 
{
    object ply;
    if (!objectp(ply = query_wield()) || !objectp(victim)) {
        return;
    }
    if (victim->query_level() >= SOUL_LIMIT) {
        tell_object(ply, "A %^L_YELLOW%^bright flame%^END%^ burns a marking " +
                    "on The Nexus Blade.\n");
        ++_souls;
        return;
    }
    tell_object(ply, "A %^L_BLUE%^bright flash%^END%^ removes a marking from " +
                "The Nexus Blade.\n");
    if (--_souls >= 0) {
        return;
    }
    tell_object(ply, "You can no longer control the spirit of your hungry " +
                "sword!\n");
    kill_player(ply);
}

private string
query_random_loc() 
{
    switch (random(8)) {
    case 0: return "on #p left side";
    case 1: return "on #p right side";
    case 2: return "in front of #oself";
    case 3: return "behind #p back";
    case 4: return "above #p head";
    case 5: return "between #p legs";
    case 6: return "under #p left arm";
    case 7: return "under #p right arm";
    }
}

private string
query_random_arch() 
{
    string *arr;
    int i, len;
    arr = ({ });
    for (i = 0, len = 1 + random(10); i < len; ++i) {
        arr += ({ query_random_loc() });
    }
    return make_list(arr);
}

public int
weapon_hit(object foe) 
{
    object ply, env;
    string str;
    if (!objectp(ply = query_wield()) ||
        !objectp(env = environment(ply)) ||
        !objectp(foe)) 
    {
        return 0;
    }
    if (random(100) > 10) {
        return random(50);
    }
    str = query_random_arch();
    tell_object(foe, ply->query_name() + " swings " + ply->query_possessive() +
                " weapon in an arch " + format_message(str, ply) + "!\n");
    tell_room(env, ply->query_name() + " swings " + ply->query_possessive() +
              " weapon in an arch " + format_message(str, ply) + ".\n", 
              ({ ply, foe }));

    str = replace_string(str, "#p", "your");
    str = replace_string(str, "#o", "your");
    tell_object(ply, "You swing The Nexus Blade in an arch " + str + "!\n");
    return strlen(str);
}
