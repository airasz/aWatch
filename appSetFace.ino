void drawSetFace()
{
        tft->setTextFont(2);
        tft->setCursor(3, 76);
        tft->setTextColor(TFT_WHITE);
        tft->print("random face every wakeup");
        // (config.rnd_face) ? drawSwitch(170, 70, TFT_BLUE, rgbToHex(200, 200, 200), true) : drawSwitch(170, 70, TFT_BLUE, rgbToHex(200, 200, 200), false);
        // drawSwitch(170, 70, TFT_BLUE, rgbToHex(200, 200, 200), config.rnd_face);
        drawSmoothSwitch(170, 70, COLOR_ACCENT[config.colorAccent], TFT_BLACK, config.rnd_face);

        // drawOutlineButton(0, 120, 80, 60, COLOR_ACCENT[config.colorAccent], TFT_WHITE, "ANALOG"); // 7//3
        // if (config.show_analog)
        //         tft->fillCircle(0 + 10, 120 + 10, 6, TFT_BLACK);
        // drawOutlineButton(80, 120, 80, 60, COLOR_ACCENT[config.colorAccent], TFT_WHITE, "NUMBER"); // 8//4
        // if (config.show_number)
        //         tft->fillCircle(80 + 10, 120 + 10, 6, TFT_BLACK);
        // drawOutlineButton(160, 120, 80, 60, COLOR_ACCENT[config.colorAccent], TFT_WHITE, "TEXT"); // 9//5}
        // if (config.show_text)
        //         tft->fillCircle(160 + 10, 120 + 10, 6, TFT_BLACK);
        tft->setTextColor(TFT_WHITE);
        tft->drawString("category to display :", 2, 170, 2);
        for (size_t i = 0; i < 3; i++)
                drawFaceFilter(i);
}
void drawFaceFilter(int col)
{
        if (col == 0)
        {
                // drawOutlineButton(0, 180, 80, 60, COLOR_ACCENT[config.colorAccent], TFT_WHITE, "ANALOG"); // 7//3
                // drawSmoothOutlineButton(0, 180, 80, 60, COLOR_ACCENT[config.colorAccent], TFT_WHITE, "ANALOG");
                //   if (config.show_analog)
                // tft->fillCircle(0 + 10, 180 + 10, 6, (config.show_analog) ? TFT_WHITE : TFT_BLACK);
                // tft->fillSmoothCircle(0 + 10, 180 + 10, 6, (config.show_analog) ? TFT_WHITE : TFT_BLACK, TFT_BLACK);

                drawSmoothButton(0, 180, 80, 60, COLOR_ACCENT[config.colorAccent], TFT_BLACK, TFT_WHITE, "ANALOG");
                tft->fillSmoothCircle(0 + 10, 180 + 10, 6, (config.show_analog) ? TFT_WHITE : COLOR_ACCENT[config.colorAccent], COLOR_ACCENT[config.colorAccent]);
        }
        else if (col == 1)
        {
                // drawOutlineButton(80, 180, 80, 60, COLOR_ACCENT[config.colorAccent], TFT_WHITE, "NUMBER"); // 8//4
                // drawSmoothOutlineButton(80, 180, 80, 60, COLOR_ACCENT[config.colorAccent], TFT_WHITE, "NUMBER");
                //    if (config.show_number)
                // tft->fillCircle(80 + 10, 180 + 10, 6, (config.show_number) ? TFT_WHITE : TFT_BLACK);
                // tft->fillSmoothCircle(80 + 10, 180 + 10, 6, (config.show_number) ? TFT_WHITE : TFT_BLACK, TFT_BLACK);

                drawSmoothButton(80, 180, 80, 60, COLOR_ACCENT[config.colorAccent], TFT_BLACK, TFT_WHITE, "NUMBER");
                tft->fillSmoothCircle(80 + 10, 180 + 10, 6, (config.show_number) ? TFT_WHITE : COLOR_ACCENT[config.colorAccent], COLOR_ACCENT[config.colorAccent]);
        }
        else if (col == 2)
        {
                // drawOutlineButton(160, 180, 80, 60, COLOR_ACCENT[config.colorAccent], TFT_WHITE, "TEXT"); // 9//5}
                // drawSmoothOutlineButton(160, 180, 80, 60, COLOR_ACCENT[config.colorAccent], TFT_WHITE, "TEXT");
                //   if (config.show_text)
                // tft->fillCircle(160 + 10, 180 + 10, 6, (config.show_text) ? TFT_WHITE : TFT_BLACK);
                // tft->fillSmoothCircle(160 + 10, 180 + 10, 6, (config.show_text) ? TFT_WHITE : TFT_BLACK, TFT_BLACK);

                drawSmoothButton(160, 180, 80, 60, COLOR_ACCENT[config.colorAccent], TFT_BLACK, TFT_WHITE, "TEXT");
                tft->fillSmoothCircle(160 + 10, 180 + 10, 6, (config.show_text) ? TFT_WHITE : COLOR_ACCENT[config.colorAccent], COLOR_ACCENT[config.colorAccent]);
        }
}