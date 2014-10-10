#include "/d/Empire/islands/blackrock.h"
#define P_FORCE ("brd_force")

inherit BRD_I_ROOM_CRUMB;

static void create() {
    ::create();
    add_trigger("render", store_fp("do_render"));
    add_hook("__reset", store_fp("update_exits"));
}

private int resolve_heading(object ply) {
    int val;
    val = ply->query_tmp_prop(BRD_P_HEADING);
    if (val == 'n' || val == 'e' || val == 's' || val == 'w') {
        return val;
    }
    return 'n';
}

private string resolve_symbol(object ply) {
    switch (resolve_heading(ply)) {
    case 'n': return "A";
    case 's': return "V";
    case 'e': return ">";
    case 'w': return "<";
    }
}

private string *paint_view(string *view, int rows, int cols, string symbol) {
    string ply, *ret;
    int i;
    ply = sprintf("%c", EMP_MAP_PLAYER);
    ret = allocate(rows + 1);
    for (i = 0; i < rows; ++i) {
        ret[i] = "|" + replace_string(view[i], ply, symbol);
    }
    ret[rows] = sprintf("+%'='*s", cols, "");
    return ret;
}

public void on_long(string arg, int nonl) {
    object ply, env;
    string img, view, *vmap;
    int row, rows, cols;
    if (!objectp(ply = this_player()) ||
        !objectp(env = environment(ply)) ||
        !ply->query_property(BRD_P_RENDER) ||
        !stringp(view = BRD_D_RENDER->render_view_at(
                            query_map_row(), query_map_col(),
                            resolve_heading(ply), ply)))
    {
        ::on_long(arg, nonl);
        return;
    }
    rows = query_view_rows();
    cols = query_view_cols();
    vmap = paint_view(query_view(ply), rows, cols, resolve_symbol(ply));
    rows = rows + 1;
    cols = cols + 3;
    img  = view[..79];
    for (row = 0; row < rows; ++row) {
        img += view[(row + 1) * 80..(row + 2) * 80 - cols];
        img += vmap[row] + "\n";
    }
    img += view[(rows + 1) * 80..];
    tell_ansi(ply, img);
}

static int do_render(string arg) {
    if (arg == "on") {
        this_player()->add_property(BRD_P_RENDER);
        write("Auto-rendering enabled.\n");
    } else if (arg == "off") {
        this_player()->remove_property(BRD_P_RENDER);
        write("Auto-rendering disabled.\n");
    } else {
        return notify_fail("Usage: render [on | off]");
    }
    return 1;
}

private void update_exit(mapping dat, string dir) {
    if (arrayp(dat[dir])) {
        change_exit(dir, EX_FUNC, store_fp("on_exit"));
    } else {
        add_exit(source_file_name(), dir, store_fp("on_exit"), 0, 0, 1);
    }
}

static void update_exits(int flag) {
    mapping dat;
    if (flag || !mapp(dat = query_exit())) {
        return;
    }
    update_exit(dat, "north");
    update_exit(dat, "south");
    update_exit(dat, "east");
    update_exit(dat, "west");
    remove_exit("northeast");
    remove_exit("northwest");
    remove_exit("southeast");
    remove_exit("southwest");
}

private void move_forward(object ply) {
    string val;
    switch (ply->query_tmp_prop(BRD_P_HEADING)) {
    default:  val = "north"; break;
    case 's': val = "south"; break;
    case 'e': val = "east";  break;
    case 'w': val = "west";  break;
    }
    ply->set_tmp_prop(P_FORCE, 1);
    ply->command(val);
}

private void move_backward(object ply) {
    string val;
    switch (ply->query_tmp_prop(BRD_P_HEADING)) {
    default:  val = "south";  break;
    case 's': val = "north";  break;
    case 'e': val = "west"; break;
    case 'w': val = "east"; break;
    }
    ply->set_tmp_prop(P_FORCE, 1);
    ply->command(val);
}

private void turn_left(object ply) {
    int val;
    switch (ply->query_tmp_prop(BRD_P_HEADING)) {
    default:  val = 'w'; break;
    case 's': val = 'e'; break;
    case 'e': val = 'n'; break;
    case 'w': val = 's'; break;
    }
    ply->set_tmp_prop(BRD_P_HEADING, val);
    ply->do_glance();
}

private void turn_right(object ply) {
    int val;
    switch (ply->query_tmp_prop(BRD_P_HEADING)) {
    default:  val = 'e'; break;
    case 's': val = 'w'; break;
    case 'e': val = 's'; break;
    case 'w': val = 'n'; break;
    }
    ply->set_tmp_prop(BRD_P_HEADING, val);
    ply->do_glance();
}

static int on_exit(string dst) {
    object ply;
    string dir;
    if (!objectp(ply = this_player()) ||
        !stringp(dir = query_verb()))
    {
        return 0;
    }
    if (!ply->query_property(BRD_P_RENDER)) {
        if (query_exit()[dir][EX_FLAGS] & RF_HIDDEN) {
            write("You can not go that way.\n");
            return 1;
        } 
        return 0;
    }
    if (ply->query_tmp_prop(P_FORCE)) {
        ply->remove_tmp_prop(P_FORCE);
        return 0;
    }
    if (dir == "north") {
        move_forward(ply);
    } else if (dir == "south") {
        move_backward(ply);
    } else if (dir == "east") {
        turn_right(ply);
    } else if (dir == "west") {
        turn_left(ply);
    }
    return 1;
}
