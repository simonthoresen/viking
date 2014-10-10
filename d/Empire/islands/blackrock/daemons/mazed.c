#include "/d/Empire/islands/blackrock.h"

inherit base I_DAEMON;

public int *create_maze(int rows, int cols) {
    int row, row_len, col, col_len, idx, *lhs, *rhs, *arr;
    row_len = (rows - 1) / 2;
    col_len = (cols + 1) / 2;
    lhs = allocate(col_len);
    rhs = allocate(col_len);
    for (lhs[0] = 1, idx = col_len; --idx; lhs[idx] = rhs[idx] = idx) {
	/* get it? */
    }
    arr = allocate(rows * cols);
    for (row = 0; row < row_len; ++row) {
        for (col = col_len; --col; ) { 
            arr[(row * 2 + 2) * cols - col * 2] = 1;
            if ((col != (idx = lhs[col - 1])) &&
		(random(100) > 40 || (row == row_len - 1 && col == rhs[col])))
	    {
		lhs[rhs[idx] = rhs[col]] = idx;
		lhs[rhs[col] = col - 1 ] = col;
                arr[(row * 2 + 2) * cols + 1 - col * 2] = 1;
            }
            if ((col != (idx = lhs[col]) && random(100) > 40) || 
		(row == row_len - 1))
	    {
                lhs[rhs[idx] = rhs[col]] = idx;
                lhs[col]     = rhs[col]  = col; 
            } else {
                arr[(row * 2 + 3) * cols - col * 2] = 1;
            }
        }
    }
    return arr;
}

public string *create_map(int rows, int cols) {
    string *map;
    int i, len, *arr;
    arr = create_maze(rows, cols);
    map = allocate(rows, sprintf("%*s", cols, ""));
    for (i = 0, len = rows * cols; i < len; ++i) {
        map[i / cols][i % cols] = arr[i] ? EMP_MAP_ROAD : EMP_MAP_MOUNTAIN;
    }
    return map;
}

public void main() {
    string str;
    str = implode(create_map(41, 79), "\n");
    str = replace_string(str, sprintf("%c", EMP_MAP_MOUNTAIN), "#");
    str = replace_string(str, sprintf("%c", EMP_MAP_ROAD), " ");
    write("\n" + str + "\n");
}
