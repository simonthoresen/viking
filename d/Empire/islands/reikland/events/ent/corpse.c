#include "/d/Empire/islands/reikland.h"

inherit I_CORPSE;

static void
create() 
{
    ::create();
    set_name("tree");
    set_short("a huge pile of lumber");
    set_long("Seems to be the remains of a HUGE tree, savagely chopped down. " +
             "Using unstandard procedures... Most of the branches are broken " +
             "in bits and the body is covered with ugly wounds.");
    add_id(({ "corpse", "pile", "lumber", "pile of lumber" }));
    add_property(({ "wood", "corpse" }));
    set_info("This is the corpse of an ancient Ent.");
    set_weight(50);
    set_value(100);

    remove_call_out("decay");
    call_out("maybe_treasure", 0);
}

public void
maybe_treasure() 
{
    if (query_level() != parse_path("ent")->query_level()) {
        return;
    }
    EMP_D_TREASURE->add_treasure(10000);
    make(parse_path("elixir"));
    make(parse_path("elixir"));
    if (random(100) < 33) {
        make(parse_path("elixir"));
    }
    make(parse_path("scroll"));
    if (random(100) < 33) {
        make(parse_path("scroll"));
    }
}

public string
short() 
{
    return query_short();
}

public varargs void
long(string arg, int nonl) 
{
    write(query_long());
}

public int
id(string arg) 
{
    return member_array(arg, query_id_array()) >= 0;
}
