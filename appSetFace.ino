void drawSetFace()
{
        tft->setTextFont(2);
        tft->setCursor(3, 76);
        tft->setTextColor(TFT_BLACK);
        tft->print("random face every wakeup");
        // (config.rnd_face) ? drawSwitch(170, 70, TFT_BLUE, rgbToHex(200, 200, 200), true) : drawSwitch(170, 70, TFT_BLUE, rgbToHex(200, 200, 200), false);
        // drawSwitch(170, 70, TFT_BLUE, rgbToHex(200, 200, 200), config.rnd_face);
        drawSmoothSwitch(170, 70, COLOR_ACCENT[config.colorAccent], TFT_BLACK, config.rnd_face);
}