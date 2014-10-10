#include "/d/Empire/islands/altdorf.h"

inherit I_DAEMON;

private string *_male_names;
private string *_female_names;
private string *_last_names;

static void create() {
    ::create();
    _male_names = ({ 
        "Allen", "Bob", "Carlton", "David", "Ernie", "Foster", "George", 
	"Howard", "Ian", "Jeffery", "Kenneth", "Lawrence", "Michael", "Nathen",
	"Orson", "Peter", "Quinten", "Reginald", "Stephen", "Thomas", "Morris",
	"Victor", "Walter", "Xavier", "Charles", "Anthony", "Gordon", "Percy",
	"Conrad", "Quincey", "Armand", "Jamal", "Andrew", "Matthew", "Mark",
	"Gerald" 
    });
    _female_names = ({ 
	"Alice", "Bonnie", "Cassie", "Donna", "Ethel", "Fannie", "Grace",
	"Heather", "Jan", "Katherine", "Julie", "Marcia", "Patricia", "Mabel",
	"Jennifer", "Dorthey", "Mary Ellen", "Jacki", "Jean", "Betty", "Diane",
	"Annette", "Dawn", "Jody", "Karen", "Mary Jane", "Shannon", 
	"Stephanie", "Kathleen", "Emily", "Tiffany", "Angela", "Christine", 
	"Debbie", "Karla", "Sandy", "Marilyn", "Brenda", "Hayley", "Linda" 
    });
    _last_names = ({ 
	"Adams", "Bowden", "Conway", "Darden", "Edwards", "Flynn", "Gilliam", 
	"Holiday", "Ingram", "Johnson", "Kraemer", "Hunter", "McDonald",
	"Nichols", "Pierce", "Sawyer", "Saunders", "Schmidt", "Schroeder",
	"Smith", "Douglas", "Ward", "Watson", "Williams", "Winters", "Yeager",
	"Ford", "Forman", "Dixon", "Clark", "Churchill", "Brown", "Blum",
	"Anderson", "Black", "Cavenaugh", "Hampton", "Jenkins", "Jefferies", 
	"Prichard" 
    });
}

public string query_male_name() {
    return _male_names[random(sizeof(_male_names))];
}

public string query_female_name() {
    return _female_names[random(sizeof(_female_names))];
}

public string query_last_name() {
    return _last_names[random(sizeof(_last_names))];
}
