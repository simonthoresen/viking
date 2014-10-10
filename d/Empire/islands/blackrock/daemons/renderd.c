#include "/d/Empire/islands/blackrock.h"

#define BORDER_LINE  ("========================================" + \
                      "=======================================\n")

#define VIEW_EMPTY   (0)
#define VIEW_BITS    (6)
#define VIEW_FILE(x) (BRD_DIR_ETC + "view." + (x))

#define ITEM_MID(x)  (1 << ((x) + 0 * VIEW_BITS))
#define LIFE_MID(x)  (1 << ((x) + 1 * VIEW_BITS))
#define WALL_LHS(x)  (1 << ((x) + 2 * VIEW_BITS))
#define WALL_MID(x)  (1 << ((x) + 3 * VIEW_BITS))
#define WALL_RHS(x)  (1 << ((x) + 4 * VIEW_BITS))


inherit base I_DAEMON;
inherit util EMP_I_UTIL;

public  void read_views();
private void read_view(int view);

private mapping _views;
private mapping _cache;

static void create() {
    base::create(); 
    util::create();
    _views = 0;
    _cache = ([ ]);

    read_views();
}

public int find_depth(int view) {
    int i;
    for (i = 0; !(view & 1) && i < VIEW_BITS; view >> 1, ++i) {
        /* empty */
    }
    return i;
}

public string render_string(string prev, string next) {
    int i, len;
    if (!stringp(prev)) {
        return next;
    } 
    if (!stringp(next)) {
        return prev;
    }
    if ((len = strlen(prev)) != strlen(next)) {
        printf(prev);
        printf(next);
        error("Expected " + len + ", got " + strlen(next) + ".");
    }
    for (i = 0; i < len; ++i) {
        if (next[i] == 'X') {
            next[i] = prev[i];
        }
    }
    return next;
}

private int query_lhs(int pos, int dir) {
    switch (dir) {
    case 'n': return add_pos(pos, to_pos( 0, -1));
    case 's': return add_pos(pos, to_pos( 0,  1));
    case 'e': return add_pos(pos, to_pos(-1,  0));
    case 'w': return add_pos(pos, to_pos( 1,  0));
    default:  error("Illegal direction.");
    }
}

private int query_rhs(int pos, int dir) {
    switch (dir) {
    case 'n': return add_pos(pos, to_pos( 0,  1));
    case 's': return add_pos(pos, to_pos( 0, -1));
    case 'e': return add_pos(pos, to_pos( 1,  0));
    case 'w': return add_pos(pos, to_pos(-1,  0));
    default:  error("Illegal direction.");
    }
}

private int query_fwd(int pos, int dir) {
    switch (dir) {
    case 'n': return add_pos(pos, to_pos(-1,  0));
    case 's': return add_pos(pos, to_pos( 1,  0));
    case 'e': return add_pos(pos, to_pos( 0,  1));
    case 'w': return add_pos(pos, to_pos( 0, -1));
    default:  error("Illegal direction.");
    }
}

public int is_wall(int pos) {
    return BRD_ISLAND->query_map_type(to_row(pos), to_col(pos)) == BRD_MAP_WALL;
}

public object *find_inventory(int pos, object *exclude) {
    string str;
    object env, *arr;
    if (!stringp(str = BRD_ISLAND->query_room(to_row(pos), to_col(pos))) ||
        file_size(str + ".c") <= 0 ||
        !objectp(env = str->__bootstrap()) ||
        !arrayp(arr = all_inventory(env)) ||
        sizeof(arr -= exclude) <= 0)
    {
        return 0;
    }
    return arr;
}

public varargs int calc_view(int pos, int dir, mixed exclude) {
    int i, view;
    object *arr;
    if (!arrayp(exclude)) {
        exclude = ({ exclude });
    }
    view = 0;
    for (i = 0; i < VIEW_BITS; ++i) {
        if (is_wall(query_lhs(pos, dir))) {
            view |= WALL_LHS(i);
        }
        if (is_wall(pos)) {
            view |= WALL_MID(i);
        } else if (arrayp(arr = find_inventory(pos, exclude))) {
            if (sizeof(filter_array(arr, "isliving", D_FILTER)) > 0) {
                view |= LIFE_MID(i);
            } else {
                view |= ITEM_MID(i);
            }
        }
        if (is_wall(query_rhs(pos, dir))) {
            view |= WALL_RHS(i);
        }
        pos = query_fwd(pos, dir);
    }
    return view;
}

public string render_view(int view) {
    string str;
    int i;
    str = _views[VIEW_EMPTY];
    for (i = VIEW_BITS; --i >= 0; ) {
        if (view & WALL_LHS(i)) {
            str = render_string(str, _views[WALL_LHS(i)]);
        }
        if (view & WALL_RHS(i)) {
            str = render_string(str, _views[WALL_RHS(i)]);
        }
        if (view & LIFE_MID(i)) {
            str = render_string(str, _views[LIFE_MID(i)]);
        } else if (view & ITEM_MID(i)) {
            str = render_string(str, _views[ITEM_MID(i)]);
        } else if (view & WALL_MID(i)) {
            str = render_string(str, _views[WALL_MID(i)]);
        }
    }
    str = BORDER_LINE + str + BORDER_LINE;
    return str;
}

public varargs string render_view_at(int row, int col, int dir, mixed exclude) {
    return render_view(calc_view(to_pos(row, col), dir, exclude));
}

public void read_views() {
    mapping dat;
    int i, len;
    _views = ([ ]);
    _cache = ([ ]);
    read_view(VIEW_EMPTY);
    for (i = 0, len = VIEW_BITS; i < len; ++i) {
        read_view(ITEM_MID(i));
        read_view(LIFE_MID(i));
        read_view(WALL_MID(i));
        read_view(WALL_LHS(i));
        read_view(WALL_RHS(i));
    }
}

private void read_view(int view) {
    string file;
    if (file_size(file = VIEW_FILE(view)) < 0) {
        error("View file '" + file + "' missing.");
    }
    _views[view] = read_file(file);
}

public mapping query_views() {
    return _views;
}
