#include <mudlib.h>

inherit I_ARMOUR;

void create() {
	::create();
	set_short("an apron splatterd in blood");
	set_long("A surgeon's apron splattered with bloods over years of medical threatments.");
	set_type("armour");
	set_ac(1);
	set_value(45);
}

/* Would have been super cool if this item could do something for the vampire guild ????? */