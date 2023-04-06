// 스위치 피아노

int melody[] = {262,293,329,349,392};
void setup()
{
  pinMode(10, OUTPUT);
  for (int buttonpin = 2; buttonpin < 7; buttonpin++)
  {
    pinMode(buttonpin, INPUT);
  }
}

void loop()
{
  for (int i = 2; i < 7; i++)
  {
    if (digitalRead(i) == HIGH)
    {
      tone(10, melody[i-2], 250);
      delay(500);
    }
  }
  noTone(10);
}
