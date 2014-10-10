#include <std.h>
#include "/d/Empire/islands/arena.h"

inherit I_ITEM;

void create() {
    ::create();
    set_name(source_file_name());
    set_short(0);
    add_hook("__destroy", store_fp("on_destroy"));
    add_hook("__move", store_fp("on_move"));
}

int drop(int silent) {
    return NO_DROP;
}

void on_move(object from, object to) {
    if (objectp(from)) {
        from->remove_hook("__bdie");
        from->remove_hook("__die");
        from->remove_hook("__move");
    }
    if (objectp(to)) {
        if (interactive(to)) {
            to->add_hook("__die",  store_fp("register_player_death"));
        } else {
            to->add_hook("__bdie", store_fp("prevent_pet_death"));
        }
        to->add_hook("__move", store_fp("dest_outside_arena"));
    }
}

void on_destroy() {
    on_move(environment(), 0);
}

void dest_outside_arena(object from, object to) {
    if (!objectp(to)) {
        return; /* ignore for safety */
    }
    if (clonep(to)) {
        return; /* icedome, etc. */
    }
    if (to->is_arena()) {
        return; 
    }
    destroy();
}

int prevent_pet_death(object foe) {
    object ply;
    if (!objectp(ply = previous_object())) {
	return 0;
    }
    catch(ply->move_player("X", R_VOID));
    catch(ply->destroy()); /* simulate pet death */
    return 1;
}

void register_player_death(object corpse, object foe) {
    object ply;
    if (!objectp(ply = previous_object())) {
	return;
    }
    if (objectp(corpse)) {
	all_inventory(corpse)->move(ply);
    }
    if (objectp(foe)) {
        catch(ARN_D_SCORE->player_kill(foe, ply));
    }
}
