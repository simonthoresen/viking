#include "/d/Artifact/artifact.h"

#define NUM_CAPTCHA_TRIES     10
#define NUM_TRACKED_ACTIONS   100
#define REQUIRE_UNIQ_WITHIN   3600
#define ILLEGAL_EXP_GAIN      100000

inherit EMP_I_UTIL;

private string  _captcha_str;
private int     _captcha_exp;
private int     _captcha_cnt;
private string *_uniq_arr;
private int     _uniq_exp; 
private int     _uniq_time; 

static void create() {
    ::create();
    _captcha_str = 0;
    _captcha_exp = 0;
    _captcha_cnt = 0;
    _uniq_arr    = ({ });
    _uniq_exp    = 0;
    _uniq_time   = 0;
}

private int ignore_arg(string act) {
    switch (act) {
    case "eshape":
    case "kill":
    case "shape":
        return 1;
    default:
        return 0;
    }
}

/*private*/ void notify_captcha(object ply, string word) {
    string str, *img;
    int i, len;
    len  = strlen(word);
    str  = sprintf("[ %75s ]\n", "");
    str += sprintf("[ %|75s ]\n", "ARE YOU HUMAN?");
    str += sprintf("[ %|75s ]\n", "PLEASE TYPE THE FOLLOWING " + 
                   upper_case(convert_number(len)) + " LETTERS:");
    str += sprintf("[ %75s ]\n", "");
    img = EMP_D_FONT->render(word);
    if (strlen(img[0]) > 75) {
        img = EMP_D_FONT->render(word[0..len / 2 - 1]) + 
              EMP_D_FONT->render(word[len / 2..]);
    }
    for (i = 0, len = sizeof(img); i < len; ++i) {
        str += sprintf("[ %|75s ]\n", img[i]);
    }
    tell_object(ply, str);    
}

private void notify_attempt(object ply, int cnt) {
    string str;
    str  = sprintf("[ %75s ]\n", "");
    str += sprintf("[ %|75s ]\n", "INCORRECT INPUT!");
    str += sprintf("[ %|75s ]\n", "ATTEMPTS : " + (NUM_CAPTCHA_TRIES - cnt));
    str += sprintf("[ %75s ]\n", "");
    tell_object(ply, str);
}

private void notify_failure(object ply, int exp) {
    string str;
    str  = sprintf("[ %75s ]\n", "");
    str += sprintf("[ %|75s ]\n", "YOU FAILED TO PROVE THAT YOU ARE HUMAN!");
    str += sprintf("[ %|75s ]\n", "EXP DEDUCTED : " + exp);
    str += sprintf("[ %75s ]\n", "");
    tell_object(ply, str);
}

private void notify_success(object ply) {
    string str;
    str  = sprintf("[ %75s ]\n", "");
    str += sprintf("[ %|75s ]\n", "YOU PROVED THAT YOU ARE HUMAN!");
    str += sprintf("[ %75s ]\n", "");
    tell_object(ply, str);
}

private void init_captcha(object ply) {
    string word;
    int *arr, len;
    arr = keys(EMP_D_FONT->query_font());
    len = sizeof(arr);
    word    = "    ";
    word[0] = arr[random(len)];
    word[1] = arr[random(len)];
    word[2] = arr[random(len)];
    word[3] = arr[random(len)];

    _captcha_str = word;
    _captcha_exp = ply->query_exp() - _uniq_exp;
    ply->add_exp(-_captcha_exp);

    notify_captcha(ply, word);
}

private int try_captcha(object ply, string arg) {
    if (!stringp(_captcha_str)) {
        return 0;
    }
    if (arg == _captcha_str) {
        _uniq_arr = ({ });
        _captcha_str = 0;
        ply->add_exp(_captcha_exp);
        ART_LOG("turingd", sprintf("%s passed captcha, %d exp restored", 
                                   ply->query_real_name(), _captcha_exp));
        notify_success(ply);
    } else if (++_captcha_cnt >= NUM_CAPTCHA_TRIES) {
        _captcha_str = 0;
        ply->set_ghost();
        ART_LOG("turingd", sprintf("%s failed to pass captcha, %d exp lost", 
                                   ply->query_real_name(), _captcha_exp));
        notify_failure(ply, _captcha_exp);
    } else {
        notify_attempt(ply, _captcha_cnt);
    }
    return 1;
}

static void register_action(object ply, string verb, string arg) {
    string *val, *arr;
    int len;
    if (!objectp(ply) || try_captcha(ply, verb)) {
        return;
    }
    if (!stringp(verb) || !strlen(verb)) {
        val = ({ "" }); 
    } else if (stringp(arg) && !ignore_arg(verb)) {
        val = ({ verb + " " + arg });
    } else {
        val = ({ verb });
    }
    if (sizeof(_uniq_arr & val)) {
        _uniq_arr -= val; /* will be re-added at end of history */
    } else {
        _uniq_exp = ply->query_exp();
        _uniq_time = time();
    }
    _uniq_arr += val;
    if ((len = sizeof(_uniq_arr)) > NUM_TRACKED_ACTIONS) {
        _uniq_arr = _uniq_arr[len - NUM_TRACKED_ACTIONS..];
    }
    if (time() > _uniq_time + REQUIRE_UNIQ_WITHIN &&
        ply->query_exp() > _uniq_exp + ILLEGAL_EXP_GAIN) 
    {
        init_captcha(ply);
    }
}
