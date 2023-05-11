
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
        tft->fillRect(80, 0, 80, 60, TFT_WHITE);

        tft->setTextColor(TFT_BLACK);
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

                tft->fillRect(0, 0, 240, 60, TFT_WHITE);
                // drawButton(2, 8, 78, 48, COLOR_ACCENT[config.colorAccent], TFT_WHITE, "BACK");
                // drawButton(160, 8, 78, 48, COLOR_ACCENT[config.colorAccent], TFT_WHITE, "EXIT");
                drawSmoothButton(2, 8, 78, 48, TFT_BLACK, TFT_WHITE, TFT_WHITE, "BACK");
                drawSmoothButton(160, 8, 78, 48, TFT_BLACK, TFT_WHITE, TFT_WHITE, "EXIT");
                tft->setTextColor(TFT_BLACK);
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
        // drawButton(2, 8, 78, 48, COLOR_ACCENT[config.colorAccent], TFT_WHITE, "BACK");
        drawSmoothButton(2, 8, 78, 48, TFT_BLACK, COLOR_ACCENT[config.colorAccent], TFT_WHITE, "BACK");
        // drawButton(160, 8, 78, 48, COLOR_ACCENT[config.colorAccent], TFT_WHITE, "EXIT");
        drawSmoothButton(160, 8, 78, 48, TFT_BLACK, COLOR_ACCENT[config.colorAccent], TFT_WHITE, "EXIT");
}

void drawHomeSettingBody()
{
        tft->fillRect(0, 60, 240, 180, TFT_BLACK);
        drawOutlineButton(0, 60, 80, 60, COLOR_ACCENT[config.colorAccent], TFT_WHITE, "STEP");
        drawOutlineButton(80, 60, 80, 60, COLOR_ACCENT[config.colorAccent], TFT_WHITE, "DISPLAY");
        drawOutlineButton(160, 60, 80, 60, COLOR_ACCENT[config.colorAccent], TFT_WHITE, "TIME");
        drawOutlineButton(0, 120, 80, 60, COLOR_ACCENT[config.colorAccent], TFT_WHITE, "ALARM");
        drawOutlineButton(80, 120, 80, 60, COLOR_ACCENT[config.colorAccent], TFT_WHITE, "FACE");
        drawOutlineButton(160, 120, 80, 60, COLOR_ACCENT[config.colorAccent], TFT_WHITE, "PRAY");
        drawOutlineButton(0, 180, 80, 60, COLOR_ACCENT[config.colorAccent], TFT_WHITE, "AC");
        drawOutlineButton(0, 180, 80, 60, COLOR_ACCENT[config.colorAccent], TFT_WHITE, "AC");
}
