#ifndef ARTIFACT_H
#define ARTIFACT_H

#include "/d/Empire/empire.h"
#include "artichoke.h"

/* flags to open the guild */
#define ART_CAN_JOIN              (0)
#define ART_CAN_PLAY              (0)

/* base directories */
#define ART_DIR                   ("/d/Artifact/")
#define ART_DIR_COM               (ART_DIR + "com/")
#define ART_DIR_COM_B             (ART_DIR_COM + "b/")
#define ART_DIR_COM_M             (ART_DIR_COM + "m/")
#define ART_DIR_COM_W             (ART_DIR_COM + "w/")
#define ART_DIR_DAEMONS           (ART_DIR + "daemons/")
#define ART_DIR_ETC               (ART_DIR + "etc/")
#define ART_DIR_ETC_HELP          (ART_DIR_ETC + "help/")
#define ART_DIR_ETC_QUESTS        (ART_DIR_ETC + "quests/")
#define ART_DIR_LOG               (ART_DIR + "log/")
#define ART_DIR_OBJ               (ART_DIR + "obj/")
#define ART_DIR_ROOMS             (ART_DIR + "rooms/")
#define ART_DIR_SLIVERS           (ART_DIR + "slivers/")
#define ART_DIR_STD               (ART_DIR + "std/")
#define ART_DIR_TESTS             (ART_DIR + "tests/")
#define ART_DIR_VAR               (ART_DIR + "var/")

/* guild master */
#define ART_MASTER                (ART_DIR + "master")

/* daemons */
#define ART_D_COMMAND             (ART_DIR_DAEMONS + "commandd")
#define ART_D_GLYPH               (ART_DIR_DAEMONS + "glyphd")
#define ART_D_LOG                 (ART_DIR_DAEMONS + "logd")
#define ART_D_MESSAGE             (ART_DIR_DAEMONS + "messaged")
#define ART_D_QUEST               (ART_DIR_DAEMONS + "questd")
#define ART_D_SCORE               (ART_DIR_DAEMONS + "scored")
#define ART_D_SLIVER              (ART_DIR_DAEMONS + "sliverd")

/* standard inheritables */
#define ART_I_APTITUDE_SKILL      (ART_DIR_STD + "aptitude_skill")
#define ART_I_CAPTCHA             (ART_DIR_STD + "captcha")
#define ART_I_DAMAGE_BASE         (ART_DIR_STD + "dmg_base")
#define ART_I_DAMAGE_UTIL         (ART_DIR_STD + "dmg_util")
#define ART_I_EFFECT              (ART_DIR_STD + "effect_sliver")
#define ART_I_GLYPH               (ART_DIR_STD + "glyph_sliver")
#define ART_I_QUIRK               (ART_DIR_STD + "quirk_sliver")
#define ART_I_SHAPE               (ART_DIR_STD + "shape_sliver")
#define ART_I_SLIVER              (ART_I_SLIVER_UTIL)
#define ART_I_SLIVER_BASE         (ART_DIR_STD + "sliver_base")
#define ART_I_SLIVER_BUILDER      (ART_DIR_STD + "sliver_builder")
#define ART_I_SLIVER_DESC         (ART_DIR_STD + "sliver_desc")
#define ART_I_SLIVER_UTIL         (ART_DIR_STD + "sliver_util")
#define ART_I_SKILL               (ART_DIR_STD + "skill_sliver")
#define ART_I_SPELL               (ART_DIR_STD + "spell_sliver")
#define ART_I_STAT_GLYPH          (ART_DIR_STD + "stat_glyph")
#define ART_I_STAT_SPELL          (ART_DIR_STD + "stat_spell")
#define ART_I_STAT_UTIL           (ART_DIR_STD + "stat_util")
#define ART_I_WEAPON              (ART_I_WEAPON_USER)
#define ART_I_WEAPON_BASE         (ART_DIR_STD + "weapon_base")
#define ART_I_WEAPON_DESC         (ART_DIR_STD + "weapon_desc")
#define ART_I_WEAPON_ECHO         (ART_DIR_STD + "weapon_echo")
#define ART_I_WEAPON_OWNER        (ART_DIR_STD + "weapon_owner")
#define ART_I_WEAPON_PLAYER       (ART_DIR_STD + "weapon_player")
#define ART_I_WEAPON_USER         (ART_DIR_STD + "weapon_user")
#define ART_I_WEAPON_UTIL         (ART_DIR_STD + "weapon_util")

/* constructable objects */
#define ART_C_ECHO_PLAYER         (ART_DIR_OBJ + "echo_player")
#define ART_C_ECHO_WEAPON         (ART_DIR_OBJ + "echo_weapon")
#define ART_C_SOULSTONE           (ART_DIR_OBJ + "soulstone")
#define ART_C_WEAPON              (ART_DIR_OBJ + "weapon")
#define ART_C_ZOMBIE              (ART_DIR_OBJ + "zombie")

/* guild rooms */
#define ART_R_CONTROL             (ART_DIR_ROOMS + "control")
#define ART_R_FURNACE             (ART_DIR_ROOMS + "furnace")
#define ART_R_GLYPH_SHOP          (ART_DIR_ROOMS + "glyph_shop")
#define ART_R_SCORES              (ART_DIR_ROOMS + "scores")
#define ART_R_SKILLS              (ART_DIR_ROOMS + "skills")
#define ART_R_SMITHY              (ART_DIR_ROOMS + "smithy")
#define ART_R_SPELLS              (ART_DIR_ROOMS + "spells")

/* guild properties */
#define ART_P_CONTROL             ("art_control")
#define ART_P_INVITED             ("art_invited")
#define ART_P_RESTED_EXP          ("art_rested_exp")
#define ART_P_SOULSTONE           ("art_soulstone")
#define ART_P_SPELL_PREFIX        ("art_spell_")
#define ART_P_SPELL(obj)          (ART_P_SPELL_PREFIX + (obj)->query_real_name())

/* misc macros */
#define ART_LOG(file, str)        (ART_D_LOG->log((file), (str)))
#define ART_LOGX                  ART_D_LOG->log

#endif
