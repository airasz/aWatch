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
                                                // tft->fillCircle(x_start + col * 12, y_start + row * 12, r, colorrnd);
                                                tft->fillSmoothCircle(x_start + col * 12, y_start + row * 12, r, colorrnd, TFT_BLACK);
                                        }
                                        else if (clock_style == 3)
                                        {
                                                tft->fillRoundRect(x_start - r + col * 12, y_start - r + row * 12, r * 2, r * 2, 0, colorrnd);
                                        }
                                        else if (clock_style == 4)
                                        {

                                                int xc = x_start + col * 13 - 1 + (random(5));
                                                int yc = y_start + row * 13 - 1 + (random(5));
                                                xpath[DIGITS[curr_digit][row][col] - 1] = xc; // put  squence path X point to array
                                                ypath[DIGITS[curr_digit][row][col] - 1] = yc; // put  squence path Y point to array

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
                                                // tft->drawCircle(x_start + col * 12, y_start + row * 12, r, colorrnd);

                                                tft->fillSmoothCircle(x_start + col * 12, y_start + row * 12, r, colorrnd, TFT_BLACK);
                                                tft->fillSmoothCircle(x_start + col * 12, y_start + row * 12, r - 1, TFT_BLACK, colorrnd);
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
                // Serial.printf("curr digit  : %d \n", curr_digit);
                if (clock_style == 4)
                {

                        int colll = COLORS_LIGHT[rnd];
                        int bcoll = TFT_BLACK;
                        // tft->drawLine(0, 0, 1, 1, TFT_BLACK);
                        tft->drawLine(246, 246, 248, 248, colll);
                        for (int i = 0; i < 19; i++)
                        {
                                // Serial.printf(" xpath[%d] : %d ", i, xpath[i]);
                                // Serial.print("\n");
                                if (xpath[i + 1] != 0)
                                {
                                        if (curr_digit == 0)
                                        {
                                                //   tft->drawBoldSmoothLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], 4, colll);
                                                tft->drawWideLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], 10, colll, bcoll);
                                                if (i > 0)
                                                        tft->drawBoldSmoothLine(xpath[i - 1], ypath[i - 1], xpath[i], ypath[i], 4, colll);
                                                if (i == 1)
                                                        tft->drawBoldSmoothLine(xpath[i - 1], ypath[i - 1], xpath[15], ypath[15], 4, colll);

                                                // tft->drawLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], colll);
                                                if (i == 0)
                                                        //   tft->drawBoldSmoothLine(xpath[i], ypath[i], xpath[15], ypath[15], 4, colll);
                                                        tft->drawWideLine(xpath[i], ypath[i], xpath[15], ypath[15], 10, colll, bcoll);
                                                // tft->drawLine(xpath[i], ypath[i], xpath[15], ypath[15], colll);
                                        }
                                        else if (curr_digit == 1)
                                        {
                                                if (i == 6)
                                                {
                                                        //   tft->drawBoldSmoothLine(xpath[i], ypath[i], xpath[9], ypath[9], 4, colll);
                                                        tft->drawWideLine(xpath[i], ypath[i], xpath[9], ypath[9], 10, colll, bcoll);
                                                        // tft->drawLine(xpath[i], ypath[i], xpath[9], ypath[9], colll);}
                                                }
                                                else
                                                { //   tft->drawBoldSmoothLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], 4, colll);

                                                        if (i == 7)
                                                        {
                                                                tft->drawBoldSmoothLine(xpath[i - 2], ypath[i - 2], xpath[6], ypath[6], 4, colll);
                                                        }
                                                        tft->drawWideLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], 10, colll, bcoll);
                                                        if (i > 0 && i - 1 != 6)
                                                                tft->drawBoldSmoothLine(xpath[i - 1], ypath[i - 1], xpath[i], ypath[i], 4, colll);
                                                        // tft->drawLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], colll);}
                                                }
                                        }
                                        else if (curr_digit == 3)
                                        {
                                                if (i != 7)
                                                {
                                                        // tft->drawLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], colll);
                                                        tft->drawWideLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], 10, colll, bcoll);
                                                        if (i > 0 && i - 1 != 7)
                                                                tft->drawBoldSmoothLine(xpath[i - 1], ypath[i - 1], xpath[i], ypath[i], 4, colll);
                                                        //   tft->drawBoldSmoothLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], 4, colll);
                                                        if (i == 8)
                                                                //   tft->drawBoldSmoothLine(xpath[i], ypath[i], xpath[8], ypath[8], 4, colll);
                                                                tft->drawWideLine(xpath[i - 2], ypath[i - 2], xpath[8], ypath[8], 10, colll, bcoll);
                                                        if (i == 9)
                                                        {
                                                                tft->drawBoldSmoothLine(xpath[6], ypath[6], xpath[7], ypath[7], 4, colll);
                                                                tft->drawBoldSmoothLine(xpath[6], ypath[6], xpath[5], ypath[5], 4, colll);
                                                        }
                                                        // tft->drawLine(xpath[i], ypath[i], xpath[8], ypath[8], colll);
                                                }

                                                else // i==7
                                                        tft->drawBoldSmoothLine(xpath[i - 1], ypath[i - 1], xpath[8], ypath[8], 4, colll);
                                        }
                                        else if (curr_digit == 8)
                                        {
                                                // tft->drawLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], colll);
                                                tft->drawWideLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], 10, colll, bcoll);
                                                if (i > 0)
                                                        tft->drawBoldSmoothLine(xpath[i - 1], ypath[i - 1], xpath[i], ypath[i], 4, colll);

                                                //   tft->drawBoldSmoothLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], 4, colll);
                                                if (i == 0)
                                                        //   tft->drawBoldSmoothLine(xpath[i], ypath[i], xpath[9], ypath[9], 4, colll);
                                                        tft->drawWideLine(xpath[i], ypath[i], xpath[9], ypath[9], 10, colll, bcoll);
                                                // tft->drawLine(xpath[i], ypath[i], xpath[9], ypath[9], colll);
                                                if (i == 1)
                                                //   tft->drawBoldSmoothLine(xpath[i], ypath[i], xpath[16], ypath[16], 4, colll);
                                                {
                                                        tft->drawWideLine(xpath[i], ypath[i], xpath[16], ypath[16], 10, colll, bcoll);
                                                        tft->drawBoldSmoothLine(xpath[i - 1], ypath[i - 1], xpath[9], ypath[9], 4, colll);
                                                }
                                                if (i == 2)
                                                        tft->drawBoldSmoothLine(xpath[i - 1], ypath[i - 1], xpath[16], ypath[16], 4, colll);
                                                if (i == 15)
                                                {
                                                        tft->drawBoldSmoothLine(xpath[1], ypath[1], xpath[16], ypath[16], 4, colll);
                                                        tft->drawBoldSmoothLine(xpath[0], ypath[0], xpath[1], ypath[1], 4, colll);
                                                        tft->drawBoldSmoothLine(xpath[0], ypath[0], xpath[9], ypath[9], 4, colll);
                                                }
                                                // tft->drawLine(xpath[i], ypath[i], xpath[16], ypath[16], colll);
                                        }
                                        else
                                        {
                                                // tft->drawLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], colll);
                                                tft->drawWideLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], 10, colll, bcoll);
                                                if (i > 0)
                                                        tft->drawBoldSmoothLine(xpath[i - 1], ypath[i - 1], xpath[i], ypath[i], 4, colll);
                                                // tft->drawWideLine(xpath[-i], ypath[-i], xpath[i], ypath[i], 6, colll, bcoll);
                                                // tft->drawBoldSmoothLine(xpath[i], ypath[i], xpath[i + 1], ypath[i + 1], 4, colll);
                                        }
                                }
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
