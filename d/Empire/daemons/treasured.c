#include "/d/Empire/empire.h"

inherit I_DAEMON;

private string query_random_noun() {
    switch (random(14)) {
    case  0: return "pearl";
    case  1: return "gem";
    case  2: return "jewel";
    case  3: return "bauble";
    case  4: return "bead";
    case  5: return "gemstone";
    case  6: return "ornament";
    case  7: return "trunket";
    case  8: return "charm";
    case  9: return "bangle";
    case 10: return "circlet";
    case 11: return "manacle";
    case 12: return "diamond";
    case 13: return "rock";
    }
}

private string query_random_adjective() {
    switch (random(24)) {
    case  0: return "copacetic";
    case  1: return "excellent";
    case  2: return "exquisite";
    case  3: return "fine";
    case  4: return "great";
    case  5: return "hunky dory";
    case  6: return "meritable";
    case  7: return "rare";
    case  8: return "superior";
    case  9: return "unreal";
    case 10: return "wonderful";
    case 11: return "exorbitant";
    case 12: return "extortionate";
    case 13: return "extravagant";
    case 14: return "fancy";
    case 15: return "precious";
    case 16: return "premium";
    case 17: return "gorgeous";
    case 18: return "invaluable";
    case 19: return "lavish";
    case 20: return "luxurious";
    case 21: return "opulent";
    case 22: return "splendid";
    case 23: return "sumptuous";
    }
}

private object create_random_treasure(int value) {
    object obj;
    if (value < 100) {
        value = 100;
    }
    if (value > 1000) {
        value = 1000;
    }
    obj = new(I_TREASURE);
    obj->set_name(query_random_noun());
    obj->set_short(add_article(query_random_adjective()) + " " + 
		   obj->query_name());
    obj->set_long("It is " + obj->query_short() + ". It looks valuable.");
    obj->set_value(value / 2 + random(value / 2));
    obj->set_weight(1);
    return obj;
}

public object *create_treasure(int value) {
    object *ret, obj;
    int sum;
    ret = ({ });
    sum = 0;
    while (sum < value) {
	if (!objectp(obj = create_random_treasure(value))) {
	    return ret;
	}
	ret += ({ obj });
	sum += obj->query_value();
    }
    return ret;
}

public varargs object *add_treasure(int value, object obj) {
    object *arr;
    if ((!objectp(obj) && !objectp(obj = previous_object())) ||
        (!arrayp(arr = create_treasure(value))))
    {
        return 0;
    } 
    arr->move(obj);
    return arr;
}

