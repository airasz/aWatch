void drawTimeSetting(int group)
{
        // tft->fillRect(0, 60, 240, 180, TFT_BLACK); // clear body area

        if (group == 1)
        {

                //row2
                drawOutlineButton(0, 70, 60, 40, TFT_BLUE, TFT_WHITE, "-");
                drawOutlineButton(240 - 62, 70, 60, 40, TFT_BLUE, TFT_WHITE, "+");
                tft->setTextDatum(MC_DATUM);
                tft->setTextColor(TFT_WHITE);
                tft->drawString("HOUR", 120, 64, 2);

                String hou = "";
                hou += old_hh;
                drawOutlineButton(62, 70, 240 - 62 - 60 - 2, 40, TFT_BLUE, TFT_BLACK, hou);
                hou = "";
                hou += hh;
                drawOutlineButton(62, 70, 240 - 62 - 60 - 2, 40, TFT_BLUE, TFT_WHITE, hou);

                //row3
                drawOutlineButton(0, 130, 60, 40, TFT_BLUE, TFT_WHITE, "-");
                drawOutlineButton(240 - 62, 130, 60, 40, TFT_BLUE, TFT_WHITE, "+");
                tft->setTextDatum(MC_DATUM);
                tft->setTextColor(TFT_WHITE);
                tft->drawString("MINUTE", 120, 124, 2);
                String mnit = "";
                mnit += old_mm;
                drawOutlineButton(62, 130, 240 - 62 - 60 - 2, 40, TFT_BLUE, TFT_BLACK, mnit);
                mnit = "";
                mnit += mm;
                drawOutlineButton(62, 130, 240 - 62 - 60 - 2, 40, TFT_BLUE, TFT_WHITE, mnit);

                //row 4
                if (hh != tmphh || mm != tmpmm)
                {
                        drawButton(0, 190, 240, 40, TFT_BLUE, TFT_WHITE, "Write to RTC");
                        write2RTC = 1;
                }
                else
                {
                        drawButton(0, 190, 240, 40, TFT_BLUE, TFT_WHITE, "NEXT");
                }
                old_hh = hh;
                old_mm = mm;
        }
        else if (group == 2)
        {

                //row2
                drawOutlineButton(0, 70, 60, 40, TFT_BLUE, TFT_WHITE, "-");
                drawOutlineButton(240 - 62, 70, 60, 40, TFT_BLUE, TFT_WHITE, "+");
                tft->setTextDatum(MC_DATUM);
                tft->setTextColor(TFT_WHITE);
                tft->drawString("DAY", 120, 64, 2);

                String sday = "";
                sday += old_day;
                drawOutlineButton(62, 70, 240 - 62 - 60 - 2, 40, TFT_BLUE, TFT_BLACK, sday);
                sday = "";
                sday += dday;
                drawOutlineButton(62, 70, 240 - 62 - 60 - 2, 40, TFT_BLUE, TFT_WHITE, sday);

                //row3
                drawOutlineButton(0, 130, 60, 40, TFT_BLUE, TFT_WHITE, "-");
                drawOutlineButton(240 - 62, 130, 60, 40, TFT_BLUE, TFT_WHITE, "+");
                tft->setTextDatum(MC_DATUM);
                tft->setTextColor(TFT_WHITE);
                tft->drawString("MONTH", 120, 124, 2);
                String smonth = "";
                smonth += old_mnt;
                drawOutlineButton(62, 130, 240 - 62 - 60 - 2, 40, TFT_BLUE, TFT_BLACK, smonth);
                smonth = "";
                smonth += mmonth;
                drawOutlineButton(62, 130, 240 - 62 - 60 - 2, 40, TFT_BLUE, TFT_WHITE, smonth);

                //row 4
                if (dday != tmpday || mmonth != tmpmnt)
                {
                        drawButton(0, 190, 240, 40, TFT_BLUE, TFT_WHITE, "Write to RTC");
                        write2RTC = 1;
                }
                else
                {
                        drawButton(0, 190, 240, 40, TFT_BLUE, TFT_WHITE, "NEXT");
                }
                old_day = dday;
                old_mnt = mmonth;
        }
        else if (group == 3)
        {
                //row2
                drawOutlineButton(0, 70, 60, 40, TFT_BLUE, TFT_WHITE, "-");
                drawOutlineButton(240 - 62, 70, 60, 40, TFT_BLUE, TFT_WHITE, "+");
                tft->setTextDatum(MC_DATUM);
                tft->setTextColor(TFT_WHITE);
                tft->drawString("YEAR", 120, 64, 2);
                String syear = "";
                syear += old_year;
                drawOutlineButton(62, 70, 240 - 62 - 60 - 2, 40, TFT_BLUE, TFT_BLACK, syear);
                syear = "";
                syear += yyear;
                drawOutlineButton(62, 70, 240 - 62 - 60 - 2, 40, TFT_BLUE, TFT_WHITE, syear);

                //row 4
                if (yyear != tmpyear)
                {
                        drawButton(0, 190, 240, 40, TFT_BLUE, TFT_WHITE, "Write to RTC");
                        write2RTC = 1;
                }
                else
                {
                        drawButton(0, 190, 240, 40, TFT_BLUE, TFT_WHITE, "DONE");
                }
                old_year = yyear;
        }
}
void writeRTC()
{

        // (write2RTC) && (ttgo->rtc->setDateTime(yyear, mmonth, dday, hh, mm, ss));
        if (write2RTC)
        {
                ttgo->rtc->setDateTime(yyear, mmonth, dday, hh, mm, ss);
                Serial.println("write RTC");
                Serial.printf("appsetTime: setting time to hh:mm:ss %02d:%02d:%02d %02d-%02d-%02d \n", hh, mm, ss, dday, mmonth, yyear);

                tmphh = hh;
                tmpmm = mm;
                tmpday = dday;
                tmpmnt = mmonth;
                tmpyear = yyear;
                write2RTC = 0;
        }
        // ttgo->rtc->setDateTime(2021, 3, 1, hh, mm, ss);
}
