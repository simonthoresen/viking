#include "/d/Artifact/artifact.h"

inherit CMD_MODULE;

public int
main(string arg)
{
    object obj;
    if (objectp(obj = find_object(ART_DIR_OBJ + "slivergen"))) {
        destruct(obj);
    }
    obj = make(ART_DIR_OBJ + "slivergen", this_player());
    obj->execute();
    write("Ok.\n");
    return 1;
}
