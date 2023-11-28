#include <RTClib.h>
#include <Servo.h>
int angle;
Servo myServo;
RTC_DS3231 rtc;
boolean movement = false;
int ledPin = 4;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  myServo.attach(10);
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1)
      ;
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {

  DateTime now = rtc.now();
  Serial.print("Date & Time: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(now.dayOfTheWeek());
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);
  digitalWrite(4, 1);  
  sweep(1000);

  // if (now.hour() >= 8 && now.hour() <= 23 && now.minute() <= 0 && now.second() <= 0) {
  //   movement = true;
  //   digitalWrite(ledPin, 1);
  //   Serial.println("led on");
  // }
  // if (movement == true) {
  //   sweep(1000);
  //   // movement = false;
  //   Serial.println("move go");
  // } else if (movement == false) {
  //   digitalWrite(ledPin, 0);
  //   Serial.println("led off");
  // }
}

void sweep(int wait) {
  static unsigned long startTime = millis();
  unsigned long currentTime = millis();
  static int angle = 0;
  if (currentTime - startTime >= wait) {
    myServo.write(angle);
    angle = angle + 20;
    myServo.write(angle);
    delay(200);
    angle = angle - 10;
    myServo.write(angle);
    delay(200);
    //reset timer
    startTime = millis();
    if (angle >= 180) {
      angle = 0;
      myServo.write(angle);
      movement = false;
    }
  }
}