#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Panasonic.h>

const uint16_t irLed = 13; // IR led pin
IRPanasonicAc ac(irLed);   // Set the GPIO used for sending messages.
IRsend irsend(13);
int itemp = 22;
int imode = 0;
int ifan = 0;
int iswing = 0;
const String armode[] = {"auto", "", "dry", "cool"};
const String arfan[] = {"min", "med", "max", "auto"};
const String arswing[] = {"", "highest", "high", "med", "low", "lowest", "auto"};
int aswing[5] = {1, 2, 3, 4, 15};
// int step;
void startAC()
{
        ac.begin();
        irsend.begin();
}
void drawSelectBrand()
{

        drawOutlineButton(0, 130, 60, 40, TFT_BLUE, TFT_WHITE, "Pana");
        drawOutlineButton(240 - 62, 130, 60, 40, TFT_BLUE, TFT_WHITE, "LG");
}
void drawACremote()
{
        Serial.println("draw AC remote");
        // tft->fillRect(0, 60, 240, 180, TFT_BLACK);
        // row2
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

        // row3
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
//========================= LG ========================

// 0 : TOWER
// 1 : WALL
const unsigned int kAcLG_Type = 0;

// 0 : cooling
// 1 : heating
unsigned int acLG_heat = 0;

// 0 : off
// 1 : on
unsigned int acLG_power_on = 0;

// 0 : off
// 1 : on --> power on
unsigned int acLG_air_clean_state = 0;

// temperature : 18 ~ 30
unsigned int acLG_temperature = 25;

// 0 : low
// 1 : mid
// 2 : high
// if kAc_Type = 1, 3 : change
unsigned int acLG_flow = 0;

const uint8_t kAcLG_Flow_Tower[3] = {0, 4, 6};
const uint8_t kAcLG_Flow_Wall[4] = {0, 2, 4, 5};

uint32_t acLG_code_to_sent;

void Ac_LG_Send_Code(uint32_t code)
{
        Serial.print("code to send : ");
        Serial.print(code, BIN);
        Serial.print(" : ");
        Serial.println(code, HEX);

#if SEND_LG
        irsend.sendPanasonic(code, 28);
#else  // SEND_LG
        Serial.println("Can't send because SEND_LG has been disabled.");
#endif // SEND_LG
}

void Ac_LG_Activate(unsigned int temperature, unsigned int air_flow,
                    unsigned int heat)
{
        acLG_heat = heat;
        unsigned int ac_msbits1 = 8;
        unsigned int ac_msbits2 = 8;
        unsigned int ac_msbits3 = 0;
        unsigned int ac_msbits4;
        if (acLG_heat == 1)
                ac_msbits4 = 4; // heating
        else
                ac_msbits4 = 0; // cooling
        unsigned int ac_msbits5 = (temperature < 15) ? 0 : temperature - 15;
        unsigned int ac_msbits6 = 0;

        if (air_flow <= 2)
        {
                if (kAcLG_Type == 0)
                        ac_msbits6 = kAcLG_Flow_Tower[air_flow];
                else
                        ac_msbits6 = kAcLG_Flow_Wall[air_flow];
        }

        // calculating using other values
        unsigned int ac_msbits7 = (ac_msbits3 + ac_msbits4 + ac_msbits5 +
                                   ac_msbits6) &
                                  B00001111;
        acLG_code_to_sent = ac_msbits1 << 4;
        acLG_code_to_sent = (acLG_code_to_sent + ac_msbits2) << 4;
        acLG_code_to_sent = (acLG_code_to_sent + ac_msbits3) << 4;
        acLG_code_to_sent = (acLG_code_to_sent + ac_msbits4) << 4;
        acLG_code_to_sent = (acLG_code_to_sent + ac_msbits5) << 4;
        acLG_code_to_sent = (acLG_code_to_sent + ac_msbits6) << 4;
        acLG_code_to_sent = (acLG_code_to_sent + ac_msbits7);

        Ac_LG_Send_Code(acLG_code_to_sent);

        acLG_power_on = 1;
        acLG_temperature = temperature;
        acLG_flow = air_flow;
}

void Ac_LG_Change_Air_Swing(int air_swing)
{
        if (kAcLG_Type == 0)
        {
                if (air_swing == 1)
                        acLG_code_to_sent = 0x881316B;
                else
                        acLG_code_to_sent = 0x881317C;
        }
        else
        {
                if (air_swing == 1)
                        acLG_code_to_sent = 0x8813149;
                else
                        acLG_code_to_sent = 0x881315A;
        }
        Ac_LG_Send_Code(acLG_code_to_sent);
}

void Ac_LG_Power_Down()
{

        acLG_code_to_sent = 0x88C0051;

        Ac_LG_Send_Code(acLG_code_to_sent);

        acLG_power_on = 0;
}

void Ac_LG_Air_Clean(int air_clean)
{
        if (air_clean == '1')
                acLG_code_to_sent = 0x88C000C;
        else
                acLG_code_to_sent = 0x88C0084;

        Ac_LG_Send_Code(acLG_code_to_sent);

        acLG_air_clean_state = air_clean;
}

auto bLG = false;
auto goSend = false;
void drawRemoteLG()
{
        Serial.println("draw LG AC remote");
        // tft->fillRect(0, 60, 240, 180, TFT_BLACK);
        // row2
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

        // row3
        drawOutlineButton(0, 130, 60, 40, TFT_BLUE, TFT_WHITE, "-");

        drawOutlineButton(240 - 62, 130, 60, 40, TFT_BLUE, TFT_WHITE, "+");
        tft->setTextDatum(MC_DATUM);
        tft->setTextColor(TFT_WHITE);
        tft->drawString("TEMP", 120, 124, 2);

        String mnit = "";
        mnit += old_tmpvib;
        drawOutlineButton(62, 130, 240 - 62 - 60 - 2, 40, TFT_BLUE, TFT_BLACK, mnit);
        mnit = "";
        mnit += acLG_temperature;
        drawOutlineButton(62, 130, 240 - 62 - 60 - 2, 40, TFT_BLUE, TFT_WHITE, mnit);

        drawButton(0, 190, 80, 40, TFT_BLUE, TFT_WHITE, "ON");
        drawButton(80, 190, 80, 40, TFT_BLUE, TFT_WHITE, "OFF");
        drawButton(160, 190, 80, 40, TFT_BLUE, TFT_WHITE, "SEND");

        old_tmpmwarn = imode;
        old_tmpvib = acLG_temperature;
}