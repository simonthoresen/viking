#include "/d/Empire/empire.h"

#define BUCKET_SIZE   (10)
#define LOG_LIMIT     (200)
#define MAX_BUCKET    (1000)
#define NUM_LEVELS    (ETERNAL_LAST + 1)
#define P_MODIFIED    ("emp_expd_modified")
#define SAVE_FILE     (EMP_DIR_VAR + "expd")
#define SAVE_INTERVAL (300)

inherit I_DAEMON;

private int    *_base_exp;
private int     _last_save;
public  mapping _live_exp;

private int *
calc_base_exp(int num_levels)
{
    int i, *out;
    object obj;
    out = allocate(num_levels);
    for (i = 0; i < num_levels; ++i) {
        obj = new(I_MONSTER);
        obj->set_level(i);
        out[i] = obj->query_exp();
        obj->destroy();
    }
    return out;
}

static void
create()
{
    ::create();
    _base_exp  = calc_base_exp(NUM_LEVELS);
    _last_save = 0;
    _live_exp  = ([ ]);
}

static void
reset(int flag)
{
    ::reset(flag);
    if (!flag) {
        restore_object(SAVE_FILE);
        if (!mapp(_live_exp)) {
            _live_exp = ([ ]);
        }
    }
}

public void
track_exp(object mob)
{
    int level, bucket;
    if (!objectp(mob) || !mob->query_npc() ||
        mob->query_property(P_MODIFIED))
    {
        return;
    }
    level = mob->query_level();
    if (level < 0 || level >= NUM_LEVELS) {
        return;
    }
    bucket = (100 * mob->query_exp()) / _base_exp[level];
    bucket = (bucket / BUCKET_SIZE) * BUCKET_SIZE;
    if (bucket > LOG_LIMIT) {
        EMP_LOG("expd", sprintf("%s (%d) has %d%% of base exp",
                                source_file_name(mob), level, bucket));
    }
    if (bucket < 0 || bucket > MAX_BUCKET) {
        return;
    }
    if (!mapp(_live_exp[level])) {
        _live_exp[level] = ([ ]);
    }
    _live_exp[level][bucket] = _live_exp[level][bucket] + 1;
    if (_last_save < time() - SAVE_INTERVAL) {
        _last_save = time();
        save_object(SAVE_FILE);
    }
}

public void
poll_objects()
{
    filter_array(objects(), "track_exp");
}

public void
player_kill(object victim, object killer)
{
    if (!objectp(victim) || !victim->query_npc() ||
        !objectp(killer) || !interactive(killer))
    {
        return;
    }
    track_exp(victim);
}

public int
query_avg_exp(int level)
{
    int i, len, key, *arr;
    float cnt, sum, val;
    mapping dat;
    cnt = 0.0;
    sum = 0.0;
    if (level < 0) {
        level = 0;
    } 
    if (level >= NUM_LEVELS) {
        level = NUM_LEVELS - 1;
    }
    if (!mapp(dat = _live_exp[level]) ||
        !arrayp(arr = keys(dat)))
    {
        return _base_exp[level];
    }
    for (i = 0, len = sizeof(arr); i < len; ++i) {
        key = arr[i];
        val = to_float(dat[key]);
        cnt += val;
        sum += val * to_float(key);
    }
    if (cnt < 1.0) {
        return _base_exp[level];
    }
    return to_int((to_float(_base_exp[level]) * sum) / cnt) / 100;
}

public int
query_smooth_avg(int level)
{
    int i, out, avg;
    out = 0;
    for (i = 0; i <= level; ++i) {
        if (out < (avg = query_avg_exp(i))) {
            out = avg;
        }
    }
    return out;
}

public int *
query_avgs()
{
    int i, *out;
    out = allocate(NUM_LEVELS);
    for (i = 0; i < NUM_LEVELS; ++i) {
        out[i] = query_avg_exp(i);
    }
    return out;
}

public void
maybe_add_exp(object mob)
{
    int actual, expected;
    if (!clonep(mob) || mob->query_property(P_MODIFIED)) {
        return;
    }
    actual   = mob->query_exp();
    expected = query_smooth_avg(mob->query_level());
    if (expected > actual) {
        EMP_LOG("expd", sprintf("added %d exp to %s (%d)", expected - actual,
                                source_file_name(mob), mob->query_level()));
        mob->add_exp(expected - actual);
        mob->add_property(P_MODIFIED);
    }
}

public int *
query_base_exp()
{
    return _base_exp;
}

public mapping
query_live_exp()
{
    return _live_exp;
}
