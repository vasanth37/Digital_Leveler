void readWiFiName()
{
  EEPROM.begin(512);    //Initializing EEPROM
  Serial.println("Reading EEPROM ssid");
  for (ASCII = 0; ASCII < 32; ++ASCII) {          //Reading EEPROM ssid
    esid += char(EEPROM.read(ASCII));  //storing the detected SSID in the EEPROM
  }
  Serial.print("SSID: ");
  Serial.println(esid);
  Serial.println("Reading EEPROM pass");
  for (ASCII = 32; ASCII < 96; ++ASCII) {
    epass += char(EEPROM.read(ASCII));  //storing the detected password in the EEPROM
  }
  Serial.print("PASS: ");
  Serial.println(epass);
  Serial.println();
  WiFi.begin(esid.c_str(), epass.c_str());  //begin the module with previously detected wifi
}

bool testWiFi(){
  Serial.println("Waiting for Wifi to connect");
  while (counter < 20) {
    if (WiFi.status() == WL_CONNECTED)  //wait for 20 seconds for detecting if the module gets connected to the previous n/w whose credentials are stored in the EEPROM
    {
      return true;
    }
    delay(500);
    Serial.print("*");
    counter++;
  }
  Serial.println("");
  Serial.println("Connect timed out, opening AP");
  return false;
}

void launchWeb()
{
  Serial.println("");
  if (WiFi.status() == WL_CONNECTED)
  Serial.println("WiFi connected");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("SoftAP IP: ");
  Serial.println(WiFi.softAPIP());
  createWebServer();
  // Start the server
  server.begin();
  Serial.println("Server started");
}

void setupAP(void)
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int numberOfWifiAvailable = WiFi.scanNetworks();    //To check how many Wifi networks are currently available
  Serial.println("scan completed");
  if (numberOfWifiAvailable == 0)
    Serial.println("No WiFi Networks found");
  else
  {
    Serial.print(numberOfWifiAvailable);
    Serial.println(" Networks found");
    for (int wifiCount = 0; wifiCount < numberOfWifiAvailable; ++wifiCount)
    {
      // Print SSID and RSSI for each network found
      Serial.print(wifiCount + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(wifiCount));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(wifiCount));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(wifiCount) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");
  string_Ssid_Rssi = "<ol>";
  for (int wifiCount = 0; wifiCount < numberOfWifiAvailable; ++wifiCount)
  {
    // Print SSID and RSSI for each network found
    string_Ssid_Rssi += "<li>";
    string_Ssid_Rssi += WiFi.SSID(wifiCount);
    string_Ssid_Rssi += " (";
    string_Ssid_Rssi += WiFi.RSSI(wifiCount);
 
    string_Ssid_Rssi += ")";
    string_Ssid_Rssi += (WiFi.encryptionType(wifiCount) == ENC_TYPE_NONE) ? " " : "*";
    string_Ssid_Rssi += "</li>";
  }
  string_Ssid_Rssi += "</ol>";
  delay(100);
  WiFi.softAP("Smart Leveler", "");
  Serial.println("Initializing_Wifi_accesspoint");
  launchWeb();
  Serial.println("over");
}

void createWebServer()
{
 {
    server.on("/", []() {
 
      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      content = "<!DOCTYPE HTML>\r\n<html>ESP8266 WiFi Connectivity Setup ";
      content += "<form action=\"/scan\" method=\"POST\"><input type=\"submit\" value=\"scan\"></form>";
      content += ipStr;
      content += "<p>";
      content += string_Ssid_Rssi;
      content += "</p><form method='get' action='setting'><label>SSID: </label><input name='ssid' length=32><input name='pass' length=64><input type='submit'></form>";
      content += "</html>";
      server.send(200, "text/html", content);
    });
    server.on("/scan", []() {
      //setupAP();
      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
 
      content = "<!DOCTYPE HTML>\r\n<html>go back";
      server.send(200, "text/html", content);
    });
 
    server.on("/setting", []() {
      String qsid = server.arg("ssid");
      String qpass = server.arg("pass");
      if (qsid.length() > 0 && qpass.length() > 0) {
        Serial.println("clearing eeprom");
        for (int eepromLocationIndex = 0; eepromLocationIndex < 96; ++eepromLocationIndex) {
          EEPROM.write(eepromLocationIndex, 0);
        }
        Serial.println(qsid);
        Serial.println("");
        Serial.println(qpass);
        Serial.println("");
 
        Serial.println("writing eeprom ssid:");
        for (int eepromLocationIndex = 0; eepromLocationIndex < qsid.length(); ++eepromLocationIndex)
        {
          EEPROM.write(eepromLocationIndex, qsid[eepromLocationIndex]);
          Serial.print("Wrote: ");
          Serial.println(qsid[eepromLocationIndex]);
        }
        Serial.println("writing eeprom pass:");
        for (int eepromLocationIndex = 0; eepromLocationIndex < qpass.length(); ++eepromLocationIndex)
        {
          EEPROM.write(32 + eepromLocationIndex, qpass[eepromLocationIndex]);
          Serial.print("Wrote: ");
          Serial.println(qpass[eepromLocationIndex]);
        }
        EEPROM.commit();
 
        content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi\"}";
        statusCode = 200;
        //ESP.reset();
  Serial.println("Reading EEPROM ssid");
  String esid;  //stores the new SSID

  for (int eepromLocationIndex = 0; eepromLocationIndex < 32; ++eepromLocationIndex)
  {
    esid += char(EEPROM.read(eepromLocationIndex));
  }
  Serial.println();
  Serial.print("SSID: ");
  Serial.println(esid);
  Serial.println("Reading EEPROM pass");
  esid.toCharArray(espSsid, 33);      //Converting to Character
 
  String epass = ""; //stores the new password
  for (int eepromLocationIndex = 32; eepromLocationIndex < 96; ++eepromLocationIndex)
  {
    epass += char(EEPROM.read(eepromLocationIndex));
  }
  Serial.print("PASS: ");
  Serial.println(epass);
  epass.toCharArray(espPassword, 33);   //Converting to Character
 
  WiFi.begin(esid.c_str(), epass.c_str());
  if (testWiFi())
  {
    Serial.println("Succesfully Connected!!!");
    //display(35, 20, "WiFi Connected");
  }
  else
  {
    Serial.println("Turning the HotSpot On");
    launchWeb();
    setupAP();    // Setup accesspoint or HotSpot
  }
  Serial.println();
  Serial.println("Waiting.");
  
  while ((WiFi.status() != WL_CONNECTED))
  {
    Serial.print(".");
    delay(100);
    server.handleClient();
    Serial.println("WiFI Not Connected");	
  }
      } else {
        content = "{\"Error\":\"404 not found\"}";
        statusCode = 404;
        Serial.println("Sending 404");
      }
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.send(statusCode, "application/json", content);
    });
  } 
}
