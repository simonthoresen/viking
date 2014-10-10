#include "/d/Empire/empire.h"

inherit EMP_I_DAEMON;

public string *
query_actions(string cmd)
{
    int len;
    mapping dat;
    mixed val;
    if (!stringp(cmd) || (len = strlen(cmd)) == 0) {
        return ({ });
    }
    if (cmd[len - 1] == '/') {
        COM_D->assure_dir_loaded(cmd);
        dat = COM_D->dump_path(cmd);
        return mapp(dat) ? keys(dat) : ({ });
    }
    if (arrayp(val = cmd->query_action())) {
        return val;
    }
    if (stringp(val)) {
        return ({ val });
    }
    return ({ base_file_name(cmd) });
}
