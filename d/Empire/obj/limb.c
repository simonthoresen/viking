#include "/d/Empire/empire.h"

inherit C_CORPSE;

public int
id(string str)
{
    return ::id(str) || sizeof(({ str }) & query_id_array());
}

private string *
create_id_array(string limb)
{
    int i, len;
    string *out;
    out = ({ "limb", limb });
    for (i = 0, len = strlen(limb); i < len - 1; ++i) {
        if (limb[i] == ' ') {
            out += ({ limb[i + 1..] });
        }
    }
    return out;
}

public varargs object
new_instance(object ply, string limb, object foe)
{
    int val;
    object obj;
    if (!objectp(ply) || !living(ply) || ply->query_no_corpse()) {
        return 0;
    }
    if (!stringp(limb)) {
        limb = "limb";
    }
    obj = clone_object(this_object());
    obj->set_name(I_GRAMMAR->genitive(ply->query_name()) + " " + limb);
    obj->set_long("");
    obj->add_id(create_id_array(limb));
    obj->set_level(ply->query_level());
    obj->set_npc(ply->query_npc());
    obj->set_race(ply->query_race());
    obj->set_old_ids(ply->query_id_array());
    obj->set_gender(ply->query_gender());
    obj->set_alignment(ply->query_alignment());
    obj->set_exp(0);
    if (objectp(foe) && living(foe)) {
        obj->set_killed_by(foe->query_real_name());
    } else {
        obj->set_killed_by("someone");
    }
    if (interactive(ply)) {
	obj->add_property("playercorpse");
    }
    if ((val = ply->query_intoxicated()) > 0) {
	obj->add_property("intoxicated", val);
    }
    return obj;
}
