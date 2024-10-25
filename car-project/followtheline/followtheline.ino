const int A_1B = 5;
const int A_1A = 6;
const int B_1B = 9;
const int B_1A = 10;

const int lineTrack = 2;

void setup() {
  Serial.begin(9600);

  // モーターのピンを出力に設定
  pinMode(A_1B, OUTPUT);
  pinMode(A_1A, OUTPUT);
  pinMode(B_1B, OUTPUT);
  pinMode(B_1A, OUTPUT);

  // モータードライバのピンを初期化（モーターを停止状態に）
  analogWrite(A_1B, 0);
  analogWrite(A_1A, 0);
  analogWrite(B_1B, 0);
  analogWrite(B_1A, 0);

  // ライントラックセンサーのピンを入力に設定
  pinMode(lineTrack, INPUT);
}

void loop() {

  int speed = 100;

  int lineColor = digitalRead(lineTrack); // 0:white  1:black
  Serial.println(lineColor);

  if (lineColor) {
    moveLeft(speed);
  } else {
    moveRight(speed);
  }

  delay(50);  // モーターを動かす時間（調整可能）

  stopMotors();  // モーターを停止させる

  delay(10);  // 次のセンサー読み取りまでの待機時間（調整可能）
}

void stopMotors() {
  analogWrite(A_1B, 0);
  analogWrite(A_1A, 0);
  analogWrite(B_1B, 0);
  analogWrite(B_1A, 0);
}

void moveLeft(int speed) {
  analogWrite(A_1B, 0);
  analogWrite(A_1A, speed);
  analogWrite(B_1B, 0);
  analogWrite(B_1A, 0);
}

void moveRight(int speed) {
  analogWrite(A_1B, 0);
  analogWrite(A_1A, 0);
  analogWrite(B_1B, 0);
  analogWrite(B_1A, speed);
}
