#include "check.h"
inherit I_DAEMON;

#define FILE_SEPARATOR "#SEPARATOR-CHARACTERS-ADJECTIVES-UNWANTED#"
#define FILE_SAVE      WHERE+"check_save.txt"
#define FILE_OBJECT    WHERE+"check_save"
#define FILE_LOG       WHERE+"check.log"

string *adjectives,*unwanted,*separators,*characters;

status  make_file();
status  do_update(); 
status  is_defined(string arg);
status  is_not_defined(string arg);
string *query(string what); 
status  adds(string what, string *arg);
status  removes(string *arg);
status  verify(status silent);
void    do_log(string t);

/* Read the original files if there is nothing registered. */
void create()
{
  string *file;
  ::create();

  restore_object(FILE_OBJECT);
  
  if(!adjectives || !unwanted || !separators || !characters) 
    {
      file = explode(read_file(FILE_SAVE),FILE_SEPARATOR);
      if(!separators) 
	{
	  separators = explode(implode(explode(file[0],"\n")," ")," ") - ({ "" });
	}
      if(!characters) 
	{
	  characters = explode(implode(explode(file[1],"\n")," ")," ") - ({ "" });
	}
      if(!adjectives) 
	{
	  adjectives = explode(implode(explode(file[2],"\n")," ")," ") - ({ "" }); 
	}
      if(!unwanted) 
	{
	  unwanted   = explode(implode(explode(file[3],"\n")," ")," ") - ({ "" });
	}
  }  
}

status make_file()
{
  int i,sa;
  sa = sizeof(adjectives);
  rm(FILE_SAVE);
  if(!write_file(FILE_SAVE,implode(separators," ")) ||
     !write_file(FILE_SAVE,"\n\n"+FILE_SEPARATOR+"\n\n") ||
     !write_file(FILE_SAVE,implode(characters," ")) ||
     !write_file(FILE_SAVE,"\n\n"+FILE_SEPARATOR+"\n\n") ||
     !write_file(FILE_SAVE,implode(adjectives," ")) ||
     !write_file(FILE_SAVE,"\n\n"+FILE_SEPARATOR+"\n\n") ||
     !write_file(FILE_SAVE,implode(unwanted," "))) return 0;
  return 1;
}

status do_update() 
{ 
  if(!random(100)) make_file();
  if(save_object(FILE_OBJECT)) return 1;
  else return notify_fail("Unable to save object-file.");
}

on_destruct()
{
  do_update();
  ::on_destruct();
}
  
status is_defined(string arg)
{
  if(member_array(arg,adjectives) > -1 ||
     member_array(arg,unwanted)   > -1 ||
     member_array(arg,characters) > -1 ||
     member_array(arg,separators) > -1) return 1;
  else return 0;
}

status is_not_defined(string arg)
{
  if(member_array(arg,adjectives) > -1 ||
     member_array(arg,unwanted)   > -1 ||
     member_array(arg,characters) > -1 ||
     member_array(arg,separators) > -1) return 0;
  else return 1;
}

string *query(string what) 
{ 
  switch(lower_case(what[0..0])) 
    {
    case ADJECTIVES:
      return copy(adjectives); 
    case SEPARATORS:
      return copy(separators);
    case UNWANTED:
      return copy(unwanted);
    case CHARACTERS:
      return copy(characters);
      
    default:
      return ({ "" });
    }
}

status adds(string what, string *arg)
{
  string g;
  arg = filter_array(arg,"is_not_defined",this_object());

  if(!sizeof(arg))
    {
      write("All words already defined.\n");
      return 0;
    }

  switch(lower_case(what[0..0])) 
    {
    case ADJECTIVES:
      g = "adjectives";
      adjectives += arg; 
      break;
    case SEPARATORS:
      if(verify(0))
	{
	  g = "separators";
	  separators += arg;
	}
      break;
    case UNWANTED:
      g = "unwanted";
      unwanted   += arg;
      break;
    case CHARACTERS:
      if(verify(0))
	{
	  g = "characters";
	  characters += arg;
	}
      break;
    default:
      write("Illegal group.\n");
      return 0;
    }
  
  write("The following "+convert_number(sizeof(arg))+" words have been added to "+
	g+": "+make_list(arg)+".\n");
  do_log("added to "+g+": "+make_list(arg)+".");
  do_update();
  return 1;
}

status removes(string *arg)
{
  if(!sizeof(arg = filter_array(arg,"is_defined",this_object())))
    {
      write("None of the words are defined.\n");
      return 0;
    }

  adjectives -= arg; 
  unwanted   -= arg;
  if(verify(1))
    {
      characters -= arg;
      separators -= arg;
    } 
 
  write("The following "+convert_number(sizeof(arg))+" words have been removed: "+
	make_list(arg)+".\n");
  do_log("removed: "+make_list(arg)+".");
  do_update();
  return 1;
}

status verify(status silent)
{
  if((string)this_player()->query_real_name() == MAINTAINER)
    {
      return 1;
    }
  else 
    {
      if(!silent)
	{
	  write("You are not authorized to modify this group.\n");
	}
      return 0;
    }
}

void do_log(string t)
{
  log_file(FILE_LOG,capitalize(this_player()->query_name())+" "+t+"\n");
}
