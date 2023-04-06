// 3주차 과제 
// 신호등 시스템

void setup() // 처음 한번만 실행됨
{
  pinMode(12, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(4, OUTPUT);
  // pinMode는 처음 한번만 지정한다.
}

void loop() // 계속 반복됨 (loopstation)
{
  digitalWrite(12, 1);
  // 1 == HIGH, 0 == LOW
  delay(5000);
  digitalWrite(12, 0);
  delay(100);
  
  digitalWrite(8, 1);
  delay(3000);
  digitalWrite(8, 0);
  delay(100);
  
  digitalWrite(4, 1);
  delay(10000);
  digitalWrite(4, 0);
  delay(100);
}
