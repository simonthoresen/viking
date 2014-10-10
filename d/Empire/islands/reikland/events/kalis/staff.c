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

    set_name("Staff of Kalis Pathon");
    set_short("a staff of ice");
    set_long("This is a staff of ever-cold, enchanted ice. Its head burns " +
             "with an icy blue flame. The staff's grip is a leather thong " +
	     "wrapped around wolf's fur.");
    add_id(({ "staff", "staff of ice" }));
    set_info("This is the staff of Kalis Pathon.");
    set_class(20);
    set_weight(4);
    set_value(2222);
    set_damage_type("cold");
    set_min_align(ALIGN_GOOD);
    set_hit_func(this_object());
    set_wield_modifier("devotion_good", 20);
    set_wield_modifier("resist_cold", 50);
    set_wield_modifier("prot_cold", 10);
    set_wield_modifier("vuln_fire", 80);
    add_hook("__break", store_fp("shatter_staff"));
    add_property(({ "artifact", "cold", "good" }));
    add_property("vuln_fire", 100);
    add_property("wield_msg", 
		 "The coldness of the staff makes your hand numb.\n");
    add_property("remove_msg", 
		 "The coldness of the staff leaves you.\n");
}

public mixed
weapon_hit(object foe) 
{
    object ply;
    int val;
    if ((!objectp(ply = query_wield()) || !objectp(foe)) || 
        (interactive(ply) && ply->query_alignment() < foe->query_alignment()))
    {
        return "miss";
    }
    val = ply->query_tmp_prop("devotion_good");
    if ((_bias += val / 4 + random(val / 2)) >= 100) {
        _bias = 0; /* by devotion 10-50% chance */
        tell_object(ply, "You channel the magic of the holy magician!\n");
        EMP_D_COMBAT->hit_players(ply, ply->query_attackers(), 
				  15 + random(10), "magic", 0, this_object());
    } 
    return 31; /* average 20 dmg at level 29 */
}

static void
shatter_staff(string type, int dmg) 
{
    object ply, env, *arr;
    int i, len;
    if (!objectp(ply = environment()) || 
        !living(ply) || 
        !objectp(env = environment(ply)) ||
        !arrayp(arr = filter_array(all_inventory(env), "isliving", FILTER_OB)))
    {
        return;
    }
    tell_room(env, "\nThe staff of ice explodes in a hail of razor-sharp " +
              "ice-fragments!\n");
    EMP_D_COMBAT->hit_players(ply, arr, 50 + random(150), "cold", 0, this_object());
    call_out("destroy", 0);
}
