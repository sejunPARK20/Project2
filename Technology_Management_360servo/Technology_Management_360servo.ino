#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);  // 블루투스 모듈의 Rx -> 3번핀, Tx -> 2번핀 연결

Servo servoA;      // A 서보 객체 생성
Servo servoB;      // B 서보 객체 생성
Servo servo1;      // 1 서보 객체 생성
Servo servo2;      // 2 서보 객체 생성

const int ledPin = 9; // LED를 연결한 핀 번호
int servoPinA = 10;   // A 서보 모터가 연결된 핀 번호
int servoPinB = 11;   // B 서보 모터가 연결된 핀 번호
int servoPin1 = 12;   // 1 서보 모터가 연결된 핀 번호
int servoPin2 = 13;   // 2 서보 모터가 연결된 핀 번호

void setup() {
  servoA.attach(servoPinA);  // A 서보 모터 핀 설정
  servoA.write(90);          // A 서보 모터 초기 위치 설정 (90도)
  
  servoB.attach(servoPinB);  // B 서보 모터 핀 설정
  servoB.write(90);          // B 서보 모터 초기 위치 설정 (90도)
  
  servo1.attach(servoPin1);  // 1 서보 모터 핀 설정
  servo1.write(0);           // 1 서보 모터 초기 위치 설정 (0도)
  
  servo2.attach(servoPin2);  // 2 서보 모터 핀 설정
  servo2.write(103);           // 2 서보 모터 초기 위치 설정 (0도)
  
  Serial.begin(9600);        // 시리얼 통신 시작
  mySerial.begin(9600);
  
  pinMode(ledPin, OUTPUT);   // LED 핀을 출력으로 설정
}

void loop() {
  char receivedChar = 0; // 변수 선언 및 초기화

   if (Serial.available() > 0) {  // 시리얼 버퍼에 데이터가 있는지 확인
    receivedChar = Serial.read();  // 시리얼 버퍼에서 문자 읽기
  } else if (mySerial.available()) {  // 블루투스 버퍼에 데이터가 있는지 확인
    receivedChar = mySerial.read();  // 블루투스 버퍼에서 문자 읽기
  }
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
    
  if (receivedChar == 'A') {  // 읽은 문자가 'A'인지 확인
    digitalWrite(ledPin, HIGH); // LED를 켬
    servoA.write(180);  // 정방향으로 최고속도 회전
    delay(1000); // 1.5초동작
    servoA.write(90); // 정지
    delay(500);  // 0.5초 동작         
    servo1.write(90);                // B 서보 모터를 180도로 회전
    delay(1000);                     // 1초 대기
    servo1.write(0);                 // B 서보 모터를 다시 0도로 회전
    delay(500);  // 0.5초 동작   
    servoA.write(0); // 역방향으로 최고속도 회전
    delay(850); // 1.5초 동작
    servoA.write(90); // 정지
    delay(500);  // 0.5초 동작
    digitalWrite(ledPin, LOW); // LED를 끔
  }  
  if (receivedChar == 'B') {  // 읽은 문자가 'B'인지 확인
    digitalWrite(ledPin, HIGH); // LED를 켬
    servoB.write(180);          // B 서보 모터를 정방향
    delay(900);                // 1초 대기
    servoB.write(90);            // B 서보 모터를 다시 0도로 회전
    delay(500);  // 0.5초 동작   
    servo2.write(13);        // 2 서보 모터를 180도로 회전
    delay(1000);              // 1초 대기
    servo2.write(103);          // 2 서보 모터를 다시 0도로 회전
    delay(500);  // 0.5초 동작   
    servoB.write(0); // 역방향으로 최고속도 회전
    delay(800); // 1.5초 동작
    servoB.write(90); // 정지
    delay(500);  // 0.5초 동작
    digitalWrite(ledPin, LOW); // LED를 끔
  }
}