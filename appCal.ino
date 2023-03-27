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
                        hddata[i][ii] = in;
                }
        }

        dbFile.close();
}
void showCal()
{
        // String mnt[] = {"Januari", "S", "S", "R", "K", "J", "S"};
        int nday = tnow.day,
            nmonth = tnow.month,
            nyear = tnow.year;
        String const dw[] = {"M", "S", "S", "R", "K", "J", "S"}; //indonesian day name start sunday
        int fday, nmon, bwidth, dwidth, dheight, row;

        const int _do = 8; // display  X position offset
        // size of a "day" cell on the calendar:
        dwidth = tft->width() / 7;
        dheight = tft->height() / 9;
        tft->fillScreen(TFT_BLACK); // Clear screen
        tft->setTextSize(1);
        tft->setTextFont(2);
        int dow = ttgo->rtc->getDayOfWeek(1, nmonth, nyear);
        dow -= 1;
        int maxday = MaxDate[nmonth - 1]; // get maximun day in current month
        //month name
        tft->setTextColor(TFT_WHITE);
        tft->setCursor(2, row * dheight);
        tft->print(bulan[nmonth - 1]);
        tft->print(", ");
        tft->print(nyear);
        row++;
        for (int i = 0; i < 7; i++)
        {
                // print day shortname
                tft->setTextColor(i == 0 ? TFT_RED : TFT_BLUE);
                tft->setCursor((i * dwidth) + _do, row * dheight);
                tft->print(dw[i]);
        }
        row++;
        // dbFile = SPIFFS.open("/holiday.json", "r");

        for (int i = 1; i < maxday + dow + 1; i++)
        {
                tft->setTextColor(TFT_GREEN);
                if (i % 7 == 0)
                        row++;
                if (i > dow)
                {
                        tft->setCursor(((i % 7) * dwidth) + _do, row * dheight);
                        // if (i % 7 == 0) // coloring sunday
                        //         tft->setTextColor(TFT_RED);
                        // if (holyday(i - dow, nmonth))       // check if date is holyday?
                        //         tft->setTextColor(TFT_RED); // coloring holyday
                        tft->setTextColor((holyday(i - dow, nmonth - 1)) || (i % 7 == 0) ? TFT_RED : TFT_GREEN);
                        if (i - dow == nday) //highlight present day
                        {
                                tft->fillRoundRect(((i % 7) * dwidth) + _do, (row * dheight) - 2, 18, 20, 2, rgbToHex(20, 20, 20));
                                tft->setTextColor(TFT_WHITE);
                        }
                        tft->print(i - dow);
                }
        }
        dbFile.close();
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
        {
                if (d == hddata[m][ii])
                {
                        hd = true;
                        break;
                }
        }

        return hd;
}
