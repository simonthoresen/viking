#include "/d/Empire/islands/reikland.h"

inherit EMP_I_ARMOUR;

static void 
create() 
{
    ::create();
    set_name("Helmet of True Sight");
    set_short("a visored helmet");
    set_long("A visored helmet made of the finest steel.");
    set_info("This helmet will grant its wearer " + 
             bold("true") + " sight.");
    add_id(({"helmet","visored helmet"}));    
    set_type("helmet");
    set_ac(1);
    set_weight(1);
    set_value(666);    
    add_property(({ "artifact", "steel" }));
    add_trigger("look", store_fp("do_look"));
}

public int
do_look(string arg) 
{
    object ply, env;
    if (!objectp(ply = query_worn_by()) ||
        !objectp(env = environment(ply))) 
    {
        return 0;
    }
    env->long();
    map_array(all_inventory(env) - ({ ply }), "write_desc");
    return 1;
}

static void
write_desc(object obj) 
{
    string name;
    if (!stringp(name = obj->query_real_name()) &&
        !stringp(name = obj->query_name())) 
    {
        return;
    }
    if (obj->query_invis()) {
        name = "(" + name + ")";
    }
    if (interactive(obj)) {
        write(capitalize(name) + " [soul]\n");
    } else if (living(obj)) {
        write(capitalize(name) + " [alive]\n");
    } else if (obj<-I_ITEM) {
        write(name + " [$" + obj->query_value() + "]\n");
    } else {
        write(name + " [dead]\n");
    }
}

