#include "/d/Empire/empire.h"

inherit base I_DAEMON;
inherit math EMP_I_MATH;

static void create() {
    base::create();
    math::create();
}

public int find_max(int *arr) {
    int i, len, max;
    max = 0;
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        max = max > arr[i] ? max : arr[i];
    }
    return max;
}

public int *create_line(int bins_len, int *data_arr) {
    int bins_idx, *bins_arr;
    int data_idx, data_len, data_val;
    data_len = sizeof(data_arr);
    bins_arr = allocate(bins_len, 0);
    for (data_idx = 0; data_idx < data_len; ++data_idx) {
        data_val = data_arr[data_idx];
        for (bins_idx = (data_idx * bins_len) / data_len; 
             bins_idx < bins_len; ++bins_idx) 
        {
            if ((bins_idx * data_len) / bins_len > data_idx) {
                break;
            }
            bins_arr[bins_idx] = max(bins_arr[bins_idx], data_val);
        }
    }
    return bins_arr;
}

public int *create_bins(int bins_len, int *data_arr) {
    int bins_idx, bins_hig, bins_low, *bins_min, *bins_max, *bins_arr;
    int data_idx, data_len, data_max;
    data_max = find_max(data_arr);  
    bins_min = allocate(bins_len, 0);
    for (bins_idx = 0; bins_idx < bins_len; ++bins_idx) {
        bins_min[bins_idx] = (bins_idx * (data_max + 1)) / bins_len;
    }
    bins_max = allocate(bins_len, 0);
    bins_hig = data_max + 1;
    bins_low = bins_min[bins_len - 1];
    for (bins_idx = bins_len; --bins_idx >= 0; ) {
        if (bins_min[bins_idx] != bins_low) {
            bins_hig = bins_low;
            bins_low = bins_min[bins_idx];
        }
        bins_max[bins_idx] = bins_hig;
    }    
    data_len = sizeof(data_arr);
    bins_arr = allocate(bins_len, 0);
    for (bins_idx = 0; bins_idx < bins_len; ++bins_idx) {
        bins_hig = bins_max[bins_idx];
        bins_low = bins_min[bins_idx];
        for (data_idx = 0; data_idx < data_len; ++data_idx) {
            if (data_arr[data_idx] < bins_low ||
                data_arr[data_idx] >= bins_hig)
            {
                continue;
            }
            ++bins_arr[bins_idx];
        }
    }
    return bins_arr;
}

public int *normalize_values(int next_max, int *prev_arr) {
    int i, len, prev_max, *next_arr;
    prev_max = find_max(prev_arr);
    if (prev_max == 0) {
        prev_max = 1;
    }
    next_arr = allocate(len = sizeof(prev_arr), 0);
    for (i = 0; i < len; ++i) {
        next_arr[i] = to_int(ceil(to_float(prev_arr[i] * next_max) / 
                                  to_float(prev_max)));
    }
    return next_arr;
}

public string render_array(int row_len, int row_max, 
			   int col_len, int col_max, int *arr) 
{
    int row, col;
    string str;
    str = "";
    for (row = 0; row < row_len; ++row) {
        if (row == 0) {
            str += sprintf("%4d |", row_max);
        } else {
            str += "     |";
        }
        for (col = 0; col < col_len; ++col) {
            str += arr[col] >= row_len - row ? "#" : " ";
        }
        str += "\n";
    }
    str += sprintf("   0 +%'-'*s>\n", col_len, ""); 
    str += sprintf("     0%*d\n", col_len, col_max); 
    return str;
}

public string render_line(int rows, int cols, int *arr) {
    int col_max, row_max;
    col_max = sizeof(arr);
    row_max = find_max(arr);
    arr = create_line(cols, arr);
    arr = normalize_values(rows, arr);
    return render_array(rows, row_max, cols, col_max, arr);
}

public string render_bins(int rows, int cols, int *arr) {
    int col_max, row_max;
    col_max = find_max(arr);
    arr = create_bins(cols, arr);
    row_max = find_max(arr);
    arr = normalize_values(rows, arr);
    return render_array(rows, row_max, cols, col_max, arr);
}
