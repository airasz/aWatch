// id=

String sdata;

bool blinking = true;
int nblinking = 6;
bool blinkstate = false;
int blinkval = 255;
int countblink = 16;

String oldsdata;
int tryrequest = 0;
bool foundRadio = false;
String data;
char c;
int toScreenSleep = 0;

int cx = 0, cy = 15;
void showSMonitor()
{
    tft->fillScreen(TFT_BLACK);
    tft->setTextSize(1);
    // testdrawtext("USB serial screen fo pi-radio, baud = 115200\nWaiting for incoming signal...", TFT_WHITE);
    printWordWrap("USB serial screen fo pi-radio, baud = 115200\nWaiting for incoming signal...", COLOR_MEDIUM[random(12)]);
    Serial.printf("screetimeout  : %d \n", screenTimeOut);
}
void listenSMonitor()
{
    while (Serial.available() > 0)
    {
        delay(10);
        c = Serial.read();
        data += c;
    }
    if (data.length() > 0)
    {
        //    Serial.println(data);
        // tb_display_print_String(data.c_str(), 20);
        toScreenSleep = 0;
        if (data.startsWith("rotation"))
        {
            int sr = data.substring(9).toInt();
            tft->setRotation(sr);
            testdrawtext("rotated", COLOR_MEDIUM[random(12)]);
        }
        else if (data.startsWith("set volume"))
        {
            printtextbig(data, COLOR_MEDIUM[random(12)]);
        }
        else if (data.startsWith("play pos"))
        {
            printtextbig(data, COLOR_MEDIUM[random(12)]);
        }
        else
        {
            testdrawtext(data, COLOR_MEDIUM[random(10)]);
            printWordWrap(data, COLOR_MEDIUM[random(12)]);
        }
        data = "";
    }
}
void testdrawtext(char *text, uint16_t color)
{
    setupFont12();
    tft->fillScreen(TFT_BLACK);
    tft->setCursor(cx, cy);
    int tl = sizeof(text);
    int cymr = map(tl, 10, 100, 80, 15);
    tft->setCursor(cx, random(1, cymr));
    tft->setTextColor(color, TFT_BLACK);
    tft->setTextWrap(true);
    tft->print(text);
}
void testdrawtext(String text, uint16_t color)
{
    setupFont12();

    tft->setCursor(cx, cy);
    tft->setTextWrap(true);
    // tft->setTextColor(TFT_BLACK, TFT_BLACK);
    // tft->print(oldsdata);
    tft->fillScreen(TFT_BLACK);
    int tl = text.length();
    int cymr = map(tl, 10, 100, 80, 15);
    tft->setCursor(cx, random(1, cymr));
    tft->setTextColor(color, TFT_BLACK);

    // tft->print(tl);
    tft->setTextWrap(true);
    tft->print(text);
    oldsdata = text;

    // tft->unloadFont();
}
void printtextbig(
    String text, uint16_t color)
{

    setupFont18();
    // tft->unloadFont();
    // delay(25);
    // tft->loadFont(sfpd_r28);
    tft->setCursor(cx, cy);
    tft->setTextWrap(true);
    // tft->setTextColor(TFT_BLACK, TFT_BLACK);
    // tft->print(oldsdata);
    tft->fillScreen(TFT_BLACK);
    int tl = text.length();
    int cymr = map(tl, 10, 100, 80, 15);
    tft->setCursor(cx, random(1, cymr));
    tft->setTextColor(color, TFT_BLACK);

    // tft->print(tl);
    tft->print(text);
    oldsdata = text;

    // tft->unloadFont();
    // delay(25);
    // tft->loadFont(sfpt_r14);
}

void printWordWrap(String text, uint16_t color)
{

    setupFont12();
    cx = 0, cy = 14;
    // tft->setCursor(cx, cy);
    tft->setTextWrap(true, false);
    // tft->setTextColor(TFT_BLACK, TFT_BLACK);
    // tft->print(oldsdata);
    tft->fillScreen(TFT_BLACK);
    int tl = text.length();
    // int cymr = map(tl, 10, 100, 80, 15);
    // tft->setCursor(cx, random(1, cymr));
    tft->setCursor(cx, cy);
    tft->setTextColor(color, TFT_BLACK);

    // tft->print(tl);
    printSplitString(text, color);
}
void printSplitString(String text, uint16_t color)
{
    int wordStart = 0;
    int wordEnd = 0;
    while ((text.indexOf(' ', wordStart) >= 0) && (wordStart <= text.length()))
    {
        wordEnd = text.indexOf(' ', wordStart + 1);
        uint16_t len = tft->textWidth(text.substring(wordStart, wordEnd));
        if (tft->getCursorX() + len >= tft->width())
        {
            tft->println();
            if (wordStart > 0)
                wordStart++;
        }
        tft->print(text.substring(wordStart, wordEnd));
        wordStart = wordEnd;
    }
}
