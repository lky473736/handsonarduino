/* 
코드 최적화 사항 2
1) const int를 핀번호에 사용해서 tinkercad 특유의 핀번호 오류를 방지했습니다
2) 주석에 약간의 설명을 첨부하였습니다
3) targetcount 변수를 새로 만들어서 처음에 목표를 설정하게끔 했습니다
4) 피에조 부저 시간을 조금 더 짧게 해서 소리가 짧게 나도록 했습니다
*/


bool start = false; // false일시 led 색 못 바꾸게 함 / true일시 센서 입력
const int buttonPins[] = {5, 6, 7}; // 버튼 핀 번호 배열
const int ledPins[] = {9, 10, 11}; // LED 핀 번호 배열
const int colors[][3] = {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}}; // LED 색상 배열
int trig = 2; // 센서 들어가는거
int echo = 3; // 센서 나가는거
const int min_distance[] = {10, 20, 40}; // 팔굽혀펴기, 턱걸이, 스쿼트 센서 길이
int targetcount = 0;
int count = 0; // 카운트
int k; // 버튼을 눌렀을 때 받아온 i값(즉 버튼의 순서를) 받아올거임.

int buttonStates[] = {LOW, LOW, LOW}; // 버튼 상태 배열

void setup() 
{
  for (int i = 0; i < 3; i++) 
  {
    pinMode(buttonPins[i], INPUT); // 버튼 핀을 입력 모드로 설정
    pinMode(ledPins[i], OUTPUT);  // LED 핀을 출력 모드로 설정
  }
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600);
  
  Serial.println("What counts you exercise? : "); // targetcount를 물음
}

void loop()
{
  if (Serial.available()) // serial monitor에 값이 들어온 걸 확인하면
  {
    targetcount = Serial.parseInt(); // targetcount 변수에 입력값을 저장함
    Serial.println(targetcount); 
    Serial.println("OK. Press the button you want"); // 이제부터 버튼을 고르면 됨
  }
  
  for (int i = 0; i < 3; i++) // 버튼 뭐 골랐는지 알기 위함
  { 
    // 버튼의 상태를 읽기
    buttonStates[i] = digitalRead(buttonPins[i]);

    // 버튼이 눌린 경우 LED 색상 변경
    if (buttonStates[i] == HIGH && start != 1 ) 
    {
      k = i; //정해진 버튼의 min_distance의 값을 불러오기 위함
      start = 1;
      
      analogWrite(ledPins[0], colors[i][0]); // 적색 LED 색상 변경
      analogWrite(ledPins[1], colors[i][1]); // 녹색 LED 색상 변경
      analogWrite(ledPins[2], colors[i][2]); // 청색 LED 색상 변경
      
      Serial.print("MODE: ");
      
      if (i == 0)
      {
        Serial.println("Push up");
      }
      else if (i == 1)
      {
        Serial.println("Pull up");
      }
      else if (i == 2)
      {
        Serial.println("Squat");
      }
    }
    
    digitalWrite(2,HIGH);
    delayMicroseconds(10);
    digitalWrite(2,LOW); // 센서 계속 쏨
    long duration = pulseIn(3,HIGH);
    
    if (duration == 0)
    {
      return;
    }
    
    long distance = duration / 58.2;
    
    if (start == 1 && distance < min_distance[k])
    {
      tone(12,523); // 소리
      delay(100);
      noTone(12);
      ++count; // 개수 올림
      Serial.print("Count:"); 
      Serial.println(count);
      delay(100); // 센서에 계속 닿으면 개수 계속 올라가니깐 딜레이
    }
    
    if (start == 1 && count >= targetcount)
    {
      tone(12,659); // 성공하면 소리
      delay(500);
      noTone(12);
      Serial.print("Good\n"); // 성공하면 good 출력
      
      start = false; // start를 false로 만들어서 버튼 고를 수 있게함
      //(그 전까지는 start가 true라 버튼을 눌러도 반응이 없음)
      
      count = 0; // 카운트 초기화
      for (int i = 0; i < 3; i++)
      {
        analogWrite(ledPins[i],0); // RGB LED 색 초기화
      }
    }
  }
}
