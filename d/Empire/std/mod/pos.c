#include "/d/Empire/empire.h"

static void
create()
{
    /* empty */
}

public int
to_pos(int row, int col)
{
    return (row << 16) + (col & 0xffff);
}

public int
to_row(int pos)
{
    return pos >> 16;
}

public int
to_col(int pos)
{
    return pos & 0xffff;
}

public int
add_pos(int lhs, int rhs)
{
    return to_pos(to_row(lhs) + to_row(rhs),
		  to_col(lhs) + to_col(rhs));
}

public int
sub_pos(int lhs, int rhs)
{
    return to_pos(to_row(lhs) - to_row(rhs),
		  to_col(lhs) - to_col(rhs));
}

public int
distance2(int from_pos, int to_pos)
{
    int row, col;
    row = to_row(to_pos) - to_row(from_pos);
    col = to_col(to_pos) - to_col(from_pos);
    return row * row + col * col;
}

public float
distance(int from_pos, int to_pos)
{
    return sqrt(to_float(distance2(from_pos, to_pos)));
}
