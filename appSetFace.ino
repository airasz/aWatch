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
        const int x[3] = {0, 80, 160};
        const String t[3] = {"ANALOG", "NUMBER", "TEXT"};
        uint16_t dol = itsLightColor(COLOR_ACCENT[config.colorAccent]) ? TFT_BLACK : TFT_WHITE;
        drawSmoothButton(x[col], 180, 80, 60, COLOR_ACCENT[config.colorAccent], TFT_BLACK, TFT_WHITE, t[col]);
        tft->fillSmoothCircle(x[col] + 10, 180 + 10, 6, (config.show_analog) ? dol : COLOR_ACCENT[config.colorAccent], COLOR_ACCENT[config.colorAccent]);
}