// モーター制御ピンの定義
const int A_1B = 5;   // 左モーター（モーターA）のピン
const int A_1A = 6;
const int B_1B = 9;   // 右モーター（モーターB）のピン
const int B_1A = 10;

// 赤外線障害物センサーのピン定義
const int rightIR = 7;
const int leftIR = 8;

// 超音波センサーのピン定義
const int trigPin = 3;
const int echoPin = 4;

void setup() {
  Serial.begin(9600);  // シリアル通信の初期化

  // モーターのピンを出力に設定
  pinMode(A_1A, OUTPUT);
  pinMode(A_1B, OUTPUT);
  pinMode(B_1A, OUTPUT);
  pinMode(B_1B, OUTPUT);

  // モータードライバのピンを初期化（モーターを停止状態に）
  stopMove();

  // 赤外線障害物センサーのピンを入力に設定
  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT);

  // 超音波センサーのピン設定
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  float distance = readSensorData();  // 超音波センサーで距離を測定
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  int left = digitalRead(leftIR);     // 左赤外線センサーの値（0: 障害物あり, 1: なし）
  int right = digitalRead(rightIR);   // 右赤外線センサーの値
  Serial.print("Left IR: ");
  Serial.print(left);
  Serial.print(" | Right IR: ");
  Serial.println(right);

  int speed = 150;  // モーターの速度設定（0〜255）

  if (distance > 10 && distance < 20) {
    moveForward(speed);
  } else if (distance <= 10 && distance > 20) {
    stopMove();
  } else if (!left && right) {
    turnRight(speed);
  } else if (left && !right) {
    turnLeft(speed);
  } else {
    stopMove();
  }
}

float readSensorData() {
  // 超音波センサーで距離を測定
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  float duration = pulseIn(echoPin, HIGH, 20000);  // タイムアウトを設定
  if (duration == 0) {
    return -1;  // 測定失敗
  } else {
    float distance = duration / 58.00;        // 距離をセンチメートルに変換
    return distance;
  }
}

// モーター制御関数
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

void moveForward(int speed) {
  // 左モーター前進
  analogWrite(A_1A, speed);
  analogWrite(A_1B, 0);
  // 右モーター前進
  analogWrite(B_1A, speed);
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

void stopMove() {
  // モーターを停止
  analogWrite(A_1A, 0);
  analogWrite(A_1B, 0);
  analogWrite(B_1A, 0);
  analogWrite(B_1B, 0);
}
