/*Original Source Code By:  by Dejan Nedelkovski, www.HowToMechatronics.com
 * You can take inspiration from this website, like i did.
 Code Improvization & Contribution by: Ashley Alex Jacob (Pakistan)
 *Feel Free To use
 *Extended Features (LCD 16x2 i2c-> shows object count at runtime
 *Get more info at www.HowToMechatronics.com
 */ 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6
Servo topServo;
Servo bottomServo;
int frequency = 0;
int color=0;
int red=0,green=0,yellow=0,purple=0,blue=0;
void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  // Setting frequency-scaling to 100% (You can adjust it according to your needs
  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);
  topServo.attach(11);
  bottomServo.attach(12);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.print("Welcome to PCS");
}
void loop() {
 
  topServo.write(125);
  delay(500);
  
  for(int i = 125; i > 65; i--) {
    topServo.write(i);
    delay(2);
  }
  delay(500);
  
  color = readColor();
  delay(10);  
  switch (color) {
    case 1:
    lcd.print("Red Objects:");
    lcd.print(red);
    bottomServo.write(45);
    break;
    
    case 2:
    lcd.print("Green Objects:");
    lcd.print(green);
    bottomServo.write(90);
    break;
    
    case 3:
    lcd.print("Yellow Objects:");
    lcd.print(yellow);
    bottomServo.write(105);
    break;
    
    case 4:
    lcd.print("Purple Objects:");
    lcd.print(purple);
    bottomServo.write(135);
    break;

    case 5:
    lcd.print("Blue Objects:");
    lcd.print(blue);
    bottomServo.write(150);
    break;
    
    case 0:
    break;
  }
  delay(300);
  
  for(int i = 65; i > 29; i--) {
    topServo.write(i);
    delay(4);
  } 
  delay(200);
  
  for(int i = 29; i < 135; i++) {
    topServo.write(i);
    delay(2);
  }
  color=0;
}
// Custom Function - readColor()
int readColor() {
  // SetTing red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing GREEN color frequency
  Serial.print("  ");
  delay(50);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(50);
 if(R>25 & R<39 & G>40 & G<58 & B>30 &B<44){    ///This value should be change according to your reding please check serial monitor to know your reading.
    Serial.println("Red");
        color = 1; // Red
        red++;
  }

  else if(R>37 & R<48 & G>40 & G<52 & B>32 &B<42){
    Serial.println("Green");
    color = 2; // Green
    green++;
  }
   else if(R>19 & R<32 & G>30 & G<38 & B>30 &B<38){
    Serial.println("Yellow");
    color = 3; // Yellow
    yellow++;
  }

   else if(R>39 & R<46 & G>51 & G<58 & B>37 &B<43){
    Serial.println("Purple");
    color = 4; // Purple
    purple++;
  }
  else if(R>45 & R<52 & G>44 & G<51 & B>30 &B<37){
    Serial.println("Blue");
    color = 5; // Blue
    blue++;
  }
  
  lcd.clear();
  return color;  
}
