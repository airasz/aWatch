void drawAlarmsetting()
{
        tft->fillRect(0, 60, 240, 180, TFT_BLACK);
        // drawResetButton();
        // drawExitButton();
        tft->setTextFont(2);
        tft->setCursor(3, 76);
        tft->print("Enabled");
        drawSwitch(170, 70, colorAccent, rgbToHex(200, 200, 200), config.alarm_enable);
}
void drawAlarmSet()
{
        // tft->fillRect(0, 60, 240, 180, TFT_BLACK);
        // row2
        drawSmoothOutlineButton(0, 70, 60, 40, colorAccent, TFT_WHITE, "-");
        drawSmoothOutlineButton(240 - 62, 70, 60, 40, colorAccent, TFT_WHITE, "+");
        tft->setTextDatum(MC_DATUM);
        tft->setTextColor(TFT_WHITE);

        tft->drawString("HOUR ALARM", 120, 64, 2);

        String hou = "";
        hou += old_tmpha;
        drawSmoothOutlineButton(62, 70, 240 - 62 - 60 - 2, 40, colorAccent, TFT_BLACK, hou);
        hou = "";
        hou += tmpha;
        drawSmoothOutlineButton(62, 70, 240 - 62 - 60 - 2, 40, colorAccent, TFT_WHITE, hou);

        // row3
        drawSmoothOutlineButton(0, 130, 60, 40, colorAccent, TFT_WHITE, "-");
        drawSmoothOutlineButton(240 - 62, 130, 60, 40, colorAccent, TFT_WHITE, "+");
        tft->setTextDatum(MC_DATUM);
        tft->setTextColor(TFT_WHITE);
        tft->drawString("MINUTE ALARM", 120, 124, 2);

        String mnit = "";
        mnit += old_tmpma;
        drawSmoothOutlineButton(62, 130, 240 - 62 - 60 - 2, 40, colorAccent, TFT_BLACK, mnit);
        mnit = "";
        mnit += tmpma;
        drawSmoothOutlineButton(62, 130, 240 - 62 - 60 - 2, 40, colorAccent, TFT_WHITE, mnit);

        // row 4

        if (tmpha != config.alarm_h || tmpma != config.alarm_m || tmpalarmenable != config.alarm_enable)
        {
                drawButton(0, 190, 80, 40, colorAccent, TFT_WHITE, "SAVE");
                bwriteAlarm = true;
        }

        tft->setTextFont(2);
        tft->setCursor(83, 196);
        tft->print("Enabled");
        // row 4

        drawSwitch(170, 190, TFT_BLUE, rgbToHex(200, 200, 200), tmpalarmenable);

        old_tmpha = tmpha;
        old_tmpma = tmpma;
        old_tmpalarmenable = tmpalarmenable;
}
void writeAlarm()
{
        if (bwriteAlarm)
        {
                config.alarm_enable = tmpalarmenable;
                config.alarm_h = tmpha;
                config.alarm_m = tmpma;
                EEPROM_writeAnything(0, config);
                EEPROM.commit();
                bwriteAlarm = 0;
                Serial.println("saved alarm");
                if (tmpalarmenable)
                {
                        ttgo->rtc->setAlarm(tmpha, tmpma, PCF8563_NO_ALARM, PCF8563_NO_ALARM);
                        ttgo->rtc->enableAlarm();
                        alarm_msg = "STOP";
                }
                else
                {
                        ttgo->rtc->disableAlarm();
                        ttgo->rtc->resetAlarm();
                }
        }
}