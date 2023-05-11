// build from scratch
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/queue.h"
#include <soc/rtc.h>
#include "esp_wifi.h"
#include "esp_sleep.h"

#include <SPIFFS.h> // includes FS.h
#include <ArduinoJson.h>
#include <FS.h>
#include <WiFi.h>
#include <WiFiUdp.h>
// #include <AceTime.h>

#define __MAIN__
#include "config.h"
#include "aWatch.h"
#include "watch_hw.h"
#include "global.h"

#include <WiFi.h>
#include <HTTPClient.h> //Remove Audio Lib error
#include "ArrayList.h"
/* #include "AudioFileSourcePROGMEM.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"
#include "beep__279.h"
#include "Audio.h"
Audio audio;
// TTGOClass *ttgo;
AudioGeneratorMP3 *mp3;
AudioFileSourcePROGMEM *file;
AudioOutputI2S *out;
AudioFileSourceID3 *id3; */
#define EEPROM_SIZE 512
QueueHandle_t g_event_queue_handle = NULL;
EventGroupHandle_t g_event_group = NULL;
EventGroupHandle_t isr_group = NULL;

int angka = 0;
bool lenergy = false;
auto toastShow = false;
long prevmi = 0;
int screenTimeOut = 12;
int count2;
int prevpage_ID, page_ID;
auto inApp = false;
// uint32_t targetTime = 0; // for next 1 second display update

// using namespace ace_time;
auto tomorow = false;
// CONFI config;
ArrayList<int> faceList;

RTC_DATA_ATTR int wakeupCounter = 0;

void update_step_counter(void)
{
  // updateStepCounter(ttgo->bma->getCounter());
  step_counter = ttgo->bma->getCounter();
}

void bright_check(void)
{
  static uint8_t old_brightness;
  if (power->isVBUSPlug())
  {
    screen_brightness = 200;
    charge_cable_connected = true;
    screenTimeOut = 30;
  }
  else
  {
    screen_brightness = config.default_brightness;
    // screen_brightness = 100;
    (page_ID > 1 || page_ID > 11) ? screenTimeOut = 10 : screenTimeOut = config.screensaver_timeout;
    int cface;
    (config.rnd_face) ? cface = random(0, 12) : cface = CF;

    screenTimeOut = (cface == 10) ? config.screensaver_timeout + 5 : config.screensaver_timeout;
    Serial.printf("Screentimeout bright : %d \n", screenTimeOut);
    charge_cable_connected = false;
  }
  if (old_brightness != screen_brightness)
  {
    ttgo->setBrightness(screen_brightness); // 0-255
    old_brightness = screen_brightness;
    // ttgo->setBrightness(255);       // 0-255
  }
}

void my_idle(void)
{
  last_activity = millis(); // extens  screen timeout
  bright_check();
}

void low_energy(void)
{
  if (ttgo->bl->isOn())
  {
    Serial.println("Entering light sleep mode.");
    xEventGroupSetBits(isr_group, WATCH_FLAG_SLEEP_MODE);

    tft->fillScreen(TFT_BLACK);
    ttgo->closeBL();
    // ttgo->stopLvglTick();
    if (!home)
      home = 1;
    if (config.stepcounter_filter)
    {
      ttgo->bma->enableStepCountInterrupt(false);
    }
    ttgo->displaySleep();
    if (!WiFi.isConnected())
    {
      lenergy = true;
      WiFi.mode(WIFI_OFF);
      // rtc_clk_cpu_freq_set(RTC_CPU_FREQ_2M);
      setCpuFrequencyMhz(20);
      // Serial.println(F("before gpio_wakeup_enable() party."));

      esp_err_t erret;
      erret = gpio_wakeup_enable((gpio_num_t)AXP202_INT, GPIO_INTR_LOW_LEVEL);
      if (erret != ESP_OK)
      {
        Serial.println(F("gpio_wakeup_enable failed for AXP202_INT"));
      }
      erret = gpio_wakeup_enable((gpio_num_t)BMA423_INT1, GPIO_INTR_HIGH_LEVEL);
      if (erret != ESP_OK)
      {
        Serial.println(F("gpio_wakeup_enable failed for BMA423_INT"));
      }
      // Serial.println(F("gpio_wakeup_enable(RTC_INT, LOW_LEVEL)"));
      erret = gpio_wakeup_enable((gpio_num_t)RTC_INT, GPIO_INTR_LOW_LEVEL);
      if (erret != ESP_OK)
      {
        Serial.println(F("gpio_wakeup_enable failed for RTC_INT"));
      }
      erret = esp_sleep_enable_gpio_wakeup();
      if (erret != ESP_OK)
      {
        Serial.println(F("esp_sleep_enable_gpio_wakeup() failed"));
      }
      esp_light_sleep_start();
    }
  }
  else
  {
    // ttgo->startLvglTick();
    ttgo->displayWakeup();
    ttgo->rtc->syncToSystem(); // set OS clock to RTC clock
    if (config.stepcounter_filter)
    {
      update_step_counter();
    }
    if (rtcIrq) // called only by rtc alarm
    {
      Serial.println(F("wake from sleep, we see rtc alarm"));
      // disable_rtc_alarm();

      ttgo->rtc->disableAlarm();
      ttgo->rtc->resetAlarm();
      rtcIrq = 0;
      if (config.alarm_enable && !alarm_active)
      {
        Serial.println(F("activate  alarm"));
        alarm_active = true;
        // beep(config.alarm_sound);
        beep(0);
        next_beep = millis() + 250;
      }
      if (config.alarm_pray && !alarm_active)
      {
        Serial.println(F("activate pray  alarm"));
        alarm_active = true;
        // beep(config.alarm_sound);
        beep(0);
        next_beep = millis() + 250;
      }
    }
#if LVGL_BATTERY_ICON
    updateBatteryLevel();
    updateBatteryIcon(LV_ICON_CALCULATION);
#endif
    // lv_disp_trig_activity(NULL);
    ttgo->openBL();
    if (config.stepcounter_filter)
    {
      ttgo->bma->enableStepCountInterrupt();
    }
  }
}

void displayTime(uint8_t update_type)
{
  bright_check();
  if (config.alarm_enable && !alarm_active && config.alarm_h == local_hour && config.alarm_m == local_minute)
  {
    alarm_active = true;
    // beep(config.alarm_sound);
    beep(0);
    // rrr(0);
    Serial.println("start bip");
    next_beep = millis() + 250;
  }
  else if (config.alarm_pray && !alarm_active && tmpaph == local_hour && tmpapm == local_minute)
  {
    alarm_active = true;
    // beep(config.alarm_sound);
    beep(0);
    // rrr(0);
    Serial.println("start pray alarm");
    next_beep = millis() + 250;
  }
  else if (alarm_active && millis() > next_beep)
  {

    // --------------------enable beep make reset
    // beep(config.alarm_sound);
    // beep(0);
    // rrr(1);
    Serial.println("end bip");
    next_beep = millis() + 50;
    rrrr = !rrrr;
    buzz_count++;
    digitalWrite(4, rrrr);
    if (buzz_count > (config.vib * 2))
    {
      digitalWrite(4, LOW);
      ttgo->rtc->disableAlarm();
      ttgo->rtc->resetAlarm();
      alarmset = 0;
      if (config.alarm_pray)
        setprayalarm(true);
      buzz_count = 0;
      alarm_active = 0;
      updateScreen(0);
      Serial.println("auto stop alarm");
    }
    my_idle();
  }
  if (update_type == 2)
  {
    date_is_up = false;
    steps_is_up = false;
    tnow = ttgo->rtc->getDateTime();
    hh = tnow.hour;
    mm = tnow.minute;

    tomorow = 0;
    getPower();
    // clock_face_digit(CF);
    page_ID = 0;
    updateScreen(0);
  }
  // clock_face_digital(8);
  angka++;
  if (angka == 1)
  {

    // clock_face_digital(8);
  }
  if (angka > 59)
  {
    angka = 0;
  }
  // switch (chosen_skin)
  // {
  // case LCARS:
  //   LCARS_Time(update_type);
  //   break;
  // case ANALOG:
  //   Analog_Time(update_type);
  //   break;
  // case LILYGO:
  //   LilyGo_Time(update_type);
  //   break;
  // case BASIC:
  // default:
  //   Basic_Time(update_type);
  //   break;
  // }
}

void Serial_timestamp(void)
{
  Serial.printf("%s UTC\n", ttgo->rtc->formatDateTime());
}

void quickBuzz(void)
{
  digitalWrite(4, HIGH);
  delay(50);
  digitalWrite(4, LOW);
}
void rrr(bool r)
{
  digitalWrite(4, r);
}

bool is_sleeping;
void setup()
{
  // put your setup code here, to run once:
  // CF = 9; //max 9

  setCpuFrequencyMhz(80);
  ttgo = TTGOClass::getWatch();
  ttgo->begin();
  ttgo->openBL();      // Turn on the backlight
  tft = ttgo->tft;     // just a shorthand for ttgo->tft
  power = ttgo->power; // just a shorthand for ttgo->power
  u8f.begin(*tft);
  tft->setTextFont(2);
  tft->fillScreen(TFT_BLACK);
  beep(0);
  startScreen(true, "initial variable");
  home = true;
  touchCount = 0;
  inApp = 0;
  startAC();
  Serial.begin(115200);
  Serial.print("stating aWatch . . . ");
  if (!SPIFFS.begin(true))
  {
    Serial.println(F("An Error has occurred while mounting SPIFFS"));

    startScreen(false, "failed mount SPIFFS");
  }
  else
  {
    startScreen(true, "success mount SPIFFS");
  }
  startMonth = tnow.month;
  pinMode(4, OUTPUT); // vibrator motor pin
  EEPROM.begin(EEPROM_SIZE);
  EEPROM_readAnything(0, config); // get saved settings
  init_holiday();                 // appcal.ino
  startScreen(true, "read EEPROM");
  if (config.magic_number != CONFIG_REVISION)
  { // this will set it up for very first use
    Serial.printf("magic wrong, was %ld, should be %ld\n", config.magic_number, CONFIG_REVISION);
    config.magic_number = CONFIG_REVISION;
    config.clock_face = 0;
    config.rnd_face = 0;
    config.pedometer_enable = false;
    config.default_brightness = 20;
    config.screensaver_timeout = 20;
    config.stepcounter_filter = 1;
    config.step_length = 45;
    // config.home_tzindex = MY_TIMEZONE;
    config.alarm_h = 8;
    config.alarm_m = 15;
    config.alarm_sound = 5;
    config.alarm_volume = 255;
    config.alarm_enable = false;
    config.twelve_hr_clock = 0;
    config.metric_units = false;
    config.alarm_pray = false;
    config.show_analog = true;
    config.show_number = false;
    config.show_text = false;
    config.alarmpraywarning = 3;
    config.vib = 8;
    config.colorAccent = 2;
    EEPROM_writeAnything(0, config);
    EEPROM.commit();
  }

  fillFaceList();

  // config.screensaver_timeout = 20;
  // EEPROM_writeAnything(0, config);
  // EEPROM.commit();
  //  config.colorAccent = COLOR_ACCENT[config.colorAccent];
  CF = config.clock_face; // max 9
  clock_face_now = config.clock_face;
  screenTimeOut = config.screensaver_timeout;
  g_event_queue_handle = xQueueCreate(20, sizeof(uint8_t));
  g_event_group = xEventGroupCreate();
  isr_group = xEventGroupCreate();

  tft->setTextColor(TFT_YELLOW, TFT_BLACK); // Note: the new fonts do not draw the background colour
  half_width = tft->width() / 2;
  half_height = tft->height() / 2;

  // Turn on the IRQ used
  power->adc1Enable(AXP202_BATT_VOL_ADC1 | AXP202_BATT_CUR_ADC1 | AXP202_VBUS_VOL_ADC1 | AXP202_VBUS_CUR_ADC1, AXP202_ON);
  power->enableIRQ(AXP202_VBUS_REMOVED_IRQ | AXP202_VBUS_CONNECT_IRQ | AXP202_CHARGING_FINISHED_IRQ, AXP202_ON);
  power->clearIRQ();

  // Turn off unused power
  power->setPowerOutPut(AXP202_EXTEN, AXP202_OFF);
  power->setPowerOutPut(AXP202_DCDC2, AXP202_OFF);
  power->setPowerOutPut(AXP202_LDO3, AXP202_OFF); // audio device
  power->setPowerOutPut(AXP202_LDO4, AXP202_OFF);

  // Initialize lvgl
  //  ttgo->lvgl_begin();

  // Enable BMA423 interrupt ，
  // The default interrupt configuration,
  // you need to set the acceleration parameters, please refer to the BMA423_Accel example
  ttgo->bma->attachInterrupt();

  // Connection interrupted to the specified pin
  pinMode(BMA423_INT1, INPUT);

  startScreen(true, "setup BMA");
  attachInterrupt(
      BMA423_INT1, []
      {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        EventBits_t bits = xEventGroupGetBitsFromISR(isr_group);
        if (bits & WATCH_FLAG_SLEEP_MODE)
        {
          //! For quick wake up, use the group flag
          xEventGroupSetBitsFromISR(isr_group, WATCH_FLAG_SLEEP_EXIT | WATCH_FLAG_BMA_IRQ, &xHigherPriorityTaskWoken);
        }
        else
        {
          uint8_t data = Q_EVENT_BMA_INT;
          xQueueSendFromISR(g_event_queue_handle, &data, &xHigherPriorityTaskWoken);
        }

        if (xHigherPriorityTaskWoken)
        {
          portYIELD_FROM_ISR();
        } },
      RISING);

  bool is_sleeping;

  startScreen(true, "setup AXP");
  // Connection interrupted to the specified pin
  pinMode(AXP202_INT, INPUT);
  attachInterrupt(
      AXP202_INT, []
      {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        EventBits_t bits = xEventGroupGetBitsFromISR(isr_group);
        if (bits & WATCH_FLAG_SLEEP_MODE)
        {
          prevmi = 0;
          //! For quick wake up, use the group flag
          xEventGroupSetBitsFromISR(isr_group, WATCH_FLAG_SLEEP_EXIT | WATCH_FLAG_AXP_IRQ, &xHigherPriorityTaskWoken);
        }
        else
        {
          uint8_t data = Q_EVENT_AXP_INT;
          xQueueSendFromISR(g_event_queue_handle, &data, &xHigherPriorityTaskWoken);
        }
        if (xHigherPriorityTaskWoken)
        {
          portYIELD_FROM_ISR();
        } },
      FALLING);

  startScreen(true, "setup RTC");
  pinMode(RTC_INT, INPUT_PULLUP);
  attachInterrupt(
      RTC_INT, []
      {
        rtcIrq = 1;
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        EventBits_t bits = xEventGroupGetBitsFromISR(isr_group);
        if (bits & WATCH_FLAG_SLEEP_MODE)
        {
          //! For quick wake up, use the group flag
          xEventGroupSetBitsFromISR(isr_group, WATCH_FLAG_SLEEP_EXIT | WATCH_FLAG_AXP_IRQ, &xHigherPriorityTaskWoken);
        }
        else
        {
          uint8_t data = Q_EVENT_AXP_INT;
          xQueueSendFromISR(g_event_queue_handle, &data, &xHigherPriorityTaskWoken);
        }
        if (xHigherPriorityTaskWoken)
        {
          portYIELD_FROM_ISR();
        } },
      FALLING);

  // Check if the RTC clock matches, if not, use compile time
  // ttgo->rtc->check();

  // Synchronize time to system time
  tnow = ttgo->rtc->getDateTime();
  startScreen(true, "SYNC RTC");
  ttgo->rtc->syncToSystem();

  hh = tnow.hour;
  mm = tnow.minute;
  ss = tnow.second;
  dday = tnow.day;
  mmonth = tnow.month;
  yyear = tnow.year;
  iday = tnow.day;
  cday = tnow.day;
  imnt = tnow.month;

  startMonth = tnow.month;
  stDay = iday;
  stHour = hh;
  stMinute = tnow.minute;

  stepMonth = tnow.month;
  stepDay = iday;
  stepHour = hh;
  stepMinute = tnow.minute;

  // Serial.printf("stminute on setup %d\n ", stMinute);
  // Serial.printf("tnow.minute on setup %d\n ", tnow.minute);

  // purpose for simulation
  // startMonth = 2;
  // stDay = 12;
  // stHour = 17;
  // stMinute = 52;
  // systemClock.setup();

  // init_timezones();

  if (config.alarm_enable)
  {
    // enable_rtc_alarm();
    ttgo->rtc->setAlarm(config.alarm_h, config.alarm_m, PCF8563_NO_ALARM, PCF8563_NO_ALARM);
    ttgo->rtc->enableAlarm();
  }

  if (config.alarm_pray)
    setprayalarm(false);

  Serial_timestamp();
  // Serial.printf("DARKGREY = %x = %d\n", TFT_DARKGREY, TFT_DARKGREY);

  initialAnalog = true;

  startScreen(true, "preparing clock face");
  displayTime(2); // Full redraw
  is_sleeping = false;
  alarm_active = false;
  next_beep = 0;
  my_idle();
  if (power->isVBUSPlug())
  {
    // power->setPowerOutPut(AXP202_LDO3, AXP202_ON);
    beep(0);
  }
  delay(1000);
  // displayTime(2);
} // end setup
//==============linux boot text log look a like===
void startScreen(bool respon, String txt)
{
  tft->setTextColor(TFT_WHITE);
  tft->print("[");
  if (respon)
  {

    tft->setTextColor(TFT_GREEN);
    tft->print("OK");
  }
  else
  {
    tft->setTextColor(TFT_RED);
    tft->print("XX");
  }
  tft->setTextColor(TFT_WHITE);
  tft->print("]");
  tft->println(txt);
  delay(50);
}
//================loop=================
void loop()
{

  // put your main code here, to run repeatedly:
  if (millis() > prevmi + htouchInterval)
  {
    // angka++;
    // if (angka > 59)
    // {
    //   // clock_face_digital(8);
    //   angka = 0;
    // }
    handleTouch();
    (htouchInterval > 10) && (htouchInterval = 10);
    prevmi = millis();
  }

  bool rlst;
  uint8_t data;

  //! Fast response wake-up interrupt
  EventBits_t bits = xEventGroupGetBits(isr_group);
  if (bits & WATCH_FLAG_SLEEP_EXIT)
  {

    my_idle();
    if (lenergy)
    {
      lenergy = false;
      // rtc_clk_cpu_freq_set(RTC_CPU_FREQ_160M);
      // setCpuFrequencyMhz(160);
      setCpuFrequencyMhz(80);
    }

    low_energy();

    if (bits & WATCH_FLAG_BMA_IRQ)
    {
      do
      {
        rlst = ttgo->bma->readInterrupt();
      } while (!rlst);
      xEventGroupClearBits(isr_group, WATCH_FLAG_BMA_IRQ);
    }
    if (bits & WATCH_FLAG_AXP_IRQ)
    {
      power->readIRQ();
      power->clearIRQ();
      // TODO: Only accept axp power pek key short press
      xEventGroupClearBits(isr_group, WATCH_FLAG_AXP_IRQ);
    }
    xEventGroupClearBits(isr_group, WATCH_FLAG_SLEEP_EXIT);
    xEventGroupClearBits(isr_group, WATCH_FLAG_SLEEP_MODE);
  }
  if ((bits & WATCH_FLAG_SLEEP_MODE))
  {
    //! No event processing after entering the information screen
    return;
  }

  //! Normal polling
  if (rtcIrq)
  {
    Serial.println(F("Polled for rtc alarm"));
    rtcIrq = 0;
    // disable_rtc_alarm();

    ttgo->rtc->disableAlarm();
    ttgo->rtc->resetAlarm();
    if (config.alarm_enable && !alarm_active)
    {
      alarm_active = true;
      // beep(config.alarm_sound);
      beep(0);
      next_beep = millis() + 250;
    }
    if (config.alarm_pray && !alarm_active)
    {
      alarm_active = true;
      // beep(config.alarm_sound);
      beep(0);
      next_beep = millis() + 250;
    }
  }
  if (xQueueReceive(g_event_queue_handle, &data, 5 / portTICK_RATE_MS) == pdPASS)
  {
    switch (data)
    {
    case Q_EVENT_BMA_INT:
      do
      {
        rlst = ttgo->bma->readInterrupt();
      } while (!rlst);
      if (config.stepcounter_filter)
      {
        if (ttgo->bma->isStepCounter())
        {
          update_step_counter();
        }
      }
      break;
    case Q_EVENT_AXP_INT:
      power->readIRQ();
#if LVGL_BATTERY_ICON
      if (power->isVbusPlugInIRQ())
      {
        updateBatteryIcon(LV_ICON_CHARGE);
      }
      if (power->isVbusRemoveIRQ())
      {
        updateBatteryIcon(LV_ICON_CALCULATION);
      }
      if (power->isChargingDoneIRQ())
      {
        updateBatteryIcon(LV_ICON_CALCULATION);
      }
#endif
      if (power->isPEKShortPressIRQ())
      {
        power->clearIRQ();
        last_activity = 0;
        is_sleeping = true;
        Serial.print("button sleep request ");
        Serial_timestamp();
        low_energy();
        return;
      }
      power->clearIRQ();
      break;
#if NEEDED
    case Q_EVENT_WIFI_SCAN_DONE:
    {
      int16_t len = WiFi.scanComplete();
      for (int i = 0; i < len; ++i)
      {
        wifi_list_add(WiFi.SSID(i).c_str());
      }
      break;
    }
#endif
    default:
      break;
    }
  }

  // if (lv_disp_get_inactive_time(NULL) < (config.screensaver_timeout * 1000))
  if (last_activity + (screenTimeOut * 1000) > millis())
  {
    if (is_sleeping)
    {
      displayTime(2); // Full redraw
      ttgo->bma->enableAccel();
      is_sleeping = false;
      Serial.print("wakey-wakey ");
      flipped = false;
      wakeupCounter++;
      Serial_timestamp();
      initialAnalog = true;
      checkday();
      // beep2();
    }
    else if (targetTime < millis())
    {
      targetTime = millis() + 1000;
      // touchCount=0;
      // appTouch();
      displayTime((ss == 0) ? 1 : 0); // Call every second but full update every minute
    }

    int mSelect;
    boolean have_run_app = false;
    touchListener();
  }
  else
  {
    if (!is_sleeping)
    {
      is_sleeping = true;
      Serial.print("sleepy-bye ");
      Serial_timestamp();
    }
    low_energy();
  }
} // end void loop

void getPower()
{
  vbus_v = power->getVbusVoltage() / 1000;
  vbus_c = power->getVbusCurrent();
  batt_v = power->getBattVoltage() / 1000;
  per = power->getBattPercentage();
  dchrg_c = power->getBattDischargeCurrent();
  chrg_c = power->getBattChargeCurrent();
}
void beep2()
{
  /*  ttgo->enableLDO3();

   // pinMode(pinName, OUTPUT);
   if (!SPIFFS.begin(true))
   {
     Serial.println("An Error has occurred while mounting SPIFFS");
   }
   else
   {
     Serial.println("beeping using audio");
     audio.setPinout(TWATCH_DAC_IIS_BCK, TWATCH_DAC_IIS_WS, TWATCH_DAC_IIS_DOUT);
     audio.setVolume(18); // 0...21
     audio.connecttoFS(SPIFFS, "sonar2.mp3");
   } */
}
void beep(int8_t w)
{
  /* // WiFi.mode(WIFI_OFF);
  // delay(500);

  //! Turn on the audio power
  ttgo->enableLDO3();

  file = new AudioFileSourcePROGMEM(beep__279_mp3, sizeof(beep__279_mp3));
  Serial.printf("sizeof sound %d is %u\n", 0, sizeof(beep__279_mp3));
  id3 = new AudioFileSourceID3(file);
#if defined(STANDARD_BACKPLANE)
  Serial.println(F("STANDARD_BACKPLANE"));
  out = new AudioOutputI2S(0, 1);
#elif defined(EXTERNAL_DAC_BACKPLANE)
#if MP3_DEBUG
  Serial.println(F("EXTERNAL_DAC_BACKPLANE"));
#endif

  out = new AudioOutputI2S();
#if MP3_DEBUG
  Serial.println(F("after AudioOutputI2S"));
#endif

  // External DAC decoding
  out->SetPinout(TWATCH_DAC_IIS_BCK, TWATCH_DAC_IIS_WS, TWATCH_DAC_IIS_DOUT);
#if MP3_DEBUG
  Serial.printf("after SetPinout(%d, %d, %d)\n", TWATCH_DAC_IIS_BCK, TWATCH_DAC_IIS_WS, TWATCH_DAC_IIS_DOUT);
#endif
#endif
  out->SetGain(4.0 * ((float)255) / 100.0);
  mp3 = new AudioGeneratorMP3();

  mp3->begin(id3, out);

  if (mp3->isRunning())
  {
    if (!mp3->loop())
      mp3->stop();
  }
  else
  {
    Serial.println("playing mp3 done");
  }
  delay(400);
  // power->setPowerOutPut(AXP202_LDO3, AXP202_OFF); */
}
// restart daily step counting
void checkday()
{
  // daily_step = step_counter - minfactor;
  if (cday != tnow.day)
  {
    minfactor = step_counter;
    // daily_step = 0;
    cday = tnow.day;
  }

  daily_step = step_counter - minfactor;
  // if (config.alarm_pray)
  //   setprayalarm(false);
}
template <typename T>
void printArray(ArrayList<T> &list)
{
  for (int i = 0; i < list.size(); i++)
  {
    Serial.print("[" + String(i) + "]: ");
    Serial.println(list[i]);
  }
  Serial.println();
}
void fillFaceList()
{
  // filling list
  faceList.add(12);
  Serial.printf("facelist size  : %d \n", faceList.size());
  if (!faceList.isEmpty())
    faceList.clear();
  if (config.show_number)
    for (size_t i = 0; i < 4; i++)
      faceList.add(i + 2);
  if (config.show_analog)
    for (size_t i = 0; i < 8; i++)
      faceList.add(i + 6);
  if (config.show_text)
    for (size_t i = 0; i < 2; i++)
      faceList.add(i + 12);

  // force fill to avoid error
  if (faceList.size() == 0)
  {
    for (size_t i = 0; i < 4; i++)
      faceList.add(i + 2);
  }

  printArray(faceList);
}