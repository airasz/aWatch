void sysinfo()
{
        tft->fillScreen(TFT_BLACK);
        tft->setFreeFont(NULL);
        tft->setTextFont(2);
        tft->setTextColor(TFT_GREEN);
        // vbus_v = power->getVbusVoltage() / 1000;
        // vbus_c = power->getVbusCurrent();
        // batt_v = power->getBattVoltage() / 1000;
        // per = power->getBattPercentage();
        getPower(); // update power info
        tft->setCursor(0, 0);
        tft->print("twatch@ESP32:--info\n");
        // tft->setCursor(0, 160);
        tft->print("  Battery : ");
        tft->setTextColor(TFT_WHITE);
        tft->printf("%.1f Volt\n", batt_v);
        tft->setTextColor(TFT_GREEN);
        tft->print("  Battery Percent : ");
        tft->setTextColor(TFT_WHITE);
        tft->printf("%d%%\n", per);
        if (!power->isChargeing())
        {
                // Show current consumption
                tft->setTextColor(TFT_GREEN);
                tft->print("  Discharge : ");
                tft->setTextColor(TFT_WHITE);
                tft->printf("%.0f mA\n", power->getBattDischargeCurrent());
        }
        else
        {
                // Print the values
                tft->setTextColor(TFT_GREEN);
                tft->print("  USB Voltage : ");
                tft->setTextColor(TFT_WHITE);
                tft->print(vbus_v, 1);
                tft->setTextColor(TFT_GREEN);
                tft->print("\n  USB Curent : ");
                tft->setTextColor(TFT_WHITE);
                tft->printf("%.1fmA\n", vbus_c);
        }

        if (config.stepcounter_filter > 0)
        {
                tft->setTextColor(TFT_GREEN);
                tft->print("  Step : ");
                tft->setTextColor(TFT_WHITE);
                tft->printf("%d | %s", step_counter, sysUpTime(0));
                // tft->print(" | ");
                // tft->print(sysUpTime(0));
                tft->setTextColor(TFT_GREEN);
                tft->print("\n  Distance coverage : ");
                tft->setTextColor(TFT_WHITE);
                long mCover = ((step_counter)*stepLenght) / 100;

                float kCover;
                if (mCover > 1100)
                        kCover = (float)mCover / 1000.0;
                tft->printf("%.0f %s\n", mCover > 1100 ? kCover : mCover, mCover > 1100 ? "km" : "m");

                tft->setTextColor(TFT_GREEN);
                tft->print("  Daily Step : ");
                tft->setTextColor(TFT_WHITE);
                // daily_step = step_counter - minfactor;
                tft->print(daily_step);
                tft->setTextColor(TFT_GREEN);
                tft->print("\n  Daily coverage : ");
                tft->setTextColor(TFT_WHITE);
                long dmCover = ((daily_step)*stepLenght) / 100;
                if (dmCover > 1100)
                        kCover = (float)dmCover / 1000.0;
                tft->printf("%.0f %s\n", dmCover > 1100 ? kCover : dmCover, dmCover > 1100 ? "km" : "m");
        }
        if (config.alarm_enable)
        {
                tft->setTextColor(TFT_GREEN);
                tft->print("  Alarm : ");
                tft->setTextColor(TFT_WHITE);
                tft->printf("active [ %02d:%02d ]\n", config.alarm_h, config.alarm_m);
        }
        if (config.alarm_pray)
        {
                tft->setTextColor(TFT_GREEN);
                tft->print("  Pray alert : ");
                tft->setTextColor(TFT_WHITE);
                tft->printf("upcoming [ %02d : %02d ]\n", tmpaph, tmpapm);
        }
        tft->setTextColor(TFT_GREEN);
        tft->print("  WakeUp Counter : ");
        tft->setTextColor(TFT_WHITE);
        tft->printf("%d time%s\n", wakeupCounter, wakeupCounter > 1 ? "s" : "");
        //==================calculate system uptime by millis reach

        //=====uptime by start date
        tft->setTextColor(TFT_GREEN);
        tft->print("  Up time : ");
        tft->setTextColor(TFT_WHITE);
        tft->print(sysUpTime(1));

        tft->setTextColor(TFT_GREEN);
        tft->print("\n  Heap used : ");
        tft->setTextColor(TFT_WHITE);
        tft->printf("%dkb/%dkb", (ESP.getHeapSize() - ESP.getFreeHeap()) / 1000, ESP.getHeapSize() / 1000);
        // tft->print("kb/");
        // tft->printf("kb" ,ESP.getHeapSize() / 1000);
        // tft->print("kb");

        tft->setTextColor(TFT_GREEN);
        tft->print("\n  Psram used : ");
        tft->setTextColor(TFT_WHITE);
        tft->printf("%dkb/%dmb", (ESP.getPsramSize() - ESP.getFreePsram()) / 1000, ESP.getFreePsram() / 1000000);

        tft->setTextColor(TFT_GREEN);
        tft->print("\n  CPU freq : ");
        tft->setTextColor(TFT_WHITE);
        tft->printf("%dMHz/", getCpuFrequencyMhz());

        // tft->print("kb/");
        // tft->print(ESP.getFreePsram() / 1000000);
        // tft->print("mb");

        // uint32_t getXtalFrequencyMhz(); // In MHz
        // uint32_t getCpuFrequencyMhz(); // In MHz
        // uint32_t getApbFrequency(); // In Hz
}
//==================calculate system uptime by compare with datetime at power up

int nowMonth = 0;

// calculating system uptime by use date time at  powerup as reference
// 0=short, 1=long
String sysUpTime(int mode)
{
        nowMonth = tnow.month;
        // nowMonth = 3;

        const uint8_t MaxDate[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        int u_day, u_hour, u_minute;
        String uptimes = "";
        if (nowMonth == startMonth)
        {
                // Serial.println("NTP month = start month");
                u_day = tnow.day - stDay;
                if (stDay > tnow.day)
                {
                        int max_Date = MaxDate[startMonth - 1];
                        u_day = 365 - (stDay - tnow.day);
                }

                if (stHour > tnow.hour) //====================
                {

                        u_day -= 1;
                        (u_day < 0) && (u_day = 365 + u_day);
                        // u_day = constrain(u_day, 0, 31);
                        u_hour = (24 - (stHour - tnow.hour));
                        // u_hour = stHour -tnow.hour;

                        if (stMinute > tnow.minute)
                        {
                                u_hour -= 1;
                                if (u_hour < 0)
                                {
                                        u_hour = 23;
                                        u_day -= 1;
                                        (u_day < 0) && (u_day = 365 + u_day);
                                }
                                u_minute = (60 - (stMinute - tnow.minute));
                                // u_minute = stMinute -tnow.minute;
                        }
                        if (stMinute <= tnow.minute)
                        {
                                u_minute = tnow.minute - stMinute;
                                // u_minute = (timeClient.getMinutes() + (60 - stMinute));
                                // u_minute = (60 - (timeClient.getMinutes() - stMinute));
                        }
                }
                if (stHour < tnow.hour) //===================
                {
                        u_hour = tnow.hour - stHour;
                        if (stMinute > tnow.minute) //--✓
                        {
                                u_hour -= 1;
                                if (u_hour < 0)
                                {
                                        u_hour = 23;
                                        u_day -= 1;
                                        (u_day < 0) && (u_day = 365 + u_day);
                                }
                                u_minute = (60 - (stMinute - tnow.minute));
                        }
                        if (stMinute <= tnow.minute)
                        {
                                u_minute = tnow.minute - stMinute; // ---✓
                        }
                }
                if (stHour == tnow.hour) //======================
                {
                        u_hour = tnow.hour - stHour;
                        if (stMinute > tnow.minute) // ---✓
                        {
                                u_hour -= 1;
                                if (u_hour < 0)
                                {
                                        u_hour = 23;
                                        u_day -= 1;
                                        (u_day < 0) && (u_day = 365 + u_day);
                                }
                                // u_minute = stMinute -tnow.minute;
                                u_minute = (60 - (stMinute - tnow.minute));
                        }
                        if (stMinute <= tnow.minute)
                        {
                                u_minute = tnow.minute - stMinute;
                        }
                }
        }
        else
        {
                // Serial.println("NTP month != start month");
                // int max_Date = MaxDate[startMonth + 1];
                // u_day = (max_Date - (stDay -tnow.day));

                if (nowMonth - startMonth == 1)
                {
                        int max_Date = MaxDate[startMonth - 1];
                        u_day = (max_Date - (stDay - tnow.day));
                }
                if (nowMonth - startMonth > 1)
                {
                        int month_range = nowMonth - startMonth;

                        int max_Date = MaxDate[startMonth - 1];
                        u_day = (max_Date - (stDay - tnow.day));

                        for (int i = 1; i < month_range; i++)
                        {
                                u_day += MaxDate[startMonth - 1 + i];
                        }
                }
                if (nowMonth - startMonth < 0) // passing new year
                {
                        Serial.println("passing new year");
                        int month_range = (12 - (startMonth - nowMonth));
                        Serial.printf("month range %d\n ", month_range);
                        int max_Date = MaxDate[startMonth - 1];
                        u_day = (max_Date - (stDay - tnow.day));
                        Serial.printf("u_day start =  %d\n ", u_day);

                        for (int i = 1; i < month_range; i++)
                        {
                                if (startMonth - 1 + i < 12)
                                {
                                        u_day += MaxDate[startMonth - 1 + i];
                                        Serial.printf("u_day + %d\n ", MaxDate[startMonth - 1 + i]);
                                }
                                else
                                {
                                        u_day += MaxDate[(startMonth - 1 + i) - 12];
                                        Serial.printf("u_day + %d\n ", MaxDate[(startMonth - 1 + i) - 12]);
                                }
                        }
                        Serial.printf("u_day + month range =  %d\n ", u_day);
                }

                if (stHour > tnow.hour)
                {
                        u_day -= 1;
                        // u_day = constrain(u_day, 0, 31);
                        u_hour = (24 - (stHour - tnow.hour));
                        // u_hour = stHour -tnow.hour;
                        if (stMinute > tnow.minute)
                        {
                                u_hour -= 1;

                                if (u_hour < 0)
                                {
                                        u_hour = 23;
                                        u_day -= 1;
                                }
                                // u_minute = (60 - (timeClient.getMinutes() - stMinute));
                                u_minute = (60 - (stMinute - tnow.minute));

                                // u_minute = stMinute -tnow.minute;
                        }
                        if (stMinute <= tnow.minute)
                        {
                                u_minute = tnow.minute - stMinute;
                                // u_minute = (60 - (timeClient.getMinutes() - stMinute));
                        }
                }
                if (stHour < tnow.hour)
                {
                        u_hour = tnow.hour - stHour;
                        if (stMinute > tnow.minute)
                        {
                                u_hour -= 1;
                                if (u_hour < 0)
                                {
                                        u_hour = 23;
                                        u_day -= 1;
                                }
                                u_minute = (60 - (stMinute - tnow.minute));
                        }
                        if (stMinute <= tnow.minute)
                        {
                                u_minute = tnow.minute - stMinute;
                        }
                }
                if (stHour == tnow.hour)
                {
                        u_hour = tnow.hour - stHour;
                        if (stMinute > tnow.minute)
                        {
                                u_hour -= 1;
                                if (u_hour < 0)
                                {
                                        u_hour = 23;
                                        u_day -= 1;
                                }
                                u_minute = (60 - (stMinute - tnow.minute));
                                // u_minute = stMinute -tnow.minute;
                        }
                        if (stMinute <= tnow.minute)
                        {
                                u_minute = tnow.minute - stMinute;
                                // u_minute = (60 - (stMinute -tnow.minute));
                        }
                }
        }
        uptimes = "";
        uptimes += u_day;
        // (mode == 0) ? uptimes += "." : uptimes += "d - ";
        uptimes += mode == 0 ? "." : "d - ";
        uptimes += u_hour;
        // (mode == 0) ? uptimes += "." : uptimes += "h - ";
        uptimes += mode == 0 ? "." : "h - ";
        uptimes += u_minute;
        if (mode == 1)
                uptimes += "m";
        // Serial.println(uptimes);
        return uptimes;
}

// display additional info on clock face
// 1. up & bottom Screen
// 2. side screen
// 3. bottom (step&coverage)
void displaySysInfo(int mode)
{
        tft->setFreeFont(NULL);
        tft->setTextColor(TFT_GREEN);
        // vbus_v = power->getVbusVoltage() / 1000;    //float
        // vbus_c = power->getVbusCurrent();           //float
        // batt_v = power->getBattVoltage() / 1000;    //float
        // per = power->getBattPercentage();           //int16_t
        // dchrg_c = power->getBattDischargeCurrent(); //float
        // chrg_c = power->getBattChargeCurrent();     //float
        getPower();
        long mCover = ((step_counter)*stepLenght) / 100;
        float kCover;
        if (mCover > 1100)
                kCover = (float)mCover / 1000.0;
        bool charging = power->isChargeing();
        switch (mode)
        {

        case 0:
                tft->setCursor(2, 1);
                if (!charging)
                {
                        // Show current consumption
                        tft->printf("Discharge: %.f mA ", power->getBattDischargeCurrent());
                        if (config.stepcounter_filter > 0)
                                tft->printf("Step : %d\n coverage  : %d m | ", step_counter, mCover);

                        // bat percent bar
                        float batt = 240;
                        batt = batt / 100;
                        batt = batt * per;
                        tft->fillRect(0, 236, batt, 4, TFT_GREEN); // bottom line as battery
                        // tft->fillRect(0, 118, batt, 4, TFT_GREEN); // // middle line as battery
                }
                else
                {
                        tft->printf("Charge:%.fmA\n", power->getBattChargeCurrent());
                        if (config.stepcounter_filter > 0)
                                tft->printf("Step : %d| coverage  : %d m", step_counter, mCover);

                        // Print the values
                        tft->setCursor(2, 240 - 18);
                        tft->printf("usb : [%.1fV%.1fmA]", vbus_v, vbus_c);
                }
                tft->printf(" bat : [%.1fV| %d%%]", batt_v, per);
                break;

        case 1:
                tft->setTextFont(2);
                tft->setCursor(0, 8);
                tft->printf("battery\n%.1fV\n[%d%%]", batt_v, per);

                // Show current consumption
                tft->setCursor(charging ? 180 : 170, 8);
                tft->print(charging ? "Charging" : "Discharge");
                tft->setCursor(170, 22);
                tft->printf("%.0f mA ", charging ? chrg_c : dchrg_c);
                tft->setCursor(0, 240 - 40);
                if (config.stepcounter_filter > 0)
                {
                        tft->printf("Step\n%d", step_counter);
                        tft->setCursor(180, 240 - 40);
                        tft->print("coverage");
                        String s = String(mCover);
                        tft->setCursor(220 - (s.length() * 6), 240 - 40 + 12);
                        tft->printf("%.0f %s\n", mCover > 1100 ? kCover : mCover, mCover > 1100 ? "km" : "m");
                }

                break;
        case 2:
                if (config.stepcounter_filter > 0)
                {
                        setupFont12();
                        tft->setTextColor(COLORS_LIGHT[random(10)]);
                        tft->setCursor(0, 240 - 30);
                        tft->printf("Step: %d", step_counter);
                        tft->setCursor(0, 240 - 10);
                        tft->printf("Coverage: %.0f %s\n", mCover > 1100 ? kCover : mCover, mCover > 1100 ? "km" : "m");
                        tft->setFreeFont(NULL);
                }

                break;
        case 3:
                tft->setCursor(2, 1);
                tft->printf("%.0f mA ", charging ? "charging:" : "discharge:", charging ? chrg_c : dchrg_c);
                if (config.stepcounter_filter > 0)
                        tft->printf("Step : %d\n coverage  : %d m | ", step_counter, ((step_counter)*stepLenght) / 100);

                if (!charging)
                {
                        // bat percent bar
                        float batt = 240;
                        batt = batt / 100;
                        batt = batt * per;
                        tft->fillRect(0, 118, batt, 4, TFT_GREEN); // // middle line as battery
                }
                else
                {
                        // Print the values
                        tft->setCursor(2, 240 - 18);
                        tft->printf("usb : [%.1fV%.1fmA]", vbus_v, vbus_c);
                }
                tft->printf(" bat : [%.1fV| %d%%]", batt_v, per);

                break;
        default:
                break;
        }
}
// 100langkah=4kalori
