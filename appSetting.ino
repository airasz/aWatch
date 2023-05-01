int oldValue;
int oldValue2;

void startSetting(int setID)
{
        // if (setID == 0)
        // {
        //         tnow = ttgo->rtc->getDateTime();
        //         hh = tnow.hour;
        //         tmpalarmenable = config.alarm_enable;
        //         tmpha = config.alarm_h;
        //         tmpma = config.alarm_m;
        //         mm = tnow.minute;
        //         ss = tnow.second;
        //         dday = tnow.day;
        //         mmonth = tnow.month;
        //         yyear = tnow.year;
        //         tmphh = hh;
        //         tmpmm = mm;
        //         tmpday = dday;
        //         tmpmnt = mmonth;
        //         tmpyear = yyear;
        // }
        // drawHomeSettingHeader(setID);
        // tft->fillRect(0, 60, 240, 180, TFT_BLACK); //clear body area
        tft->fillRect(80, 0, 80, 60, TFT_RED);
        switch (setID)
        {
        case 0:
                tnow = ttgo->rtc->getDateTime();
                hh = tnow.hour;
                tmpalarmenable = config.alarm_enable;
                tmpha = config.alarm_h;
                tmpma = config.alarm_m;
                tmpvib = config.vib;
                tmpmwarn = config.alarmpraywarning;
                tmpalarmpray = config.alarm_pray;
                mm = tnow.minute;
                ss = tnow.second;
                dday = tnow.day;
                mmonth = tnow.month;
                yyear = tnow.year;
                tmphh = hh;
                tmpmm = mm;
                tmpday = dday;
                tmpmnt = mmonth;
                tmpyear = yyear;

                tft->fillRect(0, 0, 240, 60, TFT_RED);
                // drawButton(2, 8, 78, 48, TFT_BLUE, TFT_WHITE, "BACK");
                // drawButton(160, 8, 78, 48, TFT_BLUE, TFT_WHITE, "EXIT");
                drawSmoothButton(2, 8, 78, 48, TFT_BLUE, TFT_RED, TFT_WHITE, "BACK");
                drawSmoothButton(160, 8, 78, 48, TFT_BLUE, TFT_RED, TFT_WHITE, "EXIT");
                tft->drawString("SETTING", 120, 24, 2);
                drawHomeSettingBody();
                break;
        case 1:
                tft->drawString("STEP", 120, 24, 2);
                drawStepSetting();
                break;
        case 2:
                tft->drawString("DISPLAY", 120, 24, 2);
                drawDisplaySetting();
                break;
        case 3:
                tft->drawString("TIME", 120, 24, 2);
                drawTimeSetting(1);
                break;
        case 4:
                tft->drawString("DATE", 120, 24, 2);
                drawTimeSetting(2);
                break;
        case 5:
                tft->drawString("DATE", 120, 24, 2);
                drawTimeSetting(3);
                break;
        case 6:
                tft->drawString("ALARM", 120, 24, 2);
                drawAlarmSet();
                break;
        case 7:
                tft->drawString("FACE", 120, 24, 2);
                drawSetFace();
                break;
        case 8:
                tft->drawString("PRAY", 120, 24, 2);
                drawPraySet();
                break;
        case 9:
                tft->drawString("SELECT", 120, 22, 2);
                tft->drawString("BRAND", 120, 34, 2);
                // drawACremote();
                drawSelectBrand();
                break;
        case 10:
                tft->drawString("pana", 120, 24, 2);
                drawACremote();
                break;
        case 11:
                tft->drawString("LG", 120, 24, 2);
                drawRemoteLG();
                break;
        default:
                break;
        }
}
void drwaBaseHeader(int setID)
{
        tft->fillRect(0, 0, 240, 60, TFT_RED);
        // drawButton(2, 8, 78, 48, TFT_BLUE, TFT_WHITE, "BACK");
        drawSmoothButton(2, 8, 78, 48, TFT_BLUE, TFT_RED, TFT_WHITE, "BACK");
        // drawButton(160, 8, 78, 48, TFT_BLUE, TFT_WHITE, "EXIT");
        drawSmoothButton(160, 8, 78, 48, TFT_BLUE, TFT_RED, TFT_WHITE, "EXIT");
}

void drawHomeSettingBody()
{
        tft->fillRect(0, 60, 240, 180, TFT_BLACK);
        drawOutlineButton(0, 60, 80, 60, TFT_BLUE, TFT_WHITE, "STEP");
        drawOutlineButton(80, 60, 80, 60, TFT_BLUE, TFT_WHITE, "DISPLAY");
        drawOutlineButton(160, 60, 80, 60, TFT_BLUE, TFT_WHITE, "TIME");
        drawOutlineButton(0, 120, 80, 60, TFT_BLUE, TFT_WHITE, "ALARM");
        drawOutlineButton(80, 120, 80, 60, TFT_BLUE, TFT_WHITE, "FACE");
        drawOutlineButton(160, 120, 80, 60, TFT_BLUE, TFT_WHITE, "PRAY");
        drawOutlineButton(0, 180, 80, 60, TFT_BLUE, TFT_WHITE, "AC");
        drawOutlineButton(0, 180, 80, 60, TFT_BLUE, TFT_WHITE, "AC");
}
void drawDisplaySetting()
{
        // tft->fillScreen(TFT_BLACK); // CLEAR DISPLAY
        tft->fillRect(0, 60, 240, 180, TFT_BLACK);
        setSTO();
        setSBright();
}
void drawStepSetting()
{
        tft->setTextFont(2);
        tft->setCursor(3, 76);
        tft->print("Enabled");
        // row 2

        drawSwitch(170, 70, TFT_BLUE, rgbToHex(200, 200, 200), config.stepcounter_filter > 0);
        // if (config.stepcounter_filter > 0)
        // {
        //         drawSwitch(170, 70, TFT_BLUE, rgbToHex(200, 200, 200), true);
        // }
        // else
        // {
        //         drawSwitch(170, 70, TFT_BLUE, rgbToHex(200, 200, 200), false);
        // }
        // row3

        drawOutlineButton(0, 130, 60, 40, TFT_BLUE, TFT_WHITE, "-");

        drawOutlineButton(240 - 62, 130, 60, 40, TFT_BLUE, TFT_WHITE, "+");
        tft->setTextDatum(MC_DATUM);
        tft->setTextColor(TFT_WHITE);
        tft->drawString("Step length", 120, 120, 2);
        String s_length = "";
        s_length += old_stepLength;
        s_length += " cm";
        drawOutlineButton(62, 130, 240 - 62 - 60 - 2, 40, TFT_BLUE, TFT_BLACK, s_length);
        s_length = "";
        s_length += stepLenght;
        s_length += " cm";
        drawOutlineButton(62, 130, 240 - 62 - 60 - 2, 40, TFT_BLUE, TFT_WHITE, s_length);

        // row 4

        drawButton(0, 190, 240, 40, TFT_BLUE, TFT_WHITE, "Reset daily step counter");
        // tft->drawRoundRect(0, 190, 240, 40, 8, TFT_BLUE);
        // tft->setCursor(13, 200);
        // tft->print("Reset step counter");
        old_stepLength = stepLenght;
}

void adjusting(int x, int y)
{
        if (x > 40 && x < 220)
                if (y < 170 && y > 120)
                        adjustSTO(x);

        if (x > 40 && x < 220)
                if (y < 90 && y > 60)
                        adjustSBright(x);
}
void setSTO()
{
        // tft->fillScreen(TFT_BLACK); // CLEAR DISPLAY
        drawWgetSeekBarTO(40, 140, config.screensaver_timeout);
        // oldValue = 0;
}
void adjustSTO(int x)
{
        if (x > 40 && x < 220)
        {
                // int SBvalue = (40 + 2) + (((240 - 40) / 30) * value);
                uint8_t value = (x - 40) / ((220 - 40) / 30);
                // int value=((240-40)/x)
                updateWgetSeekBarTO(40, 140, value);
        }
}
void updateWgetSeekBarTO(uint8_t X, uint8_t Y, uint8_t value)
{
        if (value != oldValue)
        {
                tft->setTextDatum(MC_DATUM);
                tft->setTextColor(TFT_GREEN, TFT_BLACK);
                tft->drawString("SCREEN TIMEOUT", 120, 124, 2); // 184
                tft->setCursor(4, 196);
                my_idle();
                // tft->print(value);
                String svalue = "";
                if (value < 9)
                        svalue += "0";
                svalue += value;
                drawButton(0, 132, 40, 30, TFT_BLACK, TFT_WHITE, svalue); // 190
                // tft->drawString(svalue, 4, 196, 2);
                Serial.printf("valeu %d\n ", value);
                int width = 220;
                int SBtrackX = X;
                int SBtrack, SBthumb;
                (value < 3) && (value = 3);

                config.screensaver_timeout = value;
                // EEPROM_writeAnything(0, config);
                // EEPROM.commit();

                int SBvalue = (X + 2) + (((width - X) / 30) * value);
                int SBOldvalue = (X + 2) + (((width - X) / 30) * oldValue);
                tft->fillCircle(SBOldvalue, Y + 3, 2, TFT_BLACK);
                tft->drawRoundRect(X, Y, width - X, 8, 3, TFT_BLUE);
                tft->fillCircle(SBvalue, Y + 3, 2, TFT_WHITE);
                oldValue = value;
                drawButton(0, 190, 80, 40, TFT_BLUE, TFT_WHITE, "SAVE");
        }
}
void drawWgetSeekBarTO(uint8_t X, uint8_t Y, uint8_t value)
{

        tft->setTextDatum(MC_DATUM);
        tft->setTextColor(TFT_GREEN);
        tft->drawString("SCREEN TIMEOUT", 120, 124, 2);
        tft->setCursor(4, 196);
        String svalue = "";
        if (value < 9)
                svalue += "0";
        svalue += value;
        drawButton(0, 132, 40, 30, TFT_BLACK, TFT_WHITE, svalue);
        int width = 220;
        int SBtrackX = X;

        int SBvalue = (X + 2) + (((width - X) / 30) * value);
        int SBOldvalue = (X + 2) + (((width - X) / 30) * oldValue);
        // tft->fillCircle(SBOldvalue, Y + 3, 2, TFT_BLACK);
        tft->drawRoundRect(X, Y, width - X, 8, 3, TFT_BLUE);
        tft->fillCircle(SBvalue, Y + 3, 2, TFT_WHITE);
        oldValue = value;
}

//======================      brightness part
void setSBright()
{
        drawWgetSeekBarBright(40, 80, config.default_brightness / 15);
        // oldValue = 0;
}

void adjustSBright(int x)
{
        if (x > 40 && x < 220)
        {
                // int SBvalue = (40 + 2) + (((240 - 40) / 30) * value);
                uint8_t value = (x - 40) / ((220 - 40) / 15);
                // int value=((240-40)/x)
                updateWgetSeekBarBright(40, 80, value);
        }
}
void updateWgetSeekBarBright(uint8_t X, uint8_t Y, uint8_t value)
{
        if (value != oldValue)
        {
                tft->setTextColor(TFT_GREEN, TFT_BLACK);
                tft->setTextDatum(MC_DATUM);
                tft->setTextColor(TFT_GREEN);
                tft->drawString("BRIGHTNESS", 120, 66, 2);
                tft->setCursor(4, 136);
                // String svalue = "";
                char svalue[3];
                sprintf(svalue, "%02d", value); // add 0 if one digit
                // if (value < 9)
                //         svalue += "0";
                // svalue += value;
                drawButton(0, 72, 40, 30, TFT_BLACK, TFT_WHITE, svalue);
                my_idle();
                // tft->print(value);
                // Serial.printf("valeu %d\n ", value);
                int width = 220;
                int SBtrackX = X;
                int SBtrack, SBthumb;

                (value == 0) && (value = 1);
                config.default_brightness = value * 15;
                // EEPROM_writeAnything(0, config);
                // EEPROM.commit();

                int SBvalue = (X + 2) + (((width - X) / 15) * value);
                int SBOldvalue = (X + 2) + (((width - X) / 15) * oldValue2);
                tft->fillCircle(SBOldvalue, Y + 3, 2, TFT_BLACK);
                tft->drawRoundRect(X, Y, width - X, 8, 3, TFT_BLUE);
                tft->fillCircle(SBvalue, Y + 3, 2, TFT_WHITE);
                oldValue2 = value;
                drawButton(0, 190, 80, 40, TFT_BLUE, TFT_WHITE, "SAVE");
        }
}
void drawWgetSeekBarBright(uint8_t X, uint8_t Y, uint8_t value)
{
        tft->setTextDatum(MC_DATUM);
        tft->setTextColor(TFT_GREEN);
        tft->drawString("BRIGHTNESS", 120, 64, 2);
        // String svalue = "";
        char svalue[3];
        sprintf(svalue, "%02d", value); // add 0 if one digit
        // if (value < 9)
        //         svalue += "0";
        // svalue += value;
        drawButton(0, 72, 40, 30, TFT_BLACK, TFT_WHITE, svalue);
        int width = 220;
        int SBtrackX = X;

        int SBvalue = (X + 2) + (((width - X) / 15) * value);
        int SBOldvalue = (X + 2) + (((width - X) / 15) * oldValue2);
        tft->drawRoundRect(X, Y, width - X, 8, 3, TFT_BLUE);
        tft->fillCircle(SBvalue, Y + 3, 2, TFT_WHITE);
        oldValue2 = value;
}