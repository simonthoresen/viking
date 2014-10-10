#include "/d/Artifact/artifact.h"

#define DIR_SLIVERS             (ART_DIR_SLIVERS + "x/")
#define SLIVERS_PER_ITERATION   (50)
#define ITERATION_DELAY         (0.1)

inherit base EMP_C_TASKLIST;
inherit util ART_I_SLIVER_BUILDER;

private int _removed;

static void
create()
{
    base::create();
    util::create();

    set_info("generate slivers");
    push_back(store_fp("updir_std"));
    push_back(store_fp("begin_remove"));
    push_back(store_fp("await_remove"));
    push_back(store_fp("build_glyphs"));
    push_back(store_fp("build_dtypes_glyphs"));
    push_back(store_fp("build_quirks"));
    push_back(store_fp("build_dtypes_quirks"));
    push_back(store_fp("build_illusionism_quirks"));
    push_back(store_fp("build_necromancy_quirks"));
    push_back(store_fp("build_transmutation_quirks"));
    push_back(store_fp("build_abjuration_spells"));
    push_back(store_fp("build_conjuration_spells"));
    push_back(store_fp("build_divination_spells"));
    push_back(store_fp("build_enchantment_spells"));
    push_back(store_fp("build_evocation_spells"));
    push_back(store_fp("build_illusionism_spells"));
    push_back(store_fp("build_necromancy_spells"));
    push_back(store_fp("build_restoration_spells"));
    push_back(store_fp("build_transmutation_spells"));
    push_back(store_fp("reset_sliverd"));
    push_back(store_fp("await_sliverd"));
}

static int
updir_std()
{
    updir(ART_DIR_STD);
    return 1;
}

static int 
begin_remove()
{
    call_out("remove_slivers", 0, get_files_absolute(DIR_SLIVERS));
    return 1;
}

static int
await_remove()
{
    if (!_removed) {
        return 0;
    }
    return 1;
}

public void 
remove_slivers(string *arr, int idx) 
{
    int len, cnt; 
    len = sizeof(arr);
    notify("remove_slivers(%d/%d)", idx, len);
    for (cnt = 0; idx < len && cnt < SLIVERS_PER_ITERATION; ++idx, ++cnt) {
        object obj;
        if (file_size(arr[idx]) < 0) {
            continue;
        }
        if (objectp(obj = find_object(arr[idx]))) {
            destruct(obj);
        }
        rm(arr[idx]);
    }
    if (idx < len) {
        call_out("remove_slivers", ITERATION_DELAY, arr, idx);
    } else {
        _removed = 1;
    }
}

static int
reset_sliverd()
{
    object obj;
    if (objectp(obj = find_object(ART_D_SLIVER))) {
        destruct(obj);
    }
    ART_D_SLIVER->__bootstrap();
    return 1;
}

static int
await_sliverd()
{
    return ART_D_SLIVER->is_ready();
}

private void 
foreach_dtype(function fnc)
{
    call_fp(fnc, "acid");
    call_fp(fnc, "bite");
    call_fp(fnc, "blunt");
    call_fp(fnc, "chop");
    call_fp(fnc, "claw");
    call_fp(fnc, "cold");
    call_fp(fnc, "drain");
    call_fp(fnc, "electricity");
    call_fp(fnc, "fire");
    call_fp(fnc, "impact");
    call_fp(fnc, "magic");
    call_fp(fnc, "pierce");
    call_fp(fnc, "slash");
}

private string
desc_skill(string name) 
{
    string desc;
    if (!stringp(desc = ART_MASTER->skill_name(name)) &&
        !stringp(desc = R_ADV_GUILD->skill_name(name)))
    {
        desc = implode(map_array(explode(name, "_"), "format_skill"), " ");
    }
    return desc;
}

static string
format_skill(string str)
{
    return capitalize(str);
}

/* ==[ GLYPHS ]============================================================= */

static int
build_glyphs()
{
    new_sliver();
    set_file(DIR_SLIVERS + "glyph_of_light");
    set_parent(ART_DIR_STD + "light_glyph");
    set_num_ranks(3);
    add_code("set_bonus(%d)", 5, 15);
    add_code("set_level_req(%d)", 1, 10);
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "glyph_of_damage");
    set_parent(ART_DIR_STD + "wc_glyph");
    set_num_ranks(5);
    add_code("set_bonus(%d)", 3, 15);
    add_code("set_level_req(%d)", 1, 20);
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "glyph_of_armour");
    set_parent(ART_DIR_STD + "stat_glyph");
    set_num_ranks(5);
    add_code("set_level_req(%d)", 1, 20);
    add_code("set_stat_bonus(\"ac\", %d)", 1, 5);
    add_code("set_stats_desc(\"armour\")");
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "glyph_of_constitution");
    set_parent(ART_DIR_STD + "stat_glyph");
    set_num_ranks(3);
    add_code("set_level_req(%d)", 1, 20);
    add_code("set_stat_bonus(\"con\", %d)", 1, 3);
    add_code("set_stats_desc(\"constitution\")");
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "glyph_of_dexterity");
    set_parent(ART_DIR_STD + "stat_glyph");
    set_num_ranks(3);
    add_code("set_level_req(%d)", 1, 20);
    add_code("set_stat_bonus(\"dex\", %d)", 1, 3);
    add_code("set_stats_desc(\"dexterity\")");
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "glyph_of_intelligence");
    set_parent(ART_DIR_STD + "stat_glyph");
    set_num_ranks(3);
    add_code("set_level_req(%d)", 1, 20);
    add_code("set_stat_bonus(\"int\", %d)", 1, 3);
    add_code("set_stats_desc(\"intelligence\")");
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "glyph_of_strength");
    set_parent(ART_DIR_STD + "stat_glyph");
    set_num_ranks(3);
    add_code("set_level_req(%d)", 1, 20);
    add_code("set_stat_bonus(\"str\", %d)", 1, 3);
    add_code("set_stats_desc(\"strength\")");
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "glyph_of_two_weapon");
    set_parent(ART_DIR_STD + "stat_glyph");
    set_num_ranks(5);
    add_code("set_level_req(%d)", 1, 29);
    add_code("set_stat_bonus(\"two_weapon\", %d)", 5, 25);
    add_code("set_stats_desc(\"skill in " +
             desc_skill("two_weapon") + "\")");
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "glyph_of_physical_resistance");
    set_parent(ART_DIR_STD + "stat_glyph");
    set_num_ranks(5);
    add_code("set_level_req(%d)", 1, 29);
    add_code("set_stat_bonus(\"resist_bite\", %d)", 10, 50);
    add_code("set_stat_bonus(\"resist_blunt\", %d)", 10, 50);
    add_code("set_stat_bonus(\"resist_chop\", %d)", 10, 50);
    add_code("set_stat_bonus(\"resist_claw\", %d)", 10, 50);
    add_code("set_stat_bonus(\"resist_pierce\", %d)", 10, 50);
    add_code("set_stat_bonus(\"resist_slash\", %d)", 10, 50);
    add_code("set_stats_desc(\"physical resistance\")");
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "glyph_of_elemental_resistance");
    set_parent(ART_DIR_STD + "stat_glyph");
    set_num_ranks(5);
    add_code("set_level_req(%d)", 1, 29);
    add_code("set_stat_bonus(\"resist_acid\", %d)", 10, 50);
    add_code("set_stat_bonus(\"resist_cold\", %d)", 10, 50);
    add_code("set_stat_bonus(\"resist_drain\", %d)", 10, 50);
    add_code("set_stat_bonus(\"resist_electricity\", %d)", 10, 50);
    add_code("set_stat_bonus(\"resist_fire\", %d)", 10, 50);
    add_code("set_stat_bonus(\"resist_impact\", %d)", 10, 50);
    add_code("set_stat_bonus(\"resist_magic\", %d)", 10, 50);
    add_code("set_stats_desc(\"elemental resistance\")");
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "glyph_of_speed");
    set_parent(ART_DIR_STD + "speed_glyph");
    set_num_ranks(5);
    add_code("set_chance(%d)", 2, 10);
    add_code("set_level_req(%d)", 1, 20);
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "glyph_of_featherweight");
    set_parent(ART_DIR_STD + "weight_glyph");
    set_num_ranks(5);
    add_code("set_bonus(%d)", -1, -5);
    add_code("set_level_req(%d)", 1, 20);
    build_slivers();
    return 1;
}

static int
build_dtypes_glyphs()
{    
    foreach_dtype(store_fp("build_dtype_glyphs"));
    return 1;
}

public void
build_dtype_glyphs(string dtype)
{
    string name;
    switch (dtype) {
    case "blunt":
        name = "the_hammer";
        break;
    case "chop":
        name = "the_axe";
        break;
    case "impact":
        name = "the_force";
        break;
    case "slash": 
        name = "the_sword";
        break;
    case "pierce":
        name = "the_spear";
        break;
    default:
        name = dtype;
        break;
    }
    new_sliver();
    set_file(DIR_SLIVERS + "glyph_of_" + name);
    set_parent(ART_DIR_STD + "dproc_glyph");
    set_num_ranks(5);
    add_code("set_chance(%d)", 2, 10);
    add_code("set_dtype(\"" + dtype + "\")");
    add_code("set_level_req(%d)", 3, 23);
    build_slivers();
}

/* ==[ QUIRKS ]============================================================= */

static int
build_quirks()
{
    new_sliver();
    set_file(DIR_SLIVERS + "iron");
    set_parent(ART_DIR_STD + "metal_quirk");
    add_code("set_level_req(1)");
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "bronze");
    set_parent(ART_DIR_STD + "metal_quirk");
    add_code("set_level_req(5)");
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "silver");
    set_parent(ART_DIR_STD + "metal_quirk");
    add_code("set_level_req(10)");
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "gold");
    set_parent(ART_DIR_STD + "metal_quirk");
    add_code("set_level_req(15)");
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "steel");
    set_parent(ART_DIR_STD + "metal_quirk");
    add_code("set_level_req(20)");
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "mithril");
    set_parent(ART_DIR_STD + "metal_quirk");
    add_code("set_level_req(25)");
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "eog");
    set_parent(ART_DIR_STD + "metal_quirk");
    add_code("set_level_req(29)");
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "true_weapon");
    set_parent(ART_DIR_STD + "crit_quirk");
    set_num_ranks(5);
    add_code("set_factor(%d)", 75, 150);
    add_code("set_level_req(%d)", 20, 29);
    add_code("set_slot(\"quirk\", %d)", -3, -15);
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "rake");
    set_parent(ART_DIR_STD + "wound_quirk");
    set_num_ranks(5);
    add_code("set_chance(%d)", 10, 50);
    add_code("set_level_req(%d)", 1, 29);
    add_code("set_skill_req(\"claw_aptitude\", %d)", 20, 100);
    add_code("set_slot(\"quirk\", %d)", -2, -10);
    build_slivers();
    return 1;
}

private void
build_color_quirks(string color)
{
    new_sliver();
    set_file(DIR_SLIVERS + color);
    set_parent(ART_DIR_STD + "color_quirk");
    add_code("set_skill_req(\"illusionism\", 25)");
    add_code("set_level_req(1)");
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "l_" + color);
    set_parent(ART_DIR_STD + "color_quirk");
    add_code("set_skill_req(\"illusionism\", 75)");
    add_code("set_level_req(10)");
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "b_" + color);
    set_parent(ART_DIR_STD + "color_quirk");
    add_code("set_skill_req(\"illusionism\", 75)");
    add_code("set_level_req(20)");
    build_slivers();
}

static int 
build_illusionism_quirks() 
{
    build_color_quirks("red");
    build_color_quirks("green");
    build_color_quirks("yellow");
    build_color_quirks("blue");
    build_color_quirks("magenta");
    build_color_quirks("cyan");
    return 1;
}

static int
build_necromancy_quirks() 
{
    new_sliver();
    set_file(DIR_SLIVERS + "drain_life");
    set_parent(ART_DIR_STD + "drain_quirk");
    set_num_ranks(5);
    add_code("set_drain_hp(%d)", 2, 10);
    add_code("set_level_req(%d)", 10, 29);
    add_code("set_skill_req(\"necromancy\", %d)", 10, 75);
    add_code("set_slot(\"quirk\", %d)", 2, 10);
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "drain_mind");
    set_parent(ART_DIR_STD + "drain_quirk");
    set_num_ranks(5);
    add_code("set_drain_sp(%d)", 2, 10);
    add_code("set_level_req(%d)", 5, 25);
    add_code("set_skill_req(\"necromancy\", %d)", 10, 50);
    add_code("set_slot(\"quirk\", %d)", 2, 10);
    build_slivers();
    return 1;
}

static int
build_transmutation_quirks()
{
    new_sliver();
    set_file(DIR_SLIVERS + "cumbersome");
    set_parent(ART_DIR_STD + "weight_quirk");
    set_num_ranks(4);
    add_code("set_bonus(%d)", 1, 4);
    add_code("set_con_req(%d)", 1, 30);
    add_code("set_level_req(%d)", 1, 15);
    add_code("set_skill_req(\"transmutation\", %d)", 10, 40);
    add_code("set_slot(\"quirk\", %d)", 1, 4);
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "weightless");
    set_parent(ART_DIR_STD + "weight_quirk");
    set_num_ranks(4);
    add_code("set_bonus(%d)", -1, -4);
    add_code("set_level_req(%d)", 5, 20);
    add_code("set_skill_req(\"transmutation\", %d)", 25, 100);
    add_code("set_slot(\"quirk\", %d)", -2, -8);
    add_code("set_str_req(%d)", 1, 30);
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "constitution");
    set_parent(ART_DIR_STD + "stat_quirk");
    set_num_ranks(5);
    add_code("set_level_req(%d)", 1, 28);
    add_code("set_skill_req(\"transmutation\", %d)", 20, 100);
    add_code("set_slot(\"quirk\", %d)", -1, -5);
    add_code("set_stat_bonus(\"con\", %d)", 1, 5);
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "bad_health");
    set_parent(ART_DIR_STD + "stat_quirk");
    set_num_ranks(5);
    add_code("set_level_req(%d)", 1, 28);
    add_code("set_skill_req(\"transmutation\", %d)", 20, 100);
    add_code("set_slot(\"quirk\", %d)", 1, 5);
    add_code("set_stat_bonus(\"con\", %d)", -2, -10);
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "dexterity");
    set_parent(ART_DIR_STD + "stat_quirk");
    set_num_ranks(5);
    add_code("set_level_req(%d)", 1, 28);
    add_code("set_skill_req(\"transmutation\", %d)", 20, 100);
    add_code("set_slot(\"quirk\", %d)", -1, -5);
    add_code("set_stat_bonus(\"dex\", %d)", 1, 5);
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "all_thumbs");
    set_parent(ART_DIR_STD + "stat_quirk");
    set_num_ranks(5);
    add_code("set_level_req(%d)", 1, 28);
    add_code("set_skill_req(\"transmutation\", %d)", 20, 100);
    add_code("set_slot(\"quirk\", %d)", 1, 5);
    add_code("set_stat_bonus(\"dex\", %d)", -2, -10);
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "intelligence");
    set_parent(ART_DIR_STD + "stat_quirk");
    set_num_ranks(5);
    add_code("set_level_req(%d)", 1, 28);
    add_code("set_skill_req(\"transmutation\", %d)", 20, 100);
    add_code("set_slot(\"quirk\", %d)", -1, -5);
    add_code("set_stat_bonus(\"int\", %d)", 1, 5);
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "idiocy");
    set_parent(ART_DIR_STD + "stat_quirk");
    set_num_ranks(5);
    add_code("set_level_req(%d)", 1, 28);
    add_code("set_skill_req(\"transmutation\", %d)", 20, 100);
    add_code("set_slot(\"quirk\", %d)", 1, 5);
    add_code("set_stat_bonus(\"int\", %d)", -2, -10);
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "strength");
    set_parent(ART_DIR_STD + "stat_quirk");
    set_num_ranks(5);
    add_code("set_level_req(%d)", 1, 28);
    add_code("set_skill_req(\"transmutation\", %d)", 20, 100);
    add_code("set_slot(\"quirk\", %d)", -1, -5);
    add_code("set_stat_bonus(\"str\", %d)", 1, 5);
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "weakness");
    set_parent(ART_DIR_STD + "stat_quirk");
    set_num_ranks(5);
    add_code("set_level_req(%d)", 1, 28);
    add_code("set_skill_req(\"transmutation\", %d)", 20, 100);
    add_code("set_slot(\"quirk\", %d)", 1, 5);
    add_code("set_stat_bonus(\"str\", %d)", -2, -10);
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "armour");
    set_parent(ART_DIR_STD + "stat_quirk");
    set_num_ranks(5);
    add_code("set_level_req(%d)", 15, 29);
    add_code("set_skill_req(\"transmutation\", %d)", 20, 100);
    add_code("set_slot(\"quirk\", %d)", -2, -10);
    add_code("set_stat_bonus(\"ac\", %d)", 1, 5);
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "unarmoured");
    set_parent(ART_DIR_STD + "stat_quirk");
    set_num_ranks(5);
    add_code("set_level_req(%d)", 15, 29);
    add_code("set_skill_req(\"transmutation\", %d)", 20, 100);
    add_code("set_slot(\"quirk\", %d)", 1, 5);
    add_code("set_stat_bonus(\"ac\", %d)", -2, -10);
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "damage");
    set_parent(ART_DIR_STD + "wc_quirk");
    set_num_ranks(5);
    add_code("set_bonus(%d)", 2, 10);
    add_code("set_level_req(%d)", 5, 29);
    add_code("set_skill_req(\"transmutation\", %d)", 20, 100);
    add_code("set_slot(\"quirk\", %d)", -2, -10);
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "unarmed");
    set_parent(ART_DIR_STD + "wc_quirk");
    set_num_ranks(5);
    add_code("set_bonus(%d)", -3, -15);
    add_code("set_level_req(%d)", 5, 29);
    add_code("set_skill_req(\"transmutation\", %d)", 20, 100);
    add_code("set_slot(\"quirk\", %d)", 1, 5);
    build_slivers();
    return 1;
}

static int
build_dtypes_quirks()
{
    foreach_dtype(store_fp("build_dtype_quirks"));
    return 1;
}

public void
build_dtype_quirks(string dtype)
{
    string name;
    switch (dtype) {
    case "blunt":
    case "chop":
    case "slash": 
    case "pierce":
        name = "edge";
        break;
    default:       
        name = "aura";
        break;
    }

    new_sliver();
    set_file(DIR_SLIVERS + dtype + "_" + name);
    set_parent(ART_DIR_STD + "dtype_quirk");
    set_num_ranks(4);
    add_code("add_dtype(\"" + dtype + "\")");
    add_code("set_bonus(%d)", 5, 20);
    add_code("set_level_req(%d)", 1, 26);
    add_code("set_skill_req(\"" + dtype + "_aptitude\", %d)", 25, 100);
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + dtype + "_vulnerability");
    set_parent(ART_DIR_STD + "stat_quirk");
    set_num_ranks(3);
    add_code("set_level_req(%d)", 10, 25);
    add_code("set_skill_req(\"" + dtype + "_aptitude\", %d)", 10, 30);
    add_code("set_slot(\"quirk\", %d)", 1, 3);
    add_code("set_stat_bonus(\"vuln_" + dtype + "\", %d)", 33, 99);
    add_code("set_stats_desc(\"vulnerability to " + dtype + "\")");
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + dtype + "_resistance");
    set_parent(ART_DIR_STD + "stat_quirk");
    set_num_ranks(5);
    add_code("set_level_req(%d)", 10, 29);
    add_code("set_skill_req(\"" + dtype + "_aptitude\", %d)", 20, 100);
    add_code("set_slot(\"quirk\", %d)", -1, -5);
    add_code("set_stat_bonus(\"resist_" + dtype + "\", %d)", 20, 100);
    add_code("set_stats_desc(\"resistance to " + dtype + "\")");
    build_slivers();
}

/* ==[ SPELLS ]============================================================= */

static int 
build_abjuration_spells() 
{
    new_sliver();
    set_file(DIR_SLIVERS + "shield");
    set_parent(ART_DIR_STD + "shield_spell");
    set_num_ranks(5);
    add_code("set_cast_cost(%d)", 25, 50);
    add_code("set_cooldown(60)");
    add_code("set_duration(60)");
    add_code("set_level_req(%d)", 20, 29);
    add_code("set_shield(%d)", 50, 250);
    add_code("set_skill_req(\"abjuration\", %d)", 5, 85);
    add_code("set_train_cost(%d)", ONE_MILLION, TEN_MILLION);
    build_slivers();

    foreach_dtype(store_fp("build_abjuration_dtype_spells"));
    return 1;
}

public void
build_abjuration_dtype_spells(string dtype)
{
    new_sliver();
    set_file(DIR_SLIVERS + dtype + "_protection");
    set_parent(ART_DIR_STD + "stat_spell");
    set_num_ranks(5);
    add_code("set_cast_cost(25)");
    add_code("set_level_req(%d)", 1, 25);
    add_code("set_skill_req(\"" + dtype + 
             "_aptitude\", %d)", 10, 50);
    add_code("set_skill_req(\"abjuration\", %d)", 5, 100);
    add_code("set_stat_bonus(\"prot_" + dtype + "\", %d)", 5, 25);
    add_code("set_train_cost(%d)", HUNDRED_THOUSAND, ONE_MILLION);
    build_slivers();
}

static int 
build_conjuration_spells() 
{
    new_sliver();
    set_parent(ART_DIR_STD + "summon_spell");
    set_num_ranks(5);
    add_code("set_cast_cost(%d)", 5, 25);
    add_code("set_cooldown(60)");
    add_code("set_level_req(%d)", 5, 20);
    add_code("set_num_items(%d)", 1, 5);
    add_code("set_skill_req(\"conjuration\", %d)", 5, 85);
    add_code("set_train_cost(%d)", ONE_THOUSAND, HUNDRED_THOUSAND);
    push_code();
    set_file(DIR_SLIVERS + "summon_food");
    add_code("set_summon_item(\"" + ART_DIR_OBJ + 
             "food_summon\")");
    build_slivers();
    pop_code();
    push_code();
    set_file(DIR_SLIVERS + "summon_water");
    add_code("set_summon_item(\"" + ART_DIR_OBJ + 
             "water_summon\")");
    build_slivers();
    pop_code();
    push_code();
    set_file(DIR_SLIVERS + "summon_liquor");
    add_code("set_summon_item(\"" + ART_DIR_OBJ + 
             "liquor_summon\")");
    build_slivers();
    pop_code();

    new_sliver();
    set_file(DIR_SLIVERS + "remember");
    set_parent(ART_DIR_STD + "remember_spell");
    set_num_ranks(5);
    add_code("set_cast_cost(25)");
    add_code("set_level_req(%d)", 20, 28);
    add_code("set_location_id(\"art_location_%d\")", 1, 5);
    add_code("set_skill_req(\"conjuration\", %d)", 20, 100);
    add_code("set_train_cost(%d)", TEN_THOUSAND, ONE_MILLION);
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "teleport");
    set_parent(ART_DIR_STD + "teleport_spell");
    set_num_ranks(5);
    add_code("set_cast_cost(50)");
    add_code("set_level_req(%d)", 20, 28);
    add_code("set_location_id(\"art_location_%d\")", 1, 5);
    add_code("set_skill_req(\"conjuration\", %d)", 20, 100);
    add_code("set_train_cost(%d)", TEN_THOUSAND, ONE_MILLION);
    build_slivers();
    return 1;
}

static int 
build_divination_spells() 
{
    new_sliver();
    set_parent(ART_DIR_STD + "stat_spell");
    set_num_ranks(4);
    add_code("set_cast_cost(25)");
    add_code("set_duration(%d)", 5 * 60, 20 * 60);
    add_code("set_skill_req(\"divination\", %d)", 5, 20);
    add_code("set_train_cost(%d)", TEN_THOUSAND, HUNDRED_THOUSAND);

    push_code();
    set_file(DIR_SLIVERS + "night_vision");
    add_code("set_level_req(%d)", 5, 20);
    add_code("set_stat_bonus(\"night_vision\", %d)", 25, 100);
    add_code("set_stats_desc(\"skill in " +
             desc_skill("night_vision") + "\")");
    build_slivers();
    pop_code();

    push_code();
    set_file(DIR_SLIVERS + "see_alignment");
    add_code("set_level_req(%d)", 5, 20);
    add_code("set_stat_bonus(\"see_alignment\", %d)", 25, 100);
    add_code("set_stats_desc(\"skill in " +
             desc_skill("see_alignment") + "\")");
    build_slivers();
    pop_code();

    push_code();
    set_file(DIR_SLIVERS + "see_curse");
    add_code("set_level_req(%d)", 5, 20);
    add_code("set_stat_bonus(\"see_curse\", %d)", 25, 100);
    add_code("set_stats_desc(\"skill in " +
             desc_skill("see_curse") + "\")");
    build_slivers();
    pop_code();

    push_code();
    set_file(DIR_SLIVERS + "see_invisible");
    add_code("set_level_req(%d)", 20, 29);
    add_code("set_stat_bonus(\"see_invisible\", %d)", 25, 100);
    add_code("set_stats_desc(\"skill in " +
             desc_skill("see_invisible") + "\")");
    build_slivers();
    pop_code();

    push_code();
    set_file(DIR_SLIVERS + "see_magic");
    add_code("set_level_req(%d)", 5, 20);
    add_code("set_stat_bonus(\"see_magic\", %d)", 25, 100);
    add_code("set_stats_desc(\"skill in " +
             desc_skill("see_magic") + "\")");
    build_slivers();
    pop_code();

    new_sliver();
    set_file(DIR_SLIVERS + "identify");
    set_parent(ART_DIR_STD + "identify_spell");
    set_num_ranks(3);
    add_code("set_cast_cost(%d)", 10, 30);
    add_code("set_level_req(%d)", 5, 20);
    add_code("set_skill_req(\"divination\", %d)", 20, 60);
    add_code("set_train_cost(%d)", TEN_THOUSAND, HUNDRED_THOUSAND);
    build_slivers();
    return 1; 
}
static int 
build_enchantment_spells() 
{ 
    new_sliver();
    set_file(DIR_SLIVERS + "mad_rage");
    set_parent(ART_DIR_STD + "speed_spell");
    set_num_ranks(5);
    add_code("set_cast_cost(%d)", 10, 50);
    add_code("set_cooldown(60)");
    add_code("set_level_req(%d)", 20, 25);
    add_code("set_num_attacks(%d)", 2, 6);
    add_code("set_skill_req(\"enchantment\", %d)", 25, 100);
    add_code("set_train_cost(%d)", HUNDRED_THOUSAND, ONE_MILLION);
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "charm");
    set_parent(ART_DIR_STD + "peace_spell");
    set_num_ranks(3);
    add_code("set_cast_cost(%d)", 10, 50);
    add_code("set_cooldown(10)");
    add_code("set_level_req(%d)", 23, 29);
    add_code("set_max_level(%d)", 10, 30);
    add_code("set_skill_req(\"enchantment\", %d)", 10, 50);
    add_code("set_train_cost(%d)", TEN_THOUSAND, HUNDRED_THOUSAND);
    build_slivers();
    return 1; 
}

static int 
build_evocation_spells() 
{ 
    foreach_dtype(store_fp("build_evocation_dtype_spells"));
    return 1; 
}

public void
build_evocation_dtype_spells(string dtype)
{
    string name;
    switch (dtype) {
    case "blunt":
        name = "hammer";
        break;
    case "chop":
        name = "axe";
        break;
    case "impact":
        name = "force";
        break;
    case "slash": 
        name = "sword";
        break;
    case "pierce":
        name = "spear";
        break;
    default:       
        name = dtype;
        break;
    }

    new_sliver();
    set_parent(ART_DIR_STD + "dmg_spell");
    set_num_ranks(5);
    add_code("set_cast_cost(%d)", 10, 25);
    add_code("set_level_req(%d)", 5, 25);
    add_code("set_skill_req(\"" + dtype + "_aptitude\", %d)", 5, 85);
    add_code("set_skill_req(\"evocation\", %d)", 5, 100);
    add_code("set_train_cost(%d)", ONE_THOUSAND, 2 * HUNDRED_THOUSAND);

    push_code();
    set_file(DIR_SLIVERS + name + "_bolt");
    add_code("set_damage(%d)", 10, 35);
    add_code("set_dtype(\"" + dtype + "\")");
    build_slivers();
    pop_code();

    push_code();
    set_file(DIR_SLIVERS + name + "_ball");
    add_code("set_damage(%d)", 10, 45);
    add_code("set_dtype(\"" + capitalize(dtype) + "\")");
    build_slivers();
    pop_code();

    new_sliver();
    set_parent(ART_DIR_STD + "aoe_spell");
    set_num_ranks(5);
    add_code("set_cast_cost(%d)", 25, 75);
    add_code("set_level_req(%d)", 20, 28);
    add_code("set_skill_req(\"" + dtype + "_aptitude\", %d)", 5, 85);
    add_code("set_skill_req(\"evocation\", %d)", 5, 100);
    add_code("set_train_cost(%d)", TEN_THOUSAND, ONE_MILLION);

    push_code();
    set_file(DIR_SLIVERS + name + "_wave");
    add_code("set_damage(%d)", 10, 25);
    add_code("set_dtype(\"" + dtype + "\")");
    build_slivers();
    pop_code();

    push_code();
    set_file(DIR_SLIVERS + name + "_storm");
    add_code("set_damage(%d)", 10, 35);
    add_code("set_dtype(\"" + capitalize(dtype) + "\")");
    build_slivers();
    pop_code();
}

static int 
build_illusionism_spells() 
{
    new_sliver();
    set_file(DIR_SLIVERS + "invisibility");
    set_parent(ART_DIR_STD + "invis_spell");
    set_num_ranks(5);
    add_code("set_cast_cost(%d)", 20, 100);
    add_code("set_duration(%d)", 10, 50);
    add_code("set_level_req(%d)", 20, 28);
    add_code("set_skill_req(\"illusionism\", %d)", 10, 50);
    add_code("set_train_cost(%d)", HUNDRED_THOUSAND, ONE_MILLION);
    build_slivers();
    return 1; 
}

static int
build_necromancy_spells() 
{ 
    new_sliver();
    set_file(DIR_SLIVERS + "siphon_life");
    set_parent(ART_DIR_STD + "drain_spell");
    set_num_ranks(5);
    add_code("set_cast_cost(%d)", 30, 150);
    add_code("set_conversion_rate(100)");
    add_code("set_drain_hp(%d)", 20, 100);
    add_code("set_level_req(%d)", 5, 25);
    add_code("set_skill_req(\"necromancy\", %d)", 10, 100);
    add_code("set_train_cost(%d)", TEN_THOUSAND, HUNDRED_THOUSAND);
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "siphon_mind");
    set_parent(ART_DIR_STD + "drain_spell");
    set_num_ranks(5);
    add_code("set_cast_cost(%d)", 20, 100);
    add_code("set_conversion_rate(50)");
    add_code("set_drain_sp(%d)", 20, 100);
    add_code("set_level_req(%d)", 5, 25);
    add_code("set_skill_req(\"necromancy\", %d)", 10, 100);
    add_code("set_train_cost(%d)", TEN_THOUSAND, HUNDRED_THOUSAND);
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "raise_dead");
    set_parent(ART_DIR_STD + "zombie_spell");
    set_num_ranks(3);
    add_code("set_cast_cost(%d)", 20, 100);
    add_code("set_duration(30)"); 
    add_code("set_level_req(%d)", 18, 28);
    add_code("set_max_level(%d)", 10, 30);
    add_code("set_num_zombies(%d)", 1, 2);
    add_code("set_skill_req(\"necromancy\", %d)", 10, 40);
    add_code("set_train_cost(%d)", TEN_THOUSAND, HUNDRED_THOUSAND);
    add_code("set_zombie_life(%d)", 100, 300); 
    add_code("set_zombie_wc(%d)", 10, 30);
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "sacrifice_corpse");
    set_parent(ART_DIR_STD + "corpse_spell");
    set_num_ranks(5);
    add_code("set_cast_cost(%d)", 1, 5);
    add_code("set_heal_hp(%d)", 1, 5); 
    add_code("set_heal_sp(%d)", 1, 5); 
    add_code("set_level_req(%d)", 6, 26);
    add_code("set_skill_req(\"necromancy\", %d)", 10, 40);
    add_code("set_train_cost(%d)", TEN_THOUSAND, HUNDRED_THOUSAND);
    build_slivers();
    return 1; 
}

static int
build_restoration_spells() 
{
    new_sliver();
    set_file(DIR_SLIVERS + "heal");
    set_parent(ART_DIR_STD + "heal_spell");
    set_num_ranks(5);
    add_code("set_cast_cost(%d)", 25, 35);
    add_code("set_heal(%d)", 25, 100);
    add_code("set_level_req(%d)", 3, 23);
    add_code("set_skill_req(\"restoration\", %d)", 5, 100);
    add_code("set_train_cost(%d)", ONE_THOUSAND, ONE_MILLION);
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "flash_heal");
    set_parent(ART_DIR_STD + "heal_spell");
    set_num_ranks(5);
    add_code("set_cast_cost(1)");
    add_code("set_cooldown(300)");
    add_code("set_heal(%d)", 100, 500);
    add_code("set_level_req(%d)", 4, 24);
    add_code("set_skill_req(\"restoration\", %d)", 5, 100);
    add_code("set_train_cost(%d)", TEN_THOUSAND, ONE_MILLION);
    build_slivers();

    new_sliver();
    set_file(DIR_SLIVERS + "rejuvination");
    set_parent(ART_DIR_STD + "hot_spell");
    set_num_ranks(5);
    add_code("set_cast_cost(%d)", 25, 50);
    add_code("set_duration(30)");
    add_code("set_heal(%d)", 3, 15);
    add_code("set_level_req(%d)", 5, 25);
    add_code("set_skill_req(\"restoration\", %d)", 5, 100);
    add_code("set_train_cost(%d)", ONE_THOUSAND, ONE_MILLION);
    build_slivers();
    return 1;
}

static int
build_transmutation_spells() 
{
    new_sliver();
    set_parent(ART_DIR_STD + "stat_spell");
    set_num_ranks(5);
    add_code("set_cast_cost(%d)", 25, 225);
    add_code("set_level_req(%d)", 9, 29);
    add_code("set_skill_req(\"transmutation\", %d)", 20, 100);
    add_code("set_train_cost(%d)", TEN_THOUSAND, ONE_MILLION);

    push_code();
    set_file(DIR_SLIVERS + "temporary_constitution");
    add_code("set_stat_bonus(\"con\", %d)", 1, 5);
    build_slivers();
    pop_code();

    push_code();
    set_file(DIR_SLIVERS + "temporary_dexterity");
    add_code("set_stat_bonus(\"dex\", %d)", 1, 5);
    build_slivers();
    pop_code();

    push_code();
    set_file(DIR_SLIVERS + "temporary_intelligence");
    add_code("set_stat_bonus(\"int\", %d)", 1, 5);
    build_slivers();
    pop_code();

    push_code();
    set_file(DIR_SLIVERS + "temporary_strength");
    add_code("set_stat_bonus(\"str\", %d)", 1, 5);
    build_slivers();
    pop_code();

    push_code();
    set_file(DIR_SLIVERS + "temporary_armour");
    add_code("set_stat_bonus(\"ac\", %d)", 1, 5);
    build_slivers();
    pop_code();

    new_sliver();
    set_file(DIR_SLIVERS + "temporary_damage");
    set_parent(ART_DIR_STD + "wc_spell");
    set_num_ranks(5);
    add_code("set_bonus(%d)", 3, 15);
    add_code("set_cast_cost(%d)", 25, 225);
    add_code("set_level_req(%d)", 9, 29);
    add_code("set_skill_req(\"transmutation\", %d)", 20, 100);
    add_code("set_train_cost(%d)", TEN_THOUSAND, ONE_MILLION);
    build_slivers();
    return 1; 
}

