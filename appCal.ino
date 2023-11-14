// display calendar, present month only
void init_holiday()
{
        dbFile = SPIFFS.open("/holiday.json", "r");
        if (!dbFile)
        {
                Serial.println("ERROR: DB file not found");
                // return false;
        }
        DynamicJsonDocument doc(1024);
        DeserializationError err = deserializeJson(doc, dbFile);
        if (err)
        {
                Serial.println("ERROR: " + String(err.c_str()));
                // return false;
        };
        // Serial.printf("pray day: %02d | mnt:  %02d | prayID%02d \n", day, mnt, in);
        for (size_t i = 0; i < 12; i++)
        {
                for (int ii = 0; ii < 4; ii++)
                {
                        int in = doc[String(i + 1)][ii];
                        hddata[i][ii] = in; // save to array data variable
                        // Serial.printf(" hddata[%d][%d] : %d ", i, ii, hddata[i][ii]);
                }
                Serial.println("");
        }

        dbFile.close();
}
int nday = tnow.day,
    nmonth = tnow.month,
    nyear = tnow.year;
void showCal()
{
        // String mnt[] = {"Januari", "S", "S", "R", "K", "J", "S"};
        nday = tnow.day,
        nmonth = tnow.month,
        nyear = tnow.year;
        String const dw[] = {"M", "S", "S", "R", "K", "J", "S"}; // indonesian day name start sunday
        int dwidth, dheight, row;

        const int _do = 8; // display  X position offset
        // size of a "day" cell on the calendar:
        dwidth = tft->width() / 7;
        dheight = tft->height() / 9;
        tft->fillScreen(TFT_BLACK); // Clear screen
        tft->setTextSize(1);
        tft->setTextFont(2);
        int dow = ttgo->rtc->getDayOfWeek(1, nmonth, nyear);
        Serial.printf("dow  : %d \n", dow);

        int maxday = MaxDate[nmonth - 1]; // get maximun day in current month
        // month name
        tft->setTextColor(TFT_WHITE);
        tft->setCursor(2, row * dheight);
        tft->print(bulan[nmonth - 1] + ", " + nyear);
        row++;
        for (int i = 0; i < 7; i++)
        {
                // print day shortname
                tft->setTextColor(i == 0 ? TFT_RED : TFT_BLUE);
                tft->setCursor((i * dwidth) + _do, row * dheight);
                tft->print(dw[i]);
        }
        row++; // NEXT ROW
        // dbFile = SPIFFS.open("/holiday.json", "r");

        for (int i = 0; i < maxday + dow; i++)
        {
                tft->setTextColor(TFT_GREEN);
                if (i % 7 == 0 && i > 0)
                        row++;
                if (i >= dow)
                {
                        tft->setCursor(((i % 7) * dwidth) + _do, row * dheight);
                        tft->setTextColor((holyday(i - dow + 1, nmonth - 1)) || (i % 7 == 0) ? TFT_RED : TFT_GREEN);
                        // coloring holyday
                        if (i - dow + 1 == nday) // highlight present day
                        {
                                tft->fillRoundRect(((i % 7) * dwidth) + _do - 1, (row * dheight) - 2, 18, 20, 2, rgbToHex(20, 20, 20));
                                tft->setTextColor(TFT_WHITE);
                        }
                        tft->print(i - dow + 1);
                }
        }
        // dbFile.close();
}
void showCal(bool next)
{
        // true= next from current, false = previous from current
        if (next && nmonth++ > 12)
        {
                nmonth = 1;
                nyear++;
        }
        if (!next && nmonth-- < 1)
        {
                nmonth = 12;
                nyear--;
        }

        String const dw[] = {"M", "S", "S", "R", "K", "J", "S"}; // indonesian day name start sunday
        int dwidth, dheight, row;

        const int _do = 8; // display  X position offset
        // size of a "day" cell on the calendar:
        dwidth = tft->width() / 7;
        dheight = tft->height() / 9;
        tft->fillScreen(TFT_BLACK); // Clear screen
        tft->setTextSize(1);
        tft->setTextFont(2);
        int dow = ttgo->rtc->getDayOfWeek(1, nmonth, nyear);

        Serial.printf("dow  : %d \n", dow);
        // dow -= 1;
        int maxday = MaxDate[nmonth - 1]; // get maximun day in selected month
        // month name
        tft->setTextColor(TFT_WHITE);
        tft->setCursor(2, row * dheight);
        tft->print(bulan[nmonth - 1] + ", " + nyear);
        row++;
        for (int i = 0; i < 7; i++)
        {
                // print day shortname
                tft->setTextColor(i == 0 ? TFT_RED : TFT_BLUE);
                tft->setCursor((i * dwidth) + _do, row * dheight);
                tft->print(dw[i]);
        }
        row++;
        for (int i = 0; i < maxday + dow; i++)
        {
                tft->setTextColor(TFT_GREEN);
                if (i % 7 == 0 && i > 0)
                        row++;
                if (i >= dow)
                {
                        tft->setCursor(((i % 7) * dwidth) + _do, row * dheight);
                        tft->setTextColor(((holyday(i - dow + 1, nmonth - 1)) && nyear == tnow.year) || (i % 7 == 0) ? TFT_RED : TFT_GREEN);
                        if (i - dow + 1 == nday) // highlight present day
                        {
                                if (nmonth == tnow.month && nyear == tnow.year)
                                {
                                        tft->fillRoundRect(((i % 7) * dwidth) + _do - 1, (row * dheight) - 2, 18, 20, 2, rgbToHex(20, 20, 20));
                                        tft->setTextColor(TFT_WHITE);
                                }
                        }
                        tft->print(i - dow + 1);
                }
        }
}
bool holyday(int d, int m)
{
        bool hd = false;
        // int hddata[][4] = {
        //     {1, 0, 0, 0},  //jan , holyday in date 1
        //     {1, 28, 0, 0}, // feb , holyday in date 1 & 28
        //     {3, 0, 0, 0},
        //     {15, 0, 0, 0},
        //     {1, 2, 3, 26},
        //     {1, 0, 0, 0},
        //     {9, 30, 0, 0},
        //     {17, 0, 0, 0}, //augst
        //     {0, 0, 0, 0},  // no holyday in sept
        //     {8, 0, 0, 0},
        //     {0, 0, 0, 0},
        //     {25, 0, 0, 0}};
        for (int ii = 0; ii < 4; ii++)
                if (d == hddata[m][ii])
                {
                        hd = true;
                        break;
                }

        return hd;
}
