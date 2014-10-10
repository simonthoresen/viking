#ifndef RUINS_H
#define RUINS_H

#include "/d/Empire/empire.h"

#define RUN_DIR                   (EMP_DIR_ISLANDS + "ruins/")
#define RUN_DIR_DAEMONS           (RUN_DIR + "daemons/")
#define RUN_DIR_ETC               (RUN_DIR + "etc/")
#define RUN_DIR_OBJ               (RUN_DIR + "obj/")
#define RUN_DIR_ROOMS             (RUN_DIR + "rooms/")
#define RUN_DIR_STD               (RUN_DIR + "std/")

#define RUN_ISLAND                (RUN_DIR + "island")

#define RUN_MAP                   (RUN_DIR + "map")
#define RUN_MAP_AEGIR             ('A')
#define RUN_MAP_FORNJOT           ('F')
#define RUN_MAP_KARI              ('K')
#define RUN_MAP_LOGI              ('L')
#define RUN_MAP_RUIN              ('r')
#define RUN_MAP_RUNESTONE         ('T')
#define RUN_MAP_RUBBLE            ('u')
#define RUN_MAP_WALL              ('w')

#define RUN_C_AEGIR               (RUN_DIR_OBJ + "aegir")
#define RUN_C_AEGIR_DAUGHTER      (RUN_DIR_OBJ + "aegir_daughter")
#define RUN_C_AEGIR_WIFE          (RUN_DIR_OBJ + "aegir_wife")
#define RUN_C_FORNJOT             (RUN_DIR_OBJ + "fornjot")
#define RUN_C_FORNJOT_GUARD       (RUN_DIR_OBJ + "fornjot_guard")
#define RUN_C_FORNJOT_RUNESTONE   (RUN_DIR_OBJ + "fornjot_runestone")
#define RUN_C_FORNJOT_SHADE       (RUN_DIR_OBJ + "fornjot_shade")
#define RUN_C_KARI                (RUN_DIR_OBJ + "kari")
#define RUN_C_KARI_ACOLYTE        (RUN_DIR_OBJ + "kari_acolyte")
#define RUN_C_KARI_TORNADO        (RUN_DIR_OBJ + "kari_tornado")
#define RUN_C_LOGI                (RUN_DIR_OBJ + "logi")
#define RUN_C_LOGI_DAUGHTER1      (RUN_DIR_OBJ + "logi_daughter1")
#define RUN_C_LOGI_DAUGHTER2      (RUN_DIR_OBJ + "logi_daughter2")
#define RUN_C_LOGI_FIRE           (RUN_DIR_OBJ + "logi_fire")
#define RUN_C_LOGI_WIFE           (RUN_DIR_OBJ + "logi_wife")

#define RUN_D_RUINS               (RUN_DIR_DAEMONS + "ruinsd")

#define RUN_I_LOGI_DAUGHTER       (RUN_DIR_STD + "logi_daughter")
#define RUN_I_MONSTER             (RUN_DIR_STD + "monster")
#define RUN_I_ROOM                (RUN_DIR_STD + "room")
#define RUN_I_STATUE              (RUN_DIR_STD + "statue")


/* balancing constants */
#define AEGIR_DAUGHTER_HEAL               (2500)
#define AEGIR_DAUGHTER_SPAWN_INTERVAL     (30)
#define AEGIR_DAUGHTER_STUN_DAMAGE        (50 + random(25))
#define AEGIR_DAUGHTER_STUN_DURATION      (2)
#define AEGIR_THROW_COUNTDOWN_BEATS       (5)
#define AEGIR_THROW_DAMAGE1               (50 + random(50))
#define AEGIR_THROW_DAMAGE2               (25 + random(25))
#define AEGIR_THROW_FORCE                 (10)
#define AEGIR_WIFE_TICK_HEAL              (250)
#define AEGIR_WIFE_TICK_SECS              (1)

#define FORNJOT_RUNESTONE_NUM_GUARDS      (2)
#define FORNJOT_RUNESTONE_RESPAWN_DELAY   (450)
#define FORNJOT_RUNESTONE_SPAWN_DELAY     (2)
#define FORNJOT_SHADE_INVULN_SECS         (3)
#define FORNJOT_SHADE_SPAWN_DELAY         (2)
#define FORNJOT_SHADE_TICK_HEAL           (10)
#define FORNJOT_SHADE_TICK_SECS           (2)
#define FORNJOT_STUN_COUNTDOWN_BEATS      (30)
#define FORNJOT_STUN_DURATION_SECS        (30)
#define FORNJOT_VULNERABILITY_SECS        (30)

#define KARI_ACOLYTE_SPAWN_INTERVAL       (45)
#define KARI_TORNADO_DAMAGE               (25 + random(25))
#define KARI_TORNADO_DURATION_SECS        (120)
#define KARI_TORNADO_SPAWN_INTERVAL       (30)

#define LOGI_DAUGHTER_THROW_DAMAGE        (50 + random(50))
#define LOGI_DAUGHTER_THROW_FORCE         (1)
#define LOGI_FIRE_INC_PER_BEAT            (25)
#define LOGI_FIRE_DURATION_SECS           (10)
#define LOGI_RAIN_INTERVAL                (3)
#define LOGI_RAIN_DAMAGE                  (50 + random(50))
#define LOGI_SPAWN_DAUGHTERS_AT           (75)
#define LOGI_SPAWN_WIFE_AT                (10)
#define LOGI_THROW_CHANCE                 (5)
#define LOGI_THROW_DAMAGE                 (15 + random(15))
#define LOGI_THROW_FORCE                  (2)
#define LOGI_WIFE_AOE_DAMAGE              (25)

#endif
