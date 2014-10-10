#include "/d/Empire/islands/blackrock.h"

inherit EMP_I_TOKEN;

static void
create()
{
    ::create();

    set_name("black coin");
    set_short(store_fp("my_short"));
    set_long(store_fp("my_long"));
    add_id(({ "coin", "coins", "black coins", source_file_name() }));
    add_property("metal");
}

static string
my_short()
{
    int val;
    val = query_amount();
    return (val > 1 ? val : "a") + " black coin" + (val > 1 ? "s" : "");
}

static void
my_long()
{
    int val;
    val = query_amount();
    write("You have " + val + " black coin" + (val > 1 ? "s" : "") + ". " +
          "You can spend these at the shop outside Blackrock mountain.");
}
