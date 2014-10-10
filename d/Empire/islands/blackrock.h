#ifndef BLACKROCK_H
#define BLACKROCK_H

#include "/d/Empire/empire.h"

#define BRD_DIR             (EMP_DIR_ISLANDS + "blackrock/")
#define BRD_DIR_DAEMONS     (BRD_DIR + "daemons/")
#define BRD_DIR_ETC         (BRD_DIR + "etc/")
#define BRD_DIR_OBJ         (BRD_DIR + "obj/")
#define BRD_DIR_ROOMS       (BRD_DIR + "rooms/")
#define BRD_DIR_STD         (BRD_DIR + "std/")

#define BRD_ISLAND          (BRD_DIR + "island")

#define BRD_MAP             (BRD_DIR + "map")
#define BRD_MAP_ENTRY       ('E')
#define BRD_MAP_EXIT        ('X')
#define BRD_MAP_WALL        ('#')

#define BRD_C_COIN          (BRD_DIR_OBJ + "coin")
#define BRD_C_KEEPER        (BRD_DIR_OBJ + "keeper")
#define BRD_C_MAZEGEN       (BRD_DIR_OBJ + "mazegen")

#define BRD_D_MAZE          (BRD_DIR_DAEMONS + "mazed")
#define BRD_D_RENDER        (BRD_DIR_DAEMONS + "renderd")
#define BRD_D_SCORE         (BRD_DIR_DAEMONS + "scored")

#define BRD_I_CRITTER       (BRD_DIR_STD + "critter")
#define BRD_I_ROOM          (BRD_DIR_STD + "room")
#define BRD_I_ROOM_BASE     (BRD_DIR_STD + "room_base")
#define BRD_I_ROOM_CRUMB    (BRD_DIR_STD + "room_crumb")
#define BRD_I_ROOM_DLEVEL   (BRD_DIR_STD + "room_dlevel")
#define BRD_I_ROOM_INVIS    (BRD_DIR_STD + "room_invis")
#define BRD_I_ROOM_RENDER   (BRD_DIR_STD + "room_render")
#define BRD_I_SPELL         (BRD_DIR_STD + "spell")

#define BRD_R_ENTRY         (BRD_DIR_ROOMS + "entry")

#define BRD_P_HEADING       ("brd_heading")
#define BRD_P_RENDER        ("brd_render")

#define BRD_COIN_LOOT(dgr)  (1 + (10 * (dgr)) / 100)
#define BRD_COIN_TREASURE   ( 25)
#define BRD_COIN_PER_QLTY   (  5)

#endif
