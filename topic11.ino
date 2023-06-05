#include <LiquidCrystal.h>

LiquidCrystal lcd (12, 11, 2, 3, 4, 5); // lcd 사용핀 입력 (순서 중요)

void setup()
{
  lcd.begin (16, 2); // 16개 * 2 짜리의 lcd를 시작한다
}

void loop()
{
  int light = analogRead(A0);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print ("light");
  lcd.setCursor(0,1);
  lcd.print (light);
  delay (1000);
}
