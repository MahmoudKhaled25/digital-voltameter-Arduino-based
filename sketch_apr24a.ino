#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//define I2C address......
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display


const int analogInputVoltage = A1;
const int analogInputResistance = A2;
const int dipSwitch = 4; 
int switchState = 0;
int analogValue = 0;
float voltage = 0;  // voltage to be measured
float Res = 0; // resistance to be measured
float resolution = 1023.0;
const float R1 = 100000.0; // 100 kΩ
const float R2 = 10000.0; // 10 kΩ
const float Rref = 10000.0; // reference resistance of 1 kΩ

void setup() {
  pinMode(analogInputVoltage, INPUT);
  pinMode(analogInputResistance, INPUT);
  pinMode(dipSwitch, INPUT);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
}

void loop() {
   switchState = digitalRead(dipSwitch);
  lcd.setCursor(0, 0);
  
  if(switchState == HIGH)
  {
    lcd.clear();
    lcd.print("DC Voltage: ");
  	analogValue = analogRead(analogInputVoltage);
    voltage = (analogValue * 5.0) / resolution;
    voltage = voltage * ((R1 + R2) / R2);
  
    lcd.setCursor(0, 1);
    lcd.print(voltage);
    lcd.print(" V   ");
  } else 
  {
    lcd.clear();
    lcd.print("Resistance: ");
    analogValue = analogRead(analogInputResistance);
    voltage = (analogValue * 5.0) / resolution;
    Res = Rref * ((5.0 - voltage) / voltage);
    Res = (Res) / 1000.0; // convert to kilo-ohms
    
    lcd.setCursor(0, 1);
    lcd.print(Res);
    lcd.print(" Kohm");
  }
  
  delay(2000);
}
