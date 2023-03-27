#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Panasonic.h>

const uint16_t irLed = 13; // IR led pin
IRPanasonicAc ac(irLed);   // Set the GPIO used for sending messages.

int itemp = 22;
int imode = 0;
int ifan = 0;
int iswing = 0;
String armode[] = {"auto", "", "dry", "cool"};
String arfan[] = {"min", "med", "max", "auto"};
String arswing[] = {"", "highest", "high", "med", "low", "lowest", "auto"};
int aswing[5] = {1, 2, 3, 4, 15};
// int step;
void startAC()
{
        ac.begin();
}
void drawACremote()
{

        // tft->fillRect(0, 60, 240, 180, TFT_BLACK);
        //row2
        drawOutlineButton(0, 70, 60, 40, TFT_BLUE, TFT_WHITE, "-");
        drawOutlineButton(240 - 62, 70, 60, 40, TFT_BLUE, TFT_WHITE, "+");
        tft->setTextDatum(MC_DATUM);
        tft->setTextColor(TFT_WHITE);
        tft->drawString("MODE", 120, 64, 2);
        String hou = "";
        hou += armode[old_tmpmwarn];
        drawOutlineButton(62, 70, 240 - 62 - 60 - 2, 40, TFT_BLUE, TFT_BLACK, hou);
        hou = "";
        hou += armode[imode];
        drawOutlineButton(62, 70, 240 - 62 - 60 - 2, 40, TFT_BLUE, TFT_WHITE, hou);

        //row3
        drawOutlineButton(0, 130, 60, 40, TFT_BLUE, TFT_WHITE, "-");

        drawOutlineButton(240 - 62, 130, 60, 40, TFT_BLUE, TFT_WHITE, "+");
        tft->setTextDatum(MC_DATUM);
        tft->setTextColor(TFT_WHITE);
        tft->drawString("TEMP", 120, 124, 2);

        String mnit = "";
        mnit += old_tmpvib;
        drawOutlineButton(62, 130, 240 - 62 - 60 - 2, 40, TFT_BLUE, TFT_BLACK, mnit);
        mnit = "";
        mnit += itemp;
        drawOutlineButton(62, 130, 240 - 62 - 60 - 2, 40, TFT_BLUE, TFT_WHITE, mnit);

        drawButton(0, 190, 80, 40, TFT_BLUE, TFT_WHITE, "ON");
        drawButton(80, 190, 80, 40, TFT_BLUE, TFT_WHITE, "OFF");
        drawButton(160, 190, 80, 40, TFT_BLUE, TFT_WHITE, "SEND");

        old_tmpmwarn = imode;
        old_tmpvib = itemp;
}

void setupAC()
{
        ac.setModel(kPanasonicRkr);
        ac.setFan(0);
        ac.setMode(imode);
        ac.setTemp(itemp);
        ac.setSwingVertical(kPanasonicAcSwingVHighest);
        ac.setSwingHorizontal(kPanasonicAcSwingHAuto);
}
void PanasonicOn()
{
        setupAC();
        ac.on();
        ac.send();
}

void PanasonicOff()
{
        ac.off();
        ac.send();
}