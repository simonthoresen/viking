#include "/d/Empire/empire.h"

static void create() {
    /* empty */
}

public int abs(int val) {
    return val < 0 ? -val : val;
}

public int min(int lhs, int rhs) {
    return lhs < rhs ? lhs : rhs;
}

public int max(int lhs, int rhs) {
    return lhs > rhs ? lhs : rhs;
}
