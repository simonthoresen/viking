#include "/d/Artifact/artifact.h"

inherit ART_I_WEAPON;

static void
create()
{
    ::create();
    if (clonep(this_object()) &&
        origin() != ORIGIN_LOCAL &&
        source_file_name(previous_object()) != source_file_name())
    {
        error("use new_instance() instead of clone_object()");
    }
}

public object
get_instance(object ply)
{
    object gem;
    if (!ART_MASTER->is_member(ply)) {
        return 0;
    }
    if (!objectp(gem = ART_C_SOULSTONE->get_instance(ply))) {
        error(sprintf("expected soulstone for %O, got 0", ply));
    }
    return gem->query_weapon();
}

public object
new_instance(object ply, object shape)
{
    object gem, wpn;
    if (!objectp(gem = ART_C_SOULSTONE->get_instance(ply))) {
        error(sprintf("expected soulstone for %O, got 0", ply));
    }
    if (objectp(wpn = gem->query_weapon())) {
        error(sprintf("did not expect existing instance, got %O", wpn));
    }
    if (!objectp(shape) || !shape<-ART_I_SHAPE) {
        error(sprintf("expected shape, got %O", shape));
    }
    wpn = clone_object(this_object());
    wpn->set_player(ply);
    wpn->add_sliver(shape);
    gem->set_weapon(wpn);
    return wpn;
}
