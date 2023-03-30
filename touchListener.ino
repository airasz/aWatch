
int newTouch, oldTouchY, oldTouchX;
int shiftX = 0;
int shiftY = 0;
bool swipeURight = false;
bool swipeULeft = false;
bool swipeBRight = false;
bool swipeBLeft = false;
bool swipeUp = false;
bool swipeDown = false;

//  <1=========2>
//    ˄______˄_______˄
//    7______9_____11
//  <3=----|----=4>
//    8_____10_____12
//    ˅_______˅______˅
//  <5========6>

uint8_t swipeID = 0;
Accel acc;
int flippos = 0;
void touchListener()
{

        if (ttgo->bma->getAccel(acc))
        {

                flippos = acc.y;
                if (flippos < (-300))
                {
                        // (!flipped) && flipped;
                        if (acc.x < 300 && acc.x > (-300))
                                flipped = !flipped;
                        // if (flipped == false)
                        //         flipped = true;
                }
                else if (flippos > 220)
                {
                        // (flipped) && !flipped;
                        if (acc.x < 300 && acc.x > (-300))
                                if (flipped && !alarm_active)
                                {
                                        if (page_ID == 0)
                                        {
                                                page_ID = 1;
                                                updateScreen(page_ID); // gui.ino
                                        }
                                        else if (page_ID == 1)
                                        {
                                                page_ID = 0;
                                                updateScreen(page_ID); // gui.ino
                                        }
                                        flipped = false;
                                }
                }
                // Serial.printf(" flipped %s\n ", (flipped) ? "true" : "false");
                // Serial.printf("acc X %d\n ", flippos);
        }

        while (ttgo->getTouch(tx, ty))
        {

                if (page_ID == 0 || page_ID == 3)
                {
                        if (ty < 60)
                        {
                                if (tx > oldTouchX)
                                {
                                        // Serial.printf("shiftX : %d\n", shiftX);
                                        if (shiftX++ > maxShifting)
                                        {
                                                swipeID = 2;
                                                if (page_ID == 3)
                                                        swipeID = 31;
                                                swipeMe = 0;
                                        }
                                        // (shiftX > 50) && (swipeBRight = 1);
                                }
                                if (tx < oldTouchX)
                                {
                                        if (shiftX++ > maxShifting)
                                        {

                                                swipeID = 1;
                                                if (page_ID == 3)
                                                        swipeID = 32;
                                                swipeMe = 0;
                                        }
                                        // (shiftX > 50) && (swipeBLeft = 1);
                                }
                                oldTouchX = tx;
                                // tmptouchreg = 0;
                        }
                        if (ty > 180)
                        {
                                if (tx > oldTouchX)
                                {
                                        // Serial.printf("shiftX : %d\n", shiftX);
                                        if (shiftX++ > maxShifting)
                                        {
                                                swipeID = 6;
                                                if (page_ID == 3)
                                                        swipeID = 31;
                                                swipeMe = 0;
                                        }
                                        // (shiftX > 50) && (swipeBRight = 1);
                                }
                                if (tx < oldTouchX)
                                {
                                        if (shiftX++ > maxShifting)
                                        {
                                                swipeID = 5;
                                                if (page_ID == 3)
                                                        swipeID = 32;
                                                swipeMe = 0;
                                        }
                                        // (shiftX > 50) && (swipeBLeft = 1);
                                }
                                oldTouchX = tx;
                                // tmptouchreg = 0;
                        }

                        if (ty > oldTouchY)
                        { // swipe down
                                if (shiftY++ > maxShifting)
                                {
                                        swipeID = 10;
                                        if (page_ID == 3)
                                                swipeID = 31;
                                        swipeMe = 0;
                                }
                                // (shiftY > 50) && (swipeDown = 1);
                                oldTouchY = ty;
                                // tmptouchreg = 0;
                        }
                        if (ty < oldTouchY)
                        {
                                if (shiftY++ > 20)
                                {
                                        swipeID = 9;
                                        if (page_ID == 3)
                                                swipeID = 32;
                                        swipeMe = 0;
                                }
                                // (shiftY > 50) && (swipeUp = 1);
                                oldTouchY = ty;
                                // tmptouchreg = 0;
                        }
                }

                // touched = 1;
                touchStage = 1;
        } // Wait for release to exit
        // (touchStage == 1) && (touchStage = 2);
        if (touchStage == 1)
        {
                if (swipeID == 0)
                {
                        touched = 1;
                }
                touchStage = 2;
        }
        if (touched)
        {
                Serial.printf("tX  : %d | tY %d \n", tx, ty);
                if (ty < 60) // 1-2-3
                {
                        if (tx > 0 && tx < 80)
                                tmptouchreg = 1;
                        if (tx > 80 && tx < 160)
                                tmptouchreg = 2;
                        if (tx > 160 && tx < 240)
                                tmptouchreg = 3;
                }
                if (ty > 60 && ty < 120) // 4-5-6
                {
                        if (tx > 0 && tx < 80)
                                tmptouchreg = 4;
                        if (tx > 80 && tx < 160)
                                tmptouchreg = 5;
                        if (tx > 160 && tx < 240)
                                tmptouchreg = 6;
                }
                if (ty > 120 && ty < 180) // 7-8-9
                {
                        if (tx > 0 && tx < 80)
                                tmptouchreg = 7;
                        if (tx > 80 && tx < 160)
                                tmptouchreg = 8;
                        if (tx > 160 && tx < 240)
                                tmptouchreg = 9;
                }
                if (ty > 180) // 10-11-12
                {
                        if (tx > 0 && tx < 80)
                                tmptouchreg = 10;
                        if (tx > 80 && tx < 160)
                                tmptouchreg = 11;
                        if (tx > 160 && tx < 240)
                                tmptouchreg = 12;
                }
                if (page_ID == 22)
                {
                        adjusting(tx, ty);
                }
                swipeMe = 1;
                touched = 0;
                if (swipeID > 0)
                        tmptouchreg = 0;
        }
        // touched = (swipeID > 0) ? false : true;
        // Serial.printf("swipeID: %d | ", swipeID);
        // Serial.printf(" tmptouchreg : %d\n", tmptouchreg);
}
void drawToast(String msg)
{
        toastShow = 1;
        count2 = 0;
        toast(msg);
}
void handleTouch()
{
        if (touchStage == 2)
        {
                Serial.printf("swipeID: %d | ", swipeID);
                Serial.printf(" tmptouchreg : %d\n", tmptouchreg);
                // Serial.printf(" swipeMe =  %s\n ", (swipeMe) ? "true" : "false");
                // Serial.printf(" tmptouchreg =  %d\n ", tmptouchreg);

                if (toastShow)
                {
                        count2++;
                        // Serial.println("toast count");
                        if (count2 > 20)
                        {
                                updateScreen(prevpage_ID);
                                count2 = 0;
                                touchCount = 0;
                                toastShow = 0;
                        }
                }
                if (tmptouchreg > 0 && swipeID == 0)
                {
                        shiftX = 0;
                        shiftY = 0;
                        if (tmptouchreg == 1) //============================  1
                        {
                                if (page_ID == 0 || page_ID == 1 || page_ID == 3 || page_ID == 31 || page_ID == 32)
                                {
                                        page_ID = 11;
                                        updateScreen(page_ID); // gui.ino
                                        // prevpage_ID = page_ID;
                                        tmptouchreg = 0;
                                }
                                else if (page_ID == 11)
                                {
                                        page_ID = 0;
                                        updateScreen(page_ID); // gui.ino
                                        // prevpage_ID = page_ID;
                                        tmptouchreg = 0;
                                }
                                else if (page_ID == 2)
                                {
                                        page_ID = 0;
                                        updateScreen(page_ID); // gui.ino
                                        // prevpage_ID = page_ID;
                                        tmptouchreg = 0;
                                }
                                else if (page_ID > 20 && page_ID < 30 || page_ID > 200 && page_ID < 299)
                                {
                                        page_ID = 2;
                                        updateScreen(page_ID); // gui.ino
                                        // prevpage_ID = page_ID;
                                        tmptouchreg = 0;
                                }
                        }

                        if (tmptouchreg == 2) //============================  2
                        {
                                if (page_ID == 0 || page_ID == 11 || page_ID == 1 || page_ID == 31 || page_ID == 32) // calender
                                {
                                        page_ID = 3;
                                        updateScreen(page_ID); // gui.ino
                                        tmptouchreg = 0;
                                }
                                else if (page_ID == 3) // calender
                                {
                                        page_ID = 0;
                                        updateScreen(page_ID); // gui.ino
                                        tmptouchreg = 0;
                                }
                        }

                        if (tmptouchreg == 3) //============================  3
                        {
                                if (page_ID == 0 || page_ID == 11 || page_ID == 3 || page_ID == 31 || page_ID == 32) // pray schedule
                                {
                                        imnt = tnow.month;
                                        iday = tnow.day;
                                        // showDayPray();
                                        // prevpage_ID = 0;
                                        page_ID = 1;
                                        updateScreen(page_ID); // gui.ino
                                        prevpage_ID = page_ID;
                                        touchCount = 0;
                                        // home = 0;
                                }
                                else if (page_ID == 1) // sys info
                                {
                                        page_ID = 0;
                                        updateScreen(page_ID); // gui.ino
                                        prevpage_ID = page_ID;
                                        // clock_face_digit(CF);
                                        // home = 1;
                                }
                                else if (page_ID == 2 || (page_ID > 20 && page_ID < 30)) // back
                                {

                                        page_ID = 0;
                                        updateScreen(page_ID); // gui.ino
                                        prevpage_ID = page_ID;
                                }
                                else if (page_ID > 230 && page_ID < 234) // back
                                {

                                        page_ID = 0;
                                        updateScreen(page_ID); // gui.ino
                                        prevpage_ID = page_ID;
                                }
                                else if (page_ID == 271 || page_ID == 272) // back
                                {
                                        page_ID = 0;
                                        updateScreen(page_ID); // gui.ino
                                        prevpage_ID = page_ID;
                                }

                                tmptouchreg = 0;
                                my_idle();
                        }
                        if (tmptouchreg == 4) //============================  4
                        {
                                if (page_ID == 2) // go to step setting
                                {
                                        page_ID = 21;
                                        tft->fillRect(0, 60, 240, 180, TFT_BLACK); // clear body area
                                        updateScreen(page_ID);                     // gui.ino
                                        prevpage_ID = page_ID;
                                }
                                else if (page_ID == 24)
                                {
                                        tmpha--;
                                        (tmpha < 0) && (tmpha = 23);
                                        updateScreen(page_ID); // gui.ino
                                }
                                else if (page_ID == 26) // PRAY
                                {
                                        tmpmwarn--;
                                        (tmpmwarn < 0) && (tmpmwarn = 15);
                                        updateScreen(page_ID); // gui.ino
                                }
                                else if (page_ID == 271) // IR pana
                                {
                                        imode--;
                                        // imode++;
                                        (imode == 1) && (imode = 2);
                                        (imode < 0) && (imode = 3);
                                        updateScreen(page_ID); // gui.ino
                                }
                                else if (page_ID == 272) // IR LG
                                {
                                        imode--;
                                        // imode++;
                                        (imode == 1) && (imode = 2);
                                        (imode < 0) && (imode = 3);
                                        updateScreen(page_ID); // gui.ino
                                }
                                else if (page_ID == 231)
                                {
                                        hh--;
                                        (hh < 0) && (hh = 23);
                                        updateScreen(page_ID); // gui.ino
                                }
                                else if (page_ID == 232)
                                {
                                        dday--;
                                        (dday < 0) && (hh = 31);
                                        updateScreen(page_ID); // gui.ino
                                }
                                else if (page_ID == 233)
                                {
                                        yyear--;
                                        (yyear < 2020) && (yyear = 2020);
                                        updateScreen(page_ID); // gui.ino
                                }
                        }
                        if (tmptouchreg == 5) //============================  5
                        {
                                if (page_ID == 2) // go to dysplay
                                {

                                        page_ID = 22;
                                        tft->fillRect(0, 60, 240, 180, TFT_BLACK); // clear body area
                                        updateScreen(page_ID);                     // gui.ino
                                        prevpage_ID = page_ID;
                                }
                        }
                        if (tmptouchreg == 6) //============================  6
                        {
                                if (page_ID == 21)
                                {
                                        if (config.stepcounter_filter > 0)
                                        {
                                                config.stepcounter_filter = 0;
                                                EEPROM_writeAnything(0, config);
                                                EEPROM.commit();
                                                updateScreen(page_ID); // appSetting.ino
                                        }
                                        else
                                        {

                                                config.stepcounter_filter = 1;
                                                EEPROM_writeAnything(0, config);
                                                EEPROM.commit();
                                                updateScreen(page_ID); // appSetting.ino
                                        }
                                }
                                if (page_ID == 25)
                                {
                                        if (config.rnd_face)
                                        {
                                                config.rnd_face = 0;
                                                EEPROM_writeAnything(0, config);
                                                EEPROM.commit();
                                                updateScreen(page_ID); // appSetting.ino
                                        }
                                        else
                                        {
                                                config.rnd_face = 1;
                                                EEPROM_writeAnything(0, config);
                                                EEPROM.commit();
                                                updateScreen(page_ID); // appSetting.ino
                                        }
                                }

                                else if (page_ID == 2)
                                {
                                        page_ID = 231;
                                        tft->fillRect(0, 60, 240, 180, TFT_BLACK); // clear body area
                                        updateScreen(page_ID);                     // gui.ino
                                        prevpage_ID = page_ID;
                                }
                                else if (page_ID == 24)
                                {
                                        tmpha++;
                                        (tmpha > 23) && (tmpha = 0);
                                        updateScreen(page_ID); // gui.ino
                                }

                                else if (page_ID == 26)
                                {
                                        tmpmwarn++;
                                        (tmpmwarn > 15) && (tmpmwarn = 0);
                                        updateScreen(page_ID); // gui.ino
                                }

                                else if (page_ID == 271) // IR pana
                                {
                                        imode++;
                                        (imode == 1) && (imode = 2);
                                        (imode > 3) && (imode = 0);

                                        updateScreen(page_ID); // gui.ino
                                }
                                else if (page_ID == 272) // IR LG
                                {
                                        imode++;
                                        (imode == 1) && (imode = 2);
                                        (imode > 3) && (imode = 0);

                                        updateScreen(page_ID); // gui.ino
                                }
                                else if (page_ID == 231)
                                {
                                        hh++;
                                        (hh > 23) && (hh = 0);
                                        updateScreen(page_ID); // gui.ino
                                }
                                else if (page_ID == 232)
                                {
                                        dday++;
                                        (dday > 31) && (dday = 1);
                                        updateScreen(page_ID); // gui.ino
                                }
                                else if (page_ID == 233)
                                {
                                        yyear++;
                                        (yyear > 9999) && (yyear = 2020);
                                        updateScreen(page_ID); // gui.ino
                                }
                        }
                        if (tmptouchreg == 7) //============================  7
                        {
                                if (page_ID == 2) // setting
                                {
                                        page_ID = 24;
                                        tft->fillRect(0, 60, 240, 180, TFT_BLACK); // clear body area
                                        updateScreen(page_ID);                     // gui.ino
                                }
                                else if (page_ID == 21)
                                {
                                        stepLenght--;
                                        updateScreen(page_ID); // gui.ino
                                        config.step_length = stepLenght;
                                        EEPROM_writeAnything(0, config);
                                        EEPROM.commit();
                                }
                                else if (page_ID == 24)
                                {
                                        tmpma--;
                                        (tmpma < 0) && (tmpma = 59);
                                        updateScreen(page_ID); // gui.ino
                                }

                                else if (page_ID == 26)
                                {
                                        tmpvib--;
                                        (tmpvib < 0) && (tmpvib = 15);
                                        updateScreen(page_ID); // gui.ino
                                }
                                else if (page_ID == 27)
                                {
                                        // itemp--;
                                        // (itemp < 19) && (itemp = 24);
                                        page_ID = 271;
                                        tft->fillRect(0, 60, 240, 180, TFT_BLACK);
                                        updateScreen(page_ID); // gui.ino
                                }
                                else if (page_ID == 271) // panasonic
                                {
                                        itemp--;
                                        (itemp < 19) && (itemp = 24);
                                        updateScreen(page_ID); // gui.ino
                                }
                                else if (page_ID == 272) // panasonic
                                {
                                        acLG_temperature--;
                                        (acLG_temperature < 20) && (acLG_temperature = 26);
                                        updateScreen(page_ID); // gui.ino
                                }
                                else if (page_ID == 231)
                                {
                                        mm--;
                                        (mm < 0) && (mm = 59);
                                        updateScreen(page_ID); // gui.ino
                                }
                                else if (page_ID == 232) // date setting
                                {
                                        mmonth--;
                                        (mmonth < 0) && (mmonth = 12);
                                        updateScreen(page_ID); // gui.ino
                                }
                        }
                        if (tmptouchreg == 8) //============================  8
                        {
                                if (page_ID == 2) // setting
                                {
                                        page_ID = 25;
                                        tft->fillRect(0, 60, 240, 180, TFT_BLACK); // clear body area
                                        updateScreen(page_ID);                     // gui.ino
                                }
                        }
                        if (tmptouchreg == 9) //============================  9
                        {

                                if (page_ID == 24)
                                {
                                        tmpma++;
                                        (tmpma > 59) && (tmpma = 0);
                                        updateScreen(page_ID); // gui.ino
                                }
                                else if (page_ID == 26)
                                {
                                        tmpvib++;
                                        (tmpvib > 15) && (tmpvib = 0);
                                        updateScreen(page_ID); // gui.ino
                                        // Serial.println("page 26");
                                }
                                else if (page_ID == 27)
                                {
                                        page_ID = 272;
                                        tft->fillRect(0, 60, 240, 180, TFT_BLACK);
                                        updateScreen(page_ID); // gui.ino
                                }
                                else if (page_ID == 271)
                                {
                                        itemp++;
                                        (itemp > 24) && (itemp = 20);
                                        updateScreen(page_ID); // gui.ino
                                }
                                else if (page_ID == 272)
                                {
                                        acLG_temperature++;
                                        (acLG_temperature > 26) && (acLG_temperature = 20);
                                        updateScreen(page_ID); // gui.ino
                                }
                                else if (page_ID == 2) // setting
                                {
                                        page_ID = 26;
                                        tft->fillRect(0, 60, 240, 180, TFT_BLACK); // clear body area
                                        updateScreen(page_ID);                     // gui.ino
                                        // Serial.println("page 26");
                                        tmptouchreg = 0;
                                }
                                if (page_ID == 21)
                                {
                                        stepLenght++;
                                        updateScreen(page_ID); // gui.ino
                                        config.step_length = stepLenght;
                                        EEPROM_writeAnything(0, config);
                                        EEPROM.commit();
                                }
                                else if (page_ID == 231)
                                {
                                        mm++;
                                        (mm > 59) && (mm = 0);
                                        updateScreen(page_ID); // gui.ino
                                }
                                else if (page_ID == 232)
                                {
                                        mmonth++;
                                        (mmonth > 12) && (mmonth = 1);
                                        updateScreen(page_ID); // gui.ino
                                }
                        }
                        if (tmptouchreg == 10) //============================  10
                        {

                                if (page_ID == 0)
                                {
                                }

                                else if (page_ID == 21)
                                {
                                        // ttgo->bma->resetStepCounter();
                                        // daily_step = 0;
                                        minfactor = step_counter;
                                        stepMonth = tnow.month;
                                        stepDay = tnow.day;
                                        stepHour = tnow.hour;
                                        stepMinute = tnow.minute;
                                        // step_counter = 0;
                                        toast("step counter resetted");
                                        prevpage_ID = page_ID;
                                }
                                else if (page_ID == 22)
                                {
                                        EEPROM_writeAnything(0, config);
                                        EEPROM.commit();
                                        page_ID = 2;
                                        updateScreen(page_ID); // gui.ino
                                }
                                else if (page_ID == 24)
                                {
                                        writeAlarm();
                                        page_ID = 2;
                                        updateScreen(page_ID); // gui.ino
                                }
                                else if (page_ID == 271)
                                {
                                        PanasonicOn();
                                }
                                else if (page_ID == 272)
                                {
                                        Ac_LG_Activate(acLG_temperature, acLG_flow, acLG_heat); // turnon AC
                                }
                                else if (page_ID == 26)
                                {
                                        // setupPrayAlarm();
                                        if (tmpmwarn != config.alarmpraywarning)
                                        {
                                                config.alarmpraywarning = tmpmwarn;
                                                EEPROM_writeAnything(0, config);
                                                EEPROM.commit();
                                                setprayalarm(false); // datajadwal.ino
                                        }

                                        if (tmpvib != config.vib)
                                        {
                                                config.vib = tmpvib;
                                                EEPROM_writeAnything(0, config);
                                                EEPROM.commit();
                                                setprayalarm(false); // datajadwal.ino
                                        }
                                        config.alarm_pray = 1;
                                        alarmset = 0;

                                        page_ID = 2;
                                        updateScreen(page_ID); // gui.ino
                                }

                                else if (page_ID == 2) // setting
                                {
                                        page_ID = 27;                              // select AC brand
                                        tft->fillRect(0, 60, 240, 180, TFT_BLACK); // clear body area
                                        updateScreen(page_ID);                     // gui.ino
                                        // Serial.println("page 26");
                                        tmptouchreg = 0;
                                }
                                else if (page_ID > 230 && page_ID < 234)
                                {

                                        tft->fillRect(0, 60, 240, 180, TFT_BLACK); // clear body area
                                        writeRTC();                                // appSettime.ino
                                        page_ID++;
                                        (page_ID > 233) && (page_ID = 0);
                                        updateScreen(page_ID); // gui.ino
                                }

                                tmptouchreg = 0;
                        }
                        if (tmptouchreg == 11) //============================  11
                        {
                                if (page_ID == 0)
                                {
                                        // page_ID = 2;
                                        // updateScreen(page_ID); //gui.ino
                                        // // startSetting();
                                        // home = 0;
                                        if (alarm_active)
                                        {
                                                alarm_active = false;
                                                ttgo->rtc->disableAlarm();
                                                ttgo->rtc->resetAlarm();
                                                if (config.alarm_pray)
                                                        setprayalarm(true);
                                                digitalWrite(4, LOW);
                                                updateScreen(page_ID); // gui.ino
                                        }
                                }
                                else if (page_ID == 21)
                                {

                                        // ttgo->bma->resetStepCounter();
                                        // daily_step = 0;
                                        minfactor = step_counter;
                                        stepMonth = tnow.month;
                                        stepDay = tnow.day;
                                        stepHour = tnow.hour;
                                        stepMinute = tnow.minute;
                                        // step_counter = 0;
                                        toast("step counter resetted");
                                        prevpage_ID = page_ID;
                                }
                                else if (page_ID == 271)
                                {
                                        PanasonicOff();
                                }
                                else if (page_ID == 271)
                                {
                                        Ac_LG_Power_Down();
                                }
                                else if (page_ID > 230 && page_ID < 234)
                                {

                                        tft->fillRect(0, 60, 240, 180, TFT_BLACK); // clear body area
                                        writeRTC();                                // appSettime.ino
                                        page_ID++;
                                        (page_ID > 233) && (page_ID = 0);
                                        updateScreen(page_ID); // gui.ino
                                }
                                prevpage_ID = page_ID;
                        }

                        if (tmptouchreg == 12) //============================  12
                        {
                                if (page_ID == 0)
                                {
                                }
                                else if (page_ID == 21)
                                {

                                        // ttgo->bma->resetStepCounter();
                                        // daily_step = 0;
                                        minfactor = step_counter;
                                        stepMonth = tnow.month;
                                        stepDay = tnow.day;
                                        stepHour = tnow.hour;
                                        stepMinute = tnow.minute;
                                        // step_counter = 0;
                                        drawToast("step counter resetted");
                                        prevpage_ID = page_ID;
                                }
                                else if (page_ID == 24)
                                {
                                        tmpalarmenable = !tmpalarmenable;
                                        updateScreen(page_ID); // gui.ino
                                }
                                if (page_ID == 26)
                                {
                                        if (config.alarm_pray)
                                        {
                                                config.alarm_pray = 0;
                                        }
                                        else
                                        {
                                                setprayalarm(false);
                                                config.alarm_pray = 1;
                                                alarmset = 0;
                                                // setprayalarm(false);
                                        }

                                        EEPROM_writeAnything(0, config);
                                        EEPROM.commit();
                                        updateScreen(page_ID); // appSetting.ino
                                }
                                else if (page_ID == 271)
                                {
                                        PanasonicOn(); // appIR.ino
                                }
                                else if (page_ID == 272)
                                {
                                        Ac_LG_Activate(acLG_temperature, acLG_flow, acLG_heat); // turnon AC
                                }

                                else if (page_ID > 230 && page_ID < 234)
                                {

                                        tft->fillRect(0, 60, 240, 180, TFT_BLACK); // clear body area
                                        writeRTC();                                // appSettime.ino
                                        page_ID++;
                                        (page_ID > 233) && (page_ID = 0);
                                        updateScreen(page_ID); // gui.ino
                                }

                                tmptouchreg = 0;
                        }
                        my_idle();
                        tmptouchreg = 0;
                }
                switch (swipeID)
                {
                case 1:
                        break;
                case 2:
                        // swip down
                        page_ID = 2;
                        updateScreen(page_ID); // gui.ino
                                               // prevpage_ID = page_ID;
                        clearSwipeCache();
                        delay(50);
                        break;
                case 5:
                        // swipe left
                        CF--;
                        // if (CF < 0)
                        // {
                        //         Serial.printf("clock face change to : %d\n", CF);
                        //         CF = 10;
                        // }
                        (CF < 2) && (CF = 12);
                        config.clock_face = CF;
                        EEPROM_writeAnything(0, config);
                        EEPROM.commit();
                        // clock_face_digit(CF);
                        face(CF);
                        my_idle();
                        clearSwipeCache();
                        break;
                case 6:
                        // swipe right
                        CF++;
                        // if (CF > 10)
                        // {
                        //         Serial.printf("clock face change to : %d\n", CF);
                        //         CF = 0;
                        // }
                        (CF > 12) && (CF = 2);
                        config.clock_face = CF;
                        EEPROM_writeAnything(0, config);
                        EEPROM.commit();
                        // clock_face_digit(CF);

                        face(CF);
                        my_idle();
                        clearSwipeCache();
                        break;
                case 10:
                        // swipe down
                        page_ID = 2;
                        updateScreen(page_ID); // gui.ino
                                               // prevpage_ID = page_ID;
                        clearSwipeCache();

                        break;
                case 9:
                        // swipe up
                        //  CF = 10;
                        //  (config.pedometer_enable) && (config.pedometer_enable = false) || (config.pedometer_enable = true);
                        //  if (config.pedometer_enable)
                        //  {
                        //          config.pedometer_enable = false;
                        //  }
                        //  else
                        //  {
                        //          config.pedometer_enable = true;
                        //  }
                        config.pedometer_enable = !config.pedometer_enable;

                        EEPROM_writeAnything(0, config);
                        EEPROM.commit();
                        updateScreen(page_ID); // gui.ino
                        // clock_face_digit(CF);
                        my_idle();
                        clearSwipeCache();

                        break;
                case 31:
                        // page_ID = swipeID;
                        updateScreen(swipeID); // gui.ino
                        shiftX = 0;
                        shiftY = 0;
                        swipeMe = 1;
                        swipeID = 0;
                        tmptouchreg = 0;
                        htouchInterval = 700;
                        prevmi = millis();
                        break;
                case 32:
                        // page_ID = swipeID;
                        updateScreen(swipeID); // gui.ino
                        shiftX = 0;
                        shiftY = 0;
                        swipeMe = 1;
                        swipeID = 0;
                        tmptouchreg = 0;
                        htouchInterval = 700;
                        prevmi = millis();
                        break;
                default:
                        break;
                }
                tmptouchreg = 0;
                touchStage = 0;
        }
}
void clearSwipeCache()
{
        shiftX = 0;
        shiftY = 0;
        swipeMe = 1;
        swipeID = 0;
        tmptouchreg = 0;
        htouchInterval = 700;
        prevmi = millis();
        // touched = 1;
}