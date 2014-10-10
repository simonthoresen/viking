#include "/d/Empire/islands/reikland.h"

inherit RED_DIR_EVENTS + "imhotep/demon_base";

static void
create()
{
    ::create();
    set_name("Demon");
    set_short("an evil looking demon");
    set_long("You stand before a foul creature of evil. It has a pair of " +
             "%^L_RED%^glowing red eyes%^END%^ and great wings protruding " +
             "from its back. The sense of foul and chaotic magic reeks from " +
             "its very presence.");
    set_level(20 + random(4));
    set_str(49 + random(3));
    set_dex(39 + random(3));
    set_con(39 + random(3));
    set_int(20);
    set_hp(1500);
    set_sp(500);
    set_al(-1000);
    set_wc(35 + random(15));
    set_ac(15 + random(5));
    add_money(750 + random(500));
    load_a_chat(30, ({ store_fp("cast_blast"), store_fp("cast_bolt")  }));
}

private string
random_type()
{
    return ({ "fire", "cold", "electricity", "impact",
              "drain", "acid", "magic" })[random(7)];
}

static void
cast_blast(object ply, object foe)
{
    tell_room(environment(ply), "%^B_MAGENTA%^%^L_YELLOW%^Demon casts a " +
              "chaos-blast!%^END%^\n");
    EMP_D_COMBAT->hit_player(ply, foe, 25 + random(25),
                             random_type(), 0, "spell");
}

static void
cast_bolt(object ply, object foe)
{
    tell_room(environment(ply), "%^B_MAGENTA%^%^L_YELLOW%^Demon casts a " +
              "chaos-bolt!%^END%^\n");
    EMP_D_COMBAT->hit_player(ply, foe, 15 + random(15),
                             random_type(), 0, "spell");
}
