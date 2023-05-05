// 창의-엔트리 11팀

#include <Arduino.h>
#include <LedControl.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include <Matrix.h>
Matrix myMatrix(A2, A3);

uint8_t LedArray0[8] = {0x00,0x18,0x24,0x42,0x81,0x99,0x66,0x00}; // 하트
uint8_t LedArray1[8] = {0x00, 0x00, 0x00, 0x18, 0x3C, 0x7E, 0xFF, 0x00}; // 미소
uint8_t LedArray2[8] = {0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00}; // 잠자는 표정
uint8_t LEDArray[8];

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

long duration;
int distance;
int i;

void notattention1(int time);
void notattention2();
void choumpa();
int ac_calculator(int a, int b, char op);
int fa_calculator();

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);

  servo1.attach(4);
  servo2.attach(5);
  myMatrix.begin(0x70);

  lcd.init();
  lcd.clear();
  lcd.setBacklight(50);
}

void loop()
{
   myMatrix.clear();
  for(int i=0; i<8; i++)
  {
    LEDArray[i]=LedArray0[i];
    for(int j=7; j>=0; j--)
    {
      if((LEDArray[i]&0x01)>0)
      myMatrix.drawPixel(j, i,1);
      LEDArray[i] = LEDArray[i]>>1;
    }
  }
  myMatrix.writeDisplay();


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
  while (!Serial.available());  
  num2 = Serial.parseFloat();    
  Serial.println(num2);    

  for (int y = 0; y < 10; y++)
  {
    choumpa();
    delay(1000);

    if (distance < 50) {
      break;
    }

    if (y == 9)
    {
        // long seed = millis();
        randomSeed(analogRead(0));
        int ran = random(2);
        
        if (ran == 0)
        {
          notattention1(15000); // 잠
          myMatrix.clear();
          myMatrix.writeDisplay();
          
        }
        else
        {
          notattention2(); // 춤
          myMatrix.clear();
          myMatrix.writeDisplay();
        }

        delay (5000);
        int fake = fa_calculator();
        // lcd.begin(16, 2);
        Serial.println (fake);
        lcd.setCursor(0, 0);
        lcd.print(fake);

        for (int k = 0; k < 3; i++)
        {
          digitalWrite(red, HIGH);
          delay(500);
          digitalWrite(red, LOW);
          delay(500);
        }

        /*while (true)
        {

        }*/
    }
  }

  delay (5000);
  // lcd.begin(16, 2);
  int result = ac_calculator(num1, num2, op);
  Serial.println (result);
  lcd.setCursor(0, 0);

  lcd.print(result);

  for (int k = 0; k < 3; i++)
   {
    digitalWrite(green, HIGH);
    delay(500);
    digitalWrite(green, LOW);
    delay(500);
  }

  /*while (true)
  {
    // 무한루프로 인해 프로그램 종료
  }*/
}

void notattention1(int time) // time 만큼 잠자기
{  
  myMatrix.clear();
  for(int i=0; i<8; i++)
  {
    LEDArray[i]=LedArray2[i];
    for(int j=7; j>=0; j--)
    {
      if((LEDArray[i]&0x01)>0)
      myMatrix.drawPixel(j, i,1);
      LEDArray[i] = LEDArray[i]>>1;
    }
  }
  myMatrix.writeDisplay();

  long starttime0 = millis();
  while(millis()-starttime0 < 7000){
    for (int angle = 0; angle <= 90; angle += 5) {
      while (angle < 90) {
        servo1.write(angle);
        servo2.write(180 - angle);
        delay(100);
      }
      servo1.write (0);
      servo1.write (0);
  }
  }
  delay(time);
}
  

void notattention2() 
{  
  myMatrix.clear();
  for(int i=0; i<8; i++)
  {
    LEDArray[i]=LedArray1[i];
    for(int j=7; j>=0; j--)
    {
      if((LEDArray[i]&0x01)>0)
      myMatrix.drawPixel(j, i,1);
      LEDArray[i] = LEDArray[i]>>1;
    }
  }
  myMatrix.writeDisplay();

  long starttime1 = millis();
  while(millis()-starttime1 < 7000){
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
