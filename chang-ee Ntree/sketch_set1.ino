/* 이제 해야하는거
1) lcd 화면이 안뜨는 문제 해결 (아마도 화질 때문에 그런 것 같음)
2) 서보모터가 돌아가지 않음 (조교님의 도움이 필요할 것 같다. 분명 코드는 올바름.)
3) 도트매트릭스가 아무래도 조금 다른 라이브러리를 써야 할 것 같음
(LedControl.h -> MD_MAX72xx.h & SPI.h)*/


#include <LedControl.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LedControl Dote = LedControl(7, 6, 5, 1);

LiquidCrystal_I2C lcd(0x27, 16, 2);

int trig = 3;
int echo = 2;

int ran = random(2);

char op;    // 연산자를 저장할 변수
float num1, num2;    // 입력받은 두 수와 결과를 저장할 변수

Servo servo1;  // 서보 모터 1 객체
Servo servo2;  // 서보 모터 2 객체

int red = 8;
int green = 9;

int sda_d = A2; // dot matrix
int scl_d = A3; // dot matrix

long duration;
int distance;
int i;

void notattention1(int time);
void notattention2();
void choumpa();
int ac_calculator(int a, int b, char op);
int fa_calculator();

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
  B00000000
};

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);

  Dote.shutdown(0, false);                    
  Dote.setIntensity(0, 7);                 
  Dote.clearDisplay(0);

  servo1.attach(4);
  servo2.attach(5);
}

void loop()
{
  digitalWrite(3, LOW);
  Serial.print("Enter an operator (+, -, *, /): ");
  while (!Serial.available());   
  op = Serial.read();    
  Serial.println(op);    

  Serial.print("Enter the first number: ");
  while (!Serial.available());   
  num1 = Serial.parseFloat();   
  Serial.println(num1);   

  Serial.print("Enter the second number: ");
  while (!Serial.available());   // 두 번째 숫자 입력 대기
  num2 = Serial.parseFloat();    // 두 번째 숫자 입력받음
  Serial.println(num2);    // 입력받은 두 번째 숫자 출력

  for (int y = 0; y < 10; y++)
  {
    choumpa();
    delay(1000);

    if (distance < 50) {
      break;
    }

    if (y == 9)
    {
        
        notattention2();

        delay (5000);
        lcd.begin(16, 2);
        int fake = fa_calculator();
        lcd.print(fake);
        Serial.println (fake);

        for (int k = 0; k < 3; i++)
        {
          digitalWrite(red, HIGH);
          delay(500);
          digitalWrite(red, LOW);
          delay(500);
        }

        while (true)
        {
          // 무한루프로 인해 프로그램 종료
        }
    }
  }

  delay (5000);
  lcd.begin(16, 2);
  int result = ac_calculator(num1, num2, op);
  lcd.print(result);
  Serial.println (result);

  for (int k = 0; k < 3; i++)
   {
    digitalWrite(green, HIGH);
    delay(500);
    digitalWrite(green, LOW);
    delay(500);
  }

  while (true)
  {
    // 무한루프로 인해 프로그램 종료
  }
}

void notattention1(int time) // time 만큼 잠자기
{  
  showMatrix(stick, 1);
  delay(time);
}

void notattention2() 
{  
  showMatrix(triangle, 1);
  for (int angle = 0; angle <= 180; angle += 20) {
    servo1.write(angle);
    servo2.write(180 - angle);
    delay(50);
  }
  
  for (int angle = 180; angle >= 0; angle -= 20) {
    servo1.write(angle);
    servo2.write(180 - angle);
    delay(50);
  }
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

  Serial.print("distance : ");
  Serial.println(distance);
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
  return random();
}

void showMatrix(byte arr[], int a)
{
  if (a == 1) {
    for (int i = 0; i < 8; i++)
    {
      Dote.setRow(0, i, arr[i]);
    }
  } else {
    for (int i = 0; i < 8; i++)
    {
      Dote.setRow(0, i, B00000000);
    }
  }
}