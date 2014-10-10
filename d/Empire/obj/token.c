#include "/d/Empire/empire.h"

inherit EMP_I_TOKEN;

static void
create()
{
    ::create();
    set_name("token of triumph");
    set_short(store_fp("my_short"));
    set_long(store_fp("my_long"));
    add_id(({ "token", "tokens", "tokens of triumph" }));
}

static string
my_short()
{
    int val;
    val = query_amount();
    return (val > 1 ? val : "a") + " token" + (val > 1 ? "s" : "") +
           " of triumph";
}

static void
my_long()
{
    int val;
    val = query_amount();
    write("You have " + val + " token" + (val > 1 ? "s" : "") + " " +
          "of triumph. You can spend these in Altdorf.");
}
