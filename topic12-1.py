void setup()
{
  pinMode (9, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int k = analogRead(A0);
  Serial.println(k);
  
  int l = k / 4; // PWM은 0~255 범위만 허용
  
  analogWrite(9, l);
}
