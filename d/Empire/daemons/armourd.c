#include "/d/Empire/empire.h"

#define CSTR_QUILTED       ("quilted")
#define CSTR_SOFT_LEATHER  ("leather")
#define CSTR_RIGID_LEATHER ("rigid leather")
#define CSTR_CHAIN         ("chain")
#define CSTR_SCALE         ("scale")
#define CSTR_SPLINTED      ("splinted")
#define CSTR_BANDED        ("banded")
#define CSTR_LAMELLAR      ("lamellar")
#define CSTR_PLATED        ("plated")

inherit EMP_I_DAEMON;

private string
random_construction()
{
    switch (random(9)) {
    case 0:  return CSTR_QUILTED;
    case 1:  return CSTR_SOFT_LEATHER;
    case 2:  return CSTR_RIGID_LEATHER;
    case 3:  return CSTR_CHAIN;
    case 4:  return CSTR_SCALE;
    case 5:  return CSTR_SPLINTED;
    case 6:  return CSTR_BANDED;
    case 7:  return CSTR_LAMELLAR;
    case 8:  return CSTR_PLATED;
    default: error("Index out of bounds.");
    }
}

private string
random_material(int quality, string cstr, object obj)
{
    switch (cstr) {
    case CSTR_QUILTED:
        return EMP_D_CLOTH->random_cloth(quality, obj);
    case CSTR_SOFT_LEATHER:
    case CSTR_RIGID_LEATHER:
        return EMP_D_LEATHER->random_leather(quality, obj);
    case CSTR_CHAIN:
    case CSTR_SCALE:
    case CSTR_SPLINTED:
    case CSTR_BANDED:
    case CSTR_LAMELLAR:
    case CSTR_PLATED:
        return EMP_D_METAL->random_metal(quality, obj);
    default:
        error("Unknown construction '" + cstr + "'.");
   }
}

private string
desc_construction(string cstr, string mat)
{
    switch (cstr) {
    case CSTR_QUILTED:
        return "It consists of two layers of " + mat + " with a layer of " +
            "cotton in between. ";
    case CSTR_SOFT_LEATHER:
        return "It is made from a soft piece of " + mat + " that has been " +
            "tanned and crafted. ";
    case CSTR_RIGID_LEATHER:
        return "It is made from a tough piece of " + mat + " that has been " +
            "tanned and crafted. ";
    case CSTR_CHAIN:
        return "It consists of small " + mat + " rings linked together in a " +
            "pattern to form a mesh. ";
    case CSTR_SCALE:
        return "It is made of small, thin plates of " + mat + " riveted " +
            "onto a cottong backing. The scales are staggered from one row " +
            "to the next to increase the strength of the armour. ";
    case CSTR_SPLINTED:
        return "It consists of long narrow strips of " + mat + " riveted " +
            "onto a leather backing. It offers good protection, but is " +
            "quite inflexible. ";
    case CSTR_BANDED:
        return "It consists of " + mat + " bands that are overlapping and " +
            "fastened on the inside with leather strips. ";
    case CSTR_LAMELLAR:
        return "It consists of small rectangular plates of " + mat +
            " attached to each other with leather lacing. ";
    case CSTR_PLATED:
        return "It consists of " + mat + " plates secured over a leather " +
            "backing. It is heavy and difficult to maneuver in. ";
    default:
        error("Unknown construction '" + cstr + "'.");
    }
}

private string
desc_quality(int quality, object obj)
{
    string str;
    if (stringp(str = EMP_D_QUALITY->desc_quality(quality, obj))) {
        return str;
    }
    return "";
}

private void
setup_armour(int quality, string type, object obj)
{
    string cstr, mat;
    cstr = random_construction();
    mat  = random_material(quality, cstr, obj);
    obj->set_name(cstr + " " + type);
    obj->set_short((add_article(cstr) + " " + type) +
                   (stringp(mat) ? " of " + mat : ""));
    obj->set_long("It is " + obj->query_short() + ". " +
                  desc_construction(cstr, mat) +
                  desc_quality(quality, obj));
    obj->add_id(mat + " " + type);
}

private void
setup_pair(int quality, string type, object obj)
{
    string cstr, mat;
    cstr = random_construction();
    mat  = random_material(quality, cstr, obj);
    obj->set_name(cstr + " " + type + "s");
    obj->set_short(("a pair of " + cstr + " " + type + "s") +
                   (stringp(mat) ? " of " + mat : ""));
    obj->set_long("It is " + obj->query_short() + ". " +
                  desc_construction(cstr, mat) +
                  desc_quality(quality, obj));
    obj->add_id(mat + " " + type + "s");
    obj->add_id(type + "s");
}

private void
setup_cloak(int quality, object obj)
{
    string color, cloth;
    color = EMP_D_COLOR->random_color();
    cloth = random(2) ? EMP_D_CLOTH->random_cloth(quality, obj) :
            EMP_D_FUR->random_fur(quality, obj);
    obj->set_name(color + " cloak");
    obj->set_short(add_article(color) + " cloak of " + cloth);
    obj->set_long("It is " + obj->query_short() + ". " +
                  desc_quality(quality, obj));
    obj->add_id(cloth + " cloak");
}

private void
setup_tabard(int quality, object obj)
{
    string color, cloth, decal;
    color = EMP_D_COLOR->random_color();
    cloth = EMP_D_CLOTH->random_cloth(quality, obj);
    decal = random(2) ? EMP_D_ANIMAL->random_animal() :
            EMP_D_SYMBOL->random_symbol();
    obj->set_name(color + " tabard");
    obj->set_short(add_article(cloth) + " tabard");
    obj->set_long("It is " + add_article(color) + " " + cloth +
                  " tabard with " + add_article(EMP_D_COLOR->random_color()) +
                  " " + decal + " embroidered on its front. " +
                  desc_quality(quality, obj));
    obj->add_id(cloth + " tabard");
}

private void
setup_amulet(int quality, object obj)
{
    string metal, stone;
    metal = EMP_D_METAL->random_metal(quality, obj);
    stone = EMP_D_GEMSTONE->random_gemstone();
    obj->set_name(metal + " amulet");
    obj->set_short(add_article(metal) + " amulet with " + add_article(stone));
    obj->set_long("It is " + add_article(metal) + " amulet inset with " +
                  add_article(stone) + " on a leather strap. " +
                  desc_quality(quality, obj));
    obj->add_property(metal);
}

private void
setup_ring(int quality, object obj)
{
    string metal, stone;
    metal = EMP_D_METAL->random_metal(quality, obj);
    stone = EMP_D_GEMSTONE->random_gemstone();
    obj->set_name(metal + " ring");
    obj->set_short(add_article(metal) + " ring with " + add_article(stone));
    obj->set_long("It is " + add_article(metal) + " ring inset with " +
                  add_article(stone) + ". " + desc_quality(quality, obj));
    obj->add_property(metal);
}

private void
setup_shield(int quality, object obj)
{
    string metal, type;
    switch (random(9)) {
    case 0:  type = "crest";  break;
    case 1:  type = "heater"; break;
    case 2:  type = "kite";   break;
    case 3:  type = "knight"; break;
    case 4:  type = "large";  break;
    case 5:  type = "round";  break;
    case 6:  type = "small";  break;
    case 7:  type = "target"; break;
    case 8:  type = "tower";  break;
    default: error("Index out of bounds.");
    }
    metal = EMP_D_METAL->random_metal(quality, obj);
    obj->set_name(type + " shield");
    obj->set_short(add_article(type) + " shield of " + metal);
    obj->set_long("It is " + obj->query_short() + ". " +
                  desc_quality(quality, obj));
    obj->add_id(metal + " shield");
}

public object
create_armour(int quality, string type)
{
    object obj;
    int max_ac;
    max_ac = ARMOUR_MAXES[type];
    obj = new(EMP_C_ARMOUR);
    obj->set_type(type);
    obj->set_ac(max(0, min(max_ac, quality * (max_ac + 1) / 100)));
    obj->set_weight(max(1, obj->query_ac()));
    obj->set_value(min(100, quality) + random(quality));
    switch (type) {
    case "amulet":  setup_amulet(quality, obj);        break;
    case "armour":  setup_armour(quality, type, obj);  break;
    case "belt":    setup_armour(quality, type, obj);  break;
    case "boot":    setup_pair(quality, type, obj);    break;
    case "cloak":   setup_cloak(quality, obj);         break;
    case "glove":   setup_pair(quality, type, obj);    break;
    case "helmet":  setup_armour(quality, type, obj);  break;
    case "legging": setup_pair(quality, type, obj);    break;
    case "ring":    setup_ring(quality, obj);          break;
    case "shield":  setup_shield(quality, obj);        break;
    case "tabard":  setup_tabard(quality, obj);        break;
    default:        error("Illegal armour type '" + type + "'.");
    }
    if (quality > 100) {
        EMP_D_ENCHANT->add_enchant(obj, quality - 100);
    }
    return obj;
}

private int
equip(object ply, object obj)
{
    if (!objectp(ply) || !objectp(obj)) {
        return 0;
    }
    obj->move(ply);
    ply->command("wear " + obj->query_name());
    return 1;
}

public object
add_armour(int quality, string type, object ply)
{
    object obj;
    if ((!objectp(ply) && !objectp(ply = previous_object())) ||
        (!living(ply)))
    {
        return 0;
    }
    if (!stringp(type)) {
        object *prev;
        string *next;
        int len;
        next = ({ "amulet", "armour", "belt", "boot", "cloak", "glove",
                  "helmet", "legging", "ring", "shield" });
        if (arrayp(prev = ply->query_worn_armour())) {
            next -= prev->query_type();
        }
        if (objectp(ply->query_weapon(2))) {
            next -= ({ "shield" });
        }
        if ((len = sizeof(next)) == 0) {
            EMP_LOG("armourd", sprintf("%O has no available slots", ply));
            return 0;
        }
        type = next[random(len)];
    }
    if (!objectp(obj = create_armour(quality, type))) {
        EMP_LOG("armourd", "found no armour of type '" + type + "'");
        return 0;
    }
    equip(ply, obj);
    return obj;
}

public object
add_unique(string file, int quality, string type, object ply)
{
    object obj;
    if ((!clonep(ply) && !clonep(ply = previous_object())) ||
        (!living(ply)))
    {
        return 0;
    }
    if (objectp(obj = D_TREASURE->get_unique(file))) {
        equip(ply, obj);
    } else {
        obj = add_armour(quality, type, ply);
    }
    return obj;
}
