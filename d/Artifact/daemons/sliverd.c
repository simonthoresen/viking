#include "/d/Artifact/artifact.h"

#define SLIVERS_PER_ITERATION   (100)
#define ITERATION_DELAY         (0.1)

inherit EMP_I_DAEMON;

private void     reload_slivers();

private object *_slivers;
private mapping _cache;
private int     _ready;

static void
create()
{
    ::create();
    reload_slivers();
}

private string *
get_sliver_files(string dir)
{
    string *arr, *out, file;
    int arr_idx, arr_len, file_len;
    arr = get_files_absolute(dir);
    out = ({ });
    for (arr_idx = 0, arr_len = sizeof(arr); arr_idx < arr_len; ++arr_idx) {
        file = arr[arr_idx];
        file_len = strlen(file);
        switch (file_size(file)) {
        case -2:
            out += get_sliver_files(file + "/");
            break;
        case -1:
            // ignore
            break;
        default:
            if (file_len > 2 && file[file_len - 2..] == ".c") {
                out += ({ file });
            }
            break;
        }
    }
    return out;
}

private void
reload_slivers()
{
    string *arr;
    while (remove_call_out("load_slivers") != -1) {
        // empty
    }
    _ready   = 0;
    _cache   = ([ ]);
    _slivers = ({ });

    arr = get_sliver_files(ART_DIR_SLIVERS);
    ART_MASTER->debug("Loading " + sizeof(arr) + " slivers.");
    call_out("load_slivers", 0, arr);
}

public void
load_slivers(string *arr, int arr_idx)
{
    object obj;
    string file;
    int arr_len, arr_cnt, file_len;
    arr_len = sizeof(arr);
    for (arr_cnt = 0, arr_len = sizeof(arr);
         arr_idx < arr_len && arr_cnt < SLIVERS_PER_ITERATION;
         ++arr_idx, ++arr_cnt)
    {
        file = arr[arr_idx];
        file_len = strlen(file);
        if (file_len < 3 ||
            file_size(file) <= 0 ||
            file[file_len - 2..] != ".c" ||
            stringp(catch(obj = file[0..file_len - 3]->__bootstrap())))
        {
            continue;
        }
        _slivers += ({ obj });
    }
    if (arr_idx < arr_len) {
        call_out("load_slivers", ITERATION_DELAY, arr, arr_idx);
    } else {
        ART_MASTER->debug("Loaded " + sizeof(_slivers) + " slivers.");
        _ready = 1;
    }
}

public varargs object *
query_slivers(string type)
{
    if (sizeof(_slivers & ({ 0 }))) {
        reload_slivers();
    }
    if (!stringp(type)) {
        return _slivers;
    }
    return filter_array(_slivers, "is_type", this_object(), type);
}

public varargs object *
filter_slivers(string fnc, mixed obj, mixed args)
{
    if (obj == 0) {
        obj = previous_object();
    }
    return filter_array(query_slivers(), fnc, obj, args);
}

public varargs mixed *
map_slivers(string fnc, mixed obj, mixed args)
{
    if (obj == 0) {
        obj = previous_object();
    }
    return map_array(query_slivers(), fnc, obj, args);
}

public varargs object
query_sliver(string type, string name)
{
    object obj, *arr;
    string key;
    int i, len;
    if (!stringp(name)) {
        name = type;
        type = 0;
    }
    if (stringp(type)) {
        type = lower_case(type);
    }
    name = lower_case(name);
    if (objectp(obj = _cache[key = type + "_" + name])) {
        return obj;
    }
    for (i = 0, len = sizeof(arr = query_slivers(type)); i < len; ++i) {
        obj = arr[i];
        if (obj->id(name)) {
            if (_ready) {
                _cache[key] = obj;
            }
            return obj;
        }
    }
    return 0;
}

public varargs object
make_sliver(string type, mixed name, mixed wpn)
{
    object obj;
    if (objectp(name)) {
        wpn = name;
        name = type;
        type = 0;
    }
    if (!objectp(obj = query_sliver(type, name))) {
        return 0;
    }
    obj = clone_object(obj);
    if (objectp(wpn)) {
        obj->move(wpn);
    }
    return obj;
}

public object *
query_extras()
{
    return query_slivers("extra");
}

public object
query_extra(string name)
{
    return query_sliver("extra", name);
}

public int
query_num_extra()
{
    return sizeof(query_extras());
}

public object *
query_glyphs()
{
    return query_slivers("glyph");
}

public object
query_glyph(string name)
{
    return query_sliver("glyph", name);
}

public int
query_num_glyphs()
{
    return sizeof(query_glyphs());
}

public object *
query_quirks()
{
    return query_slivers("quirk");
}

public object
query_quirk(string name)
{
    return query_sliver("quirk", name);
}

public int
query_num_quirks()
{
    return sizeof(query_quirks());
}

public object *
query_shapes()
{
    return query_slivers("shape");
}

public object
query_shape(string name)
{
    return query_sliver("shape", name);
}

public int
query_num_shapes()
{
    return sizeof(query_shapes());
}

public object *
query_skills()
{
    return query_slivers("skill");
}

public object
query_skill(string val)
{
    return query_sliver("skill", val);
}

public int
query_num_skills()
{
    return sizeof(query_skills());
}

public object *
query_spells()
{
    return query_slivers("spell");
}

public object
query_spell(string name)
{
    return query_sliver("spell", name);
}

public int
query_num_spells()
{
    return sizeof(query_spells());
}

static int
is_type(object obj, string type)
{
    return objectp(obj) && obj->query_type() == type;
}

public int
is_ready()
{
    return _ready;
}
