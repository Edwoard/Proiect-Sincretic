#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int TEMP_PIN = A0;
void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);

  lcd.setCursor(0,1);

}

void loop()
{
  
  float raw_val = ((analogRead(TEMP_PIN)*5.0)/1023)*1000;
  float val = (raw_val - 500)/10.0;
  
  Serial.print("val=");
  Serial.println(val);

  Serial.print("raw=");
  Serial.println(raw_val);
  lcd.setCursor(0,0);
  lcd.print("temp= ");
  lcd.print(val);
  delay(1000); // Wait for 1000 millisecond(s)

}