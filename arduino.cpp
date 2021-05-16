#include <Arduino.h>
#include <ESP32Servo.h>

Servo servoX;
Servo servoY;

int servoPinX = 26;
int servoPinY = 27;
int Xval = 0;
int Yval = 0;

String getValue(String data, char separator, int index) //idk what some of function is even doing i copied it from stack overflow and its working xD
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void ServoWrite(int X, int Y)
{
  servoX.write(X);
  servoY.write(Y);
}

void setup() {
  Serial.begin(115200);

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  servoX.setPeriodHertz(50);
  servoY.setPeriodHertz(50);
  servoY.attach(servoPinY, 500, 2250);
  servoX.attach(servoPinX, 500, 2250);
  servoX.write(0);
  servoY.write(0);
  
  Serial.setTimeout(10);
  
  //Serial.print("waiting");
}

void loop() {

  if(Serial.available() > 0)
  {
    //Serial.println("GOT DATA");
    String SerialRec = Serial.readString();
    //Serial.println(SerialRec);
    String Xval = getValue(SerialRec, ':', 0);
    String Yval = getValue(SerialRec, ':', 1);
    int Xvalue = Xval.toInt();
    int Yvalue = Yval.toInt();
    delay(1);
    //Serial.println("X: " + Xval + " Y: " + Yval);
    ServoWrite(Xvalue, Yvalue);
    delay(1);
  }
}
