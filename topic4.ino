// 4주차 과제 
// 신호등 시스템 + 변수 개념 적용

int pin1 = 12;
int pin2 = 8;
int pin3 = 4;
int delaytime1 = 1000;
int delaytime2 = 100;

void setup() // 처음 한번만 실행됨
{
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  // pinMode는 처음 한번만 지정한다.
}

void loop() // 계속 반복됨 (loopstation)
{
  digitalWrite(pin1, 1);
  // 1 == HIGH, 0 == LOW
  delay(delaytime1);
  digitalWrite(pin1, 0);
  delay(delaytime2);
  
  digitalWrite(pin2, 1);
  delay(delaytime1);
  digitalWrite(pin2, 0);
  delay(delaytime2);
  
  digitalWrite(pin3, 1);
  delay(delaytime1);
  digitalWrite(pin3, 0);
  delay(delaytime2);
}
