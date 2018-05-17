//#define  C0 16.35
//#define Db0 17.32
//#define D0  18.35
//#define Eb0 19.45
//#define E0  20.60
//#define F0  21.83
//#define Gb0 23.12
//#define G0  24.50
//#define Ab0 25.96
//#define LA0 27.50
//#define Bb0 29.14
//#define B0  30.87
//#define C1  32.70
//#define Db1 34.65
//#define D1  36.71
//#define Eb1 38.89
//#define E1  41.20
//#define F1  43.65
//#define Gb1 46.25
//#define G1  49.00
//#define Ab1 51.91
//#define LA1 55.00
//#define Bb1 58.27
//#define B1  61.74
//#define C2  65.41
//#define Db2 69.30
//#define D2  73.42
//#define Eb2 77.78
//#define E2  82.41
//#define F2  87.31
//#define Gb2 92.50
//#define G2  98.00
//#define Ab2 103.83
//#define LA2 110.00
//#define Bb2 116.54
//#define B2  123.47
//#define C3  130.81
//#define Db3 138.59
//#define D3  146.83
//#define Eb3 155.56
//#define E3  164.81
//#define F3  174.61
//#define Gb3 185.00
//#define G3  196.00
//#define Ab3 207.65
//#define LA3 220.00
//#define Bb3 233.08
//#define B3  246.94
//#define C4  261.63
//#define Db4 277.18
//#define D4  293.66
//#define Eb4 311.13
//#define E4  329.63
//#define F4  349.23
//#define Gb4 369.99
//#define G4  392.00
//#define Ab4 415.30
//#define LA4 440.00
//#define Bb4 466.16
//#define B4  493.88
//#define C5  523.25
//#define Db5 554.37
//#define D5  587.33
//#define Eb5 622.25
//#define E5  659.26
//#define F5  698.46
//#define Gb5 739.99
//#define G5  783.99
//#define Ab5 830.61
//#define LA5 880.00
//#define Bb5 932.33
//#define B5  987.77
//#define C6  1046.50
//#define Db6 1108.73
//#define D6  1174.66
//#define Eb6 1244.51
//#define E6  1318.51
//#define F6  1396.91
//#define Gb6 1479.98
//#define G6  1567.98
//#define Ab6 1661.22
//#define LA6 1760.00
//#define Bb6 1864.66
//#define B6  1975.53
//#define C7  2093.00
//#define Db7 2217.46
//#define D7  2349.32
//#define Eb7 2489.02
//#define E7  2637.02
//#define F7  2793.83
//#define Gb7 2959.96
//#define G7  3135.96
//#define Ab7 3322.44
//#define LA7 3520.01
//#define Bb7 3729.31
//#define B7  3951.07
//#define C8  4186.01
//#define Db8 4434.92
//#define D8  4698.64
//#define Eb8 4978.03
//// DURATION OF THE NOTES 
//#define BPM 120    //  you can change this value changing all the others
//#define H 2*Q //half 2/4
//#define Q 60000/BPM //quarter 1/4 
//#define E Q/2   //eighth 1/8
//#define S Q/4 // sixteenth 1/16
//#define W 4*Q // whole 4/4
//début
#define trigPin 3
#define echoPin 2
#define buzzer 4
#define trigPin2 6
#define echoPin2 1
int motor1_enablePin = 11; //pwm
int motor1_in1Pin = 13;
int motor1_in2Pin = 12;
 
int motor2_enablePin = 10; //pwm
int motor2_in1Pin = 8;
int motor2_in2Pin = 7;




void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
//  pinMode(trigPin2, OUTPUT);
//  pinMode(echoPin2, INPUT);
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
  long duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
 long duration2, distance2;
  digitalWrite(trigPin2, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2/2) / 29.1;

  if (distance < 80 && distance > 45) {
    SetMotor2(130, true);
    Serial.print(distance);
    Serial.print(distance2);
    Serial.println(" cm");
    SetMotor1(90, false);
   
}
else if (distance < 45 && distance2 < 45) {
   SetMotor2(130, false);
    SetMotor1(90, false);
}
else if (distance < 45) {
    SetMotor2(130, true);
    SetMotor1(90, true);
}
  else {
    SetMotor2(250, true);
    SetMotor1(200, false);
//    int counter = 0;
//    while (counter != 3)
//    {
//      tone(4,E4,E);
//      delay(1+Q);
//      tone(4,D4,E);
//      delay(1+Q);
//      tone(4,C4,E);
//      delay(1+Q);
//      tone(4,Bb3,E);
//      delay(1+Q);
//      tone(4,B3,E);
//      delay(1+S);
//      tone(4,C4,E);
//      delay(1+Q);
//      tone(4,E4,E);
//      delay(1+Q);
//      tone(4,D4,E);
//      delay(1+Q);
//      tone(4,C4,E);
//      delay(1+Q);
//      tone(4,Bb3,H);
//      delay(1+3*Q);
//      counter++;
//       
//    }
  }

 
 
    
   
  
 
    Serial.print(distance);
//    Serial.print(distance2);
    Serial.println(" cm");
   
   
  
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
