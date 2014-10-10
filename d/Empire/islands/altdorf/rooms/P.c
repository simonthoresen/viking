#include "/d/Empire/islands/altdorf.h"

inherit EMP_I_ROOM;

void create() {
    ::create();
    set_short("The Imperial Postal Service");
    set_long("You are in the offices of the Imperial Postal Service. You may " +
             "send or receive mails here. There is a sign on the wall.");
    add_item(({ "sign" }), 
             "While here, you may:\n\n" +
             "  - %^BOLD%^mail <name>%^END%^, send a mail to someone\n" +
             "  - %^BOLD%^mail%^END%^, to read your unread mail\n"+
             "  - %^BOLD%^mail -f%^END%^, to read your old mailbox\n\n");
    add_property(({ "indoors", "post_office" }));
}
