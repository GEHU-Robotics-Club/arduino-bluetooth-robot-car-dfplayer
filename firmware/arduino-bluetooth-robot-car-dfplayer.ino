#include <SoftwareSerial.h> 
 
SoftwareSerial BT(2, 3); // RX, TX 
 
// Motor pins 
#define ENA 5 
#define ENB 6 
#define IN1 7 
#define IN2 8 
#define IN3 9 
#define IN4 10 
 
int speedCar = 150;  // default speed 
 
void setup() { 
  pinMode(ENA, OUTPUT); 
  pinMode(ENB, OUTPUT); 
 
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT); 
 
  stopCar(); 
  BT.begin(9600); 
} 
 
void loop() { 
  if (BT.available()) { 
    char cmd = BT.read(); 
 
    // Speed control 
    if (cmd >= '0' && cmd <= '9') { 
      speedCar = map(cmd - '0', 0, 9, 0, 255); 
    } 
    else if (cmd == 'q') { 
      speedCar = 255; 
    } 
 
    switch (cmd) { 
      case 'F': forward(); break; 
      case 'B': backward(); break; 
      case 'L': left(); break; 
      case 'R': right(); break; 

      case 'G': forwardLeft(); break; 
      case 'I': forwardRight(); break; 
      case 'H': backLeft(); break; 
      case 'J': backRight(); break; 
      case 'S': stopCar(); break; 
      case 'D': stopCar(); break; 
    } 
  } 
} 
 
// ================= MOTOR FUNCTIONS ================= 
 
void forward() { 
  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW); 
  setSpeed(); 
} 
 
void backward() { 
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, HIGH); 
  setSpeed(); 
} 
 
// ✅ LEFT–RIGHT FIXED 
void left() { 
  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, HIGH); 
  setSpeed(); 
} 
 
void right() { 
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW); 
  setSpeed(); 
} 
 
void forwardLeft() { 
  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW); 

  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW); 
  analogWrite(ENA, speedCar / 2); 
  analogWrite(ENB, speedCar); 
} 
 
void forwardRight() { 
  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW); 
  analogWrite(ENA, speedCar); 
  analogWrite(ENB, speedCar / 2); 
} 
 
void backLeft() { 
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, HIGH); 
  analogWrite(ENA, speedCar / 2); 
  analogWrite(ENB, speedCar); 
} 
 
void backRight() { 
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, HIGH); 
  analogWrite(ENA, speedCar); 
  analogWrite(ENB, speedCar / 2); 
} 
 
void stopCar() { 
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, LOW); 
  analogWrite(ENA, 0); 
  analogWrite(ENB, 0); 
} 
 
void setSpeed() { 
  analogWrite(ENA, speedCar); 
  analogWrite(ENB, speedCar); 
}