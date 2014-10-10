#include "/d/Artifact/artifact.h"

#define P_VALUE           ("actual_value")
#define REWARD_PER_LEVEL  (500)
#define VALUE_PER_LEVEL   (20000)

inherit I_SHOP;

static void
create()
{
    object obj;
    ::create();
    set_short("The Reikland Artificer Shoppe");
    set_long("You are in a luxurious shop. Apparently this place is going " +
             "very well. Behind the counter are several cabinets made to " +
             "keep items deposited for sale by people. There is a sign on " +
             "the counter.");
    add_property("indoors");

    obj = query_store(); // created on first query
    obj->add_hook("__enter_inv", store_fp("on_store_enter_inv"));
    obj->add_hook("__leave_inv", store_fp("on_store_leave_inv"));
}

public void
reset(int flag)
{
    object obj;
    ::reset(flag);
    obj = present("standard_shopkeeper"); // is a reset object
    obj->set_name("Abduhl");
    obj->set_short("Artificer Abduhl Al'Haraz");
    obj->set_long("Abduhl Al'Haraz is in the artifact trading business. He " +
                  "is rather cunning in the arts of trading. He is carrying " +
                  "all sorts of jewelry showing how rich he is. He looks " +
                  "you over for things he could sell for you.");
    obj->add_id(({ "man", "shopkeeper", "keeper", "artificer", "al'haraz",
                   "abduhl al'haraz" }));
}

private int
query_rank(object obj)
{
    return (objectp(obj) && obj<-ART_I_GLYPH) ? obj->query_rank() : 0;
}

private int
query_reward(object obj)
{
    return query_rank(obj) * REWARD_PER_LEVEL;
}

private int
query_value(object obj)
{
    return query_rank(obj) * VALUE_PER_LEVEL;
}

public void
on_store_enter_inv(object obj, object from)
{
    if (objectp(from) && living(from)) {
        ART_LOGX("glyphs", "%s sold %s for %d",
                 from->query_real_name(),
                 obj->query_real_name(),
                 query_reward(obj));
    }
    obj->set_property(P_VALUE, obj->query_value(1));
    obj->set_value(query_value(obj) / 2);
}

public void
on_store_leave_inv(object obj, object to)
{
    if (objectp(to) && living(to)) {
        ART_LOGX("glyphs", "%s bought %s for %d",
                 to->query_real_name(),
                 obj->query_real_name(),
                 query_value(obj));
    }
    obj->set_value(obj->query_property(P_VALUE));
    obj->remove_property(P_VALUE);
}

varargs int
do_sell(object obj, int flag, object *exclude)
{
    int val;
    object ply;
    if (!flag && obj->query_property("tagged")) {
        return 0;
    }
    val = query_reward(obj);
    if (val == 0) {
        write(obj->short() + " has no value to Abduhl.\n");
        return 1;
    }
    ply = this_player();
    ply->add_money(val);
    write(obj->short() + ":\tYou get " + val + " gold coins.\n");
    say(ply->query_name() + " sells " + obj->short() + ".\n", exclude);
    query_store()->store(obj);
    return 1;
}

varargs int
do_value(object obj)
{
    int val;
    val = query_reward(obj);
    if (val == 0) {
        write(obj->short() + " has no value to Abduhl.\n");
    } else {
        write("You would get " + val + " gold coins for " +
              obj->short() + ".\n");
    }
    return 1;
}
