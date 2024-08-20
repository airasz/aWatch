
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
                        int rnd = random(faceList.size());
                        cface = config.rnd_face ? faceList[rnd] : CF;
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
                        Serial.printf("cface  : %d \n", cface);
                }
                if (alarm_active)
                {
                        drawButton(0, 190, 240, 40, COLOR_ACCENT[config.colorAccent], TFT_WHITE, alarm_msg);
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
                startSetting(2); // display
                screenTimeOut = config.screensaver_timeout + 15;
                break;
        case 221:
                pickAccent(); // display
                screenTimeOut = config.screensaver_timeout + 15;
                break;
        case 222:
                startSetting(2); // display
                screenTimeOut = config.screensaver_timeout + 15;
                break;
        case 24:
                startSetting(6);
                screenTimeOut = config.screensaver_timeout + 15;
                break;
        case 25:
                startSetting(7); // setface
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
        // Serial.printf("st out  : %d \n", screenTimeOut);
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
        // tft->setTextColor(tc);
        tft->setTextColor((itsLightColor(bc)) ? TFT_BLACK : TFT_WHITE);
        tft->fillRoundRect(x, y, w, h, 5, bc);
        tft->drawString(txt, x + (w / 2), y + (h / 2), 2);
}
void drawSmoothButton(int x, int y, int w, int h, int fc, int bc, int tc, String txt)
{

        tft->setTextDatum(MC_DATUM);
        // tft->setTextColor(tc);
        tft->setTextColor((itsLightColor(fc)) ? TFT_BLACK : TFT_WHITE);

        // tft->fillRoundRect(x, y, w, h, 5, bc);
        tft->fillSmoothRoundRect(x, y, w, h, 5, fc, bc);
        // tft->fillSmoothRoundRect(x, y, w, h, 5, (itsLightColor(bc)) ? TFT_BLACK : TFT_WHITE, bc);
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
                tft->fillCircle(x + w - 3 - 12, y + 3 + 12, 12, COLOR_ACCENT[config.colorAccent]);
        }
        else
        {
                tft->fillRoundRect(x, y, w, h, r, TFT_BLACK);
                tft->drawRoundRect(x, y, w, h, r, strokeColor);
                // tft->fillCircle(170 + 3 + 12, 70 + 3 + 12, 12, TFT_BLUE);
                tft->fillCircle(x + 3 + 12, y + 3 + 12, 12, COLOR_ACCENT[config.colorAccent]);
        }
}
void drawSmoothSwitch_(int x, int y, int strokeColor, int activeColor, bool enabled)
{
        // size is fixed
        int w = 60;
        int h = 30;
        int r = h / 2;
        if (enabled)
        {
                tft->fillSmoothRoundRect(x, y, w, h, r, TFT_BLACK, TFT_BLACK); // clear area before draw
                tft->drawSmoothRoundRect(x, y, r, r - 2, w, h, COLOR_ACCENT[config.colorAccent], TFT_BLACK);
                // tft->fillSmoothCircle(80, 120, 4, TFT_BLACK, TFT_BLACK);
                tft->fillCircle(x + w - 3 - 12, y + 3 + 12, 12, COLOR_ACCENT[config.colorAccent]);
                // tft->fillSmoothCircle(x + w - 3 - 12, y + 3 + 12, 12, TFT_BLUE, TFT_BLACK);
        }
        else
        {
                // tft->fillRoundRect(x, y, w, h, r, TFT_BLACK);
                // tft->drawRoundRect(x, y, w, h, r, strokeColor);

                // tft->fillCircle(170 + 3 + 12, 70 + 3 + 12, 12, TFT_BLUE);
                // tft->fillCircle(x + 3 + 12, y + 3 + 12, 12, TFT_BLUE);

                tft->fillSmoothRoundRect(x, y, w, h, r, TFT_BLACK, TFT_BLACK); // clear area before draw
                tft->drawSmoothRoundRect(x, y, r, r - 2, w, h, COLOR_ACCENT[config.colorAccent], TFT_BLACK);

                tft->fillSmoothCircle(80, 120, 4, TFT_BLACK, TFT_BLACK);
                // tft->fillSmoothRoundRect(x, y, w, h, r, strokeColor, TFT_BLACK);
                // tft->fillSmoothRoundRect(x + 1, y + 1, w - 2, h - 2, r, TFT_BLACK, strokeColor);

                tft->fillCircle(x + 3 + 12, y + 3 + 12, 12, COLOR_ACCENT[config.colorAccent]);
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

void drawSmoothSwitch(int x, int y, int strokeColor, int activeColor, bool enabled)
{
        // size is fixed
        int w = 60;
        int h = 30;
        int r = h / 2;
        if (enabled)
        {

                tft->fillSmoothRoundRect(x, y, w, h, r, TFT_BLACK, TFT_BLACK); // clear area before draw
                tft->drawSmoothRoundRect(x, y, r, r - 2, w, h, strokeColor, TFT_BLACK);
                tft->fillSmoothRoundRect(x + 3, y + 3, w - 5, h - 5, r, TFT_WHITE, strokeColor); // fill inside
                tft->fillSmoothCircle(x + w - 3 - 12, y + 3 + 12, 10, strokeColor, TFT_WHITE);
        }
        else
        {
                tft->fillSmoothRoundRect(x, y, w, h, r, TFT_BLACK, TFT_BLACK); // clear area before draw
                tft->drawSmoothRoundRect(x, y, r, r - 2, w, h, strokeColor, TFT_BLACK);
                tft->fillSmoothCircle(x + 3 + 12, y + 3 + 12, 10, strokeColor, TFT_BLACK);
        }
}

// bool itsLightColor(int color)
// {
//         int r, g, b;
//         double hsp;

//         r = (color >> 11) & 0x1F;
//         g = (color >> 5) & 0x3F;
//         b = color & 0x1F;
//         r = (r * 255) / 31;
//         g = (g * 255) / 64;
//         b = (b * 255) / 31;

//         // HSP equation
//         hsp = sqrt(0.299 * (r * r) + 0.587 * (g * g) + 0.114 * (b * b));
//         Serial.printf("color  : %d \n", color);
//         Serial.printf("hsp  : %s \n", String(hsp, 2));
//         // Using the HSP value, determine whether the color is light or dark
//         if (hsp > 127.5)
//         {
//                 return true;
//         }
//         else
//         {
//                 return false;
//         }
// }

// create by chatGBT v4
bool itsLightColor(uint16_t color)
{
        // Extract RGB components from 16-bit RGB565 color
        uint8_t red = (color >> 11) & 0x1F;  // 5 bits for red
        uint8_t green = (color >> 5) & 0x3F; // 6 bits for green
        uint8_t blue = color & 0x1F;         // 5 bits for blue

        // Scale the values to 0-255 range
        red = (red * 255) / 31;
        green = (green * 255) / 63;
        blue = (blue * 255) / 31;

        // Calculate perceived brightness (luminance)
        float brightness = 0.299 * red + 0.587 * green + 0.114 * blue;

        // Serial.printf("color  : %d \n", color);
        // Serial.printf("brightness  : %s \n", String(brightness, 2));
        // Determine if the color is light or dark
        return (brightness > 127) ? true : false;
}
