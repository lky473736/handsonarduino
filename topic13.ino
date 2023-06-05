#include <Servo.h>

Servo servo;

void setup() 
{
  servo.attach(8);
  // 서보모터는 핀모드 지정 안해줌
}

void loop()
{
  int k = analogRead(A0);
  int p = map(k, 0, 1023, 0, 180);
  servo.write(p);
  delay(10);
}
