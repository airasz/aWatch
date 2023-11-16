// TTGOClass *ttgo;
// #include "aWatch.h"
// RTC_Date tnow;

int mm180, hh180;
int hourATCarrow;

int rnddot = random(20, 40);
int rndHandMinuteShadow;
// analog clock variant
float sx = 0,
      sy = 1, mx = 1, my = 0, hx = -1, hy = 0;
float sdeg = 0, mdeg = 0, hdeg = 0;
int cr = 80; // circle radius
uint16_t osx = cr, osy = cr, omx = cr, omy = cr, ohx = cr, ohy = cr;

uint16_t x0 = 0, x1 = 0, yy0 = 0, yy1 = 0;
uint32_t targetTime = 0;
bool touched = false;
int CF, touchStage = 0;
int16_t tx, ty; // touch coordinate
//  1   2   3
//  4   5   6
//  7   8   9
// 10 11 12
int tmptouchreg = 0;

int tmphh, tmpmm, tmpday, tmpmnt, tmpyear, tmpvib, tmpmwarn;
int old_hh, old_mm, old_day, old_mnt, old_year, old_vib, old_mwarning;
int tmpha, tmpma;
int old_tmpha, old_tmpma, old_tmpmwarn, old_tmpvib;
bool tmpalarmenable, old_tmpalarmenable, tmpalarmpray, old_tmpalarmpray;
auto write2RTC = false;
auto bwriteAlarm = false;
int atep;
bool swipeMe = true;
//===============

int stepLenght = 45;
int old_stepLength;
auto maxShifting = 15;
uint32_t COLOR_MED[] = {
    0x4810, TFT_BLUE, TFT_GREEN, 0x7380,
    TFT_PINK, 0x7380, TFT_RED, 0x032D, TFT_MAGENTA};
uint32_t COLOR_ATC[] = {TFT_BLUE, TFT_MAGENTA, TFT_GREEN};

//===power info===
int16_t per;
float vbus_v, vbus_c, batt_v, dchrg_c, chrg_c;