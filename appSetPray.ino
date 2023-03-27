void drawPraySet2()
{
        tft->setTextFont(2);
        tft->setCursor(3, 76);
        tft->print("Enable alarm pray");
        //row 2

        drawSwitch(170, 70, TFT_BLUE, rgbToHex(200, 200, 200), config.alarm_pray);
}
void drawPraySet()
{

        // tft->fillRect(0, 60, 240, 180, TFT_BLACK);
        //row2
        drawOutlineButton(0, 70, 60, 40, TFT_BLUE, TFT_WHITE, "-");
        drawOutlineButton(240 - 62, 70, 60, 40, TFT_BLUE, TFT_WHITE, "+");
        tft->setTextDatum(MC_DATUM);
        tft->setTextColor(TFT_WHITE);
        tft->drawString("ALERT MIN", 120, 64, 2);
        String hou = "";
        hou += old_tmpmwarn;
        drawOutlineButton(62, 70, 240 - 62 - 60 - 2, 40, TFT_BLUE, TFT_BLACK, hou);
        hou = "";
        hou += tmpmwarn;
        drawOutlineButton(62, 70, 240 - 62 - 60 - 2, 40, TFT_BLUE, TFT_WHITE, hou);

        //row3
        drawOutlineButton(0, 130, 60, 40, TFT_BLUE, TFT_WHITE, "-");

        drawOutlineButton(240 - 62, 130, 60, 40, TFT_BLUE, TFT_WHITE, "+");
        tft->setTextDatum(MC_DATUM);
        tft->setTextColor(TFT_WHITE);
        tft->drawString("VIBRATIONS", 120, 124, 2);

        String mnit = "";
        mnit += old_tmpvib;
        drawOutlineButton(62, 130, 240 - 62 - 60 - 2, 40, TFT_BLUE, TFT_BLACK, mnit);
        mnit = "";
        mnit += tmpvib;
        drawOutlineButton(62, 130, 240 - 62 - 60 - 2, 40, TFT_BLUE, TFT_WHITE, mnit);

        //row 4
        // if (hh != tmphh || mm != tmpmm)
        // {
        //         drawButton(0, 190, 240, 40, TFT_BLUE, TFT_WHITE, "Write to RTC");
        //         write2RTC = 1;
        // }
        // else
        // {
        //         drawButton(0, 190, 240, 40, TFT_BLUE, TFT_WHITE, "NEXT");
        // }

        if (tmpmwarn != config.alarmpraywarning || tmpvib != config.vib || tmpalarmpray != config.alarm_pray)
        {
                drawButton(0, 190, 80, 40, TFT_BLUE, TFT_WHITE, "SAVE");
                // bwriteAlarm = true;
        }

        // tft->fillRect(0, 60, 240, 180, TFT_BLACK);
        // drawResetButton();
        // drawExitButton();
        tft->setTextFont(2);
        tft->setCursor(83, 196);
        tft->print("Enabled");
        //row 4
        drawSwitch(170, 190, TFT_BLUE, rgbToHex(200, 200, 200), config.alarm_pray);

        old_tmpmwarn = tmpmwarn;
        old_tmpvib = tmpvib;
        old_tmpalarmpray = tmpalarmpray;
}
void setupPrayAlarm()
{
        config.vib = tmpvib;
        config.alarmpraywarning = tmpmwarn;

        if (tmpalarmpray)
        {
                // ttgo->rtc->setAlarm(tmpha, tmpma, PCF8563_NO_ALARM, PCF8563_NO_ALARM);
                // ttgo->rtc->enableAlarm();
                setupPrayAlarm();
                alarm_msg = "STOP";
        }
        else
        {
                ttgo->rtc->disableAlarm();
                ttgo->rtc->resetAlarm();
        }
        EEPROM_writeAnything(0, config);
        EEPROM.commit();
}