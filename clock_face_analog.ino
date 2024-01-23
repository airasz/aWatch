

// #include "aWatch.h"

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
  tnow = ttgo->rtc->getDateTime();
  int nday = tnow.day,
      nmonth = tnow.month,
      nyear = tnow.year, g = 250;
  String const dw[] = {"MGG", "SEN", "SEL", "RBU", "KMS", "JMT", "SBT"};
  int dow = ttgo->rtc->getDayOfWeek(nday, nmonth, nyear);
  // Serial.printf(" day of week : %d \n", dow);
  hh = tnow.hour;
  mm = tnow.minute;
  ss = tnow.second;
  v -= 6;
  int hh12 = hh >= 12 ? hh - 12 : hh; // hh += hh > 12 ? (-12) : 0;
  int hq;
  hq = getQuadrant(hh);
  sdeg = ss * 6;                     // 0-59 -> 0-354   Pre-compute
  mdeg = mm * 6 + sdeg * 0.01666667; // 0-59 -> 0-360 - includes seconds
  hdeg = hh * 30 + mdeg * 0.0833333; // 0-11 -> 0-360 - inc min and seconds

  if (v == 0)
  {
    // face=6
    tft->fillScreen(TFT_BLACK); // CLEAR DISPLAY
    tft->setTextColor(TFT_WHITE, TFT_BLACK);
    // int o_colcircle;
    int o_colcircle = COLOR_MEDIUM[random(10)];
    // int i_colcircle;
    int i_colcircle = COLORS_DARK[random(10)];
    tft->drawSmoothCircle(120, 120, 82, o_colcircle, TFT_BLACK);
    tft->fillSmoothCircle(120, 120, 80, i_colcircle, o_colcircle);
    // 12 LINES
    // rainbow color for every multiple 5  minute line mark
    for (int i = 0; i < 360; i += 30)
      tft->drawLine(posX(80, i), posY(80, i), posX(72, i), posY(72, i), COLOR_MEDIUM[random(10)]); // DRAW 12 LINES

    // 60 DOTS
    for (int i = 0; i < 360; i += 6)
    {
      tft->drawPixel(posX(78, i), posY(79, i), COLOR_MEDIUM[random(10)]); // MINUTE DOT
      if (i % 90 == 0)
        tft->fillCircle(posX(78, i), posY(79, i), 3, TFT_WHITE); // DOTS
    }
    // middle dot
    tft->fillCircle(120, 120, 3, TFT_RED);
    // Serial.printf("hh=%01d, mm=%02d, ss=%03d\n",hh,mm,ss);

    tft->drawWideLine(posX(50, hdeg), posY(50, hdeg), 120, 120, 6, COLOR_MEDIUM[random(10)], i_colcircle); // DRAW  HOUR
    tft->drawWideLine(posX(71, mdeg), posY(71, mdeg), 120, 120, 6, COLOR_MEDIUM[random(10)], i_colcircle); // DRAW  MINUTE
    tft->fillSmoothCircle(120, 120, 6, TFT_RED, i_colcircle);
    displaySysInfo(0); // appInfo.ino

    if (enableSS)
      screenServer();
  }
  else if (v == 1)
  {
    // pie line guard

    hdeg = hh12 * 30 + mdeg * 0.0833333; // 0-11 -> 0-360 - inc min and seconds
    tft->fillScreen(TFT_BLACK);          // CLEAR DISPLAY

    int xx2 = 120;
    int yy2 = 120;
    int xx = posX(65, hdeg, xx2);
    int yy = posY(65, hdeg, yy2);
    int mx = posX(80, mdeg, xx2);
    int my = posY(80, mdeg, yy2);
    int hcol = COLOR_MEDIUM[random(10)];
    int mcol = COLOR_MEDIUM[random(10)];
    // draw a pie minute  guide
    for (int i = 0; i < 720; i += 6)
      if (i + 1 > mdeg - 50 && i + 1 < mdeg + 50 || i + 1 > (360 + mdeg) - 50 && i + 1 < (mdeg + 360) + 50)
        tft->drawWideLine(posX(90, i, xx2), posY(90, i, yy2), posX(90 - ((i % 15 == 0) ? 20 : 10), i, xx2), posY(90 - ((i % 15 == 0) ? 20 : 10), i, yy2), (i % 15 == 0) ? 2 : 1, ((i % 15 == 0) ? rgbToHex(200, 80, 0) : TFT_YELLOW), TFT_BLACK); // DRAW  MINUTE

    tft->drawWideLine(mx, my, xx2, yy2, 6, mcol, TFT_BLACK); // DRAW  MINUTE
    // draw 5 minutes line guide
    for (int i = 0; i < 720; i += 30)
      if (i + 1 > hdeg - 60 && i + 1 < hdeg + 60 || i + 1 > (360 + hdeg) - 60 && i + 1 < (hdeg + 360) + 60)
        tft->drawWideLine(posX(80, i, xx2), posY(80, i, yy2), posX(80 - ((i % 90 == 0) ? 20 : 10), i, xx2), posY(80 - ((i % 90 == 0) ? 20 : 10), i, yy2), (i % 90 == 0) ? 3 : 2, TFT_WHITE, TFT_BLACK); // DRAW  MINUTE

    // 60 DOTS
    tft->drawWideLine(xx, yy, xx2, yy2, 6, hcol, TFT_BLACK); // DRAW  HOUR HAND
    tft->fillSmoothCircle(xx2, yy2, 6, TFT_WHITE, TFT_BLACK);
    displaySysInfo(0); // appInfo.ino
    if (enableSS)
      screenServer();
  }
  else if (v == 2)
  {
    // arc progress. face=7
    tft->fillScreen(TFT_BLACK); // CLEAR DISPLAY
    tft->setTextColor(TFT_WHITE, TFT_BLACK);
    hdeg = hh12 * 30 + mdeg * 0.0833333; // 0-11 -> 0-360 - inc min and seconds
                                         // int startMAngle, endMAngle, startHAngle, endHAngle;
                                         // clock degree is oposite position to arc degre
                                         //  convert 24 to 12 hours format

    //  progress minute
    tft->drawSmoothArc(120, 120, 84, 76, (mm >= 30) ? mdeg - 180 : 180, (mm >= 30) ? 180 : 180 + mdeg, TFT_RED, TFT_BLACK, false);
    // progress hour
    tft->drawSmoothArc(120, 120, 66, 74, (hh12 >= 6) ? hdeg - 180 : 180, (hh12 >= 6) ? 180 : 180 + hdeg, TFT_BLUE, TFT_BLACK, false);

    // 12 LINES
    for (int i = 0; i < 360; i += 30)
      tft->drawLine(posX(74, i), posY(74, i) + 1, posX((i % 90 == 0) ? 60 : 66, i), posY((i % 90 == 0) ? 60 : 66, i) + 1, TFT_WHITE);

    displaySysInfo(0); // appInfo.ino
    // Serial.printf("ohx=%01d, ohy=%02d, \n", ohx, ohy);
    // Serial.printf("omx=%01d, omy=%02d, \n", omx, omy);
    if (enableSS)
      screenServer();
  }

  else if (v == 3)
  {
    // comet race mode. face =8
    // Serial.printf("hh=%01d, mm=%02d, ss=%03d\n", hh, mm, ss);
    tft->fillScreen(TFT_BLACK); // CLEAR DISPLAY
    tft->setTextColor(TFT_WHITE, TFT_BLACK);
    for (size_t i = 6; i < 9; i++)
      tft->drawSmoothCircle(120, 120, i * 10, COLOR_MEDIUM[random(10)], TFT_BLACK);

    // dot hour
    for (int t = 15; t > (-1); t--)
    {
      g = 255 - (t * 17); // create gradient squences dark to bright
      dgree = ((hh * 30) + (mm / 2)) - t;
      tft->fillCircle(posX(65, dgree), posY(65, dgree), 2, rgbToHex(0, 0, g));
      tft->fillCircle(posX(75, (mm * 6) - t), posY(75, (mm * 6) - t), 2, rgbToHex(g, 0, 0)); // minutes
    }

    tft->drawLine(posX(78, 0), posY(78, 0), posX(68, 0), posY(68, 0), COLOR_MEDIUM[random(10)]); // DRAW TOP LINES
    displaySysInfo(0);                                                                           // appInfo.ino
    if (enableSS)
      screenServer();
    // Serial.printf("hh=%01d, mm=%02d, ss=%03d\n", hh, mm, ss);
  }

  else if (v == 4)
  {
    // marine radar. face =9
    tft->fillScreen(TFT_BLACK); // CLEAR DISPLAY
    tft->setTextColor(TFT_WHITE, TFT_BLACK);
    tft->fillSmoothCircle(120, 120, 80, TFT_GREEN, TFT_BLACK);
    tft->fillSmoothCircle(120, 120, 77, TFT_BLACK, TFT_GREEN);

    for (size_t i = 60; i > 19; i -= 20)
      tft->drawSmoothCircle(120, 120, i, 0x0140, TFT_BLACK);

    // dot hour pretend detected object
    dgree = ((hh * 30) + (mm / 2)) - 1;
    tft->fillCircle(posX(random(50, 76), dgree), posY(random(50, 76), dgree), 2, rgbToHex(200, 225, 180));

    // 4 cross LINES (12,3,6,9)
    for (int i = 0; i < 360; i += 30)
      if (i % 90 == 0)
        tft->drawLine(posX(78, i), posY(78, i) + 1, 120, 121, 0x0140);

    // hdeg = hh * 30 + mdeg * 0.0833333; // 0-11 -> 0-360 - inc min and seconds
    wipetracelong = 4;
    for (int t = 50; t > (-1); t--)
    {
      g = 150 - (t * 3);
      tft->drawLine(posX(76, mdeg - (t * wipetracelong)), posY(80, mdeg - (t * wipetracelong)), 120, 120, rgbToHex(t == 0 ? 200 : 0, t == 0 ? 255 : g, 0)); // Draw shadow swiper
    }
    displaySysInfo(1); // appInfo.ino

    if (enableSS)
      screenServer();
  }
  else if (v == 5)
  {
    // atc radar . face 10
    tft->fillScreen(TFT_BLACK); // CLEAR DISPLAY
    tft->setTextColor(TFT_WHITE, TFT_BLACK);
    ss = 0;
    // manipulated for testing
    //  hh=2;
    //  mm=52;
    tft->drawCircle(120, 120, 80, 0x3186);
    // tft->drawSmoothCircle(120, 120, 80, TFT_BLACK, 0x3186);

    // DRAW  island using random shape
    int plygon = 21;
    int rndstartdeg = random(2, 50);
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
        // closing the shape, end point match to start point
        tft->drawLine(Ox, Oy, sx, sy, 0x3186);
        // Serial.println("^3");
      }
      Ox = x2,
      Oy = y2;
    }
    // };

    // draw real hand H & M
    tft->drawLine(posX(120, hdeg), posY(120, hdeg), 120, 120, 0x3186); // DRAW  HOUR
    tft->drawLine(posX(120, mdeg), posY(120, mdeg), 120, 120, 0x3186); // DRAW  MIN

    sdeg = ss * 6;
    // mm > 29 ? mm180 = mm - 30 : mm180 = 30 + mm;
    mm180 = mm > 29 ? mm - 30 : 30 + mm;
    mm180 = ((mm180 - 5) + random(11));
    mdeg = mm180 * 6 + sdeg * 0.01666667; // 0-59 -> 0-360 - includes seconds
    // hh > 5 ? hh180 = hh - 6 : hh180 = 6 + hh;
    hh180 = hh > 5 ? hh - 6 : 6 + hh;
    hdeg = hh180 * 30 + mdeg * 0.0833333; // 0-11 -> 0-360 - inc min and seconds
    // draw oponent hand H & M with random bending
    tft->drawLine(posX(120, hdeg), posY(120, hdeg), 120, 120, 0x3186); // DRAW  HOUR
    tft->drawLine(posX(120, mdeg), posY(120, mdeg), 120, 120, 0x3186); // DRAW  MIN
    tft->drawLine(posX(30, mdeg), posY(30, mdeg), 120, 120, TFT_BLUE); // DRAW  MIN

    // double BLUE line for runaway

    // tft->drawLine(posX(120, mdeg) + xx, posY(80, mdeg) + yy, 120 + xxx, 120 + yyy, TFT_BLUE);
    int xx = (mm > 15 && mm < 31) ? (-1) : 1;
    int yy = (mm > 15 && mm < 31) ? (-1) : 1;
    int xxx = (mm > 15 && mm < 31) ? (-1) : 1;
    int yyy = (mm > 15 && mm < 31) ? (-1) : 1;

    tft->drawLine(posX(70, mdeg) + xx, posY(70, mdeg) + yy, 120 + xxx, 120 + yyy, TFT_BLUE); // DRAW  BLUE line
    // tft->drawLine(posX(120, mdeg) + xx, posY(80, mdeg) + yy, 120 + xxx, 120 + yyy, TFT_BLUE);

    rnddot = (mm > 5 || mm < 35) ? random(40, 70) : random(40, 110);
    old_rnddot = rnddot;

    yy0 = posY(rnddot, ((hh * 30) + (mm / 2)) - 1);
    x0 = posX(rnddot, ((hh * 30) + (mm / 2)) - 1);

    // int mmh;
    int mmh = hh12 * 5;
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

    x0 = posX(rnddot, mm * 6);
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

    if (enableSS)
      screenServer();
  }
  else if (v == 6)
  {
    // CF=13
    // chaotic pendulum
    tft->fillScreen(TFT_BLACK);          // CLEAR DISPLAY
    hdeg = hh12 * 30 + mdeg * 0.0833333; // 0-11 -> 0-360 - inc min and seconds
    hq = getQuadrant(hh12);
    int xx2 = 120;
    int yy2 = 120;
    int xx = posX(50, hdeg, xx2);
    int yy = posY(50, hdeg, yy2);
    int mx = posX(80, mdeg, xx);
    if (mx > 180)
    {
      xx2 = xx2 - (mx - 180);
      xx = posX(50, hdeg, xx2);
      mx = posX(80, mdeg, xx);
    }
    if (mx < 60)
    {
      xx2 = xx2 + (60 - mx);
      xx = posX(50, hdeg, xx2);
      mx = posX(80, mdeg, xx);
    }
    my = posY(80, mdeg, yy);
    if (my > 180)
    {
      yy2 = yy2 - (my - 180);
      yy = posY(50, hdeg, yy2);
      my = posY(80, mdeg, yy);
    }
    if (my < 60)
    {
      yy2 = yy2 + (60 - my);
      yy = posY(50, hdeg, yy2);
      my = posY(80, mdeg, yy);
    }
    // int hcol, mcol;
    int hcol = COLOR_MEDIUM[random(10)];
    int mcol = COLOR_MEDIUM[random(10)];
    // draw a minute line guide
    for (int i = 0; i < 720; i += 6)
      if (i + 1 > mdeg - 50 && i + 1 < mdeg + 50 || i + 1 > (360 + mdeg) - 50 && i + 1 < (mdeg + 360) + 50)
        tft->drawWideLine(posX(90, i, xx), posY(90, i, yy), posX(90 - ((i % 15 == 0) ? 20 : 10), i, xx), posY(90 - ((i % 15 == 0) ? 20 : 10), i, yy), (i % 15 == 0) ? 2 : 1, ((i % 15 == 0) ? rgbToHex(200, 80, 0) : TFT_YELLOW), TFT_BLACK); // DRAW  MINUTE

    tft->drawWideLine(mx, my, xx, yy, 6, mcol, TFT_BLACK); // DRAW  MINUTE
    tft->fillSmoothCircle(xx, yy, 6, TFT_WHITE, TFT_BLACK);
    // draw pie hour line guide
    for (int i = 0; i < 720; i += 30)
      if (i + 1 > hdeg - 60 && i + 1 < hdeg + 60 || i + 1 > (360 + hdeg) - 60 && i + 1 < (hdeg + 360) + 60)
        tft->drawWideLine(posX(60, i, xx2), posY(60, i, yy2), posX(60 - ((i % 90 == 0) ? 20 : 10), i, xx2), posY(60 - ((i % 90 == 0) ? 20 : 10), i, yy2), (i % 90 == 0) ? 3 : 2, TFT_WHITE, TFT_BLACK); // DRAW  MINUTE

    tft->drawWideLine(xx, yy, xx2, yy2, 6, hcol, TFT_BLACK); // DRAW  HOUR HAND
    tft->fillSmoothCircle(xx2, yy2, 6, TFT_WHITE, TFT_BLACK);
    displaySysInfo(0); // appInfo.ino

    if (enableSS)
      screenServer();
  }
  else if (v == 7)
  {
    // CF=11
    javaneseClock(hh, mm); // clock_face_text.ino

    if (enableSS)
      screenServer();
  }
  else if (v == 8)
  {
    // CF=12
    mathFace(hh, mm); // clock_face_text.ino

    if (enableSS)
      screenServer();
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
int posX(int radius, int degree)
{
  int r = getCos(degree) * radius + 120;
  return r;
}
int posY(int radius, int degree)
{
  int r = getSin(degree) * radius + 120;
  return r;
}

int posX(int radius, int degree, int pivot)
{
  int r = getCos(degree) * radius + pivot;
  return r;
}
int posY(int radius, int degree, int pivot)
{
  int r = getSin(degree) * radius + pivot;
  return r;
}
int getQuadrant(int hh)
{
  if (hh < 3)
    return 1;
  if (hh >= 3 && hh < 6)
    return 2;
  if (hh >= 6 && hh < 9)
    return 3;
  if (hh >= 9 && hh < 12)
    return 4;
}
void assignDegree()
{
}