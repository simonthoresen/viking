#include "/d/Empire/islands/altdorf.h"

inherit EMP_I_WEAPON;

static void
create()
{
    ::create();
    set_name("Axe of Executing");
    set_short("the Axe of Executing");
    set_long("This axe is simply huge, easily matching a man-height. "+
             "It has two black edges on each side of a long metal pole. "+
             "These edges are stained with old browny bloodstains.");
    add_id(({ "axe", "execute", "blood-stained axe", "bloody axe",
              "huge axe", "executioner axe" }));
    add_property(({ "artifact", "iron" }));
    set_class(19);
    set_weight(7);
    set_value(1500 + random(500));
    set_damage_type(({ "slash", "chop", "Chop" }));
    set_type("twohanded");
    set_hit_func(this_object());
    set_wield_modifier("dex", -2,11);
    set_wield_modifier("int", -1,11);
    set_wield_modifier("str", 3,11);
    set_wield_modifier("con", 3,11);

    add_hook("__wield", store_fp("on_wield"));
    add_hook("__remove", store_fp("on_remove"));
}

static void
on_wield(object weapon, string hand)
{
    tell_object(query_wield(),
                "The long pole weights heavily into your arm as you " +
                "arm yourself, but somehow you feel stronger. " +
                "Is that smell of blood you smell?\n");
}

static void
on_remove()
{
    tell_object(query_wield(), "You arms feel heavy again.\n");
}

public int
query_damage(object ply)
{
    int ret;
    ret = ({ 60, 55, 45, 40, 35, 30, 25, 20, 15, 10, 9, 9, 9, 9, 0 })
          [random(15)];
    ret -= 50 - (int)ply->query_str();
    return ret;
}

public int
weapon_hit(object foe)
{
    int dmg, hp;
    object ply;
    string loc;
    if (!objectp(ply = query_wield()) || !objectp(foe)) {
        return 0;
    }
    if ((dmg = query_damage(ply)) < 50) {
        return dmg; /* not enough damage */
    }
    hp = foe->query_hp();
    if (random(hp / 100) > 1) {
        return dmg; /* enemy has too much hp */
    }
    if (!stringp(loc = EMP_D_LIMB->query_random_limb(foe, hp < 100))) {
        return dmg; /* no limb to cut */
    }
    message("hityou", format_message("#N chops you wickedly, severing your " +
                                     loc + ".\n", ply), foe);
    message("youhit", format_message("You chop #N wickedly, severing #p " +
                                     loc + ".\n", foe), ply);
    tell_room(environment(foe),
              format_message("#N chops $N wickedly, severing $p " +
                             loc + ".\n", ply, foe),
              ({ ply, foe }));
    EMP_D_CRITICAL->perform_cut(ply, foe, loc);
    if (!objectp(foe) || foe->query_ghost()) {
        return dmg;
    }
    if(loc == "head") {
        foe->hit_player(hp + 1, "Drain", ply);
    } else {
        foe->hit_player(50 + random(25), "chop", ply);
    }
    return dmg;
}
