#include "/d/Empire/islands/fort.h"

inherit I_KEY;

public void
set_wing(string val)
{
    set_type(val);
    set_keycode(source_file_name() + "_" + val);
}
