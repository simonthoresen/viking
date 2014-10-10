#include "/d/Empire/islands/reikland.h"

inherit base EMP_I_ARMOUR;

static void
create() 
{
    ::create();
    set_name("Cloak of the Lord");
    set_short("an undescribable cloak");
    set_long("It is forever changing, and it can not be described in words.");
    set_type("cloak");
    set_ac(1);
    set_weight(1); 
    set_value(1111);
    add_property("wear_msg", "You feel strangely random in this cloak.\n");
    add_property("remove_msg", "You feel less random.\n");
    add_hook("__wear", store_fp("on_wear"));
    add_hook("__remove", store_fp("on_remove"));
}

static void
on_wear(int silent, object obj)
{
    object ply;
    if (!objectp(ply = query_worn_by())) {
        return;
    }
    ply->add_hook("__heart_beat", store_fp("on_wearer_heart_beat"));
}

static void
on_remove(int silent) 
{
    object ply;
    mapping dat;
    string *arr;
    int i, len;
    if (!objectp(ply = query_worn_by())) {
        return;
    }
    ply->remove_hook("__heart_beat");
    if (!mapp(dat = ply->query_modifier())) 
    {
        return;
    } 
    for (i = 0, len = sizeof(arr = keys(dat)); i < len; ++i) {
        if (!sscanf(arr[i], "random:%*s")) {
            continue;
        }
        ply->remove_modifier(arr[i]);
    }
}

private string
random_dtype() 
{
    return ({ "slash", "blunt", "pierce", "chop", "claw", "bite", "fire", 
              "cold", "electricity", "impact", "acid", "magic" })[random(12)];
}

private string
apply_change(object ply) 
{
    switch (random(37)) {
    case 0:
        ply->add_intoxication(-1000);
        return "completely sober";
    case 1:
        ply->add_intoxication(-100);
        return "sober";
    case 2:
        ply->add_intoxication(100);
        return "drunk";
    case 3:
        ply->add_intoxication(1000);
        return "totally drunk";
    case 4:
        ply->add_stuffed(-1000);
        return "starving";
    case 5:
        ply->add_stuffed(-100);
        return "hungry";
    case 6:
        ply->add_stuffed(100);
        return "bloated";
    case 7:
        ply->add_stuffed(1000);
        return "about to burst";
    case 8:
        ply->add_soaked(-1000);
        return "dehydrated";
    case 9:
        ply->add_soaked(-100);
        return "thirsty";
    case 10:
        ply->add_soaked(100);
        return "soaked";
    case 11:
        ply->add_soaked(100);
        return "overflowing";
    case 12:
        ply->add_alignment(ALIGN_EVIL);
        return "evil";
    case 13:
        ply->add_alignment(ALIGN_NASTY);
        return "nasty";
    case 14:
        ply->add_alignment(ALIGN_GOOD);
        return "good";
    case 15:
        ply->add_alignment(ALIGN_SAINTLY);
        return "saintly";
    case 16:
        ply->heal_self(100);
        return "refreshed";
    case 17:
        ply->heal_self(666);
        return "rejuvinated";
    case 18:
        ply->reduce_hit_point(max(0, ply->query_hp() - 50));
        return "about to die";
    case 19:
        ply->reduce_hit_point(max(0, ply->query_hp() - 100));
        return "physically exhausted";
    case 20:
        ply->reduce_spell_point(1000);
        return "mentally drained";
    case 21:
        ply->reduce_spell_point(100);
        return "mentally tired";
    case 22:
        ply->add_exp(-1000 * ply->query_level());
        return "inexperienced";
    case 23:
        ply->add_exp(1000 * ply->query_level());
        return "experienced";
    case 24:
        ply->set_modifier("random:str", "str", "magic", -4);
        return "weak";
    case 25:
        ply->set_modifier("random:str", "str", "magic", 4);
        return "strong";
    case 26:
        ply->set_modifier("random:dex", "dex", "magic", -4);
        return "clumsy";
    case 27:
        ply->set_modifier("random:dex", "dex", "magic", 4);
        return "agile";
    case 28:
        ply->set_modifier("random:con", "con", "magic", -4);
        return "fragile";
    case 29:
        ply->set_modifier("random:con", "con", "magic", 4);
        return "tough";
    case 30:
        ply->set_modifier("random:str", "int", "magic", -4);
        return "dumb";
    case 31:
        ply->set_modifier("random:str", "int", "magic", 4);
        return "smart";
    case 32:
        ply->set_modifier("random:vuln", "vuln_" + random_dtype(), 
                          "magic", 100);
        return "vulnerable";
    case 33:
        ply->set_modifier("random:resist", "resist_" + random_dtype(),
                          "magic", 100);
        return "resistant";
    case 34:
        ply->set_modifier("random:prot", "prot_" + random_dtype(), 
                          "magic", 25);
        return "protected";
    case 35:
        ply->set_modifier("random:ac", "ac", "magic", -5);
        return "naked";
    case 36:
        ply->set_modifier("random:ac", "ac", "magic", 5);
        return "shielded";
    }
}

public void
on_wearer_heart_beat() 
{
    object ply;
    if (!objectp(ply = query_worn_by()) ||
        !interactive(ply) ||
        random(100) > 1) 
    {
        return;
    }
    tell_object(ply, "You feel " + apply_change(ply) + "!\n");
}
