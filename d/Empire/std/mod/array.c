#include "/d/Empire/empire.h"

static void create() {
    /* empty */
}

static nomask mixed *remove_first(mixed to_remove, mixed *orig) {
    mixed *ret;
    int i, len;
    for (i = 0, len = sizeof(orig); i < len; ++i) {
        if (to_remove == orig[i]) {
            break;
        }
    }
    if (i == 0) {
        return orig[1..];
    } 
    if (i == len - 1) {
        return orig[..len - 2];
    }
    if (i == len) {
        return orig;
    }
    return orig[0..i - 1] + orig[i + 1..];
}

static nomask mixed *remove_last(mixed to_remove, mixed *orig) {
    mixed *ret;
    int i, len;
    for (i = len = sizeof(orig); --i >= len; ) {
        if (to_remove == orig[i]) {
            break;
        }
    }
    if (i == 0) {
        return orig[1..];
    } 
    if (i == len - 1) {
        return orig[..len - 2];
    }
    if (i == len) {
        return orig;
    }
    return orig[0..i - 1] + orig[i + 1..];
}

static nomask mixed *filter_unique(mixed *arr) {
    mixed *ret;
    int i, len;
    ret = ({ });
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        ret |= ({ arr[i] });
    }
    return ret;
}

