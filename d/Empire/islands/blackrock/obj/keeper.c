#include "/d/Empire/islands/blackrock.h"

inherit EMP_I_MONSTER;

static void
create() 
{
    ::create();
    set_male();
    set_name("Daedalus");
    set_short("the keeper of Blackrock");
    set_long("This thoughtful man has narrow eyes the color of an overcast " +
	     "sky. His fine, wavy, soot-black hair is worn in a style that " +
	     "reminds you of a dustball. He is very tall and has a broad-" +
	     "shouldered build. His skin is dark, and he has a high " +
	     "forehead. He is Daedalus, the keeper and craftsman of " +
	     "Blackrock mountain.");
    add_id(({ "keeper", "craftsman", "man" }));
    add_id(source_file_name());
    set_level(29);
    add_property("no_fight");
    add_hook("__heart_beat", store_fp("check_mazegen"));
}

public void
leave_area() 
{
    move_player("X", R_VOID);
    destroy();
}

private void
execute_task() 
{
    object obj;
    obj = make(BRD_C_MAZEGEN);
    obj->push_back(store_fp("leave_area"));
    obj->execute();
}

static void
check_mazegen() 
{
    object obj;
    string err;
    if (objectp(obj = present(BRD_C_MAZEGEN)) &&
        stringp(err = obj->query_error())) 
    {
        command("scratch");
        command("say " + err + "?");
        obj->destroy();
        execute_task();
    }
}

private void
notify(string str) 
{
    BRD_ISLAND->tell_island("\nThe keeper of Blackrock yells: " +
                            str + "\n");
    command("say " + str);
}

public void
count_down(int val) 
{
    if (find_call_out("count_down") >= 0) {
	return;
    }
    if (val <= 0) {
	notify("The labyrinth of Blackrock will now be demolished!");
        execute_task();
        return;
    }
    notify("The labyrinth of Blackrock will be demolished in " + 
	   format_time(val) + "!");
    call_out("count_down", val < 30 ? val : 30, val - 30);
}
