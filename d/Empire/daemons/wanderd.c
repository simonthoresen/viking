
#include "/d/Empire/empire.h"

inherit EMP_I_DAEMON;

private int    *_neighbours;
private int     _num_neighbours;
private mapping _directions;

static void
create()
{
    ::create();
    _neighbours = ({ to_pos(-1, -1), to_pos(-1, 0), to_pos(-1, 1),
                     to_pos( 0, -1),                to_pos( 0, 1),
                     to_pos( 1, -1), to_pos( 1, 0), to_pos( 1, 1) });
    _num_neighbours = sizeof(_neighbours);
    _directions = ([
        to_pos(-1, -1) : "northwest",
        to_pos(-1,  0) : "north",
        to_pos(-1,  1) : "northeast",
        to_pos( 0, -1) : "west",
        to_pos( 0,  1) : "east",
        to_pos( 1, -1) : "southwest",
        to_pos( 1,  0) : "south",
        to_pos( 1,  1) : "southeast",
    ]);
}

private int
next_pos(int *open_set, mapping f_score)
{
    int i, len, min, ret;
    ret = open_set[0];
    min = f_score[ret];
    for (i = 1, len = sizeof(open_set); i < len; ++i) {
        int pos, val;
        pos = open_set[i];
        val = f_score[pos];
        if (val < min) {
            ret = pos;
            min = val;
        }
    }
    return ret;
}

private int *
reconstruct_path(mapping came_from, int pos)
{
    int from;
    if ((from = came_from[pos]) != 0) {
        return reconstruct_path(came_from, from) + ({ pos });
    } else {
        return ({ pos });
    }
}

public int *
calc_path(int start, int goal, mapping roads)
{
    int num_open;
    mapping open_set, closed_set, came_from;
    mapping g_score, h_score, f_score;
    if (!roads[start] || !roads[goal] || start == goal) {
        return 0;
    }
    open_set   = ([ start : 1 ]);
    closed_set = ([ ]);
    came_from  = ([ ]);
    g_score    = ([ start : 0 ]);
    h_score    = ([ start : distance2(start, goal) ]);
    f_score    = ([ start : h_score[start] ]);
    while ((num_open = map_sizeof(open_set)) > 0) {
        int x, neighbour;
        x = next_pos(keys(open_set), f_score);
        if (x == goal) {
            return reconstruct_path(came_from, goal);
        }
        open_set[x] = 0;
        closed_set[x] = 1;
        for (neighbour = 0; neighbour < _num_neighbours; ++neighbour) {
            int y, g_val, g_use;
            y = add_pos(x, _neighbours[neighbour]);
            if (!roads[y] || closed_set[y]) {
                continue;
            }
            g_val = g_score[x] + distance2(x, y);
            if (!open_set[y]) {
                open_set[y] = 1;
                g_use = 1;
            } else if (g_val < g_score[y]) {
                g_use = 1;
            } else {
                g_use = 0;
            }
            if (g_use) {
                came_from[y] = x;
                g_score[y] = g_val;
                h_score[y] = distance2(y, goal);
                f_score[y] = g_score[y] + h_score[y];
            }
        }
    }
    EMP_LOG("wanderd", sprintf("No path found from (%d, %d) to (%d, %d) " +
                               "for %O (%O).",
			       to_row(start), to_col(start),
			       to_row(goal), to_col(goal),
                               previous_object(),
                               this_player()));
    return 0;
}

public string *
calc_route(int *path)
{
    string *ret;
    int i, len;
    if (!arrayp(path)) {
        return 0;
    }
    ret = allocate(len = sizeof(path) - 1);
    for (i = 0; i < len; ++i) {
        ret[i] = _directions[sub_pos(path[i + 1], path[i])];
    }
    return ret;
}
