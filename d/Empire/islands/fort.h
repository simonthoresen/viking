#ifndef FORT_H
#define FORT_H

#include "/d/Empire/empire.h"

#define FOR_DIR           (EMP_DIR_ISLANDS + "fort/")
#define FOR_DIR_DAEMONS   (FOR_DIR + "daemons/")
#define FOR_DIR_ETC       (FOR_DIR + "etc/")
#define FOR_DIR_OBJ       (FOR_DIR + "obj/")
#define FOR_DIR_ROOMS     (FOR_DIR + "rooms/")
#define FOR_DIR_STD       (FOR_DIR + "std/")

#define FOR_ISLAND        (FOR_DIR + "island")
#define FOR_MAP           (FOR_DIR + "map")
#define FOR_NUM_WINGS     (4)

#define FOR_D_BOSS        (FOR_DIR_DAEMONS + "bossd")
#define FOR_D_GATE        (FOR_DIR_DAEMONS + "gated")
#define FOR_D_GUARD       (FOR_DIR_DAEMONS + "guardd")
#define FOR_D_LEVER       (FOR_DIR_DAEMONS + "leverd")

#define FOR_I_ENTRY       (FOR_DIR_STD + "entry")
#define FOR_I_GOAL        (FOR_DIR_STD + "goal")
#define FOR_I_HALLWAY     (FOR_DIR_STD + "hallway")
#define FOR_I_MONSTER     (FOR_DIR_STD + "monster")
#define FOR_I_WING        (FOR_DIR_STD + "wing")

#define FOR_C_KEY         (FOR_DIR_OBJ + "key")
#define FOR_C_TREASURE    (FOR_DIR_OBJ + "treasure")

#endif
