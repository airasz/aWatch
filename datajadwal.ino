

uint8_t jsu, msu, jdz, mdz, jas, mas, jmag, mmag, jis, mis;
int dPray[5] = {0, 0, 0, 0, 0};
void formating(void)
{
    getPdata(imnt, iday);

    jsu = dPray[0] / 100;
    msu = dPray[0] - ((dPray[0] / 100) * 100);
    jdz = dPray[1] / 100;
    mdz = dPray[1] - ((dPray[1] / 100) * 100);
    jas = dPray[2] / 100;
    mas = dPray[2] - ((dPray[2] / 100) * 100);
    jmag = dPray[3] / 100;
    mmag = dPray[3] - ((dPray[3] / 100) * 100);
    jis = dPray[4] / 100;
    mis = dPray[4] - ((dPray[4] / 100) * 100);

    // dbFile.close();
}
void getPdata(uint8_t mnt, uint8_t day)
{
    dbFile = SPIFFS.open("/" + String(mnt - 1) + ".json", "r");
    // File dbFile = SPIFFS.open("/0.json", "r");
    if (!dbFile)
    {
        Serial.println("ERROR: DB file not found");
        // return false;
    }
    DynamicJsonDocument doc(3248);
    DeserializationError err = deserializeJson(doc, dbFile);
    if (err)
    {
        Serial.println("ERROR: " + String(err.c_str()));
        // return false;
    }
    for (size_t i = 0; i < 5; i++)
    {
        int in = doc[String(day)][i];
        dPray[i] = in;
    }
    // Serial.printf("pray day: %02d | mnt:  %02d | prayID%02d \n", day, mnt, in);

    dbFile.close();
}
uint16_t getpray(uint8_t mnt, uint8_t day, uint8_t prayID)
{
    // Serial.printf("load month  : %d \n", mnt-1);
    dbFile = SPIFFS.open("/" + String(mnt - 1) + ".json", "r");
    // File dbFile = SPIFFS.open("/0.json", "r");
    if (!dbFile)
    {
        Serial.println("ERROR: DB file not found");
        // return false;
    }
    DynamicJsonDocument doc(3248);
    DeserializationError err = deserializeJson(doc, dbFile);
    if (err)
    {
        Serial.println("ERROR: " + String(err.c_str()));
        // return false;
    }
    int in = doc[String(day)][prayID];
    // Serial.printf("pray day: %02d | mnt:  %02d | prayID%02d \n", day, mnt, in);

    // dbFile.close();
    return in;
}

//return string
String getDailyJWS(int id)
{
    // String jadwal = "";
    char jadwal[20];
    int maxday = MaxDate[imnt - 1];
    // formating();
    if (tomorow)
    {
        //if maximum day, jump to next month
        if (iday + 1 > maxday)
        {
            imnt += 1;
            iday = 1;
        }
        else
        {
            iday += 1;
        }
    }

    switch (id)
    {
    case 0:
        //                                                           .___________.
        //                                                  v----v----.         |
        sprintf(jadwal, "Subuh    > %02i:%02i", jsu, msu);
        // jadwal = "Subuh    > 0";
        // jadwal += jsu;
        // jadwal += (msu < 10) ? ":0" : ":";
        // jadwal += msu;

        break;
    case 1:
        sprintf(jadwal, "Dzuhur   > %02i:%02i", jdz, mdz);
        break;
    case 2:
        sprintf(jadwal, "Ashar    > %02i:%02i", jas, mas);
        break;
    case 3:
        sprintf(jadwal, "Maghrib  > %02i:%02i", jmag, mmag);
        break;
    case 4:
        sprintf(jadwal, "Isya'    > %02i:%02i", jis, mis);
        break;
    default:
        break;
    }
    if (tomorow)
        iday -= 1;
    return jadwal;
}
void setprayalarm(bool next)
{

    if (!alarmset)
    {
        ttgo->rtc->resetAlarm();
        getPraytaskID();
        int IDA;
        if (next)
        {
            IDA = ID_ + 1;
            (IDA > 4) && (IDA = 0);
            Serial.printf(" set pray alarm ID next : %d \n", IDA);
        }
        else
        {
            IDA = ID_;
            Serial.printf(" set pray alarm ID : %d \n", IDA);
        }
        int alh, alm;
        alarm_msg = String(config.alarmpraywarning);
        alarm_msg += " menit ";
        switch (IDA)
        {
        case 0:
            alm = (msu - config.alarmpraywarning < 0) ? 60 - (config.alarmpraywarning - msu) : alm = msu - config.alarmpraywarning;
            alh = (msu - config.alarmpraywarning < 0) ? jsu - 1 : jsu;
            alarm_msg += "menjelang subuh";
            break;
        case 1:
            alm = (mdz - config.alarmpraywarning < 0) ? 60 - (config.alarmpraywarning - mdz) : alm = mdz - config.alarmpraywarning;
            alh = (mdz - config.alarmpraywarning < 0) ? jdz - 1 : jdz;
            alarm_msg += "menjelang dzuhur";
            break;
        case 2:
            alm = (mas - config.alarmpraywarning < 0) ? 60 - (config.alarmpraywarning - mas) : alm = mas - config.alarmpraywarning;
            alh = (mas - config.alarmpraywarning < 0) ? jas - 1 : jas;
            alarm_msg += "menjelang ashar";
            break;
        case 3:
            alm = (mmag - config.alarmpraywarning < 0) ? 60 - (config.alarmpraywarning - mmag) : alm = mmag - config.alarmpraywarning;
            alh = (mmag - config.alarmpraywarning < 0) ? jmag - 1 : jmag;
            alarm_msg += "menjelang maghrib";
            break;
        case 4:
            alm = (mis - config.alarmpraywarning < 0) ? 60 - (config.alarmpraywarning - mis) : alm = mis - config.alarmpraywarning;
            alh = (mis - config.alarmpraywarning < 0) ? jis - 1 : jis;
            alarm_msg += "menjelang isya'";
            break;

        default:
            break;
        }

        ttgo->rtc->setAlarm(alh, alm, PCF8563_NO_ALARM, PCF8563_NO_ALARM);
        tmpaph = alh;
        tmpapm = alm;
        alarmset = true;
        ttgo->rtc->enableAlarm();
        config.alarm_pray = true;
        Serial.println("pray alarm has been set");
    }
}