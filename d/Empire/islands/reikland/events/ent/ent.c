#include "/d/Empire/islands/reikland.h"

inherit EMP_I_MONSTER;

private object _caught;

static void 
create() 
{
    ::create();
    _caught = 0;

    set_race("ent");
    set_name("Ent");
    set_short("an ancient looking tree");
    set_long("This tree seems to be more than a thousand years old. It has " +
             "long intwining branches with ash-gray leaves on. It doesn't " +
             "look particular friendly, with a witchy black colour on the " +
             "surface. Its size is however the most astonishing. It is " +
             "simply... HUGE.\n" +
             "You feel your neckhair raise in the presence of this majestic " +
             "being.");
    add_id(({ "tree", "old tree", "ancient tree" }));
    add_item(({ "surface", "rough surface" }), "The surface is rough and " +
             "hard. You can see a dark hole in it.");
    add_item(({ "colour", "black colour" }), "The colour doesn't look very " +
             "healthy, to put it that way.");
    add_item(({ "hole", "dark hole", "opening", "mouth" }), "You can't see " +
             "anything in there it is too dark...");
    add_item(({ "branch", "branches" }), "They are gnarled but seem to be " +
             "incredibly strong.\n");
    set_level(50);
    set_hp(30000);
    set_al(-3000);
    set_wc(35);
    set_ac(40);
    set_str(60);	
    set_dex(5);	
    set_aggressivity(1);
    set_scary(1);
    set_bored_secs(300);
    set_corpse_object(parse_path("corpse"));
    set_combat_arr(({
        10, " with its long branches", "grazed", 0,
        20, " hard", "whipped", 0,
        30, " with a terrific sound", "whipped", 0,
        40, " tearing through most armours", "smashed", 0,
        50, " spreading blood everywhere", "gnawed", 0,
        60, " pulverising bones", "pushed", 0,
        70, " to the ground with a mighty lash with a branch", "knocked", 0
    }));
    load_a_chat(50, ({
        "The Ent grumbles: Yet another mortal trying to beat the " +
        "unbeatable...\n",
        "*emote shakes in the wind.",
        "*cackle dem",
        "Ent asks: Me have lived for millennias, how long have you lived?\n",
        "Ent asks: How long do you expect to live?\n",
        "The Ent says: MAY THE PLAGUE VISIT YOUR FAMILY!\n",
        "The Ent says: Me have seen countless deaths.\n",
        "The Ent says: Me have caused countless deaths!\n",
        "The Ent curses you!\n",
        "The Ent creeks: HOW DARE YOU DISTURB MY SLUMBER??\n",
        "Ent mumbles: Me knows everything worth to know.\n",
        "Ent mumbles: Me have seen what is worth to be seen.\n",
        "You see the terrifying branches gather for attack.\n",
        "You can hear awful whip-like sounds from the branches.\n"
    }));
    add_exp(10000000 + random(10000000));
    add_money(30000 + random(50000));
    add_skill("vuln_chop",10);      
    add_skill("vuln_fire",10);      
    add_skill("vuln_electricity",5);
    add_skill("resist_pierce",70); 
    add_skill("resist_cold",60); 
    add_skill("resist_blunt",40);
    add_trigger("search", store_fp("search_mouth"));
    add_trigger("climb", store_fp("climb_tree"));
    add_trigger("quit", store_fp("loot_leaver"));
    add_property(({ "guardian", "wood", "no_headchop", "no_crit", 
                    "no_glaze", "no_disease" }));
    add_property("unarmed_weapon_type", ({ "impact", "Impact", "Drain" }));
    add_hook("__fight_beat", store_fp("extra_attack"));
    add_hook("__die", store_fp("final_attack"));   
    add_hook("__destroy", store_fp("free_hand"));
}

public void 
loot_leaver(string str) 
{
    call_out("command", 0, "get all");
}

public int 
climb_tree(string str) 
{
    if (!id(str)) {
        return notify_fail("Climb what?");
    }
    if (!random(2)) {
        write("Hey, what was that? Did that branch just move?\n"+
              "You figure it wouldn't be wise to climb up this tree!\n");
    } else {
        write("As you grab for a branch to hold on, it moves out of your " +
              "way!\n");
    }
    return 1;
}

public int 
search_mouth(string arg) 
{
    if (arg != "hole" && 
        arg != "dark hole" && 
        arg != "opening" && 
        arg != "mouth") 
    {
        return notify_fail("Search what?");
    }
    if (objectp(_caught)) {
        return notify_fail(_caught->query_name() + " is blocking it!");
    }
    write("You gently put your hand into the opening, searching for a " +
          "potion of dragon juice or something similar. The hole is " +
          "pretty big on the inside, so expect this to take a second or " +
          "two.\n");
    say(this_player()->query_name() + " starts searching an opening in " +
        "the old tree.\n");
    call_out("catch_hand", 2 + random(3), this_player());
    return 1;
}

public void 
catch_hand(object ply) 
{
    object env;
    if (!objectp(ply) ||
        !objectp(env = environment()) ||
        !objectp(present(ply, env))) 
    {
        return;
    }
    if (objectp(_caught)) {
        tell_object(ply, "Just before the opening closed you managed to get " +
                    "your hand out!\n");
        return;
    }
    _caught = ply;
    call_out("free_hand", 15 + random(20));

    message("hityou", "P A I N !  Your arm is almost teared off as the " +
            "opening suddenly closes around it.\n", ply);
    tell_object(ply, "You scream your brains out!!\n");
    tell_room(env, "Suddenly the opening in the old tree clutches around " +
              "the arm of " + ply->query_name() + " making " + 
              ply->query_objective() + " scream in pain!\n", ({ ply }));
    ply->add_hook("__bmove_player", store_fp("prevent_move"));
    ply->set_busy_next_round();
    ply->hit_player(100 + random(100), "bite", this_object());
}

public int
prevent_move(string dir, object env, mixed dst) 
{
    object ply;
    if (!objectp(ply = previous_object()) ||
        !objectp(env)) 
    {
        return 0;
    }
    if (!objectp(present(ply, env))) {
        ply->remove_hook("__bmove_player");
        return 0;
    }
    tell_object(ply, "Your hand is trapped in the tree, you try but fail to " +
                "escape!!\n");
    tell_room(env, ply->query_name() + " tries to get loose from the tree's " +
              "deadly grasp.\n", ({ ply }));
    ply->set_busy_next_round();
    return 1;
}

public void 
free_hand() 
{
    object env;
    if (!objectp(_caught)) {
        return;
    }
    _caught->remove_hook("__bmove_player");
    if (objectp(env = environment()) && 
        objectp(present(_caught, env))) 
    {
        tell_object(_caught, "You are once again free from the tree!\n");
        tell_room(env, _caught->query_name() + " phews.\n", ({ _caught }));
    }
    _caught = 0;
}

private void
do_snap(object foe, object env) 
{
    int dmg, val;
    tell_room(env, foe->query_name() + " falls down to the ground by a " +
              "POWERFUL KNOCK from the Ent!!!!\n", ({ foe }));
    message("hityou", "You hear an awful SNAP! Everything turns black for a " +
            "moment...\n\n\n\n\n\n\n\n\n\n\n", foe);
    foe->set_busy_next_round();
    foe->hit_player(20 + random(20), "Drain", this_object()); 
    if (!objectp(foe) || foe->query_dead()) {
        return;
    }
    dmg = 140 + random(60);
    val = foe->query_hp() / 2;
    if (val > dmg) {
        dmg = val + random(val);
    }
    if (dmg > 500) {
        dmg = 500;
    }
    foe->reduce_hit_point(dmg / 2);
    foe->hit_player(dmg / 2, "Impact", this_object());    
}

private void 
do_lash(object foe, object env) 
{
    tell_room(env, foe->query_name() + " gets hit by a POWERFUL lash!\n",
              ({ foe }));
    message("hityou", "You get hit by a POWERFUL lash!\n", foe);
    foe->set_busy_next_round();
    foe->hit_player(20 + random(20), "Drain", this_object());
    if (!objectp(foe) || foe->query_dead()) {
        return;
    }
    foe->hit_player(70 + random(30), "impact", this_object());
}

private void 
do_swipe(object foe, object env) 
{
    object *arr; 
    if (!arrayp(arr = filter_array(all_inventory(env), "is_target"))) {
        return;
    }  
    tell_room(env, "The tree swings its branches with one MIGHTY " +
              "stroke, hitting everyone extremely hard!!\n");
    message("hityou", "You are hit by a strong black branch!\n", arr);
    arr->set_busy_next_round();
    arr->hit_player(30 + random(120), "Drain", this_object());

    arr = arr - ({ 0 });
    arr->hit_player(60 + random(130), "impact", this_object());
}

static int 
is_target(object obj) 
{
    if (!objectp(obj) || !living(obj) || obj == this_object()) {
        return 0;
    }
    return do_attack(obj);
}

private void
do_miss(object foe, object env) 
{
    message("missyou", "Suddenly you see a branch coming right at you!\n" +
            "You barely manage to dodge it!\n", foe);
    tell_room(env, foe->query_name() + " dodges a great hit from a branch.\n",
              ({ foe }));
    foe->set_busy_next_round();
}

static void
extra_attack(object foe) 
{
    object env;
    if (!objectp(foe) || 
        !objectp(env = environment()))
    {
        return;
    }
    switch (random(100)) {
    case 0..2:   catch_hand(foe);    break;
    case 3..6:   do_snap(foe, env);  break;
    case 7..21:  do_lash(foe, env);  break;
    case 22..40: do_swipe(foe, env); break;
    case 41..59: do_miss(foe, env);  break;
    case 60..99: /* empty */         break;
    }
}

static void 
final_attack(object corpse, object killer) 
{
    object env, *arr;
    int i, len;
    if (!objectp(env = environment())) {
        return;
    }
    tell_room(env, "As the tree is chopped down it tips to one side with a " +
              "MIGHTY CRASH!!\n");
    for (i = 0, len = sizeof(arr = query_attackers()); i < len; ++i) {
        object foe;
        if (!objectp(foe = arr[i])) {
            continue;
        }
        tell_room(env, foe->query_name() + " is crushed under the heavy " +
                  "lumber!!! Ouch, that must hurt!\n", ({ foe }));
        message("hityou", "You are crushed under the heavy lumber! OUUUUCH, " +
                "it hurts!\n\n\n", foe);
        foe->hit_player(40 + random(30), "Impact", this_object());  
        if (objectp(foe) && !foe->query_dead()) {
            foe->hit_player(40 + random(30), "impact", this_object());
        }
        if (objectp(foe) && !foe->query_dead()) {
            foe->hit_player(40 + random(30), "impact", this_object());
        }
        if (objectp(foe) && !foe->query_dead()) {
            foe->hit_player(40 + random(30), "impact", this_object());
        }
    }
    message("", "You hear something sounding like an enormous tree falling " +
            "down with a big crash from the forest of Reikland.\n", 
            filter_array(users(), "is_player"), all_inventory(env));
    catch(resolve_path("event")->set_next_time(time() + (UPTIME - uptime())));
}

static int 
is_player(object obj) 
{
    return objectp(obj) && !obj->query_property("no_noise");
}
