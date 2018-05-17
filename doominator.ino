//début
#define trigPin 3
#define echoPin 2
#define buzzer 1
#define trigPin2 6
#define echoPin2 4
int motor1_enablePin = 11; //pwm
int motor1_in1Pin = 13;
int motor1_in2Pin = 12;
 
int motor2_enablePin = 10; //pwm
int motor2_in1Pin = 8;
int motor2_in2Pin = 7;

int eye[][2] = {{0, 0},  {0, 0}};

int motor_speed_min = 10;
int motor_speed_max = 250;
float motor_reg_1 = 0.88;
float motor_reg_2 = 1;
int motor_speed[] = {round(motor_speed_max / 2 * motor_reg_1), round(motor_speed_max / 2 * motor_reg_2)};
bool motor_rotate[] = {false, true};


void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(buzzer, OUTPUT);
  //on initialise les pins du moteur 1
  pinMode(motor1_in1Pin, OUTPUT);
  pinMode(motor1_in2Pin, OUTPUT);
  pinMode(motor1_enablePin, OUTPUT);
 
  //on initialise les pins du moteur 2
  pinMode(motor2_in1Pin, OUTPUT);
  pinMode(motor2_in2Pin, OUTPUT);
  pinMode(motor2_enablePin, OUTPUT);
}

void loop() {
  long distance, distance2;
  // Front Eye
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  eye[0][0] = pulseIn(echoPin, HIGH); // duration
  eye[0][1] = (eye[0][0]/2) / 29.1; // distance

  // Side Eye
  digitalWrite(trigPin2, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  eye[1][0] = pulseIn(echoPin2, HIGH); // duration
  eye[1][1] = (eye[1][0]/2) / 29.1; // distance

  distance = eye[0][1];
  distance2 = eye[1][1];

  if (distance < 80 && distance > 45) { // Voix libre
    SetMotor1(90, false);
    SetMotor2(130, true);
  }
  else if (distance < 45){ // Obstacle devant
    if(distance2 < 45){ // Obstacle à coté
      SetMotor1(90, false);
      SetMotor2(130, false);
    }
    else{
      SetMotor1(90, true);
      SetMotor2(130, true);
    }
  } 
  else if(distance2 < 10) {
    SetMotor1(90, false);
    SetMotor2(130, false);
  }
  else {
    SetMotor1(motor_speed[0], false);
    SetMotor2(motor_speed[1], true);
//    playDoom();
  }

  Serial.print(eye[0][0]);
  Serial.println(" (brut)");
  Serial.print(eye[0][1]);
  Serial.println(" cm (front)"); 

  Serial.print(eye[1][0]);
  Serial.println(" (brut)");
  Serial.print(eye[1][1]);
  Serial.println(" cm (side)"); 
  Serial.println("--------");
  
  delay(500);
}

void SetMotor1(int speed, boolean reverse)
{
  analogWrite(motor1_enablePin, speed);
  digitalWrite(motor1_in1Pin, ! reverse);
  digitalWrite(motor1_in2Pin, reverse);
}
 
//Fonction qui set le moteur2
void SetMotor2(int speed, boolean reverse)
{
  analogWrite(motor2_enablePin, speed);
  digitalWrite(motor2_in1Pin, ! reverse);
  digitalWrite(motor2_in2Pin, reverse);
}


void playDoom(){
  int counter = 0;
    while (counter != 3)
    {
      tone(4,E4,E);
      delay(1+Q);
      tone(4,D4,E);
      delay(1+Q);
      tone(4,C4,E);
      delay(1+Q);
      tone(4,Bb3,E);
      delay(1+Q);
      tone(4,B3,E);
      delay(1+S);
      tone(4,C4,E);
      delay(1+Q);
      tone(4,E4,E);
      delay(1+Q);
      tone(4,D4,E);
      delay(1+Q);
      tone(4,C4,E);
      delay(1+Q);
      tone(4,Bb3,H);
      delay(1+3*Q);
      counter++;
    }  
}
