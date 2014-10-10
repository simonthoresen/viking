#include "/d/Artifact/artifact.h"

inherit ART_I_SKILL;

private string _dtype;

static void
create() 
{
    ::create();
    _dtype = 0;
    if (!sscanf(file_name(), ART_DIR_SLIVERS + "%s_aptitude", _dtype)) {
        return;
    }
    set_info(query_name() + " affects all spells that involve " + _dtype +
             " damage. As you train this skill, more and more powerful " +
             _dtype + " spells become available. The level of this skill " +
             "is also applied as a scaling-factor for the " + _dtype + " " + 
             "spells, meaning that even low-level " + _dtype + " spells " +
             "become useful in end-game situations once this skill is " +
             "high enough.");
    add_quest_req(_dtype + "_aptitude_0");
}

public nomask string
query_dtype()
{
    return _dtype;
}
