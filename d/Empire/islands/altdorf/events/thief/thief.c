#include "/d/Empire/islands/altdorf.h"

#define P_KICK ("alt_thief_kick")

inherit EMP_I_MONSTER;

private int    _cheats;
private string _name;

static void
create()
{
    object obj;
    ::create();
    _cheats = 5;
    _name   = ({ "Cujo", "Totto", "Kenny", "Grooo", "Beetle", "Desperado",
                 "Wardancer", "Grimreaper", "Lone", "Thekiller" })[random(10)];

    set_scary_id(0);
    set_name(_name);
    set_short("a suspicious looking man called " + _name);
    set_long("There is really little you know about " + _name + ", " +
             "except that he is very evasive. You can't see his face " +
             "properly, because of his hooded cloak. You also notice how " +
             "silently he is able to walk around. He seems to be " +
             "unaware of the presence of a note sticking to his back, so " +
             "he can't be very bright.");
    add_id(({ "man", "suspicious man", "thief" }));
    set_male();

    add_item(({ "object", "invisible object" }),
             "You can't really see the object since it's invisible, " +
             "but you know it's there.");
    add_item(({ "note" }),
             "You walk behind the man and read the note: \n"+
             "\nThis is " + _name + " the cheater. We started to suspect he " +
             "was a cheater when we saw him do Fort, Gray Knight, Rodriques, " +
             "Morgul, etc, each of them in 10-15 seconds. He is carrying an " +
             "invisible object that makes him able to 'puke' on monsters to " +
             "to kill them in one round. "+
             "Please kick him hard in the back for being who he is.\n\n\n" +
             "KICK ME!\n\n");

    set_level(15);
    set_str(25);
    set_dex(30);
    set_int(1);
    set_hp(500);
    set_wc(15);
    set_ac(0);
    set_al(-666);
    set_scary(1);
    set_bored_secs(300);

    setmin("sneaks in");
    setmout("sneaks");

    add_skill("vuln_electricity",80);
    add_skill("resist_fire",70);
    add_skill("vuln_pierce",20);
    add_skill("vuln_cold",20);
    add_skill("resist_blunt",30);
    add_skill("two_weapon",100);
    add_skill("night_vision",100);

    add_eq(resolve_path("dagger"));
    add_eq(resolve_path("dagger"));
    add_eq(resolve_path("lantern"));
    add_eq(resolve_path("bag"));
    add_eq(I_TORCH);

    load_chat(7, ({ "You feel someone watching you.\n",
                    "You hear silent footsteps nearby.\n",
                    "Someone is here.\n",
                    "You spot a man sneaking around.\n",
                    "There is someone lurking in the corner here.\n" }));
    load_a_chat(30, ({ "The thief pleads #N: Stop! Stop! You're making " +
                       "a big mistake!\n",
                       "Thief says: It's all society's fault you know.\n",
                       "Thief tries to run, but can't hide.\n",
                       "Thief drops a claim for #N.\n",
                       "The cheater pukes on tha monsie.\n",
                       "The cheater abuses a bug.\n",
                       "Thief says: You know you can't beat me.\n",
                       "The thief attempts to trick #N, but fails.\n" }));
    set_wimpy_hp(20);

    add_hook("__bdie", store_fp("on_bdie"));
    add_hook("__bnotify_attack", store_fp("on_bnotify_attack"));
    add_hook("__die", store_fp("on_die"));
    add_hook("__kill", store_fp("on_kill"));
    add_hook("__peace_beat", store_fp("on_peace_beat"));
    add_hook("__receive_feeling", store_fp("on_receive_feeling"));
    add_hook("__wander_done", store_fp("on_wander_done"));
}

private string
query_random_notify()
{
    switch (random(2)) {
    case 0: return "Your purse feels lighter.\n";
    case 1: return "Someone fishes through your pockets.\n";
    }
}

private string
query_random_taunt()
{
    switch (random(3)) {
    case 0: return "Hehehe...";
    case 1: return "You know you can not beat me! :-P";
    case 2: return "I just could not let you ruin my anarchy rating...";
    }
}

private string
query_random_whine()
{
    switch (random(6)) {
    case 0: return "Hey! Stop doing that!";
    case 1: return "Ouch!";
    case 2: return "Oh!";
    case 3: return "Eeeek!";
    case 4: return "Yikes!";
    case 5: return "Stop! Stop! Stop!";
    }
}

public int
try_pick_pocket(object foe)
{
    int val;
    if ((val = foe->query_money()) <= 1000) {
	return 0;
    }
    if (val > 10000) {
	val = 10000;
    }
    val = val / 2 + random(val / 2);
    foe->add_money(-val);
    add_money(val);
    if (!arrayp(query_wandering_route())) {
	set_goal(26, 0);
	set_wandering_time(5);
	set_wandering_chance(80);
    }
    tell_object(foe, query_random_notify());
    return 1;
}

static int
on_bdie(object foe)
{
    if (--_cheats < 0) {
        return 0;
    }
    tell_room(environment(),
              _name + " seems to have lost his sense of reality!\n" +
              "Two thralls appear, dump " + _name + " on a stretcher and " +
              "carry him away.\n");
    message("channels", "[INFO]: " + _name + " goes linkdead.\n", foe);
    foe->stop_fight();
    stop_fight();

    invis();
    run_away();
    call_out("do_reenter", 5 + random(5), foe);
    return 1;
}

static void
on_bnotify_attack(object foe)
{
    tell_object(foe, "The gods are notified of your attack, " +
                "and are pleased.\n");
}

static void
on_die(object corpse, object killer)
{
    object env, obj;
    if (!objectp(env = environment())) {
        return;
    }
    if (!random(100) && objectp(corpse)) {
        make("scabbard", corpse);
    }
    tell_room(env, _name + " curses his killer as he sinks down on his " +
              "knees and dies, caughing up blood.\n", ({ killer }));

    message("channels", "[INFO]: " + _name + " just died.\n", killer);
    message("channels", "[INFO]: " + _name + " is now " + _name +
            " the silly cheater.\n", killer);

    tell_room(env, "You see a dark shape gathering some mist... " +
              "or maybe you are just imagining that.\n");

    command("tell " + killer->query_real_name() +
            " I hope you rot in hell for this!");

    call_other(resolve_path("event"), "notify_pit", killer, _name);
}

static void
on_kill(object victim, object killer)
{
    command("cheer");
    command("tell " + victim->query_real_name() +
            " I guess I was too strong for you :)");
}

static void
on_peace_beat()
{
    object *arr;
    int i, len;
    if (query_money() >= 25000) {
	return;
    }
    arr = filter_array(all_inventory(environment()), "isplayer", FILTER_OB);
    for (i = 0, len = sizeof(arr); i < len; ++i) {
	if (try_pick_pocket(arr[i])) {
	    break;
	}
    }
}

static void
on_receive_feeling(string verb, string adverb, object ply)
{
    int val;
    if (objectp(query_attack()) || verb != "kick") {
        return;
    }
    if (ply->query_tmp_prop(P_KICK) < 5) {
        command("say " + query_random_whine());
    } else {
        do_attack(ply);
    }
    ply->add_tmp_prop(P_KICK, 1);
}

static void
on_wander_done()
{
    command("hide");
    invis();
    destroy(2);
}

public void
do_reenter(object foe)
{
    vis();
    if (objectp(foe)) {
        message("channels", "[INFO]: " + _name + " reenters the game.\n", foe);
        command("tell " + foe->query_real_name() + " " + query_random_taunt());
    }
    if (!random(3)) {
        message("channels", _name + " shouts: I was down to " +
                query_hp() + " hp!!", foe);
    }
    heal_self(200 + random(50));
}
