#include <IRremote.h>

const int IR_RECEIVE_PIN = 12;  // Define the pin number for the IR Sensor

// モーター制御ピンの定義
const int A_1B = 5;   // 左モーター（モーターA）のピン
const int A_1A = 6;
const int B_1B = 9;   // 右モーター（モーターB）のピン
const int B_1A = 10;

int speed = 150;

void setup() {
  Serial.begin(9600);

  // モーターのピンを出力に設定
  pinMode(A_1A, OUTPUT);
  pinMode(A_1B, OUTPUT);
  pinMode(B_1A, OUTPUT);
  pinMode(B_1B, OUTPUT);

  // モータードライバのピンを初期化（モーターを停止状態に）
  stopMove();

  // IRリモコンの初期化
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("REMOTE CONTROL START");
}

void loop() {

  if (IrReceiver.decode()) {
    String key = decodeKeyValue(IrReceiver.decodedIRData.command);
    if (key != "ERROR") {
      Serial.println(key);

      if (key == "+") {
        speed += 50;
      } else if (key == "-") {
        speed -= 50;
      } else if (key == "2") {
        moveForward(speed);
        delay(1000);
      } else if (key == "8") {
        moveBackward(speed);
        delay(1000);
      } else if (key == "4") {
        turnLeft(speed);
        delay(1000);
      } else if (key == "6") {
        turnRight(speed);
        delay(1000);
      } else if (key == "1") {
        moveLeft(speed);
        delay(1000);
      } else if (key == "3") {
        moveRight(speed);
        delay(1000);
      } else if (key == "7") {
        backLeft(speed);
        delay(1000);
      } else if (key == "9") {
        backRight(speed);
        delay(1000);
      }

      if (speed >= 255) {
        speed = 255;
      }
      if (speed <= 0) {
        speed = 0;
      }
      stopMove();
    }

    IrReceiver.resume();  // Enable receiving of the next value
  }
}

// モーター制御関数
void moveForward(int speed) {
  // 左モーター前進
  analogWrite(A_1A, speed); // 左側の速度が遅いので調整
  analogWrite(A_1B, 0);
  // 右モーター前進
  analogWrite(B_1A, speed + 20);
  analogWrite(B_1B, 0);
}

void moveBackward(int speed) {
  // 左モーター後進
  analogWrite(A_1A, 0);
  analogWrite(A_1B, speed);
  // 右モーター後進
  analogWrite(B_1A, 0);
  analogWrite(B_1B, speed);
}

void turnRight(int speed) {
  // 左モーター前進
  analogWrite(A_1A, speed);
  analogWrite(A_1B, 0);
  // 右モーター後進
  analogWrite(B_1A, 0);
  analogWrite(B_1B, speed);
}

void turnLeft(int speed) {
  // 左モーター後進
  analogWrite(A_1A, 0);
  analogWrite(A_1B, speed);
  // 右モーター前進
  analogWrite(B_1A, speed);
  analogWrite(B_1B, 0);
}

void moveLeft(int speed) {
  // 左モーター停止
  analogWrite(A_1A, 0);
  analogWrite(A_1B, 0);
  // 右モーター前進
  analogWrite(B_1A, speed);
  analogWrite(B_1B, 0);

  // 曲がる動作の持続時間を設定（例：500ミリ秒）
  delay(500); // 適切な値に調整

  // 前進動作
  moveForward(speed);
}

void moveRight(int speed) {
  // 左モーター前進
  analogWrite(A_1A, speed);
  analogWrite(A_1B, 0);
  // 右モーター停止
  analogWrite(B_1A, 0);
  analogWrite(B_1B, 0);

  // 曲がる動作の持続時間を設定（例：500ミリ秒）
  delay(500); // 適切な値に調整

  // 前進動作
  moveForward(speed);
}


void backLeft(int speed) {
  // 左モーター停止
  analogWrite(A_1A, 0);
  analogWrite(A_1B, speed);
  // 右モーター後進
  analogWrite(B_1A, 0);
  analogWrite(B_1B, 0);

  // 曲がる動作の持続時間を設定（例：500ミリ秒）
  delay(500); // 適切な値に調整

  // 前進動作
  moveBackward(speed);
}

void backRight(int speed) {
  // 左モーター後進
  analogWrite(A_1A, 0);
  analogWrite(A_1B, 0);
  // 右モーター停止
  analogWrite(B_1A, 0);
  analogWrite(B_1B, speed);

  // 曲がる動作の持続時間を設定（例：500ミリ秒）
  delay(500); // 適切な値に調整

  // 前進動作
  moveBackward(speed);
}

void stopMove() {
  // モーターを停止
  analogWrite(A_1A, 0);
  analogWrite(A_1B, 0);
  analogWrite(B_1A, 0);
  analogWrite(B_1B, 0);
}

String decodeKeyValue(long result)
{
  switch(result){
    case 0x16:
      return "0";
    case 0xC:
      return "1"; 
    case 0x18:
      return "2"; 
    case 0x5E:
      return "3"; 
    case 0x8:
      return "4"; 
    case 0x1C:
      return "5"; 
    case 0x5A:
      return "6"; 
    case 0x42:
      return "7"; 
    case 0x52:
      return "8"; 
    case 0x4A:
      return "9"; 
    case 0x9:
      return "+"; 
    case 0x15:
      return "-"; 
    case 0x7:
      return "EQ"; 
    case 0xD:
      return "U/SD";
    case 0x19:
      return "CYCLE";         
    case 0x44:
      return "PLAY/PAUSE";   
    case 0x43:
      return "FORWARD";   
    case 0x40:
      return "BACKWARD";   
    case 0x45:
      return "POWER";   
    case 0x47:
      return "MUTE";   
    case 0x46:
      return "MODE";       
    case 0x0:
      return "ERROR";   
    default :
      return "ERROR";
    }
}
