#include <AccelStepper.h>

  const int in1 = 13;
  const int in2 = 12;
  const int in3 = 11;
  int state=0;
  int scanCount=0;

// Define the stepper motor and the pins that is connected to
AccelStepper stepper1(1, 2, 3); // (Type of driver: with 2 pins, STEP, DIR)
AccelStepper stepper2(1, 4, 5); // (Type of driver: with 2 pins, STEP, DIR)


void setup() {

  
  Serial.begin(9600);
  //delay(5000);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);

  stepper1.setMaxSpeed(80); // Set maximum speed value for the stepper
  stepper1.setAcceleration(500); // Set acceleration value for the stepper
  stepper1.setCurrentPosition(0); // Set the current position to 0 steps
  stepper2.setMaxSpeed(80); // Set maximum speed value for the stepper
  stepper2.setAcceleration(500); // Set acceleration value for the stepper
  stepper2.setCurrentPosition(0); // Set the current position to 0 steps
}

void zLineScan(AccelStepper stepper, int amount){
  stepper.moveTo(amount); // Set desired move: 800 steps (in quater-step resolution that's one rotation)
  stepper.runToPosition(); // Moves the motor to target position w/ acceleration/ deceleration and it blocks until is in position
  delay(1);

  stepper.moveTo(0); // Set desired move: 800 steps (in quater-step resolution that's one rotation)
  stepper.runToPosition(); // Moves the motor to target position w/ acceleration/ deceleration and it blocks until is in position
  delay(1);
}

void loop() {

  if (state == 0){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(in3, 65);
  }

  if (state == 1){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(in3, 0);
  zLineScan(stepper1,+200);
  scanCount++;
  }

  if(scanCount>2){
    state=2;
  } 

  if (state == 2){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(in3, 0);   
  }

  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);

  if (sensorValue < 500){
    if (state==0){
      delay(1000);
      state=1;
    }
  }
}