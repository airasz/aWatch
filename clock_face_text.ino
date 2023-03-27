#include "stringres.h"
#include "Free_Fonts.h"
#include "mathematicalize.h"
// #include "MATHS18pt7b.h"
// void displaySysInfo(int);
// void setupFont12();
// void setupFont18();
// void setupFont24();
void javaneseClock(int h, int m)
{

        // tnow = ttgo->rtc->getDateTime();
        int currentHour = h;
        int currentMinute = m;
        tft->setTextSize(1);
        tft->setTextColor(COLORS_LIGHT[random(10)]);
        tft->setTextFont(2);
        tft->fillScreen(TFT_BLACK); // CLEAR DISPLAY
        String word, word1, word2;
        if (currentMinute < 40)
        {
                if (currentMinute == 30)
                {
                        if (currentHour == 23)
                        {
                                word = minuteTOword(currentMinute);
                                word1 = "\n    ";
                                word2 = jamTOword(currentHour - 11);
                        }
                        else
                        {
                                word = minuteTOword(currentMinute);
                                word1 = "\n   ";
                                word2 = jamTOword(currentHour + 1);
                        }
                }
                else if (currentMinute == 0 || currentMinute == 15)
                {
                        word = jamTOword(currentHour);
                        word1 = " \n    ";
                        word2 = minuteTOword(currentMinute);
                }
                else
                {
                        word = jamTOword(currentHour);
                        word1 = "\n  luwih        ";
                        word2 = minuteTOword(currentMinute);
                }
        }
        else
        {

                word = jamTOword(currentHour + 1);
                word1 = "\n   kurang      ";
                word2 = minuteTOword(currentMinute);
        }
        int totalLength = word.length() + word1.length() + word2.length();
        Serial.printf("clock face text, total length =  %d\n ", totalLength);
        if (totalLength > 35 && totalLength < 45)
                tft->setCursor(random(0, 3), random(60, 65));
        else if (totalLength > 15 && totalLength < 36)
                tft->setCursor(random(0, 3), random(80, 110));
        else
                tft->setCursor(random(0, 3), random(90, 110));

        // tft->setCursor(random(3, 12), random(50, 110));
        (word.length() > 7) ? setupFont18() : setupFont24();
        tft->print(word);

        setupFont12();
        tft->setTextColor(COLORS_LIGHT[random(10)]);
        tft->print(word1);
        if (word1.length() > 5)
        {
                setupFont18();
                tft->print(" \n");
        }

        (word2.length() > 10) ? setupFont12() : setupFont18();
        tft->setTextColor(COLORS_LIGHT[random(10)]);
        tft->print(word2);

        displaySysInfo(0);
}

void recordActivity()
{
        int rf12 = random(9);
        int rf18 = random(9);
        tft->fillScreen(TFT_BLACK); // CLEAR DISPLAY
        tft->setCursor(0, 20);
        float cal;
        setupFont12(rf12);
        int color_ = COLORS_LIGHT[random(10)];
        //  tft->setTextColor(COLORS_LIGHT[random(10)]);
        tft->setTextColor(color_);
        tft->print("Today step : \n");
        setupFont18(rf18);
        tft->setTextColor(TFT_WHITE);
        tft->print(daily_step);
        tft->setTextColor(color_);

        setupFont12(rf12);
        tft->print("\nToday coverage : \n");
        tft->setTextColor(TFT_WHITE);
        setupFont18(rf18);
        tft->print(((daily_step)*stepLenght) / 100);
        tft->print(" m");
        tft->setTextColor(color_);

        setupFont12(rf12);
        tft->print("\nCalory burned : \n");
        tft->setTextColor(TFT_WHITE);
        cal = (float)daily_step / 25.0;
        setupFont18(rf18);
        tft->print(cal);
        tft->print(" kcal");

        tft->setTextColor(color_);
        setupFont12(rf12);
        tft->print("\nEstimate drop weight: \n");
        tft->setTextColor(TFT_WHITE);
        cal = (float)daily_step / 25.0;
        setupFont18(rf18);
        float w = cal * 0.128;
        if (w < 1000)
        {

                tft->print(w);
                tft->print(" grams");
        }
        else
        {
                w = w / 1000.00;
                tft->print(w);
                tft->print(" Kg");
        }
}
void mathFace2(int h, int m)
{
        // U8G2_FOR_ADAFRUIT_GFX u8f; // U8g2 font instance

        int currentHour = h;
        int currentMinute = m;
        tft->setTextSize(1);
        tft->setTextColor(COLORS_LIGHT[random(10)]);
        tft->setTextFont(2);
        tft->fillScreen(TFT_BLACK); // CLEAR DISPLAY
        tft->setCursor(random(0, 3), random(60, 65));
        String word, word2;
        // setupFont18();
        int r = random(0, h);
        word = drawFormula(1, h);
        tft->setTextColor(COLORS_LIGHT[random(10)]);
        // u8f.begin(*tft);
        int totalLength = word.length() + 1 + word2.length();
        setupFont24();
        // Serial.printf("clock face text, total length =  %d\n ", totalLength);
        if (totalLength > 35 && totalLength < 45)
        {
                tft->setCursor(random(0, 3), random(60, 65));
        }
        else if (totalLength > 15 && totalLength < 36)
        {
                tft->setCursor(random(0, 3), random(80, 110));
        }
        else
        {
                tft->setCursor(random(0, 3), random(90, 110));
        }

        if (word.indexOf("**") > 0)
        {
                // word.replace("**", "²");
                tft->setTextColor(COLORS_LIGHT[random(10)]);
                tft->setCursor(random(2, 40), random(110, 40)); // start writing at this position
                tft->print(word);
                // tft->clearBuffer();
        }
        else if (word.startsWith("sqr"))
        {

                // word.replace("sqr", "√");
                word.replace("sqr", "V");
                tft->setTextColor(COLORS_LIGHT[random(10)]);
                tft->setCursor(random(2, 40), random(110, 40)); // start writing at this position
                tft->print(word);
        }
        else
        {
                tft->setCursor(random(2, 40), random(110, 40));
                tft->setTextColor(COLORS_LIGHT[random(10)]);
                // (word.length() > 3) ? setupFont18() : setupFont24();
                setupFont24();
                tft->print(word);
        }

        word2 = "";
        for (int i = 0; i < r / 10; i++)
        {
                word2 += " ";
        }
        // word2 += "m=";
        word2 = drawFormula(1, m);

        if (word2.indexOf("**") > 0)
        {
                // word2.replace("**", "²");
                tft->setTextColor(COLORS_LIGHT[random(10)]);
                tft->setCursor(random(2, 40), random(180, 230)); // start writing at this position
                tft->print(word2);
        }
        else if (word2.startsWith("sqr"))
        {
                // word2.replace("sqr", "√");
                word2.replace("sqr", "V");
                tft->setTextColor(COLORS_LIGHT[random(10)]);
                tft->setCursor(random(2, 40), random(180, 230)); // start writing at this position
                tft->print(word2);
        }
        else
        {
                tft->setCursor(random(2, 40), random(180, 230));
                // (word2.length() > 10)
                //     ? setupFont12()
                //     : setupFont18();

                // (word2.length() > 3) ? setupFont18() : setupFont24();
                // setupFont24();
                tft->setTextColor(COLORS_LIGHT[random(10)]);
                tft->print(word2);
        }

        displaySysInfo(3); // appInfo.ino
}
void mathFace(int h, int m)
{
        // U8G2_FOR_ADAFRUIT_GFX u8f; // U8g2 font instance

        int currentHour = h;
        int currentMinute = m;
        tft->setTextSize(1);
        tft->setTextColor(COLORS_LIGHT[random(10)]);
        tft->setTextFont(2);
        tft->fillScreen(TFT_BLACK); // CLEAR DISPLAY
        tft->setCursor(random(0, 3), random(60, 65));
        String word, word2;
        setupFont18();
        int r = random(0, h);
        word += drawFormula(1, h);
        tft->setTextColor(COLORS_LIGHT[random(10)]);

        int totalLength = word.length() + 1 + word2.length();
        // Serial.printf("clock face text, total length =  %d\n ", totalLength);
        if (totalLength > 35 && totalLength < 45)
        {
                u8f.setCursor(random(0, 3), random(60, 65));
        }
        else if (totalLength > 15 && totalLength < 36)
        {
                u8f.setCursor(random(0, 3), random(80, 110));
        }
        else
        {
                u8f.setCursor(random(0, 3), random(90, 110));
        }

        if (word.indexOf("**") > 0)
        {
                word.replace("**", "²");
                u8f.setFont(u8g2_font_fur42_tf); // extended font
                u8f.setFontMode(1);              // use u8g2 transparent mode (this is default)
                u8f.setForegroundColor(COLORS_LIGHT[random(10)]);
                u8f.setCursor(random(2, 40), random(40, 110)); // start writing at this position
                u8f.print(word);
                // u8f.clearBuffer();
        }
        else if (word.startsWith("sqr") || word.indexOf("sqr") > 0)
        {

                word.replace("sqr", "√");
                u8f.setFont(u8g2_font_fur42_t_symbol); // extended font
                u8f.setFontMode(1);                    // use u8g2 transparent mode (this is default)
                u8f.setForegroundColor(COLORS_LIGHT[random(10)]);
                u8f.setCursor(random(2, 40), random(40, 110)); // start writing at this position
                u8f.print(word);
        }
        else
        {
                tft->setCursor(random(2, 40), random(40, 110));
                tft->setTextColor(COLORS_LIGHT[random(10)]);
                // (word.length() > 3) ? setupFont18() : setupFont24();
                setupFont24();
                tft->print(word);
        }

        word2 = "";
        for (int i = 0; i < r / 10; i++)
        {
                word2 += " ";
        }
        // word2 += "m=";
        word2 += drawFormula(1, m);

        if (word2.indexOf("**") > 0)
        {
                word2.replace("**", "²");
                u8f.setFont(u8g2_font_fur42_tf); // extended font
                u8f.setFontMode(1);              // use u8g2 transparent mode (this is default)
                u8f.setForegroundColor(COLORS_LIGHT[random(10)]);
                u8f.setCursor(random(2, 40), random(180, 200)); // start writing at this position
                u8f.print(word2);
        }
        else if (word2.startsWith("sqr") || word2.indexOf("sqr") > 0)
        {
                word2.replace("sqr", "√");
                u8f.setFont(u8g2_font_fur42_t_symbol); // extended font
                u8f.setFontMode(1);                    // use u8g2 transparent mode (this is default)
                u8f.setForegroundColor(COLORS_LIGHT[random(10)]);
                u8f.setCursor(random(2, 40), random(180, 200)); // start writing at this position
                u8f.print(word2);
        }
        else
        {
                tft->setCursor(random(2, 40), random(180, 200));
                // (word2.length() > 10)
                //     ? setupFont12()
                //     : setupFont18();

                // (word2.length() > 3) ? setupFont18() : setupFont24();
                setupFont24();
                tft->setTextColor(COLORS_LIGHT[random(10)]);
                tft->print(word2);
        }

        displaySysInfo(3); // appInfo.ino
}
String drawFormula(int clock, int value)
{
        // String rslt;
        char rslt[10];
        if (clock == 0) // mode 0 , without square root and multiply
        {
                int rnd1 = random(0, 2);
                if (rnd1 == 0) // multiply formula
                {
                        for (int i = 11; i > 0; i--)
                        {
                                if (value % i == 0) // habis dibagi 10
                                {
                                        int rr = value / i;
                                        int rndp = random(0, 2);
                                        sprintf(rslt, "%dx%d", rndp < 1 ? rr : value / rr, rndp < 1 ? value / rr : rr);
                                        // break;
                                }
                        } // end for
                }
                if (rnd1 == 1) // +/- formula
                {
                        int rnd2 = random(0, 2);
                        int r = random(0, value);
                        sprintf(rslt, "%d%s%d", (rnd2 < 1) ? value + r : r, (rnd2 < 1) ? "-" : "+", (rnd2 < 1) ? r : value - r);
                }
                return String(rslt);
        }
        if (clock == 1)
        {
                if (isPerfectSquare(value))
                {
                        Serial.printf(" %d is prefect square\n", value);
                        int rn = random(0, 2);
                        if (rn < 1) //*math
                        {
                                int rut = sqrt(value);
                                sprintf(rslt, "%d**", rut);
                                // rslt += String(rut);
                                return String(rslt);
                                // word2 = rslt;
                        }
                        else
                        {
                                return formulaize(value);
                        }
                }
                else
                {
                        if (value < 10)
                        {
                                int rn = random(0, 3);
                                if (rn == 0) //*math
                                {
                                        Serial.printf(" %d is not prefect square\n", value);
                                        return formulaize(value);
                                }
                                else if (rn == 1)
                                {
                                        int x = random(1, 10);
                                        int rr = value * x;
                                        sprintf(rslt, "%d/%d", rr, x);
                                        return String(rslt);
                                }
                                else if (rn == 2)
                                {
                                        int sqr = value * value;
                                        sprintf(rslt, "sqr%d", sqr);
                                        return String(rslt);
                                }
                        }
                        else
                        {
                                return formulaize(value);
                        }
                }
        }

        displaySysInfo(0);
}
bool isPerfectSquare(long double val)
{
        if (val >= 0)
        {
                long sq = sqrt(val);
                return (sq * sq == val);
        }
        return false;
}

String formulaize(int value)
{

        char rslt[6];
        int rnd1 = random(0, 2);
        // int rnd1 = 1;
        if (rnd1 == 0) // multiply formula
        {              // suspect heap crash
                for (int i = 0; i < 10; i++)
                {
                        int ii = 9 - i;
                        if (value % ii == 0) // habis dibagi 10
                        {
                                int rr = value / ii;
                                int rndp = random(0, 2);
                                sprintf(rslt, "%dx%d", rndp < 1 ? rr : value / rr, rndp < 1 ? value / rr : rr);
                                break;
                        }
                } // end for
                return String(rslt);
        }
        if (rnd1 == 1) // +/- formula
        {
                int rnd2 = random(0, 2);
                int r = random(0, value);
                sprintf(rslt, "%d%s%d", rnd2 < 1 ? value + r : r, rnd2 < 1 ? "-" : "+", rnd2 < 1 ? r : value - r);

                return String(rslt);
        }
}
String multiplize(int value)
{
}
void setupFont12()
{
        int rf = random(9);
        switch (rf)
        {
        case 0:
                tft->setFreeFont(FSSO12);
                // tft->loadFont(FSSO12, true);
                break;
        case 1:
                tft->setFreeFont(FMBO12);
                break;
        case 2:
                tft->setFreeFont(FMO12);
                break;
        case 3:
                tft->setFreeFont(FF14);
                break;
        case 4:
                tft->setFreeFont(FF26);
                break;
        case 5:
                tft->setFreeFont(FF30);
                break;
        case 6:
                tft->setFreeFont(FF38);
                break;
        case 7:
                tft->setFreeFont(FF46);
                break;
        case 8:
                tft->setFreeFont(FSI12);
                break;
        case 9:
                tft->setFreeFont(FSBI12);
                break;
        default:
                break;
        }
}
void setupFont12(int font)
{
        Serial.printf("font 12 : %d\n ", font);
        // Serial.print("font12: ");
        // Serial.println(font);
        switch (font)
        {
        case 0:
                tft->setFreeFont(FSSO12);
                break;
        case 1:
                // tft->setFreeFont(FMBO12);
                tft->setFreeFont(FSS12);
                break;
        case 2:
                // tft->setFreeFont(FMO12);
                tft->setFreeFont(FF42);
                break;
        case 3:
                // tft->setFreeFont(FF14);
                tft->setFreeFont(FF18);
                break;
        case 4:
                tft->setFreeFont(FF26);
                break;
        case 5:
                // tft->setFreeFont(FF30);
                tft->setFreeFont(FF34);
                break;
        case 6:
                tft->setFreeFont(FF38);
                break;
        case 7:
                tft->setFreeFont(FF46);
                break;
        case 8:
                tft->setFreeFont(FSI12);
                break;
        case 9:
                tft->setFreeFont(FSBI12);
                break;
        default:
                break;
        }
}
void setupFont18()
{
        int rf = random(9);
        switch (rf)
        {
        case 0:
                tft->setFreeFont(FM18);
                break;
        case 1:
                tft->setFreeFont(FMB18);
                break;
        case 2:
                tft->setFreeFont(FSS18);
                break;
        case 3:
                tft->setFreeFont(FSSB18);
                break;
        case 4:
                tft->setFreeFont(FS18);
                break;
        case 5:
                tft->setFreeFont(FSB18);
                break;
        case 6:
                tft->setFreeFont(FF3);
                break;
        case 7:
                tft->setFreeFont(FF23);
                break;
        case 8:
                tft->setFreeFont(FF19);
                break;
        case 9:
                tft->setFreeFont(FF35);
                break;
        default:
                break;
        }
}
void setupFont18(int font)
{
        switch (font)
        {
        case 0:
                tft->setFreeFont(FM18);
                break;
        case 1:
                tft->setFreeFont(FMB18);
                break;
        case 2:
                tft->setFreeFont(FSS18);
                break;
        case 3:
                tft->setFreeFont(FSSB18);
                break;
        case 4:
                tft->setFreeFont(FS18);
                break;
        case 5:
                tft->setFreeFont(FSB18);
                break;
        case 6:
                tft->setFreeFont(FF3);
                break;
        case 7:
                tft->setFreeFont(FF23);
                break;
        case 8:
                tft->setFreeFont(FF19);
                break;
        case 9:
                tft->setFreeFont(FF35);
                break;
        default:
                break;
        }
}
void setupFont24()
{
        int rf = random(5);
        switch (rf)
        {
        case 0:
                tft->setFreeFont(FMB24);
                break;
        case 1:
                tft->setFreeFont(FSSB24);
                break;
        case 2:
                tft->setFreeFont(FSB24);
                break;
        case 3:
                tft->setFreeFont(FF8);
                break;
        case 4:
                tft->setFreeFont(FF24);
                break;

        case 5:
                tft->setFreeFont(FF44);
                break;
        case 6:
                tft->setFreeFont(FF38);
                break;
        case 7:
                tft->setFreeFont(FF46);
                break;
        case 8:
                tft->setFreeFont(FSB12);
                break;
        case 9:
                tft->setFreeFont(FSBI12);
                break;
        default:
                break;
        }
}
