#include <LiquidCrystal.h> // LCD
#include <Wire.h>
#include <Servo.h> // 서보모터
#include <LedControl.h> // LED

/*아이디어명 : 한시라도 집중을 못하는 천방지축 계산기 

필요 부품 : 브레드보드 큰거, 우노보드 하나, 점퍼선 많이, 디스플레이 하나, 초음파센서 하나, 모터 2개 (팔 표현), 버튼 하나, 피에조부저 하나, 저항 5개 (220k옴)

1) 계산문제 연산을 시킨다.
(이때 계산기의 표정표현을 위해 디스플레이가 필요하다.)

2) 계산기는 이때 초음파센서를 이용하여 사용자가 근처에 없을 때에는 문제를 풀지 않고 딴 짓을 한다.
2-1) 문제를 풀지 않고 잠을 자기 (눈 감고 있는 디스플레이 구현)
2-2) 춤추기 (이때 춤추는 팔을 제어할 모터와 스피커 필요)
2-3) 그냥 멍때리기
사용자가 초음파센서의 범위 안에 들어왔을 때는 다시 집중하는 표정을 짓는다.

3) 사용자가 로봇에게 “다 했냐”는 일종의 신호를 버튼으로 주면 해맑은 표정을 출력하여 해당 문제의 답과 엉뚱한 답을 출력한다.
(이때 난수 헤더파일이 필요할 것이다.)
*/

int trig = 3;
int echo = 2;

int servo1 = 4;
int servo1 = 5;
int servo1 = 6;
int servo1 = 7;

int red = 8;
int green = 9;

int sda = A4;
int scl = A5;

int sda_d = A2; // dot matrix
int scl_d = A3; // dot matrix

LiquidCrystal lcd (A4, A5);

void notattention1(time); // 딴짓1 : 잠자기
void notattention2(time); // 딴짓2 : 춤추기
void choumpa(); // 초음파
void ac_calculator(a, b, c); // 정확한 계산
void fa_calculator(); // 잘못된 계산

void setup() 
{
    // 시리얼 통신을 위한 통신 시작 알림

    Serial.begin(9600);

    // 초음파 센서

    pinMode (trig, OUTPUT); // Trig
    pinMode (echo, INPUT); // Echo

    // 서보모터

    pinMode (servo1, OUTPUT); // servo 1
    pinMode (servo2, OUTPUT); // servo 2
    pinMode (servo3, OUTPUT); // servo 3
    pinMode (servo4, OUTPUT); // servo 4

    // LED

    pinMode (red, OUTPUT) // 빨강
    pinMode (green, OUTPUT) // 초록
}

void loop()
{
    Serial.print ("Input maths symbols : ")

    if (Serial.available() > 0) // 시리얼 입력값이 있는 경우엔
    {
        char input1 = Serial.read(); // input

        if (input1 == '+' || input1 == '-' || input1 == '*' || input1 == '/')
    {
        int a, b;

        if (Serial.available() >= 2) 
        {
          a = Serial.parseInt();
          b = Serial.parseInt();
        }

        choumpa();

        if (distance < 100)
        {
            delay (15000);

            if (distance < 100)
            {
                lcd.begin(16, 2);
                lcd.print(ac_calculator(a, b, input1)); // 정확한 값
            }

            else // 거리가 100 이상이면
            {
              for (i = 0; i < 2; i++)
              {
                mode = random (2);
                
                if (mode == 0)
                {
                  notattention1(15000);
                }

                else if (mode == 1)
                {
                  notattention2(15000);
                }
              }

              lcd.begin(16, 2);
              lcd.print(fa_calculator()); // 이상한 값         
              }
        }

        else 
        {
            mode = random (2);
                
                if (mode == 0)
                {
                  notattention1(15000);
                }

                else if (mode == 1)
                {
                  notattention2(15000);
                }

            lcd.begin(16, 2);
            lcd.print(fa_calculator()); // 이상한 값
        }
    }

    else
    {
        return 0;
    }
}

void notattention1(time) // time 만큼 잠자기
{

}


void notattention2(time) // time 만큼 춤추기
{
}


void choumpa()
{
        digitalWrite (trig, LOW);
        delayMicroseconds(2);
        digitalWrite(trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig, LOW);

         // measure the duration of the echo pulse
        duration = pulseIn(echo, HIGH);

        // convert duration to distance
        distance = duration * 0.034 / 2;
}
    
void ac_calculator(a, b, c)
{
  if (c == '+')
  {
    return a + b;
  }

  else if (c == '-')
  {
    return a - b;
  }

  else if (c == '*')
  {
    return a * b;
  }
  else 
  {
    return a / b;
  }
}

void fa_calculator()
{
  return random(100000);
}
