#include <U8g2lib.h>
#include <Wire.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include "HTTPSRedirect.h"
#include "variable.h"

#define LASER_PIN1 D8     
#define LASER_PIN2 D7

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); // Constructor for OLED 1.3inc Dispaly

void setup() {  // put your setup code here, to run once:
  Serial.begin(115200);
  u8g2.begin();
  pinMode(upButtonPin, INPUT_PULLUP);      // Set the up button pin as input with internal pull-up resistor
  pinMode(downButtonPin, INPUT_PULLUP);    // Set the down button pin as input with internal pull-up resistor
  pinMode(selectButtonPin, INPUT_PULLUP);  // Set the select button pin as input with internal pull-up resistor
  pinMode(LASER_PIN1, OUTPUT);              // Set the Laser Module1 pin as Output  
  pinMode(LASER_PIN2, OUTPUT);              // Set the Laser Module2 pin as Output 
  pinMode(BUZZER_PIN, OUTPUT);              // Set the Buzzer pin as Output
  attachInterrupt(digitalPinToInterrupt(upButtonPin), upButtonPressed, FALLING);
  attachInterrupt(digitalPinToInterrupt(downButtonPin), downButtonPressed, FALLING);
  attachInterrupt(digitalPinToInterrupt(selectButtonPin), selectedButtonPressed, FALLING);
  initializeMpu6050();                     // Initialize the MPU6050 Sensor
  welcomeNote();                           // User Welcome Note
  readWiFiName();
  if(testWiFi())
  {
    Serial.println("WiFi Connected");
    WIFI_LABEL = HIGH;                              //Setting the Wifi label HIGH
    display(25, 35, "WiFi Connected");              //Display in oled wifi connected
  }
  else{
    Serial.println("Wifi Not Connected");
    display(5, 35, "WiFi Not Connected");           //Display in oled wifi not connected
  }
  ptr = &alarm[0];
}

void loop() {
  // put your main code here, to run repeatedly:
  readAccelerometer();
  calculateAngles();
  if(LABEL_180)
  {
    degree180();
  }
  if(LABEL_90)
  {
    degree90(); 
  }
  if(ANGLE_RESET_LABEL)
  {
    angleReset();
  }
  if(MENU_LABEL)
  {
    DISPLAY_LABEL = LOW;
    menuPage();
  }
  if(LOG_LABEL)
  {
    logData();
  }
  checkLaserModule();
  readAccelerometer();
  calculateAngles();
  checkHold();
  checkLabel();
  batteryStatus();
  if(DISPLAY_LABEL)
  {
   displayOLED();
  }
}
