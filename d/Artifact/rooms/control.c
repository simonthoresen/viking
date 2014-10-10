#include "/d/Empire/islands/artifact.h"

inherit EMP_I_ROOM;

private int     _init_done;
private string *_cmds;

static void
create()
{
    ::create();
    _init_done = 0;
    _cmds =
        ART_D_COMMAND->query_actions(ART_DIR_COM_M) |
        ART_D_COMMAND->query_actions("/com/g/alias") |
        ART_D_COMMAND->query_actions("/com/g/asnoop") |
        ART_D_COMMAND->query_actions("/com/g/block") |
        ART_D_COMMAND->query_actions("/com/g/colour") |
        ART_D_COMMAND->query_actions("/com/g/converse") |
        ART_D_COMMAND->query_actions("/com/g/do") |
        ART_D_COMMAND->query_actions("/com/g/finger") |
        ART_D_COMMAND->query_actions("/com/g/history") |
        ART_D_COMMAND->query_actions("/com/g/last") |
        ART_D_COMMAND->query_actions("/com/g/password") |
        ART_D_COMMAND->query_actions("/com/g/plan") |
        ART_D_COMMAND->query_actions("/com/g/prompt") |
        ART_D_COMMAND->query_actions("/com/g/quit") |
        ART_D_COMMAND->query_actions("/com/g/save") |
        ART_D_COMMAND->query_actions("/com/g/screen") |
        ART_D_COMMAND->query_actions("/com/g/toggle") |
        ART_D_COMMAND->query_actions("/com/g/which") |
        ART_D_COMMAND->query_actions("/com/g/unalias") |
        ART_D_COMMAND->query_actions("/com/m/chat") |
        ART_D_COMMAND->query_actions("/com/m/party");

    set_light(1);
    set_short("A dark place.");
    set_long("It is too dark.");
    add_hook("__destroy", store_fp("on_destroy"));
    add_hook("__enter_inv", store_fp("on_enter_inv"));
    add_hook("__leave_inv", store_fp("on_leave_inv"));
    add_reset_object("echo", ART_C_ECHO_PLAYER);
}

public void
reset(int flag)
{
    ::reset(flag);
    _init_done = 1;
}

public object *
query_members()
{
    return filter_array(all_inventory(), "is_member", ART_MASTER);
}

public object
query_member()
{
    object *arr;
    return sizeof(arr = query_members()) ? arr[0] : 0;
}

public object
query_weapon()
{
    object ply;
    return objectp(ply = query_member()) ? ART_C_WEAPON->get_instance(ply) : 0;
}

public object
query_room()
{
    object wpn;
    return objectp(wpn = query_weapon()) ? wpn->query_room() : 0;
}

public string
short()
{
    object env;
    if (!objectp(env = query_room())) {
        return ::short();
    }
    return env->short();
}

public varargs mixed
long(string str)
{
    object env;
    if (!objectp(env = query_room())) {
        return ::long(str);
    }
    return env->long(str);
}

public void
init()
{
    ::init();
    add_action("do_command", "", 1);
}

public int
do_command(string arg)
{
    object wpn;
    string cmd;
    if (!objectp(wpn = ART_C_WEAPON->get_instance(this_player()))) {
        destroy_later();
        return 1; /* _P_A_R_A_N_O_I_A_ */
    }
    if (strlen(cmd = query_verb()) == 0 ||
        sizeof(({ cmd }) & _cmds))
    {
        return 0; /* fall through to player command */
    }
    return wpn->command(cmd + (stringp(arg) ? " " + arg : ""));
}

static void
on_destroy()
{
    object *arr;
    arr = filter_array(all_inventory(), "isplayer", FILTER_OB);
    message("", bold("\nTHE WORLD AROUND YOU FALLS APART!\n\n"), arr);
    arr->move_player("X", ATI_ISLAND->find_map_type(ATI_MAP_SMITHY));
}

static void
on_enter_inv(object obj, object from)
{
    object env;
    if (!_init_done) {
        return; /* reset objects are getting added */
    }
    if (ART_MASTER->is_member(obj) && sizeof(query_members()) == 1) {
        return; /* no other guild member present */
    }
    if (!objectp(env = query_room())) {
        env = R_VOID->__bootstrap();
    }
    if (living(obj)) {
        obj->move_player("Z", env);
    } else {
        obj->move(env);
    }
}

static void
on_leave_inv(object obj, object to)
{
    if (!objectp(query_member())) {
        destroy_later();
    }
}
