

#define SERIAL_USB_BAUDRATE   115200
#define PIN_QUALITY_INDICATOR 13
#define LED_PWM_PIN 7
#define LED_PWM_PIN1 11
#include <Servo.h>
#include <mindwaveTools.h>

Servo servo1;
Servo servo2;

MindwaveHeadset headset( Serial1 );

void setup() {
  servo1.attach(8);
  servo2.attach(9);
  Serial.begin(SERIAL_USB_BAUDRATE);       
  Serial1.begin(HEADSET_BAUDRATE);          
  pinMode(PIN_QUALITY_INDICATOR, OUTPUT);
  pinMode(LED_PWM_PIN, OUTPUT);
  pinMode(LED_PWM_PIN1, OUTPUT);
  headset.setOutputQualityPin( PIN_QUALITY_INDICATOR );
}


void loop() {
  headset.readHeadset();
  Serial.print(":");
  Serial.print(headset.getQuality());
  Serial.print(",");
  Serial.print("Att:");
  Serial.print(headset.getAttention());
  analogWrite(LED_PWM_PIN, headset.getAttention());
  Serial.print(",");
  Serial.print("Med:");
  Serial.print(headset.getMeditation());
  analogWrite(LED_PWM_PIN1, headset.getMeditation());
  Serial.print(",");
  Serial.print(headset.getRaw());
  Serial.print("\n");


  analogWrite(LED_PWM_PIN, map(headset.getAttention(), 0, 100, 0, 255));
  analogWrite(LED_PWM_PIN1, map(headset.getMeditation(), 0, 100, 0, 255));


  int servoAngle = map(headset.getMeditation(), 0, 100, 0, 180);
  servo1.write(servoAngle);
  servo2.write(servoAngle);




  
}
