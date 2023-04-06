void setup()
{
  pinMode (9, OUTPUT);
  pinMode (8, INPUT);
  Serial.begin(9600); // baud rate
}

void loop()
{
  digitalWrite(9, HIGH);
  delayMicroseconds(10);
  digitalWrite(9, LOW);
  
  long duration = pulseIn(8, HIGH); // duration
  
  if (duration == 0)
  {
    return;
  }
  
  else if (duration != 0)
  {
  long distance = duration / 58.2; // distance
  Serial.print("distance : ");
  Serial.print(distance);
  Serial.println("cm");
  }
}
