#include "/d/Empire/islands/artifact.h"

inherit EMP_I_ROOM;

static void
create()
{
    ::create();
    set_light(1);
    set_short("Ruins of a post office");
    set_long("You are in the ruins of post office. Commands:\n\n" +
	     "mail <name>/<malias>  Mail to player 'name'.\n" +
	     "mail                  Read your new/unread mailbox.\n"+
	     "mail -f               Read your old mailbox.\n\n" +
             "There is a working clock on that far wall.");
    add_property(({ "indoors", "no_nothing", "post_office" }));
    add_reset_object("postman", ATI_DIR_OBJ + "postman", 1);
    add_item("clock", store_fp("exa_clock"));
}

static string
exa_clock()
{
    return "It shows " + EMP_D_TIME->query_stime() + ".";
}
