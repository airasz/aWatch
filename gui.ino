
// #include "clock_face_digit.h"

// #include "prayTask.h"
//                    / 10.   info
// 0=home<
//                     \30.  setting

// by pageID
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
                        cface = config.rnd_face ? random(2, 15) : CF;
                        screenTimeOut = cface == 1 ? config.screensaver_timeout + 5 : config.screensaver_timeout;
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
                screenTimeOut = config.screensaver_timeout + 8;
                break;
        case 2:
                startSetting(0);
                screenTimeOut = config.screensaver_timeout + 15;
                break;
        case 3:
                showCal();
                screenTimeOut = config.screensaver_timeout + 8;
                break;
        case 11:
                sysinfo();
                screenTimeOut = config.screensaver_timeout + 8;
                break;
        case 21:
                startSetting(1);
                screenTimeOut = config.screensaver_timeout + 15;
                break;
        case 22:
                startSetting(2);
                screenTimeOut = config.screensaver_timeout + 15;
                break;
        case 24:
                startSetting(6);
                screenTimeOut = config.screensaver_timeout + 15;
                break;
        case 25:
                startSetting(7);
                screenTimeOut = config.screensaver_timeout + 15;
                break;
        case 26:
                startSetting(8);
                screenTimeOut = config.screensaver_timeout + 15;
                break;
        case 27:
                startSetting(9); // to app remote select AC
                screenTimeOut = config.screensaver_timeout + 15;
                break;
        case 271:
                startSetting(10); // to panasonic
                screenTimeOut = config.screensaver_timeout + 15;
                break;
        case 272:
                startSetting(11); // to panasonic
                screenTimeOut = config.screensaver_timeout + 15;
                break;
        case 31:
                showCal(true); // show next month
                screenTimeOut = config.screensaver_timeout + 8;
                break;

        case 32:
                showCal(false); // show previous month
                screenTimeOut = config.screensaver_timeout + 8;
                break;

        case 231:
                startSetting(3);
                screenTimeOut = config.screensaver_timeout + 15;
                break;
        case 232:
                startSetting(4);
                screenTimeOut = config.screensaver_timeout + 15;
                break;
        case 233:
                startSetting(5);
                screenTimeOut = config.screensaver_timeout + 15;
                break;
        default:
                break;
        }

        screenTimeOut = dis_ID != 0 ? config.screensaver_timeout + 15 : config.screensaver_timeout;
        Serial.printf("st out  : %d \n", screenTimeOut);
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
void drawSmoothButton(int x, int y, int w, int h, int fc, int bc, int tc, String txt)
{

        tft->setTextDatum(MC_DATUM);
        tft->setTextColor(tc);
        // tft->fillRoundRect(x, y, w, h, 5, bc);
        tft->fillSmoothRoundRect(x, y, w, h, 5, fc, bc);
        tft->drawString(txt, x + (w / 2), y + (h / 2), 2);
}
void drawOutlineButton(int x, int y, int w, int h, int bc, int tc, String txt)
{

        tft->setTextDatum(MC_DATUM);
        tft->setTextColor(tc);
        tft->drawRoundRect(x, y, w, h, 5, bc);
        tft->drawString(txt, x + (w / 2), y + (h / 2), 2);
}
void drawSmoothOutlineButton(int x, int y, int w, int h, int bc, int tc, String txt)
{

        tft->setTextDatum(MC_DATUM);
        tft->setTextColor(tc);
        // tft->drawRoundRect(x, y, w, h, 5, bc);
        tft->drawSmoothRoundRect(x, y, 5, 5 - 1, w, h, bc, TFT_BLACK);
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
void drawSmoothSwitch(int x, int y, int strokeColor, int activeColor, bool enabled)
{
        // size is fixed
        int w = 60;
        int h = 30;
        int r = h / 2;
        if (enabled)
        {
                // tft->fillRoundRect(x, y, w, h, r, activeColor);
                // tft->drawRoundRect(x, y, w, h, r, strokeColor);
                // tft->drawSmoothRoundRect(x, y, r, r - 2, w, h, strokeColor, TFT_BLACK);

                // tft->fillSmoothRoundRect(x, y, w, h, r, strokeColor, TFT_BLACK);
                // tft->fillSmoothRoundRect(x + 1, y + 1, w - 2, h - 2, r, TFT_WHITE, strokeColor);

                tft->fillSmoothRoundRect(x, y, w, h, r, TFT_BLACK, TFT_BLACK); // clear area before draw
                tft->drawSmoothRoundRect(x, y, r, r - 2, w, h, strokeColor, TFT_BLACK);
                // tft->fillSmoothCircle(80, 120, 4, TFT_BLACK, TFT_BLACK);
                tft->fillCircle(x + w - 3 - 12, y + 3 + 12, 12, TFT_BLUE);
                // tft->fillSmoothCircle(x + w - 3 - 12, y + 3 + 12, 12, TFT_BLUE, TFT_BLACK);
        }
        else
        {
                // tft->fillRoundRect(x, y, w, h, r, TFT_BLACK);
                // tft->drawRoundRect(x, y, w, h, r, strokeColor);

                // tft->fillCircle(170 + 3 + 12, 70 + 3 + 12, 12, TFT_BLUE);
                // tft->fillCircle(x + 3 + 12, y + 3 + 12, 12, TFT_BLUE);

                tft->fillSmoothRoundRect(x, y, w, h, r, TFT_BLACK, TFT_BLACK); // clear area before draw
                tft->drawSmoothRoundRect(x, y, r, r - 2, w, h, strokeColor, TFT_BLACK);

                tft->fillSmoothCircle(80, 120, 4, TFT_BLACK, TFT_BLACK);
                // tft->fillSmoothRoundRect(x, y, w, h, r, strokeColor, TFT_BLACK);
                // tft->fillSmoothRoundRect(x + 1, y + 1, w - 2, h - 2, r, TFT_BLACK, strokeColor);

                tft->fillCircle(x + 3 + 12, y + 3 + 12, 12, TFT_BLUE);
                // tft->fillSmoothCircle(x + 3 + 12, y + 3 + 12, 12, TFT_BLUE, TFT_BLACK);
        }
}
void drawSmoothSwitch2(int x, int y, int strokeColor, int activeColor, bool enabled)
{
        // size is fixed
        int w = 60;
        int h = 30;
        int r = h / 2;
        if (enabled)
        {
                // tft->fillRoundRect(x, y, w, h, r, activeColor);
                // tft->drawRoundRect(x, y, w, h, r, strokeColor);
                tft->drawSmoothRoundRect(x, y, r, r - 2, w, h, strokeColor, TFT_BLACK);

                // tft->fillSmoothRoundRect(x, y, w, h, r, strokeColor, TFT_BLACK);
                // tft->fillSmoothRoundRect(x + 1, y + 1, w - 2, h - 2, r, TFT_WHITE, strokeColor);

                tft->fillSmoothRoundRect(x, y, w, h, r, TFT_BLACK, TFT_WHITE); // clear area before draw
                tft->drawSmoothRoundRect(x, y, r, r - 2, w, h, strokeColor, TFT_BLACK);
                // tft->fillCircle(x + w - 3 - 12, y + 3 + 12, 12, TFT_BLUE);
                tft->fillSmoothCircle(x + w - 3 - 12, y + 3 + 12, 12, TFT_BLUE, TFT_WHITE);
        }
        else
        {
                // tft->fillRoundRect(x, y, w, h, r, TFT_BLACK);
                // tft->drawRoundRect(x, y, w, h, r, strokeColor);

                // tft->fillCircle(170 + 3 + 12, 70 + 3 + 12, 12, TFT_BLUE);
                // tft->fillCircle(x + 3 + 12, y + 3 + 12, 12, TFT_BLUE);

                tft->fillSmoothRoundRect(x, y, w, h, r, TFT_BLACK, TFT_BLACK); // clear area before draw
                tft->drawSmoothRoundRect(x, y, r, r - 2, w, h, strokeColor, TFT_BLACK);

                // tft->fillSmoothRoundRect(x, y, w, h, r, strokeColor, TFT_BLACK);
                // tft->fillSmoothRoundRect(x + 1, y + 1, w - 2, h - 2, r, TFT_BLACK, strokeColor);

                tft->fillCircle(x + 3 + 12, y + 3 + 12, 12, TFT_BLUE);
                // tft->fillSmoothCircle(x + 3 + 12, y + 3 + 12, 12, TFT_BLUE, TFT_BLACK);
        }
}