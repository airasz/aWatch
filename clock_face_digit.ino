#include "res.h"
// #include "global.h"
// #include "clock_face_digit.h"
// #include "aWatch.h"
// TTGOClass *ttgo;

// RTC_Date tnow;

void face(int face)
{
        if (face == 0)
        {

                // info
        }
        else if (face == 1)
        {
                // pedometer
                recordActivity();
        }
        else if (face > 1 && face < 6)
        {
                clock_face_digit(face);
        }
        else
        {
                analogClockVariant(face);
        }
}
void clock_face_digit(int clock_style)
{
        // ttgo = TTGOClass::getWatch();
        // ttgo->begin();
        // tft = ttgo->tft; // just a shorthand for ttgo->tft
        int count = 0;
        tft->fillScreen(TFT_BLACK);
        tft->setTextSize(1);

        count = hh * 100 + mm;
        // startTime = loopTime;
        auto x_start = (clock_style < 4) ? 60 : 50;
        auto x_delta = (clock_style < 4) ? 70 : 60;
        auto r = (clock_style < 4) ? 5 : 14;

        int rd = random(2);

        int y2 = 11;

        // Serial.printf("testgigit %d\n",testgigit);
        int y_start = 10; // y position of number
        for (int pos = 0; pos < 4; pos++)
        {
                uint8_t curr_digit = 0;
                if (pos == 0)
                {
                        curr_digit = count / 1000;
                }
                else if (pos == 1)
                {
                        curr_digit = count / 100 % 10;
                }
                else if (pos == 2)
                {
                        curr_digit = count / 10 % 10;
                }
                else if (pos == 3)
                {
                        curr_digit = count % 10;
                }
                int rnd = random(10);
                int xpath[20];
                int ypath[20];
                for (int i = 0; i < 20; i++)
                        xpath[i] = 0, ypath[i] = 0;

                for (int row = 0; row < 7; row++)
                {
                        for (int col = 0; col < 5; col++)
                        {
                                uint32_t color = DIGITS[curr_digit][row][col] ? COLORS_LIGHT[curr_digit] : COLORS_DARK[curr_digit];
                                uint32_t colorrnd = DIGITS[curr_digit][row][col] ? COLORS_LIGHT[rnd] : COLORS_DARK[rnd];
                                if (DIGITS[curr_digit][row][col] > 0)
                                {
                                        if (clock_style == 2)
                                        {
                                                tft->fillCircle(x_start + col * 12, y_start + row * 12, r, colorrnd);
                                        }
                                        else if (clock_style == 3)
                                        {
                                                tft->fillRoundRect(x_start - r + col * 12, y_start - r + row * 12, r * 2, r * 2, 0, colorrnd);
                                        }
                                        else if (clock_style == 4)
                                        {

                                                int xc = x_start + col * 13 - 1 + (random(5));
                                                int yc = y_start + row * 13 - 1 + (random(5));
                                                xpath[DIGITS[curr_digit][row][col] - 1] = xc;
                                                ypath[DIGITS[curr_digit][row][col] - 1] = yc;

                                                // tft->fillCircle(x_start + col * 13 - 1 + random(4), y_start + row * 13 - 1 + random(4), r + 2, colorrnd);
                                                // tft->fillCircle(x_start + col * 7 -1+random(4), y_start + row * 7-1+random(4), 3, BLACK);
                                                // tft->fillCircle(x_start + col * 7 -1+random(4), y_start + row * 7-1+random(4), r, colorrnd);
                                        }
                                        else if (clock_style == 5)
                                        {
                                                tft->fillRoundRect(x_start - r + col * 12, y_start - r + row * 12, r + 4, r + 4, 0, colorrnd);
                                        }
                                }
                                else
                                {
                                        if (clock_style == 3)
                                        {
                                                tft->drawRoundRect(x_start - r + col * 12, y_start - r + row * 12, r * 2, r * 2, 0, colorrnd);
                                        }
                                        else if (clock_style == 2)
                                        {
                                                tft->drawCircle(x_start + col * 12, y_start + row * 12, r, colorrnd);
                                        }
                                        else if (clock_style == 5)
                                        {
                                                tft->drawRoundRect(x_start - r + col * 13, y_start - r + row * 13, r + 4, r + 4, 0, colorrnd);
                                        }
                                        else if (clock_style == 4)
                                        {
                                                // tft->drawCircle(x_start + col * 7, y_start + row * 7, r, colorrnd);
                                        }
                                }
                                // delay(2);
                                // tft->fillRect (x_start + col * 7, y_start + row * 7, r, colorrnd);
                                // RGB565 = (((RGB888&0xf80000)>>8) + ((RGB888&0xfc00)>>5) + ((RGB888&0xf8)>>3));
                        }
                }
                if (clock_style == 4)
                {
                        int colll = COLORS_LIGHT[rnd];
                        for (int i = 0; i < 19; i++)
                        {
                                // Serial.printf(" xpath[%d] : %d ", i, xpath[i]);
                                // Serial.print("\n");
                                if (xpath[i + 1] != 0)
                                        tft->drawLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], colll);
                        }
                }
                (pos == 1) ? x_start = 60 : x_start += 65;
                if (pos == 1)
                {
                        x_start = (clock_style > 3 ? 50 : 60);
                }
                else
                {
                        x_delta += 65;
                }
                if (pos == 1)
                        y_start += 100;
                // space betwen single digit
        }
        displaySysInfo(2); // appInfo.ino
}
