void setup ()
{
  pinMode (13, OUTPUT); // Trig
  pinMode (11, INPUT); // Echo
  pinMode (8, OUTPUT); // 피에조
  Serial.begin(9600);
}

void loop() 
{
  analogWrite (3, 0); // R
  analogWrite (9, 0); // B
  analogWrite (10, 0); // G
  
  digitalWrite (13, HIGH); // Trig에서 초음파 날림
  delayMicroseconds (10);
  digitalWrite (13, LOW);
  
  long duration = pulseIn (11, HIGH); // 11에서 받고, HIGH -> LOW로 되는 시간 duration에 실수형으로 저장함.
  long distance = duration / 58.2; // cm 기준
  
  if (distance > 10 && distance < 80) 
  {
    tone (8, 330, 1000);
    analogWrite (10, 255);
  }
  
  else 
  {
    noTone(8);
    analogWrite (9, 255);
  }
  
  Serial.println(distance);
}
