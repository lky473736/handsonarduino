#include <LiquidCrystal.h>
#include <Wire.h>
#include <Servo.h>
#include <LedControl.h>

LedControl dot = LedControl(A2, A3); // Dot matrix 핀번호 입력
// 작동이 이상하다 - 디지털 핀에 연결

byte triangle[]={
  B00000000,
  B00000000,
  B11111111,
  B11111111,
  B01111110,
  B00111100,
  B00000000,
  B00000000
};

byte stick[]={
  B00000000,
  B00000000,
  B00000000,
  B11111111,
  B11111111,
  B00000000,
  B00000000,
  B00000000,
};

int trig = 3;
int echo = 2;

Servo servo1;
Servo servo2; 
Servo servo3; 
Servo servo4; 

int red = 8;
int green = 9;

int sda_d = A2; // dot matrix
int scl_d = A3; // dot matrix

LiquidCrystal lcd(A4, A5); // 디지털 핀으로 고쳐야 할 수도 있음

long duration;
int distance;
int i;

void notattention1(int time);
void notattention2(int time);
void choumpa();
int ac_calculator(int a, int b, char op);
int fa_calculator();

void dotmatrix_tri();
void dotmatrix_sti();

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  servo1.attach(4);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(7);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);

  dot.shutdown(0, false);
  dot.setIntensity(0, 8);
  dot.clearDisplay(0);
}

void loop() {
  Serial.print("Input maths symbols : ");

  if (Serial.available() > 0) {
    char input1 = Serial.read();
    if (input1 == '+' || input1 == '-' || input1 == '*' || input1 == '/') {
      int a, b;
      if (Serial.available() >= 2) {
        a = Serial.parseInt();
        b = Serial.parseInt(); // 여기 틀릴수도 있음
      }

      choumpa();
      if (distance < 100) {
        delay (15000);

        if (distance < 100) {
          lcd.begin(16, 2);
          int result = ac_calculator(a, b, input1);
          lcd.print(result);
          digitalWrite(green, HIGH);
          delay(10000);
          digitalWrite(green, Low);
        }

        else {
          fa_calculator();
          digitalWrite(red, HIGH);
          delay(10000);
          digitalWrite(red, Low);
        }
      }
    }
  }
}

void notattention1(int time) // time 만큼 잠자기
{  
  dotmatrix_sti();
  delay(time);
}

void notattention2(int time) // time 만큼 춤추기
{  
  Servo myservo1;
  myservo1.attach(servo1);
  Servo myservo2;
  myservo2.attach(servo2);

  for (int pos = 150; pos <= 210; pos += 1) {  // 150도부터 210도까지 회전
    myservo1.write(pos);  // 서보 모터 회전 각도 설정
    myservo2.write(pos);  // 서보 모터 회전 각도 설정
    delay(15);  // 15밀리초 딜레이
    dotmatrix_tri();
  }
  for (int pos = 210; pos >= 150; pos -= 1) {  // 210도부터 150도까지 회전
    myservo1.write(pos);  // 서보 모터 회전 각도 설정
    myservo2.write(pos);  // 서보 모터 회전 각도 설정
    delay(15);  // 15밀리초 딜레이
    dotmatrix_tri();
  }
  myservo1.detach();
  myservo2.detach();
}

void choumpa()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // measure the duration of the echo pulse
  duration = pulseIn(echo, HIGH);

  // convert duration to distance
  distance = duration * 0.034 / 2;
}

int ac_calculator(int a, int b, char op)
{
  if (op == '+')
  {
    return a + b;
  }
  else if (op == '-')
  {
    return a - b;
  }
  else if (op == '*')
  {
    return a * b;
  }
  else 
  {
    return a / b;
  }
}

int fa_calculator()
{
  return random(100000);
}

void dotmatrix_tri()
{
  for (int i = 0; i < 8; i++) {
    dot.setRow(0, i, triangle[i]);
    delay(150);  // 150밀리초 딜레이
  }
}

void dotmatrix_sti()
{
  for (int i = 0; i < 8; i++) {
    dot.setRow(0, i, stick[i]);
    delay(150);  // 150밀리초 딜레이
  }
}