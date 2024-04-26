
void initializeMpu6050(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

void readAccelerometer() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 6, 1);
  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
}

void calculateAngles() {
  angle_z_90 = angle_z_180 = atan2(-AcX, -AcY) * 180.0 / PI;
}

void degree180(){
  angle_z_180 = angle_z_180 - 180;
  angle_180 = abs(angle_z_180);
  if((angle_180 <= 359) && (angle_180 > 180))
  {
    convAngle_180 = angle_180 % 360; 
    Finangle_180 = -(360 - convAngle_180);
    dis180 = String(Finangle_180);
    dis180.toCharArray(car1,5);
  }
  else if((angle_180 >= 0)&&(angle_180 <= 180))
  { 
    Finangle_180 = angle_180;
    dis180 = String(angle_180);
    dis180.toCharArray(car1,5);
  }
  if(HOLD_LABEL == HIGH)
  {
    if(HOLD_VARIABLE_SAVE)
    {
      memcpy(HOLD_VARIABLE, car1, sizeof(car1));
      HOLD_VARIABLE_SAVE = LOW;
    }
  }
}

void degree90(){
  angle_z_90 = angle_z_90 - 180; 
  angle_90 = abs(angle_z_90);              // Get the absolute angle value
  if((angle_90 > 90)&&(angle_90 <= 180))   // Wrap the angle around if it crosses 90 degrees
  {
    convAngle_90 = angle_90 % 90;          // Calculate the remainder when dividing the angle by 90
    Finangle_90 = 90 - convAngle_90;       // Calculate the wrapped angle by subtracting the remainder from 90
    if(Finangle_90 == 90)
      {
        Finangle_90 = 0;
      }
      //Serial.print("Fz-: "); Serial.println(Finangle_90);
    dis90 = String(Finangle_90);
    dis90.toCharArray(car2,5);
  } 
  else if((angle_90 >= 0)&&(angle_90 <= 90))
  {
    //Serial.print(" z: "); Serial.println(angle_90); // If the angle is less than 90, simply print it
    Finangle_90 = angle_90;   
    dis90 = String(angle_90);
    dis90.toCharArray(car2,5);
  }
  if(HOLD_LABEL == HIGH)
  {
    if(HOLD_VARIABLE_SAVE)
    {
      memcpy(HOLD_VARIABLE, car2, sizeof(car2));
      HOLD_VARIABLE_SAVE = LOW;
    }
  }
}

void checkHold(){
 if(HOLD_COUNT != 0)
 {
   if(PREVIOUS_HOLD_COUNT != HOLD_COUNT && HOLD_LABEL)
   {
     HOLD_COUNT = 0;
     PREVIOUS_HOLD_COUNT = 0;
     HOLD_LABEL = LOW;
     HOLD_VARIABLE_SAVE = HIGH;
     Serial.println("Hold Released");
   }
   else
   {
     HOLD_LABEL = HIGH;
     PREVIOUS_HOLD_COUNT = HOLD_COUNT;
     Serial.println("Hold Pressed");
   }
 }
}

void angleReset(){
  angle_z_180 = angle_z_180 - 180;
  angle_180 = abs(angle_z_180);
  //Serial.println(angle_180);
    if(SAVE_RESET_LABEL)
    {
        SAVE_RESET_LABEL = LOW;
        SAVE_RESET_ANGLE = angle_180;
        Serial.println("Save Reset Angle");
    }
    NEW_ANGLE = angle_180 - SAVE_RESET_ANGLE;
    if(NEW_ANGLE > 180)
    {
      display(0,20,"Max Angle Reach 180Dec");
    }
    else 
    {
      NEW_ANGLE_STRING = String(NEW_ANGLE);
      NEW_ANGLE_STRING.toCharArray(car3,5);
      Serial.println(car3);
    } 
}

void onAlarm(){
  int result;  
  for (int i = 0; i < 3; i++){
   result += alarm[2-i] * pow(10, i);
  }
  if(result == angle_180)
  {
    digitalWrite(BUZZER_PIN, HIGH);
  }
  else
  {
    digitalWrite(BUZZER_PIN, LOW);
  }
}

void batteryStatus(){
 batteryVoltageRaw = analogRead(VOLTAGE_PIN);
 batteryLevelInPercentage = map(batteryVoltageRaw, 550, 665, 0, 100);
 //Serial.println(batteryVoltageRaw);
 //Serial.println(batteryLevelInPercentage);
}
