#include "/d/Empire/empire.h"

inherit base I_DAEMON;
inherit util EMP_I_UTIL;

static void create() {
    base::create();
    util::create();
}

private string desc_enchant(int power) {
    switch (power) {
    case 0:      return "no more";
    case 1..5:   return "a tiny bit more";
    case 6..10:  return "a little bit more";
    case 11..20: return "a bit more";
    case 21..30: return "somewhat more";
    case 31..40: return "more";
    case 41..50: return "even more";
    case 51..60: return "much more";
    case 61..70: return "alot more";
    case 71..80: return "a whole lot more";
    case 81..90: return "unearthly more";
    default:     return "unnaturally more";
    }
}

private string desc_quality(int quality) {
    switch (quality) {
    case  0..19: return "very small ";
    case 20..39: return "small ";
    case 40..59: return "";
    case 60..79: return "large ";
    case 80..99: return "very large ";
    default:     return "bottomless ";
    }
}

private void setup_bag(int quality, object obj) {
    string cloth;
    cloth = EMP_D_CLOTH->random_cloth(quality, obj);
    obj->set_name(desc_quality(quality) + "bag");
    obj->set_short(add_article(obj->query_name()));
    obj->set_long("It is " + obj->query_short() + " made of " + cloth + ".");
    obj->add_id("bag");
}

private void setup_chest(int quality, object obj) {
    string wood;
    wood = EMP_D_WOOD->random_wood(quality, obj);
    obj->set_name(desc_quality(quality) + "chest");
    obj->set_short(add_article(obj->query_name()));
    obj->set_long("It is " + obj->query_short() + " made of " + wood + ".");
    obj->add_id("chest");
}

public object create_container(int quality) {
    object obj;
    obj = new(EMP_C_CONTAINER);
    obj->set_max_weight(4 + quality / 10);
    obj->set_weight(1 + obj->query_max_weight() / 15);
    obj->set_value(min(100, quality) + random(quality));
    if (quality > 100) {
        obj->add_property("magic");
    }
    if (random(2)) {
        setup_bag(quality, obj);
    } else {
        setup_chest(quality, obj);
    }
    return obj;
}

public object add_container(int quality, object ply) {
    object obj;
    if ((!objectp(ply) && !objectp(ply = previous_object())) ||
        (!living(ply)))
    {
        return 0;
    }
    if (!objectp(obj = create_container(quality))) {
        return 0;
    }
    obj->move(ply);
    return obj;
}
