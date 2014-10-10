#ifndef ARENA_H
#define ARENA_H

#include "/d/Empire/empire.h"

#define ARN_DIR         (EMP_DIR_ISLANDS + "arena/")
#define ARN_DIR_DAEMONS (ARN_DIR + "daemons/")
#define ARN_DIR_OBJ     (ARN_DIR + "obj/")
#define ARN_DIR_ROOMS   (ARN_DIR + "rooms/")

#define ARN_ISLAND      (ARN_DIR + "island")

#define ARN_C_FAILSAFE  (ARN_DIR_OBJ + "failsafe")
#define ARN_C_SNOOP     (ARN_DIR_OBJ + "snoop")

#define ARN_D_SCORE     (ARN_DIR_DAEMONS + "scored")

#define ARN_I_ROOM      (ARN_DIR_ROOMS + "room_base")

#define ARN_R_INSIDE    (EMP_DIR_VAR_ISLANDS + "arena/4/6")
#define ARN_R_LOUNGE    (ARN_DIR_ROOMS + "lounge")
#define ARN_R_ARENA     (ARN_DIR_ROOMS + "arena")

#define ARN_MAP         (ARN_DIR + "map")
#define ARN_MAP_WALL    ('w')

#endif
