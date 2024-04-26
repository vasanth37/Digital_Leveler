//#include "pins_arduino.h"
const int MPU_addr = 0x68;       // I2C address for MPU6050 sensor
const int NUM_OPTIONS = 5;       // Total number of options
const char* host = "script.google.com"; 
const int httpsPort = 443;
const char* fingerprint = "";

int16_t AcX, AcY, AcZ, angle_90, angle_180, convAngle_90, convAngle_180, Finangle_90, Finangle_180, NEW_ANGLE, SAVE_RESET_ANGLE;

double angle_z_90, angle_z_180;
double adjustAngle = 0.0;        //Need to check this part 

int selectedOption = 1;          // Initialize selected option to the first option
int BUZZER_PIN = D6;
int upButtonPin = D5;            // Pin for the up button
int downButtonPin = D3;          // Pin for the down button
int selectButtonPin = D4;        // Pin for the select button
int VOLTAGE_PIN = A0;
int batteryVoltageRaw;
int y, j, k, op_lab = 0, v = 1, m = 0;  // To rotate the Loop 
int LASER_COUNT = 0;
int PERVIOUS_LASER_COUNT = 0;
int MENU2OPTION = 1;
int MENU4OPTION = 1;             // Initialize menu4option option to the first option
int MENU3OPTION = 1;             // Initialize menu3option option to the first option
int MENU5OPTION = 1;             // Initialize menu5option option to the first option
int MENU6OPTION = 1;             // Initialize menu5option option to the first option
int INTERVAL_TIME = 10000;       // Time given to user to choose the option
int unsigned long PREVIOUS_TIME = 0;   
int unsigned long CURRENT_TIME = 0;
int HOLD_COUNT = 0;
int PREVIOUS_HOLD_COUNT = 0;
int value0, value1, tureValue=0;

#define DEBOUNCE_DELAY 400 // Adjust debounce delay as needed

volatile unsigned long lastUpPressTime = 0;
volatile unsigned long lastDownPressTime = 0;
volatile unsigned long lastSelectPressTime = 0;

volatile bool UP_BUTTON_LABEL = HIGH;
volatile bool DOWN_BUTTON_LABEL = HIGH;
volatile bool SELECT_BUTTON_LABEL = HIGH;

bool DISPLAY_ALARM_LABEL =LOW;
bool MENU_LABEL = LOW;
bool LASER1_LABEL = LOW, LASER2_LABEL = LOW;
bool LABEL_180 = HIGH;
bool LABEL_90 = LOW;
bool DISPLAY_LABEL = HIGH;
bool SELECT_DEGREE_LABEL = LOW;
bool SET_ALARM_LABEL = LOW;
bool WIFI_RESET_LABEL = LOW;
bool LOG_LABEL = LOW, LOG_LABEL_OPTION = LOW, LOG_BUTTON_LABEL = LOW;
bool ANGLE_RESET_OPTION_LABEL = LOW;
bool ANGLE_RESET_LABEL = LOW;
bool SAVE_RESET_LABEL = HIGH; 
bool HOLD_LABEL = LOW;
bool HOLD_VARIABLE_SAVE = LOW;
bool WIFI_LABEL = LOW;
bool ALARM_LABEL_OPTION = LOW;
bool ALARM_LABEL = LOW; 

int ASCII = 0;
char espSsid[33];               //To store SSID
char espPassword[33];           //To store Password
String esid;                    //stores the new SSID
String epass = "";              //stores the new password
int counter = 0;
int eepromLocationIndex = 0;    //Used in for loop to store ssid & password in particular location
int statusCode;
String string_Ssid_Rssi;        //creates the string for SSID and RSSI
String content;                 //Used for creating webpage

String dis180, dis90, NEW_ANGLE_STRING;
char car1[5], car2[5], car3[5];
char HOLD_VARIABLE[5]= {0,0,0,0,0};
int alarm[3] ={0,0,0};
int *ptr;
int batteryLevelInPercentage;

ESP8266WebServer server(80);    //--------Establishing Local server at port 80 whenever required

// Enter Google Script Deployment ID:
const char *GScriptId = "AKfycbxOvSaQhyOSog9Qj55WyVCH0VmkHFPi5aE_1RNwM9_8zfh62XUUC2Lr07XyZF6H_-1ZBw";

// Enter command (insert_row or append_row) and your Google Sheets sheet name (default is Sheet1):
String payload_base =  "{\"command\": \"insert_row\", \"sheet_name\": \"Sheet1\", \"values\": ";
String payload = "";

String url = String("/macros/s/") + GScriptId + "/exec";
HTTPSRedirect* client = nullptr;

// Custom mobile data ON symbols (up and down arrows)
const unsigned char LOWER_ARROW_BITMAP[] = {
  0x00, 0x04, 0x04, 0x04,
  0x04, 0x1F, 0x0E, 0x04
};

const unsigned char UPPER_ARROW_BITMAP[] = {
  0x04, 0x0E, 0x1F, 0x04,
  0x04, 0x04, 0x04, 0x00
};
