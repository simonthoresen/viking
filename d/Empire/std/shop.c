#include "/d/Empire/empire.h"

inherit EMP_I_ROOM;

private object *_for_sale;
private string  _price_list;

static void create() {
    ::create();
    _for_sale   = ({ });
    _price_list = 0;

    add_item(({ "menu", "list", "price list", "prices" }), 
             store_fp("query_price_list"));
    add_trigger(({ "buy", "order" }), store_fp("do_buy"));
    add_trigger(({ "list" }), store_fp("do_list"));
    add_hook("__destroy", store_fp("on_destroy"));
}

public void on_destroy() {
    if (arrayp(_for_sale)) {
	_for_sale -= ({ 0 });
	_for_sale->destroy();
    }
}

private void create_price_list() {
    int i, len;
    _for_sale = sort_array(_for_sale, "cmp_item");
    _price_list = sprintf("%'-'79s\n", "");
    for (i = 0, len = sizeof(_for_sale); i < len; ++i) {
        _price_list += sprintf("%-60s  %17d\n", 
                               maybe_add_article(_for_sale[i]->short()),
                               _for_sale[i]->query_value());
    }
    _price_list += sprintf("%'-'79s\n", "");
}

static int cmp_item(object lhs, object rhs) {
    return (int)lhs->query_value() - (int)rhs->query_value();
}

public void set_price_list(string val) {
    _price_list = val;
}

public string query_price_list() {
    return _price_list;
}

public void add_for_sale(mixed val) {
    int i, len;
    if (!arrayp(val)) {
        val = ({ val });
    }
    for (i = 0, len = sizeof(val); i < len; ++i) {
        _for_sale += ({ new(val[i]) });
    }
    _price_list = 0;
}

public mixed query_for_sale(string arg) {
    int i, len;
    if (!stringp(arg)) {
        return _for_sale;
    }
    for (i = 0, len = sizeof(_for_sale); i < len; ++i) {
        object obj;
        if (objectp(obj = _for_sale[i]) && obj->id(arg)) {
            return obj;
        }
    }
    return 0;
}

public int do_buy(string arg) {
    object ply, obj;
    string str;
    int val;
    if (!objectp(ply = this_player())) {
        return 0; /* erm */
    }
    if (!stringp(arg)) {
        return notify_fail(capitalize(query_verb()) + " what?");
    }
    if (!objectp(obj = query_for_sale(arg))) {
        return notify_fail("That is not for sale.");
    }
    if ((val = obj->query_value()) > ply->query_money()) {
        return notify_fail("You can not afford that.");
    }
    if (!objectp(obj = new(source_file_name(obj)))) {
        return notify_fail("There is no more in stock, try again later.");
    }
    obj->move(ply);
    ply->add_money(-val);
    str = maybe_add_article(obj->short());
    say(ply->query_name() + " orders " + str + ".\n");
    write("You pay " + val + " coins for " + str + "\n");
    return 1;
}

public int do_list(string arg) {
    if (!arrayp(_for_sale) || sizeof(_for_sale) == 0) {
        return 0;
    }
    if (!stringp(_price_list)) {
        create_price_list();
    }
    write(_price_list);
    return 1;
}

