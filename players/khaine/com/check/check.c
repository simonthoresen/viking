/*
 * check.c
 *
 * This is an incredibly usefull command, which has been updated and rewritten several
 * times. It goes through a room and finds all the missing add_items() in it,
 * or at least it tries. It has a 'dictionary' in a daemon which helps sort out various
 * words and separators. The dictionary may be queried, set or adjusted by anyone.
 *
 */
#include "/players/khaine/com/check.h"
inherit CMD_MODULE;

#define PROCESSER "/players/shauni/daemons/processer"

#define CLI(x)  "%^BOLD%^"+x+"%^END%^"
#define FILE(x) "%^CYAN%^"+x+"%^END%^"

string *query_action()
{
  return ({"check","checkd","look","l"});
}

void    check_room(int pid, object p, string cfile, string *ofile, string *na, string *nu, int index);

int     action_check(string file);
int     action_checkd(string arg);

string *add_path(string p, string *f);
int     is_room(string f);

string  short_help();
string  help();


int main(string arg)
{
  /* Override look to print progress from PROCESSER. */
  if(member_array(query_verb(),({"look","l"})) > -1)
    {
      call_other(PROCESSER,"print_status");
      return 0;
    }

  /* Control command issued. */
  write(HEADER+"\n");
  if(!arg) return notify_fail(capitalize(query_verb())+" what?");

  arg = lower_case(arg);

  if(member_array(arg,({"?","help"})) > -1)
    {
      write(help());
      return 1;
    }

  switch(query_verb())
    {
    case "checkd":
      return action_checkd(arg);

    case "check":
      return action_check(arg);
    }

  return notify_fail("Uh oh..");
}

int action_checkd(string arg)
{
  int sa;
  string *args;

  args = explode(arg," ");
  sa   = sizeof(args);
  if((member_array(args[0][0..0],({"?","help"})) > -1) ||
     (args[0][0..0] == "a" && sa > 2) || 
     (args[0][0..0] == "r" && sa > 1) || 
     (args[0][0..0] == "q" && sa == 2)) 
    {
      switch(args[0][0..0]) 
	{
	case "a":
	  call_other(D_CHECK,"adds",args[1][0..0],args[2..sa]);
	  break;
	case "r":
	  call_other(D_CHECK,"removes",args[1..sa]);
	  break;
	case "q":
	  args = call_other(D_CHECK,"query",args[1][0..0]);
	  if(sa = sizeof(args))
	    {
	      write(capitalize(convert_number(sa))+" words:\n"+
		    make_list(args)+".\n");
	    }
	  else
	    {
	      write("No such group.\n");
	    }
	  break;
	default:
	  return notify_fail("Illegal option!");
	}
    }
  else
    {
      return notify_fail("SYNTAX: checkd <add|query|remove> [<group>] [<word(s)>]");
    }
  return 1;
}

int action_check(string file)
{
  object p;
  int sw,pid;
  string *w,*ofile,cfile,path, /* File information. */
         *na,*nu;              /* Words detected. */

  file = getopts("s",file);

  /* Test through argument. */
  p = this_player();
  path = p->query_path();
  if(member_array(file, ({".","env","environment"})) > -1) {
    if(!sizeof(ofile = filter_array(({ source_file_name(environment(p))+".c" }),"is_room",this_object())))
      return notify_fail("No access to environment's path, or environment not a loaded room.");

    sw = sizeof(w = explode(ofile[0],"/"));
    cfile = "/"+implode(w[0..sw - 2],"/") + "/CHECK_" + w[sw - 1];
  }
  else if(member_array(file, ({"*","all","everything"})) > -1) {
    if(!sizeof(ofile = filter_array(add_path(path,get_dir(path+"/")),"is_room",this_object())))
      return notify_fail("No access to, or no loaded room-files in your current path.");

    cfile = path + "/CHECK_REPORT";
  }
  else {
    if((file[0..0] == "/" && !ofile = filter_array(({ file }),"is_room",this_object())) ||
       !sizeof(ofile = filter_array(({ path + "/" + file }),"is_room",this_object())))
      return notify_fail("No access to, or not a loaded room file.");

    sw = sizeof(w = explode(ofile[0],"/"));
    cfile = "/"+implode(w[0..sw - 2],"/") + "/CHECK_" + w[sw - 1];
  }

  /* Write file-header. */
  rm(cfile);
  write_file(cfile,HEADER+"\n"+FILE("Date: "+ctime(time())+"\n"+
				    "Checker: "+capitalize(p->query_real_name())+", level "+p->query_level()+"\n\n"));

  /* Use Shauni's PROCESSER-daemon to prompt progress. */
  pid = call_other(PROCESSER,"add_task","CHECK ("+convert_number(sw = sizeof(ofile))+" room"+
		   (sw == 1 ? "" : "s") + ")",p->query_real_name(),0,sw);

  /* Use call_outs to lower eval cost. */
  na = nu = ({ });
  call_out("check_room",5,pid,p,cfile,ofile,na,nu,0);
  
  return 1;
}

void check_room(int pid, object p, string cfile, string *ofile, string *na, string *nu, int index)
{
  object r; 
  mapping m;
  int i,j,k,l,           /* Integers for loops. */
      ss,sw,sk,skm,sc,   /* SizeOf variables. */
      a,cc;              /* Counter of All items and characters. */
  string *unwanted,      /* Words to remove. */
         *adj,           /* adjectives */
         *w,*c,*s,*ns,   /* words, combinations, strings. */
         *km,lc,nc,      /* key_mapping, last_char, new_char. */
         *ac;            /* All combinations. */

  /* Loop through all rooms. */
  if(clonep(p) && !opts['s'])
    {
      message("info","Popped '"+ofile[index]+"' and starting check.\n",p);
    }	
  
  /* Make a string array *s contain long + all query_items. */
  r = find_object(ofile[index]);
  s = ({ lower_case(r->query_long()) });
  
  if(m = r->query_item()) 
    {
      km = keys(m);
      skm = sizeof(km);
      for(i = 0; i < skm; i++) 
	{
	  if(stringp(m[km[i]]))
	    {
	      m[km[i]] = lower_case(m[km[i]]);
	      if(member_array(m[km[i]],s) == -1) 
		{
		  s += ({ m[km[i]] });
		}
	    }
	}
    }
  
  /* Remove all unwanted characters. */
  w  = call_other(D_CHECK,"query",CHARACTERS);
  w += ({ "\t", "\n" });
  sw = sizeof(w);
  for(i = 0; i < sw; i++) {
    ss = sizeof(s);
    for(j = 0; j < ss; j++) {
      s[j] = replace_string(s[j],w[i]," ");
      s[j] = implode(explode(s[j]," ") - ({ " ","" })," ");
    }
  }
  
  /* Separate all sentences into individual strings. */
  w  = call_other(D_CHECK,"query",SEPARATORS);
  sw = sizeof(w);
  for(i = 0; i < sw; i++) {
    s = explode(implode(s,w[i]),w[i]);
  }
  
  /* Import the 'dictionary'. */
  unwanted = call_other(D_CHECK,"query",UNWANTED);
  adj      = call_other(D_CHECK,"query",ADJECTIVES);
  
  /* File-heading for room. */
  write_file(cfile,FILE("Room: "+ofile[index]+"\n"));
  
  /* Go through all the sentences. */
  a  = 0;
  ss = sizeof(s);
  ac = ({ "" });
  for(j = 0; j < ss; j++) {
    w = explode(s[j]," ") - unwanted - ({ "" });
    
    /* Remove numbers. */
    for(i = 0; i <= 100; i++) {
      w -= ({ convert_number(i) });
    }
    
    /* Check each word. */
    sw = sizeof(w);
    for(i = 0; i < sw; i++) {
      /* Detect new unwanted words. */
      if((sizeof(w[i]) < 3 || w[i][sizeof(w[i])-2..sizeof(w[i])-1] == "ly") &&
	 !call_other(D_CHECK,"is_defined",w[i]) && member_array(w[i],nu) == -1)
	{
	  nu = nu + ({ w[i] });
	}
      /* Detect and update adjectives. */ 
      else if(sizeof(w[i]) > 2 && w[i][sizeof(w[i])-3..sizeof(w[i])-1] == "ing" &&
	      !call_other(D_CHECK,"is_defined",w[i]) && member_array(w[i],na) == -1) 
	{
	  na = na + ({ w[i] });
	}
      /* Remove words containing three equal chars next to each other. */
      sk = sizeof(w[i]);
      cc = 0;
      for(k = 0; k < sk; k++) {
	nc = w[i][k..k];
	if(nc == lc) cc++;
	else         cc = 0;
	if(cc == 2) {
	  w -= ({ w[i] });
	  break;
	}
	lc = nc;
      }
      
      sw = sizeof(w);
    }
    
    /* Make combinations. */
    c = ({ });
    for(i = 0; i < sw; i++) {
      /* w[i] must be a noun. */
      if(member_array(w[i],adj) == -1) {
	c += ({ w[i] });
	/* w[i-1] must be an adjective. */
	if(i > 0 && w[i-1] && w[i-1] != w[i] && member_array(w[i-1],adj) > -1) { 
	  c += ({ w[i-1] + " " + w[i] });
	}
	if(i > 1 && w[i-2]) {
	  /* w[i-2] must be an adjective. */
	  if(w[i-2] != w[i] && member_array(w[i-2],adj) > -1) {
	    c += ({ w[i-2] + " " + w[i] });
	  }
	  /* Both w[i-1] and w[i-2] must be an adjective. */
	  if(w[i-2] != w[i-1] && w[i-2] != w[i] && w[i-1] != w[i] &&
	     member_array(w[i-1],adj) > -1 && member_array(w[i-2],adj) > -1) {
	    c += ({ w[i-2] + " " + w[i-1] + " " + w[i] });
	    c += ({ w[i-1] + " " + w[i-2] + " " + w[i] });
	  }
	}
      }
    }
    
    /* Remove combinations that exists. */
    if(km) c = c - km - ({ "" });
    
    /* Keep only one of each combination. */
    sc = sizeof(c);
    for(i = 0; i < sc; i++) {
      c = c - ({ c[i] }) + ({ c[i] });
      sc = sizeof(c);
    }
    
    /* Write lacking combinations to file. */
    c  -= ac;
    ac += c;
    sc  = sizeof(c);
    for(i = 0; i < sc; i++) {
      a++;
      if(clonep(p) && !opts['s'])
	{
	  write(a+" ");
	}
      write_file(cfile,"- "+c[i]+"\n");
    }
  }
  
  if(a) 
    {
      if(clonep(p) && !opts['s'])
	{
	  write("\nMissing "+a+" add_items().\n");
	}
      write_file(cfile,FILE("Missing "+convert_number(a)+" add_items().\n\n"));
    }
  else 
    {
      if(clonep(p) && !opts['s'])
	{
	  write("This room is in "+CLI("perfect")+" working order.\n");
	}
      write_file(cfile,"This room is in "+FILE("perfect")+" working order.\n\n");
    }
  

  if(++index < sizeof(ofile))
    {
      /* Make new call_out and update PROCESSER-daemon. */
      call_out("check_room",5,pid,p,cfile,ofile,na,nu,index);
      call_other(PROCESSER,"update_task",pid,index,sizeof(ofile));
    }
  else
    {
      if(clonep(p))
	{
	  message("info",CLI("\nResults in `"+cfile+"'.\n")+
		  (sizeof(na) ? ("Define if adjectives: "+make_list(na)+"\n") : "")+
		  (sizeof(nu) ? ("Define if unwanted: "+make_list(nu)+"\n") : ""),p);
	}
      call_other(PROCESSER,"remove_task",pid);
    }
}

/* kim gruszecki, 556 leonard NE, Grand Rapids, MICH , 49503 */
/* (616)459-4951 */

status is_room(string f)
{
  int i;
  object o;
  string *p;
  i = sizeof(p = explode(f,"."));

  /* File must end with .c */
  if(i < 2 || p[--i] != "c") return 0;

  /* File must be loadable */
  if(catch(call_other(f,"???")) ||
     !o = find_object(f)) return 0;

  /* File must be a room */
  if(!o->query_property("room")) return 0;

  /* A standard room at that */
  if(!stringp(o->query_long())) return 0;

  write("Pushed '"+f+"'.\n");

  /* Oh yeah! */
  return 1;
}

string *add_path(string p, string *f)
{
  int i;
  for(i = sizeof(f); --i >= 0; )
    {
      f[i] = p+"/"+f[i];
    }
  return f;
}

/* Show help on this command. */
string short_help()
{
  return "Check for missing add_items() in a room.\n";
}

string help()
{
  return ("COMMAND:             \n"+
	  "        check, checkd\n"+
	  "                     \n"+
	  "                     \n"+
	  "SYNTAX:                                  \n"+
	  "        check <room>                     \n"+
	  "        checkd <action> <group> <word(s)>\n"+
	  "                                         \n"+
	  "                                         \n"+
	  "DESCRIPTION:                             \n"+
	  "        This command will work through a collection of room-files, trying to\n"+
	  "        find missing add_items(). The results are stored in a file in the   \n"+
	  "        same directory as the room-file.                                    \n"+
	  "                                                                            \n"+
	  "        The command is based upon a dictionary that should be updated       \n"+ 
	  "        whenever anyone stumbles over a new word that it does not yet know. \n"+
	  "        The dictionary contains one list containing all unwanted words, and \n"+
	  "        one list of all known adjectives. The unwanted words are filtered   \n"+
	  "        from room-descriptions, while encountered adjectives are combined   \n"+
	  "        with the following noun, if any.                                    \n"+
	  "                                                                            \n"+
	  "        To check a room, use the command <check>.                           \n"+
	  "        To update the dictionary, use the command <checkd>.                 \n"+
	  "                                                                            \n"+
	  "        Valid groups are:                                                   \n"+
	  "           unwanted   - words removed from sentences  (most verbs)          \n"+
	  "           characters - words removed completely      (#, &, etc)           \n"+
	  "           separators - words that separate sentences (., :, etc)           \n"+
	  "           adjectives - words describing nouns        (adjectives)          \n"+
	  "                                                                            \n"+
	  "        The groups characters and separators are only available for updating\n"+
	  "        by special permit, since their effect seriously affects the outcome.\n"+
	  "                                                                            \n"+
	  "                                                                            \n"+
	  "ARGUMENTS:                                                                  \n"+
	  "        check <.|env|environment> - checks the user's current environment.  \n"+
	  "        check <*|all|everything>  - checks every loaded room-file in the    \n"+
	  "                                    user's current path.                    \n"+
	  "                                                                            \n"+
	  "        checkd add <group> <word(s)> - adds <word(s)> (separated with space)\n"+
	  "                                       to specified <group>.                \n"+
	  "        checkd query <group>         - list members of <group>.             \n"+
	  "        checkd remove <word(s)>      - remove <word(s)> from dictionary.    \n"+
	  "                                                                            \n"+
	  "                                                                            \n"+
	  "NOTE:                                                                       \n"+
	  "        All arguments, except words, are identified by their first letter   \n"+
	  "        only.                                                               \n");
}

