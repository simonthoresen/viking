#include "/d/Empire/empire.h"

#define MAX_WEIGHT   (20)
#define BURN_TIME    (30 * 60)

inherit EMP_I_WEAPON;

static void
create() 
{
    ::create();
    set_class(0);
    set_weight(MAX_WEIGHT);
    set_value(1 + random(10));
    set_damage_type(({ "blunt", "blunt", "impact" }));
    set_hit_func(store_fp("weapon_hit"));
    set_light(1);
    add_property(({ "wood", "afire", "flammable" }));
    add_hook("__bwield", store_fp("on_bwield"));
    if (clonep(this_object())) {
        call_out("burn_trunk", BURN_TIME);
    }
}

private void
set_weight(int next_val) 
{
    string prev_name, next_name, next_short, next_long, *id_arr;
    int twohanded, prev_val;
    object obj;
    prev_name = query_name(); 
    prev_val  = query_weight();
    if (next_val > 16) {
        twohanded  = 1;
        next_name  = "huge tree-trunk";
        short_desc = "a huge %^L_YELLOW%^BURNiNG%^END%^ tree-trunk";
        long_desc  = "This huge and heavy tree-trunk can hardly classify as " +
                     "a weapon. All the roots and dirt on the end of this " +
                     "enormous club suggests that it was ripped from the " +
                     "ground.";
        id_arr     = ({ "tree-trunk", "trunk", "huge trunk" });
    } else if (next_val > 8) {
        twohanded  = 1;
        next_name  = "tree-trunk";
        short_desc = "a %^L_YELLOW%^BURNiNG%^END%^ tree-trunk";
        long_desc  = "This huge and heavy tree-trunk can hardly classify as " +
                     "a weapon. All the roots and dirt on the end of this " +
                     "enormous club suggests that it was ripped from the " +
                     "ground.";
        id_arr     = ({ "trunk" });
    } else if (next_val > 4) {
        twohanded  = 1;
        next_name  = "wooden log";
        short_desc = "a %^L_YELLOW%^BURNiNG%^END%^ wooden log";
        long_desc  = "This huge and heavy wooden log can hardly classify " +
                     "as a weapon.";
        id_arr     = ({ "log" });
    } else if (next_val > 2) {
        twohanded  = 0;
        next_name  = "branch"; 
        short_desc = "a %^L_YELLOW%^BURNiNG%^END%^ branch";
        long_desc  = "This wooden branch can hardly classify as a weapon.";
        id_arr     = ({ "wooden branch" });
    } else if (next_val > 1) {
        twohanded  = 0;
        next_name  = "stick"; 
        short_desc = "a %^L_YELLOW%^BURNiNG%^END%^ stick";
        long_desc  = "This wooden stick can hardly classify as a weapon.";
        id_arr     = ({ "wooden stick" });
    } else {
        twohanded  = 0;
        next_name  = "twig"; 
        short_desc = "a %^L_YELLOW%^BURNiNG%^END%^ twig";
        long_desc  = "This wooden twig can hardly classify as a weapon.";
        id_arr     = ({ "wooden twig" });
    }
    if (twohanded == 0 && 
        query_type() == "twohanded" && 
        objectp(obj = query_wield())) 
    {
        tell_object(obj, "You loose your grip on the " + prev_name + 
                    " as its fire licks your fingers.\n");
        unwield(1, 1);
    }
    remove_id(query_id_array());
    set_name(next_name);
    set_short(short_desc);
    set_long(long_desc);
    set_type(twohanded ? "twohanded" : "onehanded");
    add_id(id_arr);
    if (objectp(obj = environment())) {
        if (next_name != prev_name) {
            message("", "The " + prev_name + " burns down to " +
                    add_article(next_name) + ".\n", obj);
        }
        obj->add_weight(next_val - prev_val);
    }
    ::set_weight(next_val);
}

public void
burn_trunk() 
{
    object env;
    int val;
    val = query_weight();
    if (--val > 0) {
        set_weight(val);
        call_out("burn_trunk", BURN_TIME);
        return;
    }
    if (objectp(env = environment())) {
        message("", "The " + query_name() + 
                " is consumed by the fire.\n.", env);
    }
    destroy();
}

static int
on_bwield(object weapon, string hands) 
{
    object ply;
    if (!objectp(ply = environment()) || 
        !interactive(ply) ||
        ply->query_skill("vuln_fire") < 0) 
    {
        return 0;
    }
    tell_object(ply, "You are too afraid of the fire.\n");
    return 1;
}

private int
burn_player(object ply, object foe) 
{
    EMP_D_COMBAT->hit_player(ply, foe, 10 + random(10), "fire", 0,
                             this_object());
    return !objectp(foe) || foe->query_dead();
}

private void
throw_player(object ply, object foe) 
{
    tell_object(ply, format_message("%^BOLD%^You smash $N with the trunk " +
                                    "of your tree.%^END%^\n", ply, foe));
    tell_object(foe, format_message("%^BOLD%^#N smashes you with the trunk " +
                                    "of #p tree.%^END%^\n", ply, foe));
    tell_object(foe, "\n\n\n\nS M A S H ! \n\n\n\n\n");
    tell_room(environment(ply), format_message(
                    "#N smashes $N with the trunk of $p tree.\n",
                    ply, foe), ({ ply, foe }));;
    if (!EMP_D_COMBAT->throw_player(foe, 1 + random(3))) {
        EMP_D_COMBAT->hit_player(ply, foe, 20 + random(20), "Impact", 0,
                                 this_object());
    }
}

private void
stun_player(object ply, object foe) 
{
    object env;
    tell_object(ply, format_message("%^BOLD%^You bring your trunk down on " + 
                                     "$N's head.%^END%^\n", ply, foe));
    tell_object(foe, format_message("%^BOLD%^#N brings #p trunk down on " +
                                    "your head.%^END%^\n", ply, foe));
    tell_room(env = environment(ply), 
              format_message("#N brings #p trunk down on $N's head.\n",
                             ply, foe),
              ({ ply, foe }));;
    if (EMP_D_COMBAT->hit_player(ply, foe, 20 + random(20), "blunt",
                                 0, this_object()) > 20) 
    {
        EMP_D_COMBAT->spray_blood(env, 15 + random(15));
        EMP_D_COMBAT->stun_player(foe, random(2));
    }
}

private void
whip_player(object ply, object foe) 
{
    int i, len;
    tell_object(ply, format_message("%^BOLD%^Rocks and shrapnel fly off " +
                                    "your trunk in every direction.%^END%^\n",
                                    ply, foe));
    tell_object(foe, format_message("%^BOLD%^Rocks and shrapnel fly off " +
                                    "#N's trunk.%^END%^\n", ply, foe));
    tell_room(environment(ply), format_message(
                    "Rocks and shrapnel fly off #N's trunk.\n",
                    ply, foe), ({ ply, foe }));;
    for (i = 0, len = 5 + random(5); i < len; ++i) {
        string dtype;
        dtype = ({ "blunt", "chop", "pierce", "slash" })[random(4)];
        EMP_D_COMBAT->hit_player(ply, foe, 10 + random(5), dtype, 0,
                                 this_object());
        if (!objectp(foe) || foe->query_dead()) {
            break; 
        }
    }
}

public int
weapon_hit(object foe) 
{
    object ply;
    int val;
    if (!objectp(ply = query_wield())) {
        return 0;
    }
    if (burn_player(ply, foe)) {
        return 0; /* dead */
    }
    val = query_weight();
    if (!ply->test_weight(val)) {
        return val; 
    }
    if (random(100) > 10) {
        return val * 2;
    }
    if (id("trunk")) {
        switch (random(5)) {
        case 0:
            stun_player(ply, foe);
            break;
        case 1..2:
            throw_player(ply, foe);
            break;
        case 3..4:
            whip_player(ply, foe);
            break;
        }
    } else if (id("log")) {
        switch (random(3)) {
        case 0:
            stun_player(ply, foe);
            break;
        case 1..2:
            throw_player(ply, foe);
            break;
        }
    }
    return val * 3;
}
