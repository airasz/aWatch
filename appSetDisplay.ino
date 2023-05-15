int oldValue;
int oldValue2;

void drawDisplaySetting()
{
        // tft->fillScreen(TFT_BLACK); // CLEAR DISPLAY
        tft->fillRect(0, 60, 240, 180, TFT_BLACK);
        setSTO();
        setSBright();

        // drawButton(1, 190, 78, 40, COLOR_ACCENT[config.colorAccent], TFT_BLACK, "ON");
        // drawButton(81, 190, 78, 40, COLOR_ACCENT[config.colorAccent], TFT_BLACK, "OFF");

        drawButton(161, 190, 78, 40, COLOR_ACCENT[config.colorAccent], TFT_BLACK, "NEXT");
}
void drawStepSetting()
{
        tft->setTextFont(2);
        tft->setCursor(3, 76);
        tft->print("Enabled");
        // row 2

        // drawSwitch(170, 70, COLOR_ACCENT[config.colorAccent], rgbToHex(200, 200, 200), config.stepcounter_filter > 0);
        drawSmoothSwitch(170, 70, COLOR_ACCENT[config.colorAccent], TFT_BLACK, config.stepcounter_filter > 0);

        // if (config.stepcounter_filter > 0)
        // {
        //         drawSwitch(170, 70, TFT_BLUE, rgbToHex(200, 200, 200), true);
        // }
        // else
        // {
        //         drawSwitch(170, 70, TFT_BLUE, rgbToHex(200, 200, 200), false);
        // }
        // row3

        drawSmoothOutlineButton(0, 130, 60, 40, COLOR_ACCENT[config.colorAccent], TFT_WHITE, "-");

        drawSmoothOutlineButton(240 - 62, 130, 60, 40, COLOR_ACCENT[config.colorAccent], TFT_WHITE, "+");
        tft->setTextDatum(MC_DATUM);
        tft->setTextColor(TFT_WHITE);
        tft->drawString("Step length", 120, 120, 2);
        String s_length = "";
        s_length += old_stepLength;
        s_length += " cm";
        drawSmoothOutlineButton(62, 130, 240 - 62 - 60 - 2, 40, COLOR_ACCENT[config.colorAccent], TFT_BLACK, s_length);
        s_length = "";
        s_length += stepLenght;
        s_length += " cm";
        drawSmoothOutlineButton(62, 130, 240 - 62 - 60 - 2, 40, COLOR_ACCENT[config.colorAccent], TFT_WHITE, s_length);

        // row 4

        drawButton(0, 190, 240, 40, COLOR_ACCENT[config.colorAccent], TFT_BLACK, "Reset daily step counter");
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
                // tft->fillCircle(SBOldvalue, Y + 3, 2, TFT_BLACK);
                tft->fillSmoothCircle(SBOldvalue, Y + 5, 2, TFT_BLACK, TFT_BLACK);
                // tft->drawRoundRect(X, Y, width - X, 8, 3, TFT_BLUE);
                tft->drawSmoothRoundRect(X, Y, 4, 4 - 1, width - X, 10, COLOR_ACCENT[config.colorAccent], TFT_BLACK);
                // tft->fillCircle(SBvalue, Y + 3, 2, TFT_WHITE);
                tft->fillSmoothCircle(SBvalue, Y + 5, 2, TFT_WHITE, TFT_BLACK);
                oldValue = value;
                drawButton(0, 190, 80, 40, COLOR_ACCENT[config.colorAccent], TFT_BLACK, "SAVE");
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
        // tft->drawRoundRect(X, Y, width - X, 8, 3, TFT_BLUE);
        tft->drawSmoothRoundRect(X, Y, 4, 4 - 1, width - X, 10, COLOR_ACCENT[config.colorAccent], TFT_BLACK);
        // tft->fillCircle(SBvalue, Y + 3, 2, TFT_WHITE);
        tft->fillSmoothCircle(SBvalue, Y + 5, 2, TFT_WHITE, TFT_BLACK);
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
                tft->fillCircle(SBOldvalue, Y + 5, 2, TFT_BLACK);
                // tft->fillSmoothCircle(SBOldvalue, Y + 5, 2, TFT_BLACK, TFT_BLACK);
                // tft->drawRoundRect(X, Y, width - X, 8, 3, TFT_BLUE);
                tft->drawSmoothRoundRect(X, Y, 4, 4 - 1, width - X, 10, COLOR_ACCENT[config.colorAccent], TFT_BLACK);

                tft->fillCircle(SBvalue, Y + 5, 2, TFT_WHITE);
                // tft->fillSmoothCircle(SBvalue, Y + 5, 2, TFT_WHITE, TFT_BLACK);
                oldValue2 = value;
                drawButton(0, 190, 80, 40, COLOR_ACCENT[config.colorAccent], TFT_BLACK, "SAVE");
        }
}
void drawWgetSeekBarBright(uint8_t X, uint8_t Y, uint8_t value)
{
        tft->setTextDatum(MC_DATUM);
        tft->setTextColor(TFT_GREEN);
        tft->drawString("BRIGHTNESS", 120, 66, 2);
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
        // tft->drawRoundRect(X, Y, width - X, 8, 3, TFT_BLUE);
        tft->drawSmoothRoundRect(X, Y, 4, 4 - 1, width - X, 10, COLOR_ACCENT[config.colorAccent], TFT_BLACK);
        tft->fillCircle(SBvalue, Y + 5, 2, TFT_WHITE);
        // tft->fillSmoothCircle(SBvalue, Y + 5, 2, TFT_WHITE, TFT_BLACK);
        oldValue2 = value;
}
void pickAccent()
{
        // set title
        tft->fillRect(80, 0, 80, 60, TFT_WHITE);
        tft->setTextColor(TFT_BLACK);
        tft->drawString("PICK", 120, 22, 2);
        tft->drawString("ACCENT", 120, 34, 2);

        tft->fillRect(0, 60, 240, 180, TFT_BLACK);
        // if (config.colorAccent == 0)

        drawSmoothButton(0, 60, 80, 60, COLOR_ACCENT[0], TFT_BLACK, TFT_BLACK, "PURPLE");    // 4//0
        drawSmoothButton(80, 60, 80, 60, COLOR_ACCENT[1], TFT_BLACK, TFT_BLACK, "BLUE");     // 5//1
        drawSmoothButton(160, 60, 80, 60, COLOR_ACCENT[2], TFT_BLACK, TFT_BLACK, "D_GREEN"); // 6//2
        drawSmoothButton(0, 120, 80, 60, COLOR_ACCENT[3], TFT_BLACK, TFT_BLACK, "YELLOW");   // 7//3
        drawSmoothButton(80, 120, 80, 60, COLOR_ACCENT[4], TFT_BLACK, TFT_BLACK, "PINK");    // 8//4
        drawSmoothButton(160, 120, 80, 60, COLOR_ACCENT[5], TFT_BLACK, TFT_BLACK, "ORANGE"); // 9//5
        drawSmoothButton(0, 180, 80, 60, COLOR_ACCENT[6], TFT_BLACK, TFT_BLACK, "RED");      // 10//6
        drawSmoothButton(80, 180, 80, 60, COLOR_ACCENT[7], TFT_BLACK, TFT_BLACK, "MAGENTA"); // 11//7
        drawSmoothButton(160, 180, 80, 60, COLOR_ACCENT[8], TFT_BLACK, TFT_BLACK, "D_CYAN"); // 11//8

        // tft->fillRect(config.colorAccent * 80, config.colorAccent/3+1*60, 240, 60, TFT_RED);
        // tft->fillCircle(((config.colorAccent / 3) * 80) + 10, (((config.colorAccent / 3) + 1) * 60) + 10, 6, TFT_BLACK);
        // tft->fillSmoothCircle(((config.colorAccent / 3) * 80) + 10, (((config.colorAccent / 3) + 1) * 60) + 10, 6, TFT_BLACK, COLOR_ACCENT[config.colorAccent]);
        int row = 70;
        int col = (-70);
        for (size_t i = 0; i < 9; i++)
        {
                col += 80;
                if (i % 3 == 0 && i > 0)
                {
                        row += 60;
                        col = 10;
                }
                if (i == config.colorAccent)
                        tft->fillSmoothCircle(col, row, 6, TFT_WHITE, COLOR_ACCENT[config.colorAccent]);
        }
}