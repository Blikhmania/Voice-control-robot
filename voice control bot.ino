#include <AFMotor.h>
#include <Servo.h>
String voice;
int pos;
AF_DCMotor motor1 (1, MOTOR12_1KHZ);
AF_DCMotor motor2 (2, MOTOR12_1KHZ);
AF_DCMotor motor3 (3, MOTOR12_1KHZ);
AF_DCMotor motor4 (4, MOTOR12_1KHZ);
Servo elbowservo;
Servo gripperservo;
void setup()
{
  Serial.begin(9600);
  elbowservo.attach(10);
  elbowservo.write(75);
  gripperservo.attach(11);
  gripperservo.write(75);
}
void forward_car()
{
  motor1.run(FORWARD);
  motor1.setSpeed(350);
  motor2.run(FORWARD);
  motor2.setSpeed(350);
  motor3.run(FORWARD);
  motor3.setSpeed(700);
  motor4.run(FORWARD);
  motor4.setSpeed(700);
}
void backward_car()
{
  motor1.run(BACKWARD);
  motor1.setSpeed(350);
  motor2.run(BACKWARD);
  motor2.setSpeed(350);
  motor3.run(BACKWARD);
  motor3.setSpeed(700);
  motor4.run(BACKWARD);
  motor4.setSpeed(700);
}
void right_car()
{
  motor1.run(FORWARD);
  motor1.setSpeed(95);
  motor2.run(FORWARD);
  motor2.setSpeed(95);
  motor3.run(BACKWARD);
  motor3.setSpeed(190);
  motor4.run(BACKWARD);
  motor4.setSpeed(190);
}
void left_car()
{
  motor1.run(BACKWARD);
  motor1.setSpeed(95);
  motor2.run(BACKWARD);
  motor2.setSpeed(95);
  motor3.run(FORWARD);
  motor3.setSpeed(190);
  motor4.run(FORWARD);
  motor4.setSpeed(190);
}
void stop_car()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
void loop()
{
  while (Serial.available())
  {
    String c = Serial.readString();
    if (c == '#')
    {
      break;
    }
    voice += c;
  }
  if (voice.length() > 0)
  {
    if (voice == "go ahead")
    {
      Serial.println("forward");
      forward_car(); 
    }
    else if (voice == "go back")
    {
      Serial.println("back");
      backward_car();  
    }
    else if (voice == "turn left")
    {
      while (voice == "turn left")
      {
        Serial.println("left");
        left_car();
        while (Serial.available())
        {
          String c = Serial.readString();
          if (c == '#')
          {
            break;
          }
          voice += c;
        }
      }
    }
    else if (voice == "turn right")
    {
      while (voice == "turn right")
      {
        Serial.println("right");
        right_car();
        while (Serial.available())
        {
          String c = Serial.readString();
          if (c == '#')
          {
            break;
          }
          voice += c;
        }
      }
    }
    else if (voice == "stop")
    {
      Serial.println("stop");
      stop_car();
    }
    else if (voice == "take up")
    { voice="";
      Serial.println("picking");
      for (pos = 80; pos >= 0; pos -= 1)
      { Serial.println("down");
        
        elbowservo.write(pos);
        delay(1000);
        while (Serial.available())
        {
          String c = Serial.readString();
          if (c == '#')
          {
            break;
          }
          voice += c;
        }
        if (voice == "stop hand")
        {
          Serial.println("arm stopped");
          break;
        }
      }
      int p = pos;
      gripperservo.write(0);
      elbowservo.write(90);
    }
    else if (voice == "drop")
    { voice="";
      Serial.println("dropping");
      for(pos=80;pos>=0;pos-=1)
      { 
       Serial.println("down");
       elbowservo.write(pos);
       delay(1000);
       while (Serial.available())
        {
          String c = Serial.readString();
          if (c == '#')
          {
            break;
          }
          voice += c;
        }
         if(voice=="place")
       {
        Serial.println("placed");
        break;
       }
      }  
      gripperservo.write(90);
      elbowservo.write(90);
    }
  }
 voice = "";
}
