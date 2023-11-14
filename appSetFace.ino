void drawSetFace()
{
        tft->setTextFont(2);
        tft->setCursor(3, 76);
        tft->setTextColor(TFT_WHITE);
        tft->print("random face every wakeup");
        drawSmoothSwitch(170, 70, COLOR_ACCENT[config.colorAccent], TFT_BLACK, config.rnd_face);
        tft->setTextColor(TFT_WHITE);
        tft->drawString("category to display :", 2, 170, 2);
        for (size_t i = 0; i < 3; i++)
                drawFaceFilter(i);
}
void drawFaceFilter(int col)
{
        if (col == 0)
        {
                drawSmoothButton(0, 180, 80, 60, COLOR_ACCENT[config.colorAccent], TFT_BLACK, TFT_WHITE, "ANALOG");
                tft->fillSmoothCircle(0 + 10, 180 + 10, 6, (config.show_analog) ? TFT_WHITE : COLOR_ACCENT[config.colorAccent], COLOR_ACCENT[config.colorAccent]);
        }
        else if (col == 1)
        {
                drawSmoothButton(80, 180, 80, 60, COLOR_ACCENT[config.colorAccent], TFT_BLACK, TFT_WHITE, "NUMBER");
                tft->fillSmoothCircle(80 + 10, 180 + 10, 6, (config.show_number) ? TFT_WHITE : COLOR_ACCENT[config.colorAccent], COLOR_ACCENT[config.colorAccent]);
        }
        else if (col == 2)
        {
                drawSmoothButton(160, 180, 80, 60, COLOR_ACCENT[config.colorAccent], TFT_BLACK, TFT_WHITE, "TEXT");
                tft->fillSmoothCircle(160 + 10, 180 + 10, 6, (config.show_text) ? TFT_WHITE : COLOR_ACCENT[config.colorAccent], COLOR_ACCENT[config.colorAccent]);
        }
}