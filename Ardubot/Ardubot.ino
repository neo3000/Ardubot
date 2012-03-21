#include <QTRSensors.h>

int NUM_SENSORS = 6;
int MotorDirRight = 12;
int MotorDirLeft = 13;
int PwmRight = 3; 
int PwmLeft = 11;
int ProgrammerCable = 4;
int Wert;
int SpeedMax = 40;
int StatusLED = 2;

QTRSensorsRC qtr((unsigned char[]) {5, 6, 7, 8, 9, 10}, NUM_SENSORS); 

void setup()
{
  pinMode(PwmRight, OUTPUT);  pinMode(MotorDirRight, OUTPUT);
  pinMode(PwmLeft, OUTPUT); pinMode(MotorDirLeft, OUTPUT);
  analogWrite(PwmRight, 0);  digitalWrite(MotorDirRight, HIGH);
  analogWrite(PwmLeft, 0);  digitalWrite(MotorDirLeft, HIGH);
  pinMode(StatusLED, OUTPUT);
  pinMode(ProgrammerCable, INPUT);
  pinMode(1, OUTPUT);
  digitalWrite(1, HIGH);
  delay(500);
  digitalWrite(StatusLED, HIGH);
  for (int i = 0; i < 250; i++){
  qtr.calibrate();
  }   
  Status_Blink(100, 5);  delay(400);
}

void loop()
{
  int ProgrammerState = digitalRead(ProgrammerCable);
  if(ProgrammerState == HIGH){
     Status_Blink(40, 5);
     analogWrite(PwmLeft, 0);
     analogWrite(PwmRight, 0);
  }else{
  unsigned int Sensors[NUM_SENSORS];
  unsigned int SensorValue = qtr.readLine(Sensors);
  
  Wert = SensorValue / NUM_SENSORS;
  
  if(Wert < 250){Turn_Half_Right();}
  if(Wert > 300 && Wert < 500){Run_Forward();}
  if(Wert > 550){Turn_Half_Left();}

  delay(10);
  }
}
  void Turn_Half_Right(){
    delay(2);
    analogWrite(PwmLeft, 0);
    analogWrite(PwmRight, 0);
    digitalWrite(MotorDirLeft, HIGH);
    digitalWrite(MotorDirRight, LOW);
    analogWrite(PwmLeft, SpeedMax - 10);
    analogWrite(PwmRight, SpeedMax - 10);
  }
  
  void Turn_Half_Left(){
    delay(2);
    analogWrite(PwmLeft, 0);
    analogWrite(PwmRight, 0);
    digitalWrite(MotorDirRight, HIGH);
    digitalWrite(MotorDirLeft, LOW);    
    analogWrite(PwmLeft, SpeedMax - 10);
    analogWrite(PwmRight, SpeedMax - 10);
  }
  
  void Run_Forward(){
    delay(2);
    analogWrite(PwmRight, 0);
    analogWrite(PwmLeft, 0);
    digitalWrite(MotorDirRight, HIGH);
    digitalWrite(MotorDirLeft, HIGH);
    analogWrite(PwmRight, SpeedMax + 5);
    analogWrite(PwmLeft, SpeedMax + 5);
  }    
    
  void Status_Blink(int Time, int Numbers){
    digitalWrite(StatusLED, HIGH);
    for(int i = 0; i < Numbers; i++){
      if (digitalRead(StatusLED) == LOW){
        digitalWrite(StatusLED, HIGH);
        }else{
        digitalWrite(StatusLED, LOW);}
      delay(Time);
    }
    digitalWrite(StatusLED, LOW);
  }

