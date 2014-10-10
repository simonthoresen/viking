#include "/d/Empire/islands/reikland.h"

inherit RED_DIR_OBJ + "fimir";

static void
create() {
    ::create();
    set_name("Dirach");
    set_short("a fimir dirach");
    set_long("He is roughly humanoid, with a great barrel-like chest, short "+
             "powerful legs ending in three-toed clawed feet, and long " +
             "sinewy arms which reach almost to the ground. It has three " +
             "horns growing from the side of its head.");
    set_level(26);
    set_hp(1000);
    set_al(-1000);
    set_wc(25);
    set_ac(20);
    set_aggressive(1);
    load_a_chat(50, ({ store_fp("cast_spell"), store_fp("tail_attack") }));

    EMP_D_ARMOUR->add_armour(75 + random(25));
    EMP_D_ARMOUR->add_armour(50 + random(25));
}

private void 
do_chant() 
{
    int word_idx, word_len;
    int char_idx, char_len;
    int vowel;
    string str;
    vowel = 0;
    str = "";
    for (word_idx = 0, word_len = 3 + random(4); 
         word_idx < word_len; ++word_idx)
    {
        for (char_idx = 0, char_len = 3 + random(4); 
             char_idx < char_len; ++char_idx)
        {
            if (++vowel % 2) {
                str += sprintf("%c", "AEIOUY"[random(5)]);
            } else {
                str += sprintf("%c", "BCDFGHJKLMNPQRSTVWXZ"[random(20)]);
            }
        }
        if (word_idx < word_len - 1) {
            str += " ";
        }
    }
    command("yell " + str + "!");
}

static void
cast_spell(object ply, object foe) 
{
    object *arr, env, obj;
    int i, len;
    if (!objectp(ply) || 
        !objectp(foe) ||
        !objectp(env = environment(ply)))
    {
        return;
    }
    do_chant();
    tell_room(env, "%^B_BLUE%^%^BOLD%^Lightning bolts shoot all around the " +
              "fimir dirach!%^END%^\n");
    for (i = 0, len = sizeof(arr = query_attackers()); i < len; ++i) {
        if (!objectp(foe = arr[i])) {
            continue;
        }
        EMP_D_COMBAT->hit_player(ply, foe, 10 + random(50), 
                                 "electricity", 0, "magic");
    }
    if (random(100) < 80 && objectp(obj = ply->query_weapon(1))) {
        tell_room(env, bold("The fimir's " + obj->query_name() + 
                            " absorbs some of the electricity.\n"));
        parse_path("spelld")->enchant_weapon(obj);
    } else {
        EMP_D_COMBAT->hit_player(ply, ply, 600,
                                 "electricity", 0, "magic");
    }
}
