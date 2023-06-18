#include <AccelStepper.h>
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
double stepsPerRevolution = 6400; // The steps per revolution of the motor, make sure the driver is set correctly
bool menu = false;

AccelStepper stepper(1,2,3);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// USER INPUT // 
int RPM = 20; // The revolutions per minute of the motor
const int holdTime = 500; // The time to wait between changing directions (ms)
// END USER INPUT //


void setup()
{  
  Serial.begin(9600);

  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  
  stepper.setMaxSpeed(stepsPerRevolution / 60 * RPM);
  stepper.setSpeed(stepsPerRevolution / 60 * RPM);
  stepper.setAcceleration(stepsPerRevolution / 60 * RPM);

  lcd.begin(16, 2);
  
}

void loop()
{  
  int buttonStateUp = digitalRead(A0);
  int buttonStateDown = digitalRead(A1);
  int buttonStateMenu = digitalRead(A2);

  if (buttonStateMenu == 0) {
    bool menu = true;
    lcd.clear();
    lcd.print("Setting RPM: ");
    lcd.print(RPM);
    delay(500);

    while (menu) {
      if (digitalRead(A0) == 0) {
        delay(200);
        RPM++;
        lcd.clear();
        lcd.print("Setting RPM: ");
        lcd.print(RPM);
        delay(500);
      }
      else if (digitalRead(A1) == 0) {
        delay(200);
        RPM--;
        lcd.clear();
        lcd.print("Setting RPM: ");
        lcd.print(RPM);
        delay(500);
      }
      if (digitalRead(A2) == 0) {
        delay(300);
        menu = false;
      } 
    }
  }

  if (RPM <= 1) {
    RPM = 1;
  }
  else if (RPM >= 60) {
    RPM = 60;
  }

  lcd.clear();
  lcd.print("RPM = ");
  lcd.print(RPM);
  lcd.setCursor(0, 1);
  lcd.print("Hold Time = ");
  lcd.print(holdTime);

  stepper.setMaxSpeed(stepsPerRevolution / 60 * RPM);
  stepper.setSpeed(stepsPerRevolution / 60 * RPM);
  stepper.setAcceleration(stepsPerRevolution / 60 * RPM);

  stepper.move(stepsPerRevolution);
  stepper.runToPosition();
  delay(holdTime);
  
  stepper.move(-stepsPerRevolution);
  stepper.runToPosition();
  delay(holdTime);
   
}
