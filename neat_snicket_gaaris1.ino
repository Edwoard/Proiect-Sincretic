#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define BUTTON_OK 6
#define BUTTON_CANCEL 7
#define BUTTON_PREV 8
#define BUTTON_NEXT 9

int TEMP_PIN = A0;
double targetTemp =30;

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

  pinMode(BUTTON_OK, INPUT);
  digitalWrite(BUTTON_OK, LOW); // pull-down
  
  pinMode(BUTTON_CANCEL, INPUT);
  digitalWrite(BUTTON_CANCEL, LOW); // pull-down
  
  pinMode(BUTTON_PREV, INPUT);
  digitalWrite(BUTTON_PREV, LOW); // pull-down
  
  pinMode(BUTTON_NEXT, INPUT);
  digitalWrite(BUTTON_NEXT, LOW); // pull-down

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

enum Buttons {
  EV_OK,
  EV_CANCEL,
  EV_NEXT,
  EV_PREV,
  EV_NONE,
  EV_MAX_NUM
};
enum Buttons getButtons();
enum Buttons getButtons(){
  if(digitalRead(BUTTON_OK)){
    return EV_OK;
  }
  if(digitalRead(BUTTON_CANCEL)){
    return EV_CANCEL;
  }
    if(digitalRead(BUTTON_NEXT)){
    return EV_NEXT;
  }
    if(digitalRead(BUTTON_PREV)){
    return EV_PREV;
  }
  return EV_NONE;
}

enum Menus {
  MENU_MAIN = 0,
  MENU_TEMP,
  MENU_MAX_NUM
};

enum Menus displayScreen = MENU_MAIN;
void printScreen(enum Menus menu);
void printScreen(enum Menus menu){
  lcd.clear();
  switch(menu){
    case MENU_MAIN :
      lcd.print("Current temp:");
    	lcd.setCursor(0,1);
      lcd.print(targetTemp);
      break;
    case MENU_TEMP :
      lcd.print("Set temp:");
        	lcd.setCursor(0,1);
      lcd.print(targetTemp);

      break;
    case MENU_MAX_NUM:
      lcd.print("System error");
    break;
  }
}

enum Menus activeMenu = MENU_MAIN;

void enterMenu(){
  activeMenu = displayScreen;
}
void nextMenu(){
  displayScreen = (Menus)(((int)displayScreen + 1) % MENU_MAX_NUM);
}
void prevMenu(){
  displayScreen = (Menus)(((int)displayScreen - 1 + MENU_MAX_NUM) % MENU_MAX_NUM);  
}
void homeMenu(){
  displayScreen = MENU_MAIN;
  activeMenu = MENU_MAIN;

}
void increaseTemp(){
  if(targetTemp >= 50){
    return;
  }
  targetTemp = targetTemp + 0.5;
}
void decreaseTemp(){
  if(targetTemp <= 0){
    return;
  }
  targetTemp = targetTemp - 0.5;
}

typedef void action();
action* menuHandlers[MENU_MAX_NUM][EV_MAX_NUM] = {
  {enterMenu, homeMenu, nextMenu, prevMenu},
  {homeMenu, homeMenu, increaseTemp, decreaseTemp},
};

void handleAction(enum Buttons event);
void handleAction(enum Buttons event){
  menuHandlers[activeMenu][event]();
}

void loop()
{
  
  // float raw_val = ((analogRead(TEMP_PIN)*5.0)/1023)*1000;
  // float val = (raw_val - 500)/10.0;
  // show_time();
    
  // Serial.print("val=");
  // Serial.println(val);

  // Serial.print("raw=");
  // Serial.println(raw_val);
  // lcd.setCursor(0,0);
  // lcd.print("temp ");
  // lcd.print(val);
  enum Buttons event = getButtons();
  if(event != EV_NONE){
    
    handleAction(event);
    Serial.println(displayScreen);

  }
  printScreen(displayScreen);

  delay(500); // Wait for 1000 millisecond(s)

}