#include "/d/Empire/islands/reikland.h"

inherit I_DRINK;

static void
create() 
{
    string form, color, type;
    ::create();
    form  = ({ "small", "strange", "large", "malformed" })[random(4)];
    color = ({ "red", "orange", "yellow", "green", "blue",
               "indigo", "violet"})[random(7)];
    type  = ({ "potion", "flask", "bottle" })[random(3)];

    set_name("potion");
    set_short(add_article(form) + " " + color + " " + type);
    set_long(capitalize(add_article(form)) + " " + type + " filled with a " +
             color + " liquid.");
    add_id(({ type, form + " " + type, color + " " + type }));
    set_heal(200 + random(200));
    set_strength(random(25));
    set_soft_strength(random(25));
    set_value(1500 + random(500));
    set_empty_container("bottle");
    set_weight(1);
}
