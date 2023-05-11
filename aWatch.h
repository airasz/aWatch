#include <EEPROM.h>
#include "EEPROM_rw_anything.h"

// #ifdef __MAIN__
// #define
// #define INIT(x) = x
// #else
// #define
// #define INIT(x)
// #endif

// void analogClockVariant(int);
// void clock_face_analog(uint8_t);
// void clock_face_digital(int);
// void updateClock(int, int);
// #define
uint8_t home_hh;
uint8_t home_mm;
uint8_t home_ss;
RTC_Date tnow;
uint8_t local_hour;
uint8_t local_minute;
boolean rtcIrq;

auto flipped = false;

void beep(int8_t);
void enable_rtc_alarm(void);
void disable_rtc_alarm(void);
void Serial_timestamp(void);

// void clock_face_digital(int clock_style);

void charge_icon(uint16_t, uint16_t, uint16_t, uint16_t, boolean);
void battery_icon(uint16_t, uint16_t, uint16_t, uint16_t);
void steps_icon(uint16_t, uint16_t, uint16_t, uint16_t, uint8_t);
void draw_step_counter_ljust(uint16_t, uint16_t, uint16_t, uint16_t, uint8_t);
void draw_step_counter_rjust(uint16_t, uint16_t, uint16_t, uint16_t, uint8_t);
void update_step_counter(void);
void sysinfo();

void displaySysInfo(int);
void setupFont12();
void setupFont18();
void setupFont24();
void updateClock(int h, int m);
void recordActivity();

void clock_face_digit(int clock_style);

int rgbToHex(uint8_t r, uint8_t g, uint8_t b);

// void updateClock();
//=========================================================================
void analog_setup(int s);
void analogClockVariant(int v);
void degree(float hd, float md);

void touchListener();
void handleTouch();

String getDailyJWS(int);
void formating(void);
// return string
String getDailyJWS(int id);

void drawAlarmsetting();

void drawTimeSetting();
void writeRTC();
void writeAlarm();

void setSTO();
void adjustSTO();
void setSBright();
void adjustSBright(int x);
void startSetting();
void adjusting(int, int);
void drawStepSetting();

// 0=home<
// 10.   info
// 30.  setting
void updateScreen();
void toast(String);

void showDayPray(void);
void getPraytaskID(void);
void beep2();
// uint8_t hh, mm, ss, mmonth, dday, gdow; // H, M, S variables
// uint16_t yyear; // Year is 16 bit int
// uint32_t last_activity;
File dbFile;
uint8_t clock_face_now;
String alarm_msg = "";
int ID_;
#define CONFIG_REVISION 12349L
typedef struct config_t
{
    long magic_number;
    uint8_t clock_face;
    bool rnd_face;
    uint8_t pedometer_enable;
    uint16_t mqtt_port;
    uint8_t default_brightness;
    uint8_t screensaver_timeout; // in seconds
    uint8_t stepcounter_filter;  // 0 to disable, 1,2,3,4 for filters
    uint32_t home_tzindex;
    uint32_t local_tzindex;
    boolean alarm_enable;
    uint8_t alarm_h;
    uint8_t alarm_m;
    int8_t alarm_days[7];
    int8_t alarm_sound;
    int8_t alarm_volume;
    int8_t step_length;
    int8_t twelve_hr_clock;
    boolean metric_units;
    boolean alarm_pray;
    boolean show_analog;
    boolean show_number;
    boolean show_text;
    uint8_t alarmpraywarning;
    uint8_t vib;
    uint16_t colorAccent;
} CONFIGGEN;
CONFIGGEN config;
// http://www.barth-dev.de/online/rgb565-color-picker/
const uint32_t COLORS_LIGHT[10] = {
    0xDB5B, 0x97E9, 0x8C7F, 0xFACC, 0xFFED,
    0x4F1F, 0x9ADF, 0xFD0B, 0x5DDF, 0xF9B1};

const uint32_t COLORS_DARK[10] = {
    0x2004, 0x0920, 0x0808, 0x4005, 0x0900,
    0x00E4, 0x280D, 0x20C0, 0x0006, 0x3000};

// uint32_t COLOR_MEDIUM[] = {
//     TFT_PURPLE, TFT_BLUE, TFT_GREEN, TFT_YELLOW, TFT_GREENYELLOW,
//     TFT_PINK, TFT_ORANGE, TFT_RED, TFT_CYAN, TFT_MAGENTA}
const uint32_t COLOR_MEDIUM[] = {TFT_PURPLE, TFT_BLUE, TFT_GREEN, TFT_YELLOW, TFT_GREENYELLOW, TFT_PINK, TFT_ORANGE, TFT_RED, TFT_CYAN, TFT_MAGENTA};
const uint32_t COLOR_ACCENT[] = {TFT_PURPLE, TFT_BLUE, TFT_GREEN, TFT_YELLOW, TFT_PINK, TFT_ORANGE, TFT_RED, TFT_MAGENTA, TFT_DARKCYAN};

String const bulan[] =
    {"Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli",
     "Agustus", "September", "Oktober", "November", "Desember"};

const uint8_t MaxDate[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int startMonth, stDay, stHour, stMinute, currentMonth; // date on watch on boot
int stepMonth, stepDay, stepHour, stepMinute;

boolean date_is_up;
boolean steps_is_up;
boolean initialAnalog;
bool enableSS = false;
extern uint8_t number_of_sounds;
char buff[512];
unsigned int half_width;
unsigned int half_height;
TFT_eSPI *tft;
AXP20X_Class *power;
uint8_t screen_brightness;
boolean charge_cable_connected;
// uint8_t number_of_sounds; // leave lower case, defined in play_sound.cpp
boolean alarm_active;
uint32_t next_beep; // the next time the alarm beep should sound

TTGOClass *ttgo;
U8G2_FOR_ADAFRUIT_GFX u8f; // U8g2 font instance

int hh, mm, ss, mmonth, dday, gdow; // H, M, S variables
uint8_t imnt, iday;
uint16_t yyear; // Year is 16 bit int
uint32_t last_activity;
uint8_t chosen_skin;
bool home, rrrr = false, alarmset = false;
int step_counter, last_step_counter, tmpaph, tmpapm;
int touchCount, cday, daily_step, minfactor, buzz_count;
int htouchInterval = 10;
// int *hd_data= (int *) ps_malloc()
int hddata[][4] = {
    {0, 0, 0, 0}, // jan , holyday in date 0
    {0, 0, 0, 0}, // feb , holyday in date 0 & 0
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}, // augst
    {0, 0, 0, 0}, // no holyday in sept
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}};
