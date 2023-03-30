
// #include "clock_face_digit.h"

// #include "prayTask.h"
//                    / 10.   info
// 0=home<
//                     \30.  setting

void updateScreen(int dis_ID)
{
        // call every screen touched
        resetTO(); // recount timeout
        switch (dis_ID)
        {
        case 0:
                if (config.pedometer_enable)
                {
                        // clock_face_digit(11);
                        face(1); // clock_face_digit.ino
                }
                else
                {
                        int cface;
                        // (config.rnd_face) ? cface = random(0, 11) : cface = CF;
                        // screenTimeOut = cface == 10 ? config.screensaver_timeout + 5 : config.screensaver_timeout;

                        // (config.rnd_face) ? cface = random(2, 13) : cface = CF;
                        cface = config.rnd_face ? random(2, 13) : CF;
                        screenTimeOut = cface == 10 ? config.screensaver_timeout + 5 : config.screensaver_timeout;
                        // if (cface == 10)
                        // {
                        //         screenTimeOut = config.screensaver_timeout + 5;
                        // }
                        // else
                        // {
                        //         screenTimeOut = config.screensaver_timeout;
                        // }

                        // Serial.printf("Screentimeout gui  : %d \n", screenTimeOut);
                        // clock_face_digit(cface);
                        face(cface); // clock_face_digit.ino
                }
                if (alarm_active)
                {
                        drawButton(0, 190, 240, 40, TFT_BLUE, TFT_WHITE, alarm_msg);
                }
                break;
        case 1:
                showDayPray();
                break;
        case 2:
                startSetting(0);
                break;
        case 3:
                showCal();
                break;
        case 11:
                sysinfo();
                break;
        case 21:
                startSetting(1);
                break;
        case 22:
                startSetting(2);
                break;
        case 24:
                startSetting(6);
                break;
        case 25:
                startSetting(7);
                break;
        case 26:
                startSetting(8);
                break;
        case 27:
                startSetting(9); // to app remote select AC
                break;
        case 31:
                showCal(true); // show next month
                break;

        case 32:
                showCal(false); // show previous month
                break;

        case 231:
                startSetting(3);
                break;
        case 232:
                startSetting(4);
                break;
        case 233:
                startSetting(5);
                break;
        default:
                break;
        }
}

void resetTO()
{
        last_activity = millis();
}
void toast(String msg)
{
        // tft->fillRoundRect(60, 60, 120, 60, 5, TFT_BLUE);
        tft->setTextFont(2);
        tft->setTextColor(TFT_GREEN, TFT_BLUE);
        tft->setCursor(65, 65);
        // tft->print(msg);
        tft->setTextDatum(MC_DATUM);
        tft->setTextPadding(tft->width() - 80);
        tft->drawString(msg, 120, 80, 2);
}
//============widget=========
void drawButton(int x, int y, int w, int h, int bc, int tc, String txt)
{

        tft->setTextDatum(MC_DATUM);
        tft->setTextColor(tc);
        tft->fillRoundRect(x, y, w, h, 5, bc);
        tft->drawString(txt, x + (w / 2), y + (h / 2), 2);
}
void drawOutlineButton(int x, int y, int w, int h, int bc, int tc, String txt)
{

        tft->setTextDatum(MC_DATUM);
        tft->setTextColor(tc);
        tft->drawRoundRect(x, y, w, h, 5, bc);
        tft->drawString(txt, x + (w / 2), y + (h / 2), 2);
}
void drawSwitch(int x, int y, int strokeColor, int activeColor, bool enabled)
{
        // size is fixed
        int w = 60;
        int h = 30;
        int r = h / 2;
        if (enabled)
        {
                tft->fillRoundRect(x, y, w, h, r, activeColor);
                tft->drawRoundRect(x, y, w, h, r, strokeColor);
                tft->fillCircle(x + w - 3 - 12, y + 3 + 12, 12, TFT_BLUE);
        }
        else
        {
                tft->fillRoundRect(x, y, w, h, r, TFT_BLACK);
                tft->drawRoundRect(x, y, w, h, r, strokeColor);
                // tft->fillCircle(170 + 3 + 12, 70 + 3 + 12, 12, TFT_BLUE);
                tft->fillCircle(x + 3 + 12, y + 3 + 12, 12, TFT_BLUE);
        }
}