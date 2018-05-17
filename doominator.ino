// Réglage des pin
#define trigPin 3
#define echoPin 2
#define buzzer 1
#define trigPin2 6
#define echoPin2 4
int motor_enablePin[] = {11, 10}; //pwm
int motor_in1Pin[] = {13, 8};
int motor_in2Pin[] = {12, 7};

// Config des yeux
int eye[][2] = {{0, 0},  {0, 0}};
const int eye_memory = 6;
int last_distance[][eye_memory] = {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};

// Config moteur
int motor_speed_min = 150;
int motor_speed_max = 250;
float motor_reg_1 = 0.72;
float motor_reg_2 = 1;
int motor_speed[] = {round(motor_speed_max / 2 * motor_reg_1), round(motor_speed_max / 2 * motor_reg_2)};
bool motor_rotate[] = {false, true};

int speed = 100;


// Function prototype (nécessaire de les définir pour les functions à argument optionnelle)
void setMotor(int id, int speed, bool reverse=false);


void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(buzzer, OUTPUT);
  
  //on initialise les pins du moteur 1
  pinMode(motor_in1Pin[0], OUTPUT);
  pinMode(motor_in2Pin[0], OUTPUT);
  pinMode(motor_enablePin[0], OUTPUT);
 
  //on initialise les pins du moteur 2
  pinMode(motor_in1Pin[1], OUTPUT);
  pinMode(motor_in2Pin[1], OUTPUT);
  pinMode(motor_enablePin[1], OUTPUT);
}

void loop() {
  long distance, distance2;
  bool wantGoAhead = true;
  bool wantTurnLeft = false;
  bool wantTurnRight = false;
  
  // Front Eye
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  eye[0][0] = pulseIn(echoPin, HIGH); // duration
  eye[0][1] = abs((eye[0][0] / 2) / 29.1); // distance cm

  // Side Eye
  digitalWrite(trigPin2, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  eye[1][0] = pulseIn(echoPin2, HIGH); // duration
  eye[1][1] = abs((eye[1][0] / 2) / 29.1); // distance cm

  distance = 0;
  distance2 = 0;
  
  for(int i = eye_memory - 1; i > 0; i--){
    last_distance[0][i] = last_distance[0][i - 1];
    last_distance[1][i] = last_distance[1][i - 1];
    distance += last_distance[0][i];
    distance2 += last_distance[1][i];
  }
  last_distance[0][0] = eye[0][1];
  last_distance[1][0] = eye[1][1];
  distance += eye[0][1];
  distance2 += eye[1][1];
  distance /= 6;
  distance2 /= 6;
  
  if (distance < 80 && distance > 20  && distance >= 0) { // Voix libre
    increaseSpeed();
  }
  else if (distance < 20){ // Obstacle devant
      wantGoAhead = false;
    if(distance2 < 20 && distance2 >= 0){ // Obstacle à coté
      wantTurnRight = true;
    }
    else{
      wantTurnLeft = true;
    }
  } 
  else if(distance2 < 10  && distance2 >= 0) {
    wantTurnRight = true;
  }
  else {
    speed = motor_speed_min;
  }

  if(wantGoAhead){
    goAhead(speed);
  }
  if(wantTurnLeft){
    turnLeft();
  }
  else if(wantTurnRight){
    turnRight();
  }
  
  Serial.print(eye[0][0]);
  Serial.println(" (brut)");
  Serial.print(eye[0][1]);
  Serial.println(" cm (front)"); 
  Serial.print(distance);
  Serial.println(" cm (front - moyenne)"); 
  
  Serial.print(eye[1][0]);
  Serial.println(" (brut)");
  Serial.print(eye[1][1]);
  Serial.println(" cm (side)"); 
  Serial.print(distance2);
  Serial.println(" cm (side - moyenne)"); 
  Serial.println("--------");
  
  delay(100);
}


void goAhead(int p_speed){ // Va de l'avant
  setMotor(0, p_speed);
  setMotor(1, p_speed);
}

void goBack(int p_speed){ // Marche arrière
  setMotor(0, p_speed, true);
  setMotor(1, p_speed, true);
}

void turnLeft(){
  SetMotor1(90, false);
  SetMotor2(130, false);
}

void turnRight(){
  SetMotor1(90, true);
  SetMotor2(130, true);
}

void increaseSpeed(){
  if(speed < motor_speed_max){
    speed += 25;
  }

  if(speed > motor_speed_max){
    speed = motor_speed_max;
  }
}

void setMotor(int id, int speed, bool reverse=false){
  analogWrite(motor_enablePin[id], speed);
  if(reverse){
    digitalWrite(motor_in1Pin[id], motor_rotate[id]);
    digitalWrite(motor_in2Pin[id], !motor_rotate[id]);
  }
  else{
    digitalWrite(motor_in1Pin[id], !motor_rotate[id]);
    digitalWrite(motor_in2Pin[id], motor_rotate[id]);
  }
}
void SetMotor1(int speed, boolean reverse)
{
  analogWrite(motor_in1Pin[0], speed);
  digitalWrite(motor_in1Pin[0], ! reverse);
  digitalWrite(motor_in2Pin[0], reverse);
}
 
//Fonction qui set le moteur2
void SetMotor2(int speed, boolean reverse)
{
  analogWrite(motor_enablePin[1], speed);
  digitalWrite(motor_in1Pin[1], ! reverse);
  digitalWrite(motor_in2Pin[1], reverse);
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
