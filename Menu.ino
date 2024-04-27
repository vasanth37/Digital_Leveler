void menuPage(){
  if(checkTime())
  {
    DISPLAY_LABEL = HIGH;
    MENU_LABEL = LOW;
  }
  menu1(selectedOption);
  if (UP_BUTTON_LABEL == LOW)
    {
      Serial.println("up");
      UP_BUTTON_LABEL = HIGH;
      selectedOption = (selectedOption == 1) ? NUM_OPTIONS : selectedOption - 1;
      menu1(selectedOption);
    }
  if (DOWN_BUTTON_LABEL == LOW)
    {
      Serial.println("Down");
      DOWN_BUTTON_LABEL = HIGH;
      selectedOption = (selectedOption % NUM_OPTIONS) + 1;
      menu1(selectedOption);
    }
  if (SELECT_BUTTON_LABEL == LOW)
    {
      Serial.println("Select");
      SELECT_BUTTON_LABEL = HIGH;                  //Enabel SELECT_BUTTON_LABEL HIGH 
      PREVIOUS_TIME = CURRENT_TIME;                //copying the Current time into previous time
      executeAction1(selectedOption);
    }
  //Serial.println("menu_page");
}

void executeAction1(int op1){
  switch(op1)
  {
    case 1:
     Serial.println("Alarm Angel option");
     MENU_LABEL = LOW;
     DISPLAY_LABEL = LOW;
     ALARM_LABEL_OPTION = HIGH;
     setAlarmOption();
     break;
    case 2:
     Serial.println("Select Degree");
     SELECT_DEGREE_LABEL = HIGH;
     MENU_LABEL = LOW;
     selectDegreeOption();
     break;
    case 3:
     Serial.println("op3");
     MENU_LABEL = LOW;
     DISPLAY_LABEL = LOW;
     LOG_LABEL_OPTION = HIGH;
     LogOption();
     break;
    case 4:
     Serial.println("op4");
     if(LABEL_90)
     {
        display(10, 35, "Change to 180 Deg");
     }
     else
     {
        MENU_LABEL = LOW;
        ANGLE_RESET_OPTION_LABEL = HIGH;
        angleResetOption();
     }
     break;
    case 5:
     Serial.println("op5");
     WIFI_RESET_LABEL = HIGH;
     MENU_LABEL = LOW;
     wifiMenu();
     break;
  }
}

void selectDegreeOption(){
  Serial.println("Menu3");
  menu3(MENU3OPTION);
  if (UP_BUTTON_LABEL == LOW)
  {
     UP_BUTTON_LABEL = HIGH;
     if(MENU3OPTION == 2)
       {
        MENU3OPTION = MENU3OPTION -1;
       }
     menu3(MENU3OPTION);
  }  
  if (DOWN_BUTTON_LABEL == LOW)
  {
     DOWN_BUTTON_LABEL = HIGH;
     if( MENU3OPTION == 1)
      {
        MENU3OPTION = MENU3OPTION +1;
      }
     menu3(MENU3OPTION);
  }
  if (SELECT_BUTTON_LABEL == LOW)
  {
      SELECT_BUTTON_LABEL = HIGH;
      PREVIOUS_TIME = CURRENT_TIME;                //copying the Current time into previous time
      executeAction3(MENU3OPTION);
  }
}

void executeAction3(int op3){
  switch(op3){
    case 1:
      Serial.println("90 DEG");
      MENU_LABEL = LOW;
      LABEL_180 = LOW;
      LABEL_90 = HIGH;
      DISPLAY_LABEL = HIGH;
      SELECT_DEGREE_LABEL = LOW;
      break;
    case 2:
      Serial.println("180 DEG");
      MENU_LABEL = LOW;
      LABEL_90 = LOW;
      LABEL_180 = HIGH;
      DISPLAY_LABEL = HIGH;
      SELECT_DEGREE_LABEL = LOW;
      break;
  }
}

void angleResetOption(){
 Serial.println("Menu5");
  menu5(MENU5OPTION);
  if(checkTime())
  {
      DISPLAY_LABEL = HIGH;
      ANGLE_RESET_OPTION_LABEL = LOW;
  }
  if (UP_BUTTON_LABEL == LOW)
  {
     UP_BUTTON_LABEL = HIGH;
     if(MENU5OPTION == 2)
       {
        MENU5OPTION = MENU5OPTION -1;
       }
     menu5(MENU5OPTION);
  }  
  if (DOWN_BUTTON_LABEL == LOW)
  {
     DOWN_BUTTON_LABEL = HIGH;
     if( MENU5OPTION == 1)
      {
        MENU5OPTION = MENU5OPTION +1;
      }
     menu5(MENU5OPTION);
  }
  if (SELECT_BUTTON_LABEL == LOW)
  {
      SELECT_BUTTON_LABEL = HIGH;
      PREVIOUS_TIME = CURRENT_TIME;                //copying the Current time into previous time
      executeAction5(MENU5OPTION);
  }
}

void executeAction5(int op5){
  switch(op5)
  {
    case 1:
      Serial.println("Set angle to 0");
      DISPLAY_LABEL = HIGH;
      ANGLE_RESET_OPTION_LABEL = LOW;
      ANGLE_RESET_LABEL = HIGH;
      LABEL_180 = LOW;
      MENU_LABEL = LOW;
      angleReset();
      break;
    case 2:
      Serial.println("Reset the Angle");
      ANGLE_RESET_LABEL = LOW;
      ANGLE_RESET_OPTION_LABEL = LOW;
      DISPLAY_LABEL = HIGH;
      SAVE_RESET_LABEL = HIGH;
      LABEL_180 = HIGH;
      MENU_LABEL = LOW;
      break;
  }
}

void LogOption(){
  Serial.println("Menu4");
  menu4(MENU4OPTION);
  if(checkTime())
  {
      DISPLAY_LABEL = HIGH;
      LOG_LABEL_OPTION = LOW;
      LOG_LABEL = LOW;
  }
  if (UP_BUTTON_LABEL == LOW)
  {
     UP_BUTTON_LABEL = HIGH;
     if(MENU4OPTION == 2)
       {
        MENU4OPTION = MENU4OPTION -1;
       }
     menu4(MENU4OPTION);
  }  
  if (DOWN_BUTTON_LABEL == LOW)
  {
     DOWN_BUTTON_LABEL = HIGH;
     if( MENU4OPTION == 1)
      {
        MENU4OPTION = MENU4OPTION +1;
      }
     menu4(MENU4OPTION);
  }
  if (SELECT_BUTTON_LABEL == LOW)
  {
      SELECT_BUTTON_LABEL = HIGH;
      PREVIOUS_TIME = CURRENT_TIME;                //copying the Current time into previous time
      executeAction4(MENU4OPTION);
  }
}

void executeAction4(int op4){
  switch(op4)
  {
    case 1:
      Serial.println("Start Log");
      DISPLAY_LABEL = HIGH;
      LOG_LABEL_OPTION = LOW;
      LOG_LABEL = HIGH;
      MENU_LABEL = LOW;
      logData();
      break;
    case 2:
      Serial.println("Stop Log");
      DISPLAY_LABEL = HIGH;
      LOG_LABEL = LOW;
      MENU_LABEL = LOW;
      LOG_LABEL_OPTION = LOW;
      break;
  }
}

void wifiMenu(){
  Serial.println("Menu6");
    if(checkTime())
    {
       DISPLAY_LABEL = HIGH;
       WIFI_RESET_LABEL = LOW;
    }
    menu6(MENU6OPTION);
    if (UP_BUTTON_LABEL == LOW)
    {
       UP_BUTTON_LABEL = HIGH;
       if(MENU6OPTION == 2)
       {
         MENU6OPTION = MENU6OPTION - 1;
       }
       menu6(MENU6OPTION);
    }  
    if (DOWN_BUTTON_LABEL == LOW)
    {
       DOWN_BUTTON_LABEL = HIGH;
       if( MENU6OPTION == 1)
       {
         MENU6OPTION = MENU6OPTION + 1;
       }
       menu6(MENU6OPTION);
    }
    if (SELECT_BUTTON_LABEL == LOW)
    {
       SELECT_BUTTON_LABEL = HIGH;
       PREVIOUS_TIME = CURRENT_TIME;                //copying the Current time into previous time
       executeAction6(MENU6OPTION);
    }
}

void executeAction6(int op6){
  switch(op6)
  {
    case 1:
     Serial.println("Yes");
     display(15,35,"Resetting the WiFi");
     launchWeb();
     setupAP();
     display(15,35,"Open 192.168.4.1");
     while ((WiFi.status() != WL_CONNECTED)) 
     {
        Serial.print(".");
        server.handleClient();
     }
     display(20,35,"WiFi Connected");
     DISPLAY_LABEL = HIGH;
     WIFI_RESET_LABEL = LOW;
     MENU_LABEL = LOW;
     break;
    case 2:
     Serial.println("NO");
     DISPLAY_LABEL = HIGH;
     WIFI_RESET_LABEL = LOW;
     MENU_LABEL = LOW;
     break;
  }
}

void checkLabel(){
  if(SELECT_DEGREE_LABEL)
  {
    Serial.println("SELECT_DEGREE_LABEL");
    selectDegreeOption();
    if(checkTime())
    {
      SELECT_DEGREE_LABEL = LOW;
      DISPLAY_LABEL = HIGH;
    }
  }
  if(WIFI_RESET_LABEL)
  {
    Serial.println("SELECT_DEGREE_LABEL");
    wifiMenu();
    if(checkTime())
    {
      WIFI_RESET_LABEL = LOW;
      DISPLAY_LABEL = HIGH;
    }
  }
  if(ANGLE_RESET_OPTION_LABEL)
  {
    Serial.println("ANGLE_RESET_OPTION_LABEL");
    angleResetOption();
    if(checkTime())
    {
      ANGLE_RESET_OPTION_LABEL = LOW;
      DISPLAY_LABEL = HIGH;
    }
  }
  if(ANGLE_RESET_LABEL)
  {
    Serial.println("ANGLE_RESET_LABEL");
    angleReset();
  }
  if(LOG_LABEL)
  {
    Serial.println("LOG_DATA_LABEL");
    logData();
  }
  if(LOG_LABEL_OPTION)
  {
    Serial.println("LOG_OPTION_LABEL");
    LogOption();  
  }
  if(ALARM_LABEL_OPTION)
  {
    Serial.println("ALARM_OPTION_LABEL");
    setAlarmOption();
  }
  if(ALARM_LABEL)
  {
    onAlarm();
    //Serial.println("SET_ALARM_LABEL");
  }
  if(DISPLAY_ALARM_LABEL)
  {
    angleSetOptionDisplay();
  }
}

void setAlarmOption(){
  Serial.println("Menu2");
  if(checkTime())
  {
    DISPLAY_LABEL = HIGH;
    MENU_LABEL = LOW;
    ALARM_LABEL_OPTION = LOW;
  }
  menu2(MENU2OPTION);
  if (UP_BUTTON_LABEL == LOW)
  {
     UP_BUTTON_LABEL = HIGH;
     if(MENU2OPTION == 2)
       {
        MENU2OPTION = MENU2OPTION -1;
       }
     menu2(MENU2OPTION);
  }  
  if (DOWN_BUTTON_LABEL == LOW)
  {
     DOWN_BUTTON_LABEL = HIGH;
     if( MENU2OPTION == 1)
      {
        MENU2OPTION = MENU2OPTION +1;
      }
     menu2(MENU2OPTION);
  }
  if (SELECT_BUTTON_LABEL == LOW)
  {
      SELECT_BUTTON_LABEL = HIGH;
      PREVIOUS_TIME = CURRENT_TIME;                //copying the Current time into previous time
      executeAction2(MENU2OPTION);
  }
}

void executeAction2(int op2){
  switch(op2)
  {
    case 1:
      ALARM_LABEL_OPTION = LOW;
      ALARM_LABEL = HIGH;
      MENU_LABEL = LOW;
      DISPLAY_LABEL = LOW;
      DISPLAY_ALARM_LABEL = HIGH;
      onAlarm();
      break;
    case 2:
      MENU_LABEL = LOW;
      ALARM_LABEL = LOW;
      DISPLAY_LABEL = HIGH;
      ALARM_LABEL_OPTION = LOW;
      m = 0;
      Serial.println("ALARM_LABEL = LOW");
      break;
  }
}
