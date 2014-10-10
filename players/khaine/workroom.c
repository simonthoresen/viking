#include <mudlib.h>

inherit I_ROOM;

static void
create()
{
    ::create();
    set_light(1);
    set_short("The workroom");
    set_long("A room in a house set aside for a hobby, such as sewing.");
    add_exit("/d/Artifact/master", "artifact");
    add_exit("/d/Runewaker/master", "runewaker");
    add_exit("/d/Empire/var/islands/altdorf/27/25", "altdorf");
    add_exit("/d/Empire/islands/arena/rooms/arena", "arena");
    add_exit("/d/Empire/islands/blackrock/rooms/entry", "blackrock");
    add_exit("/d/Empire/var/islands/chaos/11/23", "chaos");
    add_exit("/d/Empire/var/islands/dragon/18/53", "dragon");
    add_exit("/d/Empire/var/islands/fort/0/22", "fort");
    add_exit("/d/Empire/var/islands/matouci/13/24", "matouci");
    add_exit("/d/Empire/var/islands/prison/1/1", "prison");
    add_exit("/d/Empire/var/islands/reikland/39/36", "reikland");
    add_exit("/d/Empire/var/islands/ruins/28/39", "ruins");
    add_exit("/room/shop", "shop");
}
