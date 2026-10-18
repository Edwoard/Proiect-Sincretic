#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int TEMP_PIN = A0;

int seconds = 0;
int minutes = 0;
int hours = 18;

unsigned long previousMillis = 0;
const unsigned long interval = 1000;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);

  lcd.setCursor(0,1);

}

void show_time(){
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    seconds++;

    if (seconds >= 60) {
      seconds = 0;
      minutes++;
    }

    if (minutes >= 60) {
      minutes = 0;
      hours++;
    }

    if (hours >= 24) {
      hours = 0;
    }

    lcd.setCursor(0, 1);

    if (hours < 10) lcd.print("0");
    lcd.print(hours);
    lcd.print(":");

    if (minutes < 10) lcd.print("0");
    lcd.print(minutes);
    lcd.print(":");

    if (seconds < 10) lcd.print("0");
    lcd.print(seconds);

  }
}


void loop()
{
  
  float raw_val = ((analogRead(TEMP_PIN)*5.0)/1023)*1000;
  float val = (raw_val - 500)/10.0;
  show_time();
    
  Serial.print("val=");
  Serial.println(val);

  Serial.print("raw=");
  Serial.println(raw_val);
  lcd.setCursor(0,0);
  lcd.print("temp ");
  lcd.print(val);
  delay(1000); // Wait for 1000 millisecond(s)

}