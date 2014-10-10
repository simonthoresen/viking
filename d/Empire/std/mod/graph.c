#include "/d/Empire/empire.h"

static void
create() 
{
    // empty
}

private void
assert_acyclic_impl(string item, mapping deps, string *path)
{
    int i, len;
    string *arr, str;
    if (!arrayp(arr = deps[item])) {
        return;
    }
    for (i = 0, len = sizeof(arr = deps[item]); i < len; ++i) {
        if (sizeof(({ str = arr[i] }) & path) > 0) {
            error("unexpected cycle; " + implode(arr, " -> ") + " -> " + str);
        }
        assert_acyclic_impl(str, deps, path + ({ str }));
    }
}

static void
assert_acyclic(mapping dat)
{
    int i, len;
    string *arr;
    for (i = 0, len = sizeof(arr = keys(dat)); i < len; ++i) {
        assert_acyclic_impl(arr[i], dat, ({ }));
    }
}

private string
render_tree(mixed graph, string pre)
{
    int i, len;
    mapping dat;
    string *arr, out;
    if (arrayp(graph)) {
        arr = graph;
        dat = ([ ]);
    } else if (mapp(graph)) {
        arr = keys(graph);
        dat = graph;
    } else {
        arr = ({ });
        dat = ([ ]);
    }
    arr = sort_array(arr, "sort_alpha_asc", D_FILTER);
    out = "";
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        out += pre + " `- " + arr[i] + "\n";
        out += render_tree(dat[arr[i]], pre + (i < len - 1 ? " |  " : "    "));
    }
    return out;
}

static string
render_forest(mapping dat)
{
    int i, len;
    string *arr, out;
    out = "\n";
    for (i = 0, len = sizeof(arr = keys(dat)); i < len; ++i) {
        out += arr[i] + "\n" + render_tree(dat[arr[i]], "");
    }
    return out;
}

private mapping
count_deps(mapping in)
{
    int items_idx, items_len;
    mapping out;
    string *items;
    out = ([ ]);
    for (items_idx = 0, items_len = sizeof(items = keys(in));
         items_idx < items_len; ++items_idx)
    {
        int deps_idx, deps_len;
        string *deps;
        for (deps_idx, deps_len = sizeof(deps = in[items[items_idx]]);
             deps_idx < deps_len; ++deps_idx)
        {
            out[deps[deps_idx]] = out[deps[deps_idx]] + 1;
        }
    }
    return out;
}

private mapping
create_tree(string item, mapping all_deps, mapping all_cnts)
{
    int i, len;
    mapping out;
    string *deps, label;
    if (!arrayp(deps = all_deps[item])) {
        return ([ ]);
    }
    out = ([ ]);
    for (i = 0, len = sizeof(deps); i < len; ++i) {
        label = deps[i];
        if (all_deps[label] == 0) {
            out[label] = 1;
        } else if (all_cnts[label] > 1) {
            out[label + "*"] = 1;
        } else {
            out[label] = create_tree(label, all_deps, all_cnts);
        }
    }
    return out;
}

static mapping
create_forest(string *items, mapping deps) 
{
    int i, len;
    mapping cnt, out;
    string item;
    cnt = count_deps(deps);
    out = ([ ]);
    for (i = 0, len = sizeof(items); i < len; ++i) {
        item = items[i];
        if (cnt[item] != 1) {
            out[items[i]] = create_tree(items[i], deps, cnt);
        }
    }
    return out;
}
