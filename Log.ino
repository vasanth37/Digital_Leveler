void logData()
  {
    if(LOG_BUTTON_LABEL)
    {
      if(testWiFi())
      {
        value0 ++;
        if(LABEL_180)
        {
          value1 = Finangle_180;
        }
        else if(LABEL_90)
        {
          value1 = Finangle_90;
        }
        static bool flag = false;
        if (!flag)
        {
          client = new HTTPSRedirect(httpsPort);
          client->setInsecure();
          flag = true;
          client->setPrintResponseBody(true);
          client->setContentTypeHeader("application/json");
        }
        if (client != nullptr)
        {
          if (!client->connected())
          {
            client->connect(host, httpsPort);
          }
        }
        else
        {
          Serial.println("Error creating client object!");
        }
        payload = payload_base + "\"" + value0 + "," + value1 +"\"}";   // Create json object string to send to Google Sheets
        Serial.println("Publishing data...");
        Serial.println(payload);                     // Publish data to Google Sheets
        if(client->POST(url, host, payload))
        {  
          display(5,35,"Data Logged Success");
        } 
        else
        {
          Serial.println("Error while connecting");   // do stuff here if publish was not successful
        }
      }
      else
      {
        display(5, 35, "WiFi Not Connected");
        Serial.println("Wifi Not Connected"); 
      }
    }
    LOG_BUTTON_LABEL = LOW;
  }
