HTTPClient http;
void getState()
{
    if (wifi.run == WL_CONNECTED)
    {
        http.begin("http://182.168.1.212");
        int httpCode = http.GET();
        if (httpCode > 0)
        {
            if (httpCode == HTTP_CODE_OK)
            {
            }
        }
    }
}
void drawState()
{
}
