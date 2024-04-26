void checkLaserModule(){
if(LASER_COUNT != 0){
  delay(100);
   if(LASER1_LABEL && LASER2_LABEL && PERVIOUS_LASER_COUNT != LASER_COUNT)
   {
      digitalWrite(LASER_PIN2, LOW);
      digitalWrite(LASER_PIN1, LOW);
      LASER2_LABEL = LOW;
      LASER1_LABEL = LOW;
      LASER_COUNT = 0;
   }
   else if(PERVIOUS_LASER_COUNT != LASER_COUNT && LASER1_LABEL == HIGH)
   {
      digitalWrite(LASER_PIN2, HIGH);
      LASER2_LABEL = HIGH;
      PERVIOUS_LASER_COUNT = LASER_COUNT;
   }
   else
   {
      digitalWrite(LASER_PIN1, HIGH);
      LASER1_LABEL = HIGH;
      PERVIOUS_LASER_COUNT = LASER_COUNT;
   }
 }
}
