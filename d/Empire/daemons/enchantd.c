#include "/d/Empire/empire.h"
#include "/d/Runewaker/runewaker.h"

#define FOREVER (666999)

inherit EMP_I_DAEMON;

private string
random_physical()
{
    switch (random(6)) {
    case 0: return "slash";
    case 1: return "blunt";
    case 2: return "pierce";
    case 3: return "chop";
    case 4: return "claw";
    case 5: return "bite";
    }
}

private string
random_element()
{
    switch (random(5)) {
    case 0: return "fire";
    case 1: return "cold";
    case 2: return "electricity";
    case 3: return "acid";
    case 4: return "magic";
    }
}

private string
random_stat()
{
    switch (random(4)) {
    case 0: return "con";
    case 1: return "dex";
    case 2: return "int";
    case 3: return "str";
    }
}

private string
random_energy()
{
    switch (random(2)) {
    case 0: return "hp";
    case 1: return "sp";
    }
}

private int
div(int power, int denum)
{
    return max(1, power / denum);
}

private mapping
random_armour_enchant(object item, int power)
{
    string type;
    if (!objectp(item) || !stringp(type = item->query_type())) {
        return 0;
    }
    switch (type) {
    case "helmet":
    case "armour":
    case "shield":
        switch (random(100)) {
        case 0..79:
            return ([ "armour"   : div(power, 6),
                      "force"    : div(power, 6),
                      "duration" : FOREVER ]);
        case 80..99:
            return ([ "armour"   : div(power, 8),
                      "dtypes"   : ([ random_physical() : div(power, 4) ]),
                      "force"    : div(power, 8),
                      "duration" : FOREVER]);
        }
        break;

    case "belt":
    case "cloak":
    case "glove":
    case "tabard":
        switch (random(100)) {
        case 0..79:
            return ([ "boost"       : div(power, 8),
                      random_stat() : div(power, 8),
                      "force"       : div(power, 8),
                      "duration"    : FOREVER ]);
        case 80..99:
            return ([ "boost"       : div(power, 8),
                      "dtypes"      : ([ random_physical() : div(power, 8) ]),
                      "force"       : div(power, 8),
                      "duration"    : FOREVER ]);
        }
        break;

    case "amulet":
    case "ring":
        return ([ "regen"         : div(power, 16), /* penalize regen */
                  random_energy() : div(power, 8),
                  "force"         : div(power, 8),
                  "duration"      : FOREVER ]);

    case "boot":
    case "legging":
        return ([ "speed"    : div(power, 8),
                  "force"    : div(power, 8),
                  "duration" : FOREVER ]);
    }
    EMP_LOG("enchantd", "found no armour enchant for '" + type + "'");
    return 0;
}

private mapping
random_weapon_enchant(object item, int power)
{
    switch (random(100)) {
    case 0..79:
        return ([ "dmg"      : div(power, 8),
                  "dtypes"   : ([ random_element() : div(power, 8) ]),
                  "force"    : div(power, 8),
                  "duration" : FOREVER ]);
    case 80..99:
        return ([ "drain"         : div(power, 8),
                  random_energy() : div(power, 8),
                  "force"         : div(power, 8),
                  "duration"      : FOREVER ]);
    }
    EMP_LOG("enchantd", sprintf("found no weapon enchant for %O", item));
    return 0;
}

public int
can_enchant(object item)
{
    return objectp(item) && sizeof(REW_MASTER->query_enchants(item)) == 0;
}

public int
add_enchant(object item, int power)
{
    int ret;
    object obj;
    mapping dat;
    if (!can_enchant(item) || power <= 0) {
        return 0;
    }
    power *= MAX_WAKE_LEVEL_BY_CASTER_LEVEL / ETERNAL_LAST;
    if (item->query_property("armour")) {
        dat = random_armour_enchant(item, power);
    } else if (item->query_property("weapon")) {
        dat = random_weapon_enchant(item, power);
    } else {
        EMP_LOG("enchantd", sprintf("no enchant for %O", item));
    }
    if (!mapp(dat)) {
        return 0;
    }
    obj = new(REW_C_ENCHANT);
    obj->set_scale(ENCHANT_SCALE);
    obj->add_effects(dat);
    catch(ret = obj->resolve(item, item));
    if (!ret && objectp(obj)) {
        EMP_LOG("enchantd", sprintf("failed to enchant %O with %O",
                                    item, obj->query_effects()));
        obj->destroy();
    }
    return ret;
}
