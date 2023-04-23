const int trigPin = 9;
const int echoPin = 10;
const int trigPin2 = 11;
const int echoPin2 = 12;
const int trigPin3 = 2;
const int echoPin3 = 3;
// defines variables
long duration;
int distance;
double mass;
long duration2;
int distance2;
double mass2;
long duration3;
int distance3;

//Includes the Arduino Stepper Library
#include <Stepper.h>

// Defines the number of steps per rotation
const int stepsPerRevolution = 2038;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 4, 5, 6, 7);

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin3, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin3, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
  // Serial.println("test");
}

void verify(){
  distance = readUltrasonic(trigPin, echoPin);
  Serial.print("Distance: + ");
  Serial.println(distance);

  distance2 = readUltrasonic(trigPin2, echoPin2);
  Serial.print("Distance2: + ");
  Serial.println(distance2);

  distance3 = readUltrasonic(trigPin3, echoPin3);
  Serial.print("Distance3: + ");
  Serial.println(distance3);

  myStepper.setSpeed(10);
  myStepper.step(stepsPerRevolution/4-20);
  delay(1000);

}

void loop2(){
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = duration3 * 0.034 / 2;

  // distance3 = readUltrasonic(trigPin3, echoPin3);
  Serial.print("DISTANCE 3: ");
  Serial.println(distance3);
  delay(500);
  
  myStepper.setSpeed(10);
  myStepper.step(stepsPerRevolution/4-20);
  delay(1000);
  
}

void loop() {

  // digitalWrite(trigPin3, LOW);
  // delayMicroseconds(2);
  // digitalWrite(trigPin3, HIGH);
  // delayMicroseconds(10);
  // digitalWrite(trigPin3, LOW);
  // duration3 = pulseIn(echoPin3, HIGH);
  // distance3 = duration3 * 0.034 / 2;

  distance3 = readUltrasonic(trigPin3, echoPin3);
  // distance3 = 1;
  // Serial.print("DISTANCE 3: ");
  // Serial.println(distance3);

  if (distance3 < 20 || distance3 > 60){
    Serial.println("t");
    // Serial.println(Serial.available());
    while (Serial.read()>0){
      Serial.flush();
    }
    while (!(Serial.available() > 0)){
      delay(500);
    }
    int mode = Serial.readString().toInt();
    // Serial.print("INPUT READ: ");
    // Serial.println(mode);
    if (mode == 0){
      // Serial.println("Processing Garbage");
      myStepper.setSpeed(10);
      myStepper.step(-stepsPerRevolution/4+20);
      delay(1000);
      
      // Rotate CCW quickly at 10 RPM
      myStepper.setSpeed(10);
      myStepper.step(stepsPerRevolution/4-20);
      delay(3000);

      distance = readUltrasonic(trigPin, echoPin);
      distance2 = readUltrasonic(trigPin2, echoPin2);
      mass = 117.0633944 * (0.22 - distance * 0.01) / 9.81;
      mass2 = 122.6375916 * (0.25 - distance2 * 0.01) / 9.81;
      Serial.print("w");
      Serial.print(mass);
      Serial.print(" ");
      Serial.println(mass2);

      while (!(Serial.available() > 0)){
        delay(500);
      }
      while (Serial.read()>0){
        Serial.flush();
      }

    } else if (mode == 1){
      myStepper.setSpeed(10);
      myStepper.step(stepsPerRevolution/4-20);
      delay(1000);
      
      // Rotate CCW quickly at 10 RPM
      myStepper.setSpeed(10);
      myStepper.step(-stepsPerRevolution/4+20);
      delay(3000);

      distance = readUltrasonic(trigPin, echoPin);
      distance2 = readUltrasonic(trigPin2, echoPin2);
      mass = 117.0633944 * (0.22 - distance * 0.01) / 9.81;
      mass2 = 122.6375916 * (0.25 - distance2 * 0.01) / 9.81;
      Serial.print("w");
      Serial.print(mass);
      Serial.print(" ");
      Serial.println(mass2);

      while (!(Serial.available() > 0)){
        delay(500);
      }
      while (Serial.read()>0){
        Serial.flush();
      }
      // Serial.println("New round");

    } else {
      Serial.println("An error occured");
    }
  }
  delay(100);

  // digitalWrite(trigPin, LOW);
  // delayMicroseconds(2);
  // digitalWrite(trigPin, HIGH);
  // delayMicroseconds(10);
  // digitalWrite(trigPin, LOW);
  // duration = pulseIn(echoPin, HIGH);

  // digitalWrite(trigPin2, LOW);
  // delayMicroseconds(2);
  // digitalWrite(trigPin2, HIGH);
  // delayMicroseconds(10);
  // digitalWrite(trigPin2, LOW);
  // duration2 = pulseIn(echoPin2, HIGH);
  
  // Calculating the distance
  // distance = duration * 0.034 / 2;
  // distance2 = duration2 * 0.034 / 2;

  // F = kx
  // mg = kx
  // m = kx / g
  // k = 117.0633944
  // mass = 117.0633944 * (0.22 - distance * 0.01) / 9.81;
  // mass2 = 122.6375916 * (0.25 - distance2 * 0.01) / 9.81;

  // Prints the distance on the Serial Monitor
  // Serial.print("Distance: ");
  // Serial.print(distance);
  // Serial.print(" Mass: ");
  // Serial.print(mass);
  // Serial.print(" Distance2: ");
  // Serial.print(distance2);
  // Serial.print(" Mass2: ");
  // Serial.println(mass2);
  // delay(200);

  
}

int readUltrasonic(int trig, int echo){
  int vals[5] = {0, 0, 0, 0, 0};
  for (int i = 0; i < 5; i++){
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    vals[i] = pulseIn(echo, HIGH) * 0.034 / 2;
  }
  // Serial.println("Done collecing data");
  // Serial.println(sizeof(vals));
  for (int i = 0; i < 5; i++){
    int max = vals[i];
    int maxI = 0;
    for (int j = i; j < 5; j++){
      // Serial.println("Iteration");
      if (max < vals[j]){
        max = vals[j];
        maxI = j;
      }
    }
    int placeholder = vals[i];
    vals[i] = max;
    vals[maxI] = placeholder;
  }
  // Serial.println("Done!!");
  return vals[2];
}
