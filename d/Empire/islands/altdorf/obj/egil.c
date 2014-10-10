#include "/d/Empire/islands/altdorf.h"

inherit ALT_I_CITIZEN;

static void
create() 
{
    ::create();
    set_name("egil");
    set_short("Egil the storyteller");
    set_long("The old sage is sitting by the fire. He looks vaguely oriental " +
	     "so you guess he's a finn. His face is aged by many years of " +
             "frost and wind.");
    add_id(({ "man", "finn", "sage","storyteller" }));
    set_level(9);
    set_al(40);
    set_male();
    set_greeting(({ 
        "*cough",
        "*say I am Egil, the incredibly wise and seasoned.",
        "*emote looks around.",
        "*say I am widely known for my wast knowledge of everything. ",
        "*stretch",
        "*say You could for instance ask me about the " + bold("Empire") +
            " if you wanted me to enlighten you on that particular topic.",
	"*say (say What do you know about the Empire?)"
    }));
    add_response("empire", "The empire consists of " +
                 "the underground " + bold("Arena") + ", " +
                 "the " + bold("Matouci") + " forest, " +
                 "the island of " + bold("Reikland") + " and its " +
                 "capital city " + bold("Altdorf") + ", " + 
                 "the " + bold("lair") + " of Onyxia, " +
                 "the " + bold("Blackrock") + " depths, " + 
                 "and the realm of " + bold("Chaos") + ".");
    add_response("arena", "The underground Arena can be found in the caves " +
                 "underneath the Larstown shop.");
    add_response("matouci", "The forest Matouci lies close to Larstown, and " +
                 "is famous for its many dangerous denizens. These are " +
                 "the hound " + bold("Cerberus") + ", " +
                 "the " + bold("crusader") + " trial, " +
                 "the deathbringer " + bold("Saurfang") + ", " +
                 "the wolf " + bold("Fenrir") + ", " +
                 "the serpent " + bold("Jormungand") + ", " +
                 "the " + bold("jotunn") + " giant, " +
                 "the " + bold("rust") + " monster, " +
                 "and the slime " + bold("Viscidus") + ".");
    add_response("cerberus", "Cerberus is a three-headed hound that will " +
                 "tear through you unless you quickly dispose of a couple " +
                 "of its heads.");
    add_response("crusader", "The trial of the crusader consists of two " +
                 "phases. You must first defeat " + bold("Gormok") + ", then " +
                 "take on " + bold("Dreadscale") + " and " + bold("Acidmaw") +
                 "at once.");
    add_response("gormok", "Gormok is a dangerous ultralisk that is able to " +
                 "spawn smaller banelings. Those banelings must be killed as " +
                 "quickly as possible as they tend to explode and inflict " +
                 "alot of damage.");
    add_response("dreadscale", "The serpent Dreadscale spews liquid fire " +
                 "that will burn through your skin. Avoid staying with him " +
                 "for too long since too much fire is bad for your skin.");
    add_response("acidmaw", "The serpent Acidmaw spits paralyzing toxins, " +
                 "but his hits are quite weak.");
    add_response("saurfang", "The deathbringer Dranosh Saurfang carries the " +
                 "mighty blood weapons of the underworld. These are said to " +
                 "grow in power as they drink the blood of their enemies.");
    add_response("fenrir", "Fenrir is a deadly wolf whose claws and jaws can " +
                 "inflict horrible wounds. You should step away and let your " +
                 "wounds close before they kill you.");
    add_response("jormungand", "The serpent Jormungand " + bold("surfaces") +
                 " from time to time to wreck havok in the " + bold("Matouci") +
                 " forest. It is so long that it can actually circle the " +
                 "world and bite its own tail.");
    add_response("surfaces", "It can be actually be summoned out of its nest " +
                 "in the underworld if a sufficiently great " + 
                 bold("offering") + " is made.");
    add_response("offering", "The serpent will only be tempted by the smell " +
                 "of untouched, freshly spilt, christian blood of a virgin " +
                 "champion.");
    add_response("jotunn", "The jotunn is a giant humanoid that uses swords " +
                 "as toothpicks and wields trees as weapons. He is said to " +
                 "loves barbequing pigs for their tender bacon.");
    add_response("rust", "The rust monster is the most dreaded enemy for the " +
                 "knight in armour. Its acid and tentacles can eat through " +
                 "ANY metal, breaking whatever it touches beyond repair.");
    add_response("viscidus", "The giant gel-o Viscidus is a terrible " +
                 "opponent unless one can find a way to freeze it solid.");
    add_response("reikland", "The island of Reikland lies south of Larstown, " +
                 "reachable by boat from the Larstown jetty. Here you may " +
                 "encounter " + 
                 "the knight " + bold("Akol") + ", " +
                 "the wild barbarian, " +
                 "the fimir Dirach, " +
                 "the ancient " + bold("Ent") + ", " +
                 "the seductive Huldra, " +
                 "the demon captain " + bold("Imhotep") + ", " +
                 "the warrior " + bold("Kaleb") + ", " +
                 "the magician " + bold("Kalis") + ", " +
                 "the necromancer " + bold("Kashryn") + ", " +
                 "the doppelganger Krugan, " +
                 "the fimir Meargh, " +
                 "the unpredictive Lord Random, " +
                 "the savage wolf rider, and " +
                 "the ferocious werewolf.");
    add_response("ent", "The ent is an ancient living tree. The local " +
                 "lumberjacks tell stories of how it runs them off their site " +
                 "site in the forest north of here.");
    add_response("imhotep", "Several eons ago the parts of the known world " +
                 "was threatened by a powerful daemon captain and its horde " +
                 "of " + bold("servants") + ".");
    add_response("servants", "This army of darkness overthrew whatever it " +
                 "encountered, so humans swiftly gathered three legendary " +
                 bold("heroes") + " that could battle this evil.");
    add_response("heroes", "These were the monk magician " + bold("Kalis") + 
                 "Pathon, the knight and weapon master " + bold("Akol") +
                 ", and the holy warrior " + bold("Kaleb") + ".");
    add_response(({ "akol", "kaleb", "kalis" }), "He was one of the " + 
                 bold("heroes") + " that fought off the initial " + 
                 bold("attack") + ".");
    add_response("attack", "They withstood the intial attack, but even they " +
                 "could not ward the big hordes of evil that pressed on to " +
                 bold("destroy") + " the entire world. And so fell knight " +
                 "Akol and the warrior Kaleb victims of the dark forces.");
    add_response("destroy", "As a final resort, the magician Kalis Pathon " +
                 "sacrificed himself to entrap the demon captain Imhotep " +
                 "within a laen " + bold("orb") + ", thereby destroying the " +
                 "demon leader and making it possible for others to rid the " +
                 "world of them for good.");
    add_response("orb", "The laen orb lay buried along with the captain's " +
                 "evil artifacts in a secret " + bold("crypt") + ". The " +
                 "presence of the artifacts of three heros and the magic " +
                 "therein is what " + bold("contained") + " the demon.");
    add_response("crypt", "Noone was supposed to know where this crypt was, " +
                 "but it is said that it was recently " + bold("disturbed") +
                 ".");
    add_response("contained", "If set free, Imhotep may establish contact " +
                 "with the underworld, and once again summon forth a horde " +
                 "of evil followers to destroy the human kind.");
    add_response("disturbed", "For the sake of every living being this " +
                 "balance must never be threatened.");
    add_response("altdorf", "Altdorf is the capital city of Reikland.");
    add_response("blackrock", "The maze of Blackrock mountains can be found " +
                 "far north on the island of " + bold("Reikland") + ".");
    add_response("lair", "The lair of the dragon queen " + bold("Onyxia") + 
                 " is a " + bold("cave") + " that lies far north on the " +
                 "island of " + bold("Reikland") + ".");
    add_response("cave", "Her cave is so large she can even " + bold("fly") + 
                 " around inside it. It is also filled with the " + 
                 bold("eggs") + " of her unborn children.");
    add_response("eggs", "Onyxia needs only signal her offspring and they " +
                 "will hatch and attend to her.");
    add_response("fly", "The dragon queen can breath lakes of " + 
                 bold("napalm") + " so intense that anyone caught in it will " +
                 "surely be burned to cinders.");
    add_response("napalm", "Onyxia would need to take a really deep breath " +
                 "to drown her enemies in napalm.");
    add_response("onyxia", "The dragon queen is soo " + bold("large") + " " +
                 "that she stretches across three taverns the size of this.");
    add_response("large", "Onyxia's " + bold("head") + ", " + bold("body") + 
                 ", and " + bold("tail") + " are each the size of a house.");
    add_response("head", "The head of the dragon queen needs to be kept " +
                 "busy, or she will start to wander. Someone needs to grab " +
                 "her attention and pull her away from the others.");
    add_response("body", "The body of the dragon queen is where you would " +
                 "want to stay to fight her, although someone would need to " +
                 "lure her " + bold("head") + " away. Just be ready to move " +
                 "quickly if she starts to wander.");
    add_response("tail", "The tail of the dragon queen is probably the most " +
                 "deadly part of her. It is strong enough to knock a full " +
                 "sized man across the width of the river Reik.");
    add_response("chaos", "The denizens of the realm of Chaos have a nasty " +
                 "habit of trying to invade us. It is said that during such " +
                 "an invasion, one may be able to pass through their " +
                 bold("portal") + " to fight back.");
    add_response("portal", "Only the most daring would challenge their own " +
                 "mortality and pass through to the realm of " + bold("Chaos") +
                 ". Lord " + bold("Angron") + " can be found there.");
    add_response("angron", "Angron is the infamous champion of Khorne, the " +
                 "good of blood. His weapons and armour grow in power depending " +
                 "on how much of it you use at the same time.");
}
