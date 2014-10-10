#include "/d/Artifact/artifact.h"

private string   _header;
private string   _file;
private string   _parent;
private int      _num_ranks;
private mapping *_code_stack;
private mapping  _code;

public void
new_sliver()
{
    _header     = 0;
    _file       = 0;
    _parent     = 0; 
    _num_ranks  = 1;
    _code_stack = ({ });
    _code       = ([ ]);
}

static void
create() 
{
    new_sliver();
}

private void
write_sliver(string file, string *code) 
{
    string str;
    if (file_size(file = file + ".c") > 0) {
        rm(file);
    }
    str = _header + "\n" +
          "inherit \"" + _parent + "\";\n" +
          "static void create() {\n" +
          "    ::create();\n" +
          "    " + implode(code, ";\n    ") + ";\n" +
          "}\n";
    if (!write_file(file, str)) {
        error("Could not write file '" + file + "'.");
    }
    file[0..strlen(file) - 3]->__bootstrap();
}

private string *
build_code(int rank)
{
    int i, len;
    string *arr, *ret;
    arr = keys(_code);
    len = sizeof(arr);
    ret = allocate(len + 1);
    for (i = 0; i < len; ++i) {
        int min, max, val;
        min = _code[arr[i]][0];
        max = _code[arr[i]][1];
        if (_num_ranks > 1) {
            val = min + ((max - min) * (rank - 1)) / (_num_ranks - 1);
        } else {
            val = max;
        }
        ret[i] = sprintf(arr[i], val);
    }
    ret[i] = "set_max_rank(" + _num_ranks + ")";
    return ret;
}

public nomask void
build_slivers()
{
    int rank;
    _header = "/* generated by " + source_file_name() + " */\n" +
              "/*           on " + ctime(time()) + "  */";
    for (rank = 1; rank <= _num_ranks; ++rank) {
        write_sliver(_file + (_num_ranks > 1 ? "_" + rank : ""), 
                     build_code(rank));
    }
}

public nomask void
push_code()
{
    _code_stack += ({ _code + ([ ]) /* force copy  */ }); 
}

public nomask void
pop_code()
{
    int len;
    len = sizeof(_code_stack);
    _code = _code_stack[len - 1];
    _code_stack = len > 1 ? _code_stack[0..len - 2] : ({ });
}

public nomask string
query_file() 
{
    return _file;
}

public nomask void
set_file(string val)
{
    _file = val;
}

public nomask string
query_parent()
{
    return _parent;
}

public nomask void
set_parent(string val)
{
    _parent = val;
}

public nomask int
query_num_ranks() 
{
    return _num_ranks;
}

public nomask void
set_num_ranks(int val)
{
    _num_ranks = val;
}

public nomask mapping
query_code()
{
    return _code;
}

public nomask void
set_code(mapping val) 
{
    _code = val;
}

public nomask varargs void
add_code(string key, int min, int max)
{
    _code[key] = ({ min, max });
}