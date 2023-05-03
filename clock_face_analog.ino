

// #include "aWatch.h"
int hh12;
// convert html rgb to rgb565
int rgbToHex(uint8_t r, uint8_t g, uint8_t b)
{
        uint32_t rgb = ((uint32_t)r << 16) | ((uint32_t)g << 8) | (long)b;
        uint16_t rgb565 = (((rgb & 0xf80000) >> 8) | ((rgb & 0xfc00) >> 5) | ((rgb & 0xf8) >> 3));
        return rgb565;
}

// void updateClock();
//=========================================================================

void analogClockVariant(int v)
{
        int wipetracelong, px, dgree, old_rnddot;
        long dmCover; // daily distance covered
        int nday = tnow.day,
            nmonth = tnow.month,
            nyear = tnow.year, g = 250;
        String const dw[] = {"MGG", "SEN", "SEL", "RBU", "KMS", "JMT", "SBT"};
        int dow = ttgo->rtc->getDayOfWeek(nday, nmonth, nyear);
        // Serial.printf(" day of week : %d \n", dow);
        hh = tnow.hour;
        mm = tnow.minute;
        ss = tnow.second;
        int plygon;
        v -= 6;
        switch (v)
        {
        case 0:
                // face=6
                tft->fillScreen(TFT_BLACK); // CLEAR DISPLAY
                tft->setTextColor(TFT_WHITE, TFT_BLACK);
                // int colorRandomMedium = COLOR_MEDIUM[random(10)];
                // tft->drawCircle(120, 120, 80, COLOR_MEDIUM[random(10)]);

                tft->drawSmoothCircle(120, 120, 82, COLOR_MEDIUM[random(10)], TFT_BLACK);
                // tft->fillSmoothCircle(120, 120, 80, COLOR_MEDIUM[random(10)], COLOR_MEDIUM[random(10)]);
                tft->fillSmoothCircle(120, 120, 80, COLORS_DARK[random(10)], TFT_BLACK);
                // tft->fillCircle( 160, 120, 118, TFT_GREEN);            // CLOCK FACE
                // tft->fillCircle( 160, 120, 110, TFT_BLACK);
                // colorRandomMedium = COLOR_MEDIUM[random(10)];          // LOCK FACE           // LOCK FACE
                // 12 LINES
                // rainbow color for every multiple 5  minute mark
                for (int i = 0; i < 360; i += 30)
                        tft->drawLine(posX(80, i), posY(80, i), posX(72, i), posY(72, i), COLOR_MEDIUM[random(10)]); // DRAW 12 LINES

                // 60 DOTS
                for (int i = 0; i < 360; i += 6)
                {
                        tft->drawPixel(posX(78, i), posY(79, i), COLOR_MEDIUM[random(10)]); // MINUTE DOT
                        // tft->fillCircle(x0, yy0, 2, COLOR_MEDIUM[random(10)]);

                        if (i % 90 == 0)
                                tft->fillCircle(posX(78, i), posY(79, i), 3, TFT_WHITE); // DOTS
                }
                // middle dot
                tft->fillCircle(120, 120, 3, TFT_RED);
                // Serial.printf("hh=%01d, mm=%02d, ss=%03d\n",hh,mm,ss);
                sdeg = ss * 6;                     // 0-59 -> 0-354   Pre-compute
                mdeg = mm * 6 + sdeg * 0.01666667; // 0-59 -> 0-360 - includes seconds
                hdeg = hh * 30 + mdeg * 0.0833333; // 0-11 -> 0-360 - inc min and seconds

                tft->drawLine(posX(50, hdeg), posY(50, hdeg), 120, 120, COLOR_MEDIUM[random(10)]); // DRAW  HOUR
                tft->drawLine(posX(61, mdeg), posY(61, mdeg), 120, 120, COLOR_MEDIUM[random(10)]); // DRAW  MIN

                // tft->fillCircle(120, 120, 5, TFT_RED); // DOT   CENTER

                tft->fillSmoothCircle(120, 120, 6, TFT_RED, TFT_BLACK);
                // tft->fillSmoothCircle(120, 120, 77, TFT_BLACK, TFT_RED);
                displaySysInfo(0); // appInfo.ino
                break;

        case 1:
                // arc progress. face=7
                tft->fillScreen(TFT_BLACK); // CLEAR DISPLAY
                tft->setTextColor(TFT_WHITE, TFT_BLACK);
                hh12 = hh >= 12 ? hh - 12 : hh;
                sdeg = ss * 6;                       // 0-59 -> 0-354   Pre-compute
                mdeg = mm * 6 + sdeg * 0.01666667;   // 0-59 -> 0-360 - includes seconds
                hdeg = hh12 * 30 + mdeg * 0.0833333; // 0-11 -> 0-360 - inc min and seconds
                // int startMAngle, endMAngle, startHAngle, endHAngle;
                // clock degree is oposite position to arc degre
                //  convert 24 to 12 hours format
                //  progress minute
                if (mm >= 30)
                {
                        // drawSmoothArc(x, y, out_radius, in_radius, start_angle, end_angle, fcolor, bcolor, rooudend);//flse
                        tft->drawSmoothArc(120, 120, 84, 76, mdeg - 180, 180, TFT_RED, TFT_BLACK, false);
                        // for (int i = (mm * 6); i < 360; i++)
                        //         tft->drawLine(posX(80, i), posY(80, i), posX(72, i), posY(72, i) + 1, TFT_RED);
                        // for (int i = 0 + 2; i < (mm * 6) - 3; i++)
                        //         tft->fillCircle(posX(76, i), posY(76, i), 2, TFT_BLACK);
                }
                else
                {
                        tft->drawSmoothArc(120, 120, 84, 76, 180, 180 + mdeg, TFT_RED, TFT_BLACK, false);

                        // for (int i = 0 + 2; i < (mm * 6) - 3; i++)
                        //         tft->fillCircle(posX(76, i), posY(76, i), 2, TFT_RED);
                        // for (int i = (mm * 6); i < 360; i++)
                        //         tft->drawLine(posX(78, i), posY(78, i), posX(72, i), posY(72, i) + 1, TFT_BLACK);
                }

                // progress hour
                if (hh12 >= 6)
                {
                        tft->drawSmoothArc(120, 120, 66, 74, hdeg - 180, 180, TFT_BLUE, TFT_BLACK, false);

                        // for (int i = ((hh12 * 30) + (mm / 2)) - 1; i < 360; i++)
                        //         tft->drawLine(posX(74, i), posY(74, i) + 1, posX(66, i), posY(66, i) + 1, TFT_BLUE);
                }
                else
                {
                        tft->drawSmoothArc(120, 120, 66, 74, 180, 180 + hdeg, TFT_BLUE, TFT_BLACK, false);

                        // for (int i = 0; i < ((hh12 * 30) + (mm / 2)) - 1; i++)
                        //         tft->drawLine(posX(74, i), posY(74, i) + 1, posX(66, i), posY(66, i) + 1, TFT_BLUE);
                }

                // 12 LINES
                for (int i = 0; i < 360; i += 30)
                {
                        tft->drawLine(posX(74, i), posY(74, i) + 1, posX(66, i), posY(66, i) + 1, TFT_WHITE);
                        if (i % 90 == 0)
                                tft->drawLine(posX(74, i), posY(74, i) + 1, posX(60, i), posY(60, i) + 1, TFT_WHITE);
                }

                displaySysInfo(0); // appInfo.ino

                // Serial.printf("ohx=%01d, ohy=%02d, \n", ohx, ohy);
                // Serial.printf("omx=%01d, omy=%02d, \n", omx, omy);
                break;

        case 2:
                // comet race mode. face =8
                // Serial.printf("hh=%01d, mm=%02d, ss=%03d\n", hh, mm, ss);
                tft->fillScreen(TFT_BLACK); // CLEAR DISPLAY
                tft->setTextColor(TFT_WHITE, TFT_BLACK);
                // int colorRandomMedium = COLOR_MEDIUM[random(10)];
                // tft->drawCircle(120, 120, 80, TFT_PURPLE);
                // tft->drawCircle(120, 120, 70, TFT_BLUE);
                // tft->drawCircle(120, 120, 60, TFT_BLUE);

                // tft->fillSmoothCircle(120, 120, 80, TFT_PURPLE, TFT_BLACK);
                // tft->fillSmoothCircle(120, 120, 79, TFT_BLACK, TFT_PURPLE);
                tft->drawSmoothCircle(120, 120, 80, COLOR_MEDIUM[random(10)], TFT_BLACK);

                // tft->fillSmoothCircle(120, 120, 70, TFT_BLUE, TFT_BLACK);
                // tft->fillSmoothCircle(120, 120, 69, TFT_BLACK, TFT_BLUE);
                tft->drawSmoothCircle(120, 120, 70, COLOR_MEDIUM[random(10)], TFT_BLACK);

                // tft->fillSmoothCircle(120, 120, 60, TFT_BLUE, TFT_BLACK);
                // tft->fillSmoothCircle(120, 120, 59, TFT_BLACK, TFT_BLUE);
                tft->drawSmoothCircle(120, 120, 60, COLOR_MEDIUM[random(10)], TFT_BLACK);

                // dot hour
                for (int t = 15; t > (-1); t--)
                {
                        g = 255 - (t * 17); // create gradient squences dark to bright
                        dgree = ((hh * 30) + (mm / 2)) - t;
                        tft->fillCircle(posX(65, dgree), posY(65, dgree), 2, rgbToHex(0, 0, g));
                }

                // dot minutes
                for (int t = 15; t > (-1); t--)
                {
                        g = 255 - (t * 17); // create gradient squences dark to bright
                        dgree = (mm * 6) - t;
                        // tft->fillCircle((getCos(dgree) * 75) + 120, (getSin(dgree) * 75) + 120, 2, rgbToHex(g, 0, 0));
                        tft->fillCircle(posX(75, dgree), posY(75, dgree), 2, rgbToHex(g, 0, 0));
                }

                // tft->drawLine((getCos(0) * 78) + 120, (getSin(0) * 78) + 120, (getCos(0) * 68) + 120, (getSin(0) * 88) + 120, COLOR_MEDIUM[random(10)]); // DRAW 12 LINES
                tft->drawLine(posX(78, 0), posY(78, 0), posX(68, 0), posY(68, 0), COLOR_MEDIUM[random(10)]); // DRAW 12 LINES

                displaySysInfo(0); // appInfo.ino
                // Serial.printf("hh=%01d, mm=%02d, ss=%03d\n", hh, mm, ss);

                break;

        case 3:
                // marine radar. face =9
                tft->fillScreen(TFT_BLACK); // CLEAR DISPLAY
                tft->setTextColor(TFT_WHITE, TFT_BLACK);
                // int colorRandomMedium = COLOR_MEDIUM[random(10)];
                // tft->drawCircle(120, 120, 80, TFT_GREEN);
                tft->fillSmoothCircle(120, 120, 80, TFT_GREEN, TFT_BLACK);
                tft->fillSmoothCircle(120, 120, 77, TFT_BLACK, TFT_GREEN);

                // tft->drawCircle(120, 120, 60, 0x0140);
                // tft->drawCircle(120, 120, 40, 0x0140);
                // tft->drawCircle(120, 120, 20, 0x0140);

                tft->drawSmoothCircle(120, 120, 60, 0x0140, TFT_BLACK);
                tft->drawSmoothCircle(120, 120, 40, 0x0140, TFT_BLACK);
                tft->drawSmoothCircle(120, 120, 20, 0x0140, TFT_BLACK);
                // tft->fillSmoothCircle(120, 120, 60, 0x0140, TFT_BLACK);
                // tft->fillSmoothCircle(120, 120, 59, TFT_BLACK, 0x0140);
                // tft->fillSmoothCircle(120, 120, 40, 0x0140, TFT_BLACK);
                // tft->fillSmoothCircle(120, 120, 39, TFT_BLACK, 0x0140);
                // tft->fillSmoothCircle(120, 120, 20, 0x0140, TFT_BLACK);
                // tft->fillSmoothCircle(120, 120, 19, TFT_BLACK, 0x0140);
                tnow = ttgo->rtc->getDateTime();
                hh = tnow.hour;
                mm = tnow.minute;

                // dot hour pretend deetected object
                dgree = ((hh * 30) + (mm / 2)) - 1;
                // tft->fillCircle((getCos(dgree) * random(50, 76)) + 120, (getSin(dgree) * random(50, 76)) + 120, 2, rgbToHex(200, 225, 180));
                tft->fillCircle(posX(random(50, 76), dgree), posY(random(50, 76), dgree), 2, rgbToHex(200, 225, 180));

                // dot minutes
                //  12 LINES (minutes step)
                for (int i = 0; i < 360; i += 30)
                {
                        sx = cos((i - 90) * 0.0174532925);
                        sy = sin((i - 90) * 0.0174532925);
                        x0 = sx * 37 + 40;
                        yy0 = sy * 37 + 40;
                        x1 = sx * 29 + 40;
                        yy1 = sy * 29 + 40;
                        //   tft->drawLine(x0, yy0, x1, yy1,  COLOR_MEDIUM[random(10)]);          // DRAW 12 LINES
                }

                // 4 LINES (12,3,6,9)
                for (int i = 0; i < 360; i += 30)
                {
                        if (i % 90 == 0)
                                tft->drawLine(posX(78, i), posY(78, i) + 1, 120, 121, 0x0140);

                        // tft->drawLine((getCos(i) * 78) + 120, (getSin(i) * 78) + 121, (getCos(i) * 0) + 120, (getSin(0) * 0) + 121, 0x0140);
                }

                sdeg = ss * 6;                     // 0-59 -> 0-354   Pre-compute
                mdeg = mm * 6 + sdeg * 0.01666667; // 0-59 -> 0-360 - includes seconds
                // hdeg = hh * 30 + mdeg * 0.0833333; // 0-11 -> 0-360 - inc min and seconds
                wipetracelong = 4;
                for (int t = 50; t > (-1); t--)
                {
                        g = 150 - (t * 3);
                        dgree = mdeg - (t * wipetracelong);
                        tft->drawLine(posX(76, dgree), posY(80, dgree), 120, 120, rgbToHex(t == 0 ? 200 : 0, t == 0 ? 255 : g, 0)); // Draw shadow swiper
                }
                displaySysInfo(1); // appInfo.ino
                break;
        case 4:
                // atc radar . face 10
                tft->fillScreen(TFT_BLACK); // CLEAR DISPLAY
                tft->setTextColor(TFT_WHITE, TFT_BLACK);
                tnow = ttgo->rtc->getDateTime();
                hh = tnow.hour;
                mm = tnow.minute;
                ss = 0;
                // manipulated for testing
                //  hh=2;
                //  mm=52;
                tft->drawCircle(120, 120, 80, 0x3186);
                // tft->drawSmoothCircle(120, 120, 80, TFT_BLACK, 0x3186);

                sdeg = ss * 6;
                mm > 29 ? mm180 = mm - 30 : mm180 = 30 + mm;
                mm180 = ((mm180 - 5) + random(11));
                mdeg = mm180 * 6 + sdeg * 0.01666667; // 0-59 -> 0-360 - includes seconds
                hh > 5 ? hh180 = hh - 6 : hh180 = 6 + hh;
                hdeg = hh180 * 30 + mdeg * 0.0833333; // 0-11 -> 0-360 - inc min and seconds

                // DRAW  random  shape ISLAND
                plygon = 21;
                int rndstartdeg;
                rndstartdeg = random(2, 50);
                int rx, ry, orx, ory, sx, sy, Ox, Oy, lr, hr;
                int nois;
                nois = 160;
                // lr = -5, hr = 5;
                lr = 0 - map((360 / plygon), 1, 360, 1, nois);
                hr = map((360 / plygon), 1, 360, 1, nois);
                rx = random(59, 120);
                ry = random(59, 120);
                sx = constrain(posX(rx, rndstartdeg), 0, 240);
                sy = constrain(posY(ry, rndstartdeg), 0, 240);
                for (int i = (0 + rndstartdeg); i < (360 + rndstartdeg); i += (360 / plygon))
                {
                        int x2, y2;
                        if (i == 0 + rndstartdeg)
                        {

                                x2 = posX(rx + random(lr, hr), i + (360 / plygon));
                                (x2 < 0) && (x2 = 0);
                                y2 = posY(ry + random(lr, hr), i + (360 / plygon));
                                (y2 < 0) && (y2 = 0);
                                orx = rx, ory = ry;
                                tft->drawLine(sx, sy, x2, y2, 0x3186);
                                // Serial.print("polygon=");
                                // Serial.print("^1");
                        }
                        else if (i < (360 + rndstartdeg) - (360 / plygon) && i > (0 + rndstartdeg))
                        {
                                x2 = posX(orx + random(lr, hr), i + (360 / plygon));
                                (x2 < 0) && (x2 = 0);
                                y2 = posY(ory + random(lr, hr), i + (360 / plygon));
                                (y2 < 0) && (y2 = 0);
                                tft->drawLine(Ox, Oy, x2, y2, 0x3186);
                                // Serial.print("^2");
                        }
                        else
                        {
                                // closing the cicle, match to start point
                                tft->drawLine(Ox, Oy, sx, sy, 0x3186);
                                // Serial.println("^3");
                        }
                        Ox = x2,
                        Oy = y2;
                }
                // };

                // draw oponent hand H & M with random bending
                tft->drawLine(posX(120, hdeg), posY(120, hdeg), 120, 120, 0x3186); // DRAW  HOUR
                tft->drawLine(posX(120, mdeg), posY(120, mdeg), 120, 120, 0x3186); // DRAW  MIN
                tft->drawLine(posX(30, mdeg), posY(30, mdeg), 120, 120, TFT_BLUE); // DRAW  MIN

                // double BLUE line for runaway
                // xx = random(-20, 21);
                // yy = random(-20, 21);
                // xxx = random(-20, 21);
                // yyy = random(-20, 21);

                xx = 0;
                yy = 0;
                xxx = 0;
                yyy = 0;
                // tft->drawLine(posX(120, mdeg) + xx, posY(80, mdeg) + yy, 120 + xxx, 120 + yyy, TFT_BLUE);
                xx += (mm > 15 && mm < 31) ? (-1) : 1;
                yy += (mm > 15 && mm < 31) ? (-1) : 1;
                xxx += (mm > 15 && mm < 31) ? (-1) : 1;
                yyy += (mm > 15 && mm < 31) ? (-1) : 1;

                tft->drawLine(posX(70, mdeg) + xx, posY(70, mdeg) + yy, 120 + xxx, 120 + yyy, TFT_BLUE); // DRAW  MIN
                // tft->drawLine(posX(120, mdeg) + xx, posY(80, mdeg) + yy, 120 + xxx, 120 + yyy, TFT_BLUE);

                // compute hour
                sdeg = ss * 6;                     // 0-59 -> 0-354   Pre-compute
                mdeg = mm * 6 + sdeg * 0.01666667; // 0-59 -> 0-360 - includes seconds
                hdeg = hh * 30 + mdeg * 0.0833333; // 0-11 -> 0-360 - inc min and seconds

                // draw real hand H & M
                tft->drawLine(posX(120, hdeg), posY(120, hdeg), 120, 120, 0x3186); // DRAW  HOUR
                tft->drawLine(posX(120, mdeg), posY(120, mdeg), 120, 120, 0x3186); // DRAW  MIN

                rnddot = (mm > 5 || mm < 35) ? random(40, 70) : random(40, 110);
                old_rnddot = rnddot;

                // yy0 = getSin(((hh * 30) + (mm / 2)) - 1) * rnddot + 120;
                yy0 = posY(rnddot, ((hh * 30) + (mm / 2)) - 1);
                // x0 = getCos(((hh * 30) + (mm / 2)) - 1) * rnddot + 120;
                x0 = posX(rnddot, ((hh * 30) + (mm / 2)) - 1);
                // x0 = sx * rnddot + 120;
                hh12 = hh >= 12 ? hh - 12 : hh;
                int mmh;
                mmh = hh12 * 5;
                tft->setCursor(x0 + 15, yy0 - 15 + 20);
                tft->setTextSize(0);
                tft->setTextFont(2);
                tft->setTextColor(TFT_GREEN);
                // tft->print(hh > 12 ? "PM-" : "AM-");
                tft->printf("H-%d", hh);

                tft->setCursor(x0 + 15, yy0 - 3 + 20);
                tft->printf("%d s", daily_step);
                tft->setCursor(x0 + 15, yy0 + 9 + 20);
                dmCover = ((daily_step)*stepLenght) / 100;
                float kCover;
                if (dmCover > 1100)
                        kCover = (float)dmCover / 1000.0;
                tft->printf("%.0f %s\n", dmCover > 1100 ? kCover : dmCover, dmCover > 1100 ? "km" : "m");

                tft->drawRect(x0 - 2, yy0 - 2, 5, 5, TFT_GREEN);
                tft->drawLine(x0 + 3, yy0 + 5, x0 + 10, yy0 + 14, TFT_WHITE); // 🡦

                // tft->printf("M%d\n", mm);
                // tft->printf("X%1d = Y%2d\n", x0, yy0);
                rnddot = (mm > 5 || mm < 35) ? random(50, 70) : random(50, 110);

                // x0 = getCos(mm * 6) * rnddot + 120;
                x0 = posX(rnddot, mm * 6);
                // yy0 = getSin(mm * 6) * rnddot + 120;
                yy0 = posY(rnddot, mm * 6);

                tft->setCursor(4, 20);
                int hrdeg;
                hrdeg = hdeg >= 360.0 ? hdeg - 360.0 : hdeg;
                // Serial.print("hrdeg = ");
                // Serial.println(hrdeg);

                // draw airplane position, reference to hour and minute
                if (mdeg - hrdeg < 60 && mdeg - hrdeg >= 0)
                {
                        // Serial.println("mdeg > hdeg");
                        tft->setTextColor(COLOR_ATC[random(3)]);
                        if (hrdeg >= 60 && hrdeg <= 240)
                        {
                                // ✔
                                tft->setCursor(x0 - 45, yy0 - 15 + 20);
                                tft->printf("M-%d\n", mm);
                                tft->setCursor(x0 - 45, yy0 - 3 + 20);
                                tft->print(dw[dow]);
                                tft->setCursor(x0 - 45, yy0 + 9 + 20);
                                tft->printf("%d-%d", tnow.day, tnow.month);
                                // tft->printf("X%1d = Y%2d\n", x0, yy0);
                                tft->drawLine(x0 - 3, yy0 + 5, x0 - 12, yy0 + 14, TFT_WHITE); // 🡗
                        }
                        else
                        {

                                tft->setCursor(x0 - 45, yy0 - 72 + 20);
                                tft->printf("M-%d\n", mm);
                                tft->setCursor(x0 - 45, yy0 - 60 + 20);
                                tft->print(dw[dow]);
                                tft->setCursor(x0 - 45, yy0 - 48 + 20);
                                tft->printf("%d-%d", tnow.day, tnow.month);
                                // tft->printf("X%1d = Y%2d\n", x0, yy0);
                                tft->drawLine(x0 - 3, yy0 - 4, x0 - 12, yy0 - 12, TFT_WHITE); // 🡔
                        }
                        // tft->drawCircle(x0, yy0, 9, TFT_RED);
                        tft->drawRect(x0 - 2, yy0 - 2, 5, 5, TFT_GREEN); // draw minute rect
                }
                else if (hrdeg - mdeg < 60 && hrdeg - mdeg >= 0)
                {
                        // Serial.println("hdeg > mdeg");
                        tft->setTextColor(COLOR_ATC[random(3)]);
                        if (hrdeg >= 60 && hrdeg <= 240)
                        {
                                tft->setCursor(x0 + 15, yy0 - 72 + 20);
                                tft->printf("M-%d\n", mm);
                                tft->setCursor(x0 + 15, yy0 - 60 + 20);
                                tft->print(dw[dow]);
                                tft->setCursor(x0 + 15, yy0 - 48 + 20);
                                tft->printf("%d-%d", tnow.day, tnow.month);
                                // tft->printf("X%1d = Y%2d\n", x0, yy0);
                                tft->drawLine(x0 + 4, yy0 - 4, x0 + 11, yy0 - 12, TFT_WHITE); // 🡥
                        }
                        else
                        {
                                tft->setCursor(x0 - 45, yy0 - 72 + 20);
                                tft->printf("M-%d\n", mm);
                                tft->setCursor(x0 - 45, yy0 - 60 + 20);
                                tft->print(dw[dow]);
                                tft->setCursor(x0 - 45, yy0 - 48 + 20);
                                tft->printf("%d-%d", tnow.day, tnow.month);
                                // tft->printf("X%1d = Y%2d\n", x0, yy0);
                                tft->drawLine(x0 - 3, yy0 - 4, x0 - 12, yy0 - 13, TFT_WHITE); // 🡤
                        }
                        // tft->drawCircle(x0, yy0, 9, TFT_RED);
                        tft->drawRect(x0 - 2, yy0 - 2, 5, 5, TFT_GREEN); // draw minute rect
                }
                else
                {
                        tft->setTextColor(COLOR_ATC[random(3)]);
                        tft->setCursor(x0 + 15, yy0 - 15 + 20);

                        // tft->setWindow(x0 + 15, x0 + 45, yy0 - 15 + 20, yy0 - 15 + 50);
                        // tft->setCursor(0, 0);

                        tft->printf("M-%d\n", mm);
                        tft->setCursor(x0 + 15, yy0 - 3 + 20);
                        tft->print(dw[dow]);
                        tft->setCursor(x0 + 15, yy0 + 9 + 20);
                        tft->printf("%d-%d", tnow.day, tnow.month);
                        // tft->printf("X%1d = Y%2d\n", x0, yy0);
                        tft->drawLine(x0 + 3, yy0 + 5, x0 + 10, yy0 + 14, TFT_WHITE);
                        tft->drawRect(x0 - 2, yy0 - 2, 5, 5, TFT_GREEN); // draw minute rect
                }
                // tft->drawString("M" + mm, x0 + 15, yy0 - 15 + 20);

                tft->setTextSize(0);
                tft->setTextFont(2);
                tft->setTextColor(TFT_GREEN);
                getPower();
                tft->setCursor(2, 1);
                tft->printf("%s : %.f mA       ", power->isChargeing() ? "charging" : "Discharge", power->isChargeing() ? chrg_c : dchrg_c);

                // Print the values
                tft->setCursor(2, 240 - 18);
                // tft->printf("usb : [%.1fV|%.fmA] bat : [%.1fV|%d%%]", vbus_v, vbus_c, batt_v, per);
                tft->printf("%s : [ %.1fV | %.0f%s ]", power->isChargeing() ? "usb " : "battery ", power->isChargeing() ? vbus_v : batt_v, power->isChargeing() ? vbus_c : per, power->isChargeing() ? "mA" : "%");

                break;
        case 5:
                // CF=11
                javaneseClock(hh, mm); // clock_face_text.ino
                break;
        case 6:
                // CF=12
                mathFace(hh, mm); // clock_face_text.ino
                break;
        case 7:
                // CF=13
                // recordActivity(); // clock_face_text.ino

                tft->fillScreen(TFT_BLACK);        // CLEAR DISPLAY
                sdeg = ss * 6;                     // 0-59 -> 0-354   Pre-compute
                mdeg = mm * 6 + sdeg * 0.01666667; // 0-59 -> 0-360 - includes seconds
                hdeg = hh * 30 + mdeg * 0.0833333; // 0-11 -> 0-360 - inc min and seconds
                hh += hh > 12 ? (-12) : 0;

                int HX2, HY2;
                int xx2;
                xx2 = 120;
                int yy2;
                yy2 = 120;
                int xx;
                xx = posX(50, hdeg, xx2);
                int yy;
                yy = posY(50, hdeg, yy2);
                int mx;
                mx = posX(80, mdeg, xx);
                if (mx > 180)
                {
                        xx2 = 120 - (mx - 180);
                        xx = posX(50, hdeg, xx2);
                        mx = posX(80, mdeg, xx);
                }
                if (mx < 60)
                {
                        xx2 = 120 + (60 - mx);
                        xx = posX(50, hdeg, xx2);
                        mx = posX(80, mdeg, xx);
                }
                int my;
                my = posY(80, mdeg, yy);
                if (my > 180)
                {
                        yy2 = 120 - (my - 180);
                        yy = posY(50, hdeg, yy2);
                        my = posY(80, mdeg, yy);
                }
                if (my < 60)
                {
                        yy2 = 120 + (60 - my);
                        yy = posY(50, hdeg, yy2);
                        my = posY(80, mdeg, yy);
                }
                int hcol, mcol;
                hcol = COLOR_MEDIUM[random(10)];
                mcol = COLOR_MEDIUM[random(10)];
                // tft->drawSmoothCircle(xx, yy, 80, mcol, TFT_BLACK);
                tft->drawWideLine(mx, my, xx, yy, 6, mcol, TFT_BLACK); // DRAW  MINUTE

                tft->fillSmoothCircle(xx, yy, 4, TFT_WHITE, TFT_BLACK);
                // tft->drawSmoothCircle(xx2, yy2, 50, hcol, TFT_BLACK);
                tft->drawWideLine(xx, yy, xx2, yy2, 6, hcol, TFT_BLACK); // DRAW  MINUTE

                tft->fillSmoothCircle(xx2, yy2, 6, TFT_WHITE, TFT_BLACK);
                displaySysInfo(0); // appInfo.ino
                break;
        default:
                break;
        }
}
// tft->drawLine(*(pos(hh, mm) + 0), *(pos(hh, mm) + 1), 120, 120, 0x3186); //
int *pos(int minute, int hour)
{
        int _ohx, _ohy, _omx, _omy;
        int _sdeg, _mdeg, _hdeg;
        int _hx, _hy, _mx, _my;
        _sdeg = 0 * 6;                          // 0-59 -> 0-354   Pre-compute
        _mdeg = minute * 6 + sdeg * 0.01666667; // 0-59 -> 0-360 - includes seconds
        _hdeg = hour * 30 + mdeg * 0.0833333;   // 0-11 -> 0-360 - inc min and seconds

        _hx = cos((_hdeg - 90) * 0.0174532925);
        _hy = sin((_hdeg - 90) * 0.0174532925);
        _mx = cos((_mdeg - 90) * 0.0174532925);
        _my = sin((_mdeg - 90) * 0.0174532925);
        _ohx = _hx * 120 + 120;
        _ohy = _hy * 120 + 120; // NEW   HOUR
        _omx = _mx * 120 + 120;
        _omy = _my * 120 + 120;
        int r[4] = {_ohx, _ohy, _omx, _omy};
        return r;
}
float getCos(int degree)
{
        float r = cos((degree - 90) * 0.0174532925);
        return r;
}
float getSin(int degree)
{
        float r = sin((degree - 90) * 0.0174532925);
        return r;
}
uint16_t posX(int radius, int degree)
{
        int r = getCos(degree) * radius + 120;
        return r;
}
uint16_t posY(int radius, int degree)
{
        int r = getSin(degree) * radius + 120;
        return r;
}

uint16_t posX(int radius, int degree, int pivot)
{
        int r = getCos(degree) * radius + pivot;
        return r;
}
uint16_t posY(int radius, int degree, int pivot)
{
        int r = getSin(degree) * radius + pivot;
        return r;
}