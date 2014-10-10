#include "/d/Empire/islands/arena.h"

inherit EMP_I_ROOM;

void create() {
    ::create();
    add_property(({ "indoors", "underground", "no_teleport" }));
    new(ARN_C_SNOOP)->move(this_object());
}

int is_arena() {
    return 1;
}
