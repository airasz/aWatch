#include "datajadwal.h"

void getPraytaskID(void)
{

        hh = tnow.hour;
        mm = tnow.minute;
        formating(); // datajadwal.ino
        if (hh < jsu || (hh == jsu && mm < msu))
        {
                ID_ = 0;
                tomorow = 0;
        }
        else if (hh > jis || (hh == jis && mm >= mis))
        {
                ID_ = 0;
                tomorow = 1;
        }
        else if ((hh < jdz || (hh == jdz && mm < mdz)) && (hh > jsu || (hh == jsu && mm >= msu)))
        {
                ID_ = 1;
        }
        else if ((hh < jas || (hh == jas && mm < mas)) && (hh > jdz || (hh == jdz && mm >= mdz)))
        {
                ID_ = 2;
        }

        else if ((hh < jmag || (hh == jmag && mm < mmag)) && (hh > jas || (hh == jas && mm >= mas)))
        {
                ID_ = 3;
        }

        else if ((hh < jis || (hh == jis && mm < mis)) && (hh > jmag || (hh == jmag && mm >= mmag)))
        {
                ID_ = 4;
        }
        // Serial.printf("hh %d\n ", hh);
        // Serial.printf("jdz %d\n ", jdz);
        // Serial.printf("pray ID %d\n ", ID_);
}
void showDayPray(void)
{
        getPraytaskID();
        tft->fillScreen(TFT_BLACK);
        // tft->setTextColor(TFT_WHITE, TFT_BLUE);
        tft->setTextColor(TFT_WHITE);
        tft->setTextFont(2);
        tft->setCursor(0, 0);
        tft->print("Jadwal solat ");
        int maxday = MaxDate[imnt - 1]; // get maximun day in current month

        String datej;
        if (tomorow)
        {
                datej = "besok, ";
                // print next day
                if (iday + 1 > maxday)
                {
                        imnt += 1;
                        (imnt > 11) && (imnt = 1); //over december  back to jan
                        iday = 1;
                        datej += iday;
                }
                else
                {
                        datej += iday + 1;
                }
        }
        else
        {
                datej = "hari ini, ";
                // iday += 1;
                datej += iday;
        }
        Serial.printf(" iday : %d \n", iday);
        datej += " ";
        datej += bulan[imnt - 1];
        tft->print(datej);
        String sdata = "";
        tft->setTextColor(TFT_GREEN);
        int r = random(10);

        while (r == 8 || r == 5) //avoid color no 5&8
                r = random(10);
        int color_ = COLOR_MEDIUM[r];
        // Serial.printf(" r : %d \n", r);
        tft->setCursor(0, 60);
        for (uint8_t i = 0; i < 5; i++)
        {
                sdata = getDailyJWS(i);
                tft->setTextColor(color_);
                if (i == ID_)
                        tft->setTextColor(TFT_WHITE, TFT_BLUE);
                tft->setFreeFont(FF14);
                tft->print(sdata + "\n");
        }
        close_incoming_event();
}
int t;
bool critical = false;
void close_incoming_event()
{ //close_incoming_event code here
        tft->setTextColor(COLOR_MEDIUM[random(10)]);
        tft->setCursor(0, 200);
        tft->setFreeFont(FF18);
        if (hh == jdz)
        {
                if (mm < mdz)
                {
                        t = mdz - mm;
                        tft->printf("%d menit\nmenjelang dzuhur", t);
                        critical = (t < 15 && t > 0) ? 1 : 0;
                }
                else
                {
                        critical = 0;
                }

        } //else{t=0;}
        if ((jdz - hh == 1) && (mm > mdz))
        {
                t = mdz + (60 - mm);
                tft->printf("%d menit\nmenjelang dzuhur", t);
                critical = (t < 15 && t > 0) ? 1 : 0;
        } //else{t=0;}
        if (hh == jas)
        {
                if (mm < mas)
                {
                        t = mas - mm;
                        tft->printf("%d menit\nmenjelang azhar", t);
                        critical = (t < 15 && t > 0) ? 1 : 0;
                }
                else
                {
                        critical = 0;
                }
        } //else{t=0;}
        if ((jas - hh == 1) && (mm > mas))
        {
                t = mas + (60 - mm);
                tft->printf("%d menit\nmenjelang azhar", t);
                critical = (t < 15 && t > 0) ? 1 : 0;
        } //else{t=0;}
        if (hh == jmag)
        {
                if (mm < mmag)
                {
                        t = mmag - mm;
                        tft->printf("%d menit\nmenjelang maghrib", t);
                        critical = (t < 15 && t > 0) ? 1 : 0;
                }
                else
                {
                        critical = 0;
                }
        } //else{t=0;}
        if ((jmag - hh == 1) && (mm > mmag))
        {
                t = mmag + (60 - mm);
                tft->printf("%d menit\nmenjelang maghrib", t);
                critical = (t < 15 && t > 0) ? 1 : 0;
        } //else{t=0;}
        if (hh == jis)
        {
                if (mm < mis)
                {
                        t = mis - mm;
                        tft->printf("%d menit\nmenjelang isya'", t);
                        critical = (t < 15 && t > 0) ? 1 : 0;
                }
                else
                {
                        critical = 0;
                }
        } //else{t=0;}
        if ((jis - hh == 1) && (mm > mis))
        {
                t = mis + (60 - mm);
                tft->printf("%d menit\nmenjelang isya'", t);
                critical = (t < 15 && t > 0) ? 1 : 0;
        } //else{t=0;}
        if (hh == jsu)
        {
                if (mm < msu)
                {
                        t = msu - mm;
                        tft->printf("%d menit\nmenjelang shubuh", t);
                        critical = (t < 15 && t > 0) ? 1 : 0;
                }
                else
                {
                        critical = 0;
                }
        } //else{t=0;}
        if ((jsu - hh == 1) && (mm > msu))
        {
                t = msu + (60 - mm);
                tft->printf("%d menit\nmenjelang shubuh", t);
                critical = (t < 15 && t > 0) ? 1 : 0;

        } //else{t=0;}

        Serial.print("t = ");
        Serial.println(t);
        Serial.print("critical = ");
        Serial.println(critical);
}