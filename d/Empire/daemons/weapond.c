#include "/d/Empire/empire.h"

#define TYPE_AXE              ("axe")
#define TYPE_CURVED_SWORD     ("curved sword")
#define TYPE_DAGGER           ("dagger")
#define TYPE_GREAT_AXE        ("greataxe")
#define TYPE_GREAT_SWORD      ("greatsword")
#define TYPE_GREAT_HAMMER     ("greathammer")
#define TYPE_HALBERD          ("halberd")
#define TYPE_HAMMER           ("hammer")
#define TYPE_KATANA           ("katana")
#define TYPE_PIERCING_SWORD   ("piercing sword")
#define TYPE_SPEAR            ("spear")
#define TYPE_SWORD            ("sword")

inherit EMP_I_DAEMON;

private string
random_onehanded()
{
    switch (random(6)) {
    case 0:  return TYPE_AXE;
    case 1:  return TYPE_CURVED_SWORD;
    case 2:  return TYPE_DAGGER;
    case 3:  return TYPE_HAMMER;
    case 4:  return TYPE_PIERCING_SWORD;
    case 5:  return TYPE_SWORD;
    default: error("Index out of bounds.");
    }
}

private string
random_twohanded()
{
    switch (random(6)) {
    case 0:  return TYPE_GREAT_AXE;
    case 1:  return TYPE_GREAT_SWORD;
    case 2:  return TYPE_GREAT_HAMMER;
    case 3:  return TYPE_HALBERD;
    case 4:  return TYPE_KATANA;
    case 5:  return TYPE_SPEAR;
    default: error("Index out of bounds.");
    }
}

private int
query_hands(string type)
{
    switch (type) {
    case TYPE_AXE:
    case TYPE_CURVED_SWORD:
    case TYPE_DAGGER:
    case TYPE_HAMMER:
    case TYPE_PIERCING_SWORD:
    case TYPE_SWORD:
        return 1;
    case TYPE_GREAT_AXE:
    case TYPE_GREAT_SWORD:
    case TYPE_GREAT_HAMMER:
    case TYPE_HALBERD:
    case TYPE_KATANA:
    case TYPE_SPEAR:
        return 2;
    default:
        error("Unknown type '" + type + "'.");
    }
}

private string
random_axe()
{
    switch (random(3)) {
    case 0:  return "battle axe";
    case 1:  return "crescent axe";
    case 2:  return "hand axe";
    default: error("Index out of bounds.");
    }
}

private string
random_curved_sword()
{
    switch (random(3)) {
    case 0:  return "falchion";
    case 1:  return "jagged blade";
    case 2:  return "scimitar";
    default: error("Index out of bounds.");
    }
}

private string
random_dagger()
{
    switch (random(4)) {
    case 0:  return "bandit's knife";
    case 1:  return "curved knife";
    case 2:  return "dagger";
    case 3:  return "parrying dagger";
    default: error("Index out of bounds.");
    }
}

private string
random_great_axe()
{
    switch (random(1)) {
    case 0:  return "greataxe";
    default: error("Index out of bounds.");
    }
}

private string
random_great_sword()
{
    switch (random(5)) {
    case 0:  return "bastard sword";
    case 1:  return "claymore";
    case 2:  return "flamberge";
    case 3:  return "greatsword";
    case 4:  return "zweihander";
    default: error("Index out of bounds.");
    }
}

private string
random_great_hammer()
{
    switch (random(2)) {
    case 0:  return "large club";
    case 1:  return "great club";
    default: error("Index out of bounds.");
    }
}

private string
random_halberd()
{
    switch (random(4)) {
    case 0:  return "great scythe";
    case 1:  return "halberd";
    case 2:  return "lucerne";
    case 3:  return "scythe";
    default: error("Index out of bounds.");
    }
}

private string
random_hammer()
{
    switch (random(5)) {
    case 0:  return "hammer";
    case 1:  return "mace";
    case 2:  return "morning star";
    case 3:  return "pickaxe";
    case 4:  return "warpick";
    default: error("Index out of bounds.");
    }
}

private string
random_katana()
{
    switch (random(5)) {
    case 0:  return "jin tachi";
    case 1:  return "katana";
    case 2:  return "nodachi";
    case 3:  return "odachi";
    case 4:  return "tachi";
    default: error("Index out of bounds.");
    }
}

private string
random_piercing_sword()
{
    switch (random(3)) {
    case 0:  return "estoc";
    case 1:  return "mail breaker";
    case 2:  return "rapier";
    default: error("Index out of bounds.");
    }
}

private string
random_spear()
{
    switch (random(5)) {
    case 0:  return "partizan";
    case 1:  return "pike";
    case 2:  return "spear";
    case 3:  return "trident";
    case 4:  return "winged spear";
    default: error("Index out of bounds.");
    }
}

private string
random_sword()
{
    switch (random(4)) {
    case 0:  return "broadsword";
    case 1:  return "shortsword";
    case 2:  return "longsword";
    case 3:  return "barbed straight sword";
    default: error("Index out of bounds.");
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

private string *
flatten_materials(string *in)
{
    string *out;
    int i, len;
    out = in;
    for (i = 0, len = sizeof(in); i < len; ++i) {
        out |= explode(in[i], " ");
    }
    return out;
}

private string *
flatten_types(string *in)
{
    string *out, *arr;
    int i, len;
    out = in;
    for (i = 0, len = sizeof(in); i < len; ++i) {
        if (find_first(' ', in[i]) < -1) {
            continue;
        }
        arr = explode(in[i], " ");
        out |= ({ arr[sizeof(arr) - 1] });
    }
    return out;
}

private string *
create_ids(string *materials, string *types)
{
    string *ret;
    int mat_idx, mat_len;
    int typ_idx, typ_len;
    materials = flatten_materials(materials);
    mat_len = sizeof(materials);
    types = flatten_types(types);
    typ_len = sizeof(types);
    ret = types;
    for (mat_idx = 0; mat_idx < mat_len; ++mat_idx) {
        for (typ_idx = 0; typ_idx < typ_len; ++typ_idx) {
            ret |= ({ materials[mat_idx] + " " + types[typ_idx] });
        }
    }
    return ret;
}

private void
setup_axe(int quality, object obj)
{
    string type, wood, metal;
    type  = random_axe();
    wood  = EMP_D_WOOD->random_wood(quality, obj);
    metal = EMP_D_METAL->random_metal(quality, obj);
    obj->set_name(metal + " " + type);
    obj->set_short(add_article(obj->query_name()));
    obj->set_long("It is " + add_article(type) + " with a head made of " +
                  metal + ", and a handle made of " + wood + ". " +
                  desc_quality(quality, obj));
    obj->add_id(create_ids(({ wood, metal, "metal" }),
                           ({ "axe", type })));
    obj->set_damage_type("chop");
}

private void
setup_curved_sword(int quality, object obj)
{
    string type, leather, metal;
    type    = random_curved_sword();
    leather = EMP_D_LEATHER->random_leather(quality, obj);
    metal   = EMP_D_METAL->random_metal(quality, obj);
    obj->set_name(metal + " " + type);
    obj->set_short(add_article(obj->query_name()));
    obj->set_long("It is " + add_article(type) + " with a curved blade of " +
                  metal + ". The hilt is wrapped in " + leather + ". " +
                  desc_quality(quality, obj));
    obj->add_id(create_ids(({ leather, metal, "metal" }),
                           ({ "curved sword", type })));
    obj->set_damage_type("slash");
}

private void
setup_dagger(int quality, object obj)
{
    string type, metal, stone;
    type  = random_dagger();
    metal = EMP_D_METAL->random_metal(quality, obj);
    stone = EMP_D_GEMSTONE->random_gemstone();
    obj->set_name(metal + " " + type);
    obj->set_short(add_article(obj->query_name()));
    obj->set_long("It is " + add_article(type) + " with a blade of " + metal +
                  ". There is " + add_article(stone) + " set in its hilt. " +
                  desc_quality(quality, obj));
    obj->set_class((int)ceil(((float)obj->weapon_class() * 2.0) / 3.0));
    obj->add_id(create_ids(({ stone, metal, "metal" }),
                           ({ "dagger", type })));
    obj->set_damage_type("pierce");
}

private void
setup_great_axe(int quality, object obj)
{
    string type, wood, metal, animal;
    type   = random_great_axe();
    wood   = EMP_D_WOOD->random_wood(quality, obj);
    metal  = EMP_D_METAL->random_metal(quality, obj);
    animal = EMP_D_ANIMAL->random_animal();
    obj->set_name(metal + " " + type);
    obj->set_short(add_article(obj->query_name()));
    obj->set_long("It is " + add_article(type) + " with a large head made " +
                  "of " + metal + ", and a handle made of " + wood + ". " +
                  "An image of " + add_article(animal) + " is burned into " +
                  "the wood. " + desc_quality(quality, obj));
    obj->set_weight(obj->query_weight() * 2);
    obj->add_id(create_ids(({ wood, animal, metal, "metal" }),
                           ({ "great axe", type })));
    obj->set_damage_type("chop");
}

private void
setup_great_hammer(int quality, object obj)
{
    string type, wood, metal, animal;
    type   = random_great_hammer();
    wood   = EMP_D_WOOD->random_wood(quality, obj);
    metal  = EMP_D_METAL->random_metal(quality, obj);
    animal = EMP_D_ANIMAL->random_animal();
    obj->set_name(wood + " " + type);
    obj->set_short(add_article(obj->query_name()));
    obj->set_long("It is " + add_article(type) + " made of " + wood +
                  " with spikes of " + metal + ". An image of " +
                  add_article(animal) + " is burned into the wood. " +
                  desc_quality(quality, obj));
    obj->set_weight(obj->query_weight() * 2);
    obj->add_id(create_ids(({ wood, "wood", animal, metal }),
                           ({ "great hammer", type })));
    obj->set_damage_type("impact");
}

private void
setup_great_sword(int quality, object obj)
{
    string type, leather, metal, symbol;
    type    = random_great_sword();
    leather = EMP_D_LEATHER->random_leather(quality, obj);
    metal   = EMP_D_METAL->random_metal(quality, obj);
    symbol  = EMP_D_SYMBOL->random_symbol();
    obj->set_name(metal + " " + type);
    obj->set_short(add_article(obj->query_name()));
    obj->set_long("It is " + add_article(type) + " with a large blade of " +
                  metal + ". " + capitalize(add_article(symbol)) + " is " +
                  "etched into the metal. The hilt is wrapped in " + leather +
                  ". " + desc_quality(quality, obj));
    obj->set_weight(obj->query_weight() * 2);
    obj->add_id(create_ids(({ leather, symbol, metal, "metal" }),
                           ({ "great sword", type })));
    obj->set_damage_type("slash");
}

private void
setup_halberd(int quality, object obj)
{
    string type, wood, metal;
    type  = random_halberd();
    wood  = EMP_D_WOOD->random_wood(quality, obj);
    metal = EMP_D_METAL->random_metal(quality, obj);
    obj->set_name(metal + " " + type);
    obj->set_short(add_article(obj->query_name()));
    obj->set_long("It is " + add_article(type) + " with a head of " + metal +
                  " and a long handle of " + wood + ". " +
                  desc_quality(quality, obj));
    obj->add_id(create_ids(({ wood, metal, "metal" }),
                           ({ "halberd", type })));
    obj->set_damage_type("slash");
}

private void
setup_hammer(int quality, object obj)
{
    string type, wood, metal;
    type  = random_hammer();
    wood  = EMP_D_WOOD->random_wood(quality, obj);
    metal = EMP_D_METAL->random_metal(quality, obj);
    obj->set_name(wood + " " + type);
    obj->set_short(add_article(obj->query_name()));
    obj->set_long("It is " + add_article(type) + " with a head of " + metal +
                  " and a handle of " + wood + ". " +
                  desc_quality(quality, obj));
    obj->add_id(create_ids(({ wood, "wood", metal }),
                           ({ "hammer", type })));
    obj->set_damage_type("blunt");
}

private void
setup_katana(int quality, object obj)
{
    string type, leather, metal;
    type    = random_katana();
    leather = EMP_D_LEATHER->random_leather(quality, obj);
    metal   = EMP_D_METAL->random_metal(quality, obj);
    obj->set_name(metal + " " + type);
    obj->set_short(add_article(obj->query_name()));
    obj->set_long("It is " + add_article(type) + " with a long, thin blade " +
                  "of " + metal + ". The hilt is wrapped in " + leather +
                  ". " + desc_quality(quality, obj));
    obj->add_id(create_ids(({ leather, metal, "metal" }),
                           ({ "sword", "katana", type })));
    obj->set_damage_type("slash");
}

private void
setup_piercing_sword(int quality, object obj)
{
    string type, metal, stone;
    type  = random_piercing_sword();
    metal = EMP_D_METAL->random_metal(quality, obj);
    stone = EMP_D_GEMSTONE->random_gemstone();
    obj->set_name(metal + " " + type);
    obj->set_short(add_article(obj->query_name()));
    obj->set_long("It is " + add_article(type) + " with a long, straight " +
                  "and stiff blade of " + metal + ". The pommel holds " +
                  add_article(stone) + ". " + desc_quality(quality, obj));
    obj->add_id(create_ids(({ stone, metal, "metal" }),
                           ({ "piercing sword", type })));
    obj->set_damage_type("pierce");
}

private void
setup_spear(int quality, object obj)
{
    string type, wood, metal;
    type  = random_spear();
    wood  = EMP_D_WOOD->random_wood(quality, obj);
    metal = EMP_D_METAL->random_metal(quality, obj);
    obj->set_name(wood + " " + type);
    obj->set_short(add_article(obj->query_name()));
    obj->set_long("It is " + add_article(type) + " made of " + wood +
                  " with a head of " + metal + ". " +
                  desc_quality(quality, obj));
    obj->set_wield_modifier("ac", 1); /* great range */
    obj->add_id(create_ids(({ wood, "wood", metal }),
                           ({ "spear", type })));
    obj->set_damage_type("pierce");
}

private void
setup_sword(int quality, object obj)
{
    string type, leather, metal;
    type    = random_sword();
    leather = EMP_D_LEATHER->random_leather(quality, obj);
    metal   = EMP_D_METAL->random_metal(quality, obj);
    obj->set_name(metal + " " + type);
    obj->set_short(add_article(obj->query_name()));
    obj->set_long("It is " + add_article(type) + " with a blade of " + metal +
                  ". The hilt is wrapped in " + leather + ". " +
                  desc_quality(quality, obj));
    obj->add_id(create_ids(({ leather, metal, "metal" }),
                           ({ "sword", type })));
    obj->set_damage_type("slash");
}

public object
create_weapon(int quality, string type)
{
    int twohanded;
    object obj;
    twohanded = 0;
    if (!stringp(type)) {
        type = random(2) ? random_onehanded() : random_twohanded();
    } else if (type == "onehanded") {
        type = random_onehanded();
    } else if (type == "twohanded") {
        type = random_twohanded();
    }
    obj = new(EMP_C_WEAPON);
    obj->set_value(min(100, quality) + random(quality));
    if (query_hands(type) == 2) {
        obj->set_type("twohanded");
        obj->set_class(max(0, min(20, (quality * 21) / 100)));
    } else {
        obj->set_class(max(0, min(19, (quality * 20) / 100)));
    }
    obj->set_weight(max(1, obj->weapon_class() / 5));
    obj->add_id(type);
    switch (type) {
    case TYPE_AXE:            setup_axe(quality, obj);            break;
    case TYPE_CURVED_SWORD:   setup_curved_sword(quality, obj);   break;
    case TYPE_DAGGER:         setup_dagger(quality, obj);         break;
    case TYPE_GREAT_AXE:      setup_great_axe(quality, obj);      break;
    case TYPE_GREAT_HAMMER:   setup_great_hammer(quality, obj);   break;
    case TYPE_GREAT_SWORD:    setup_great_sword(quality, obj);    break;
    case TYPE_HALBERD:        setup_halberd(quality, obj);        break;
    case TYPE_HAMMER:         setup_hammer(quality, obj);         break;
    case TYPE_KATANA:         setup_katana(quality, obj);         break;
    case TYPE_PIERCING_SWORD: setup_piercing_sword(quality, obj); break;
    case TYPE_SPEAR:          setup_spear(quality, obj);          break;
    case TYPE_SWORD:          setup_sword(quality, obj);          break;
    default:                  error("Unknown type '" + type + "'.");
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
    if (obj->query_type() != "twohanded" && objectp(ply->query_weapon(1))) {
        ply->command("wield " + obj->query_name() + " in left hand");
    } else {
        ply->command("wield " + obj->query_name());
    }
    return 1;
}

public object
add_weapon(int quality, string type, object ply)
{
    object obj;
    if ((!objectp(ply) && !objectp(ply = previous_object())) ||
        (!living(ply)))
    {
        return 0;
    }
    if (!stringp(type) && objectp(ply->query_worn_armour("shield"))) {
        type = "onehanded";
    }
    if (!objectp(obj = create_weapon(quality, type))) {
        EMP_LOG("weapond", "found no weapon of type '" + type + "'");
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
        obj = add_weapon(quality, type, ply);
    }
    return obj;
}
