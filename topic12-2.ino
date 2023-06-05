void setup()
{
  pinMode (3, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int k = analogRead(A0);
  int p = k / 4;
  
  Serial.println(p);
  analogWrite(3, p);
}
