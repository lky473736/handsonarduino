/* 
팀플 1
컴퓨터공학전공 임규연
2023년 4월 6일 작성

모드 1 : 팔굽혀펴기 
내려갔을때에는 가슴과 봉사이에 10cm(주먹하나) 유지시에만 정확한 자세로 인정
따라서 초음파 센서를 10cm 기준으로

모드 2 : 턱걸이
봉이 턱에 닿아야 인정
따라서 distance가 줄어들었다가 다시 늘어나는 걸 count로 취급

모드 3 : 스쿼트
모드 2와 동일

모드 1 버튼 : 2번 핀
모드 2 버튼 : 3번 핀
모드 3 버튼 : 4번 핀

버튼의 폴다운을 주기 위하여 10k 옴 사용

trig : 9번 핀
echo : 8번 핀
*/


int button1 = 2;  // 모드 1 버튼
int button2 = 3;  // 모드 2 버튼
int button3 = 4;  // 모드 3 버튼
int trig = 9;  // 초음파 센서 트리거 핀
int echo = 8;     // 초음파 센서 에코 핀
int pushupstandard = 10;  // 거리 기준값 (단위: cm)

int mode = 0;              // 현재 모드
int count = 0;             // 운동 count
int targetCount = 0;       // 목표 count
bool counting = false;   // count 중인지 여부 (불리언 변수 사용)
bool finished = false;   // 목표 count 달성 여부 (불리언 변수 사용)

void setup() {
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
  
  Serial.println("Enter the target count:");
  while (!Serial.available()) 
  {
    // 출력 잠깐만 대기하기
  }
  
  targetCount = Serial.parseInt(); // int값으로 시리얼 입력받기
  Serial.print("Target count: ");
  Serial.println(targetCount);
}

void loop() {
  if (digitalRead(button1) == HIGH) 
  {
    mode = 1;
    Serial.println("Mode 1: Push-up");
    delay(500);
  } 
  
  else if (digitalRead(button2) == HIGH) 
  {
    mode = 2;
    Serial.println("Mode 2: Pull-up");
    delay(500);
  } 
  
  else if (digitalRead(button3) == HIGH) 
  {
    mode = 3;
    Serial.println("Mode 3: Squat");
    delay(500);
  }
  
  if (mode != 0 && !finished) 
  {
    // 초음파 센서로부터 거리 측정
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    float duration = pulseIn(echo, HIGH);
    // cm 변환
    float distance = duration * 0.034 / 2; 
    
    
    if (!counting && distance < pushupstandard) 
    {
      // 운동 count 시작
      counting = true;
      count++;
      Serial.print("Count: ");
      Serial.println(count);
    } 
    
    else if (counting && distance > pushupstandard) 
    {
      // 운동 count 종료
      counting = false;
      delay(500);  
    }
    
    // 목표 count 달성 여부 확인
    if (count >= targetCount) 
    {
      finished = true;
      Serial.println("Well done!!");
      return;
    }
  }
}

/* 추가하면 좋을 것 같은거

1) 삼색 led 사용해서 운동 모드마다 색깔 다르게 하기
2) 목표 count 다 달성하면 피에조 부저로 소리나게 하기

*/
