void welcomeNote(){
  u8g2.clearBuffer();					              // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);      	// choose a suitable font
  u8g2.drawStr(35,20,"Welcome!");         	// write something to the internal memory
  u8g2.drawStr(30,50,"Smart Leveler");	// write something to the internal memory
  u8g2.sendBuffer();					              // transfer internal memory to the display
  delay(2000); 
}

void display(int x,int y, char *subject){
  u8g2.clearBuffer();					              // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);      	// choose a suitable font
  u8g2.drawStr(x, y, subject);    	// write something to the internal memory
  u8g2.sendBuffer();					              // transfer internal memory to the display
  delay(2000);
}

void displayOLED(){
  u8g2.clearBuffer();					              // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);      	// choose a suitable font
  if(WIFI_LABEL)
  {
    u8g2.drawXBMP(97, 2, 8, 8, UPPER_ARROW_BITMAP);
    u8g2.drawXBMP(102, 2, 8, 8, LOWER_ARROW_BITMAP);
  }
  if(LABEL_180)
  {
    u8g2.drawStr(40,60,"180 Deg");
    if(HOLD_LABEL)
    {
      u8g2.drawCircle(95, 32, 8, U8G2_DRAW_ALL);
      u8g2.drawStr(91,37,"H");
      u8g2.setFont(u8g2_font_ncenB14_tr);
      u8g2.drawStr(45,40,HOLD_VARIABLE);
    }
    else 
    {
      u8g2.setFont(u8g2_font_ncenB14_tr);
      u8g2.drawStr(45,40,car1);	
    }
  }
  if(LABEL_90)
  {
    u8g2.drawStr(40,60,"90 Deg"); 
    if(HOLD_LABEL)
    {
      u8g2.drawCircle(95, 32, 8, U8G2_DRAW_ALL);
      u8g2.drawStr(91,37,"H");
      u8g2.setFont(u8g2_font_ncenB14_tr);
      u8g2.drawStr(45,40,HOLD_VARIABLE);	
    }
    else 
    {
      u8g2.setFont(u8g2_font_ncenB14_tr);
      u8g2.drawStr(45,40,car2);	
    }        	
  }
  if(ANGLE_RESET_LABEL)
  {
    u8g2.drawStr(35,60,"User Ang"); 
    if(HOLD_LABEL)
    {
      u8g2.drawCircle(95, 32, 8, U8G2_DRAW_ALL);
      u8g2.drawStr(91,36,"H");
      u8g2.setFont(u8g2_font_ncenB14_tr);
      u8g2.drawStr(50,40,HOLD_VARIABLE);
    }
    else 
    {
      u8g2.setFont(u8g2_font_ncenB14_tr);
      u8g2.drawStr(50,40, car3);	
    }
  }
  if(ALARM_LABEL)
  {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawCircle(25, 32, 8, U8G2_DRAW_ALL);
    u8g2.drawStr(22,35,"A");   
  }
  if(LOG_LABEL)
  {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawCircle(95, 32, 8, U8G2_DRAW_ALL);
    u8g2.drawStr(92,37,"L");
  }

  u8g2.drawFrame(112,2,16,8);// Battery Outer layer 
  u8g2.drawFrame(110,4,3,3);
  if((batteryLevelInPercentage <= 14))
  {
     
  }
  else if((batteryLevelInPercentage <= 25) && (batteryLevelInPercentage >= 15))
  {
    u8g2.drawVLine(124,3,7);
  }
  else if((batteryLevelInPercentage >= 26) && (batteryLevelInPercentage <= 50))
  {
    u8g2.drawVLine(124,3,7);
    u8g2.drawVLine(121,3,7);
  }
  else if((batteryLevelInPercentage >= 51) && (batteryLevelInPercentage <= 75))
  {
    u8g2.drawVLine(124,3,7);
    u8g2.drawVLine(121,3,7);
    u8g2.drawVLine(118,3,7);
  }
  else if(batteryLevelInPercentage >= 76)
  {
    u8g2.drawVLine(124,3,7);
    u8g2.drawVLine(121,3,7);
    u8g2.drawVLine(118,3,7);
    u8g2.drawVLine(115,3,7);
  }
  u8g2.sendBuffer();
}

void menu1(int selectedOption){
  u8g2.clearBuffer();					
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setCursor(45, 10);                 // Set cursor position for heading
  u8g2.print("Menu");                     // Print heading

  if((selectedOption == 4)||(selectedOption == 5))
  {  
    u8g2.clearBuffer();					
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.setCursor(45, 10);                 // Set cursor position for heading
    u8g2.print("Menu");
    for(int s=4;s<=5;s++)
    {
     k = 15 + v * 14;
     if ((s == selectedOption)) 
      {
         u8g2.drawButtonUTF8(2, k, U8G2_BTN_INV, u8g2.getDisplayWidth()-10*2,  12,  2, getOptionText(s));
      }
     else{
        u8g2.drawButtonUTF8(2, k, 0, u8g2.getDisplayWidth()-10*2,  12,  2, getOptionText(s));
     }
     v = v+1;
    }
    v=1;
    u8g2.sendBuffer();
  }
  else{
  for(int i=0; i<4; i++)       //Print the options 
  { 
      y = 15 + i * 14;
      if ((i == selectedOption)) 
      { 
        u8g2.drawButtonUTF8(2, y, U8G2_BTN_INV, u8g2.getDisplayWidth()-10*2,  12,  2, getOptionText(i));
      } 
      else
      {
        u8g2.drawButtonUTF8(2, y, 0, u8g2.getDisplayWidth()-10*2,  12,  2, getOptionText(i));
      }
  }
    u8g2.sendBuffer();	
  }				
}

const char* getOptionText(int option) {
  switch(option) 
  {
    case 1:
      return "Set Angle for Alarm";
    case 2:
      return "90 or 180 Degree";
    case 3:
      return "Log the Data";
    case 4:
      return "Angle Reset";
    case 5:
      return "WiFi Reset";
    default:
      return "";
  }
}

void menu2(int selectedOption){
  Serial.println("Set Alarm");
  u8g2.clearBuffer();					
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setCursor(15, 10);                 // Set cursor position for heading
  u8g2.print("Set Alarm");
  for(int s=1; s<3; s++)
  {
    int k = 15 + s * 14;
    if(s == MENU2OPTION) 
      {
        u8g2.drawButtonUTF8(2, k, U8G2_BTN_INV, u8g2.getDisplayWidth()-10*2,  12,  2, getMenu2Option(s));
      }
    else
      {
        u8g2.drawButtonUTF8(2, k, 0, u8g2.getDisplayWidth()-10*2,  12,  2, getMenu2Option(s));
      }
  }
  u8g2.sendBuffer();
}

const char* getMenu2Option(int option){
  switch(option) 
  {
    case 1:
      return "ON Alarm";
    case 2:
      return "OFF Alram";
    default:
      return "";
  }
}

void menu3(int MENU3OPTION){
  Serial.println("Menu_Func");
  u8g2.clearBuffer();					
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setCursor(15, 10);                 // Set cursor position for heading
  u8g2.print("Choose the Degree");
  for(int s=1; s<3; s++)
  {
    int k = 15 + s * 14;
    if(s == MENU3OPTION) 
      {
        u8g2.drawButtonUTF8(2, k, U8G2_BTN_INV, u8g2.getDisplayWidth()-10*2,  12,  2, getMenu3Option(s));
      }
    else
      {
        u8g2.drawButtonUTF8(2, k, 0, u8g2.getDisplayWidth()-10*2,  12,  2, getMenu3Option(s));
      }
  }
  u8g2.sendBuffer();
}

const char* getMenu3Option(int option){
  switch(option) 
  {
    case 1:
      return "90 Degree";
    case 2:
      return "180 Degree";
    default:
      return "";
  }
}

void menu4(int MENU4OPTION){
  Serial.println("Menu_Func");
  u8g2.clearBuffer();					
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setCursor(15, 10);                 // Set cursor position for heading
  u8g2.print("Log Menu");
  for(int s=1; s<3; s++)
  {
    int k = 15 + s * 14;
    if(s == MENU4OPTION) 
      {
        u8g2.drawButtonUTF8(2, k, U8G2_BTN_INV, u8g2.getDisplayWidth()-10*2,  12,  2, getMenu4Option(s));
      }
    else
      {
        u8g2.drawButtonUTF8(2, k, 0, u8g2.getDisplayWidth()-10*2,  12,  2, getMenu4Option(s));
      }
  }
  u8g2.sendBuffer();
}

const char* getMenu4Option(int option){
  switch(option) 
  {
    case 1:
      return "Start Log";
    case 2:
      return "Stop Log";
    default:
      return "";
  }
}

void menu5(int MENU5OPTION){
  Serial.println("Menu_Func");
  u8g2.clearBuffer();					
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setCursor(15, 10);                 // Set cursor position for heading
  u8g2.print("Reset The Angle");
  for(int s=1; s<3; s++)
  {
    int k = 15 + s * 14;
    if(s == MENU5OPTION) 
      {
        u8g2.drawButtonUTF8(2, k, U8G2_BTN_INV, u8g2.getDisplayWidth()-10*2,  12,  2, getMenu5Option(s));
      }
    else
      {
        u8g2.drawButtonUTF8(2, k, 0, u8g2.getDisplayWidth()-10*2,  12,  2, getMenu5Option(s));
      }
  }
  u8g2.sendBuffer();
}

const char* getMenu5Option(int option){
  switch(option) 
  {
    case 1:
      return "Set Angle to 0";
    case 2:
      return "Reset The Angle";
    default:
      return "";
  }
}

void menu6(int MENU6OPTION){
  u8g2.clearBuffer();					
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setCursor(15, 10);                 // Set cursor position for heading
  u8g2.print("Need to Search WiFi");
  for(int s=1; s<3; s++)
  {
    int k = 15 + s * 14;
    if(s == MENU6OPTION) 
      {
        u8g2.drawButtonUTF8(2, k, U8G2_BTN_INV, u8g2.getDisplayWidth()-10*2,  12,  2, getMenu6Option(s));
      }
    else
      {
        u8g2.drawButtonUTF8(2, k, 0, u8g2.getDisplayWidth()-10*2,  12,  2, getMenu6Option(s));
      }
  }
  u8g2.sendBuffer(); 
}

const char* getMenu6Option(int option){
  switch(option) 
  {
    case 1:
      return "Yes";
    case 2:
      return "No";
    default:
      return "";
  }
}

void angleSetOptionDisplay()
{
  u8g2.clearBuffer();					              // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB14_tr);      	// choose a suitable font
  u8g2.setCursor(45, 40); // Set cursor position
  for (int i = 0; i < sizeof(alarm)/sizeof(alarm[0]); i++, ptr[i])
   {
      u8g2.print(ptr[i]); // Print each integer element of the array
      u8g2.print(" "); // Print a space between elements
   }
   u8g2.setFont(u8g2_font_ncenB08_tr);
   u8g2.setCursor(55, 55); // Set cursor position
   u8g2.print("Set Alarm");
   u8g2.sendBuffer();
}
