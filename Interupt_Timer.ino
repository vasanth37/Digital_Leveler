
ICACHE_RAM_ATTR void upButtonPressed(){
  unsigned long currentTime = millis();
  if (currentTime - lastUpPressTime >= DEBOUNCE_DELAY) 
  {
    lastUpPressTime = currentTime;
      Serial.println("UP_ISR");
      if(MENU_LABEL || SELECT_DEGREE_LABEL || WIFI_RESET_LABEL || ANGLE_RESET_OPTION_LABEL || LOG_LABEL_OPTION || ALARM_LABEL_OPTION){
        UP_BUTTON_LABEL = LOW;
      }
      else if(ALARM_LABEL)
      {
        if(m == 0)
        {
          if(ptr[0] < 1) ptr[0]++; else ptr[0] = 0;
        }
        if(ptr[0] == 1)
        {
          if(m == 1)
          {
            if(ptr[1] < 8) ptr[1]++; else ptr[1] = 0;
          }
        }
        else if(ptr[0] == 0)
        {
          if(m == 1)
          {
            if(ptr[1] < 9) ptr[1]++; else ptr[1] = 0;
          }
        }
        if(m == 2)
        {
          if(ptr[2] < 9) ptr[2]++; else ptr[2] = 0;
        }
      }
      else if(!(MENU_LABEL || SELECT_DEGREE_LABEL || WIFI_RESET_LABEL || ANGLE_RESET_OPTION_LABEL || LOG_LABEL_OPTION || ALARM_LABEL_OPTION))
      {
        LASER_COUNT++;
      }
  }
}  

ICACHE_RAM_ATTR void downButtonPressed(){
  unsigned long currentTime = millis();
  if (currentTime - lastUpPressTime >= DEBOUNCE_DELAY){ 
    lastUpPressTime = currentTime;
    Serial.println("DOWN_ISR");
    if(MENU_LABEL || SELECT_DEGREE_LABEL || WIFI_RESET_LABEL || ANGLE_RESET_OPTION_LABEL || LOG_LABEL_OPTION || ALARM_LABEL_OPTION)
    {
       DOWN_BUTTON_LABEL = LOW;
    }
    else if(LOG_LABEL)
    {
      LOG_BUTTON_LABEL = HIGH;
      Serial.println("Log Button");
    }
    else if(ALARM_LABEL)
    {
      if(m == 0)
      {
        if(ptr[0] > 0) ptr[0]--;
      }
      if(m == 1)
      { 
        if(ptr[1] > 0) ptr[1]--;
      }
      if(m == 2)
      { 
        if(ptr[2] > 0) ptr[2]--;
      }
    }
    if(!(SELECT_DEGREE_LABEL || WIFI_RESET_LABEL || ANGLE_RESET_OPTION_LABEL || LOG_LABEL_OPTION || ALARM_LABEL_OPTION))
    {
      HOLD_COUNT++;
      Serial.println("Hold Pressed");
    }
  }
}

ICACHE_RAM_ATTR void selectedButtonPressed(){
  unsigned long currentTime = millis();
  if (currentTime - lastUpPressTime >= DEBOUNCE_DELAY)
  { 
      lastUpPressTime = currentTime;  
      if(MENU_LABEL || SELECT_DEGREE_LABEL || WIFI_RESET_LABEL || ANGLE_RESET_OPTION_LABEL || LOG_LABEL_OPTION || ALARM_LABEL_OPTION)
      {
        Serial.println("Select button");
        SELECT_BUTTON_LABEL = LOW;
      }
      if(ALARM_LABEL && !(DISPLAY_LABEL))
      {
        if(m == 2)
        {
          m = 0;
          DISPLAY_LABEL = HIGH;
          DISPLAY_ALARM_LABEL = LOW;
        }
        else ++m;
      }
      else
      {
        Serial.println("Menu Label");
        MENU_LABEL = HIGH;
      }
  }
}

bool checkTime(){
  CURRENT_TIME = millis();
  if(CURRENT_TIME - PREVIOUS_TIME > INTERVAL_TIME)
  { 
    PREVIOUS_TIME = CURRENT_TIME;
    return 1;
  }
  else
  {
    return 0;
  }
}
