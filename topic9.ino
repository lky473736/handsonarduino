int pin[] = {2, 3, 4, 5, 6, 7, 8};
int digitpin[2] = {A0, A1};

int digit[10][7] = {
  {0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 1, 1, 1, 1},
  {0, 0, 1, 0, 0, 1, 0},
  {0, 0, 0, 0, 1, 1, 0},
  {1, 0, 0, 1, 1, 0, 0},
  {0, 1, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0}
};

unsigned long readtime = 0;
int d1 = 0;
int d2 = 0;

void setup() {
  for (int i = 0; i < 7; i++)
  {
    pinMode (pin[i], OUTPUT);
  }
  pinMode (digitpin[0], OUTPUT);
  pinMode (digitpin[1], OUTPUT);
}

void loop() {
  readtime = millis()/1000;
  d1 = readtime % 10;
  d2 = readtime / 10;
  
  segoutput(1, d1);
  if (readtime >= 10)
  {
    segoutput(0, d2);
  }
}

void segclear()
{
  for (int i = 0; i < 7; i++)
  {
    digitalWrite(pin[i], HIGH);
  }
}

void segoutput(int d, int number)
{
  segclear();
  digitalWrite(digitpin[d], HIGH);
  for (int i = 0; i < 7; i++)
  {
    digitalWrite(pin[i], digit[number][i]);
  }
  
  delayMicroseconds(1000);
  digitalWrite(digitpin[d], LOW);
}
