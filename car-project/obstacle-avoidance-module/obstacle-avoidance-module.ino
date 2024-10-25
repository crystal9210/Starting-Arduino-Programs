const int A_1B = 5;
const int A_1A = 6;
const int B_1B = 9;
const int B_1A = 10;

const int rightIR = 7;
const int leftIR = 8;

void setup() {
  Serial.begin(9600);

  // モーターのピンを出力に設定
  pinMode(A_1A, OUTPUT);
  pinMode(A_1B, OUTPUT);
  pinMode(B_1A, OUTPUT);
  pinMode(B_1B, OUTPUT);

  // モータードライバのピンを初期化（モーターを停止状態に）
  analogWrite(A_1A, 0);
  analogWrite(A_1B, 0);
  analogWrite(B_1A, 0);
  analogWrite(B_1B, 0);

  // IR障害物センサーのピンを入力に設定
  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT);
}

void loop() {

  int left = digitalRead(leftIR);  // 0: Obstructed   1: Empty
  int right = digitalRead(rightIR);
  int speed = 150;

  if (!left && right) {
    backLeft(speed);
  } else if (left && !right) {
    backRight(speed);
  } else if (!left && !right) {
    moveBackward(speed);
  } else {
    moveForward(speed);
  }
}

void moveForward(int speed) {
  analogWrite(A_1A, speed);  // 左モーターA：前進
  analogWrite(A_1B, 0);
  analogWrite(B_1A, speed);  // 右モーターB：前進
  analogWrite(B_1B, 0);
}

void moveBackward(int speed) {
  analogWrite(A_1A, 0);     // 左モーターA：後進
  analogWrite(A_1B, speed);
  analogWrite(B_1A, 0);     // 右モーターB：後進
  analogWrite(B_1B, speed);
}

void backLeft(int speed) {
  analogWrite(A_1A, 0);     // 左モーターA：後進
  analogWrite(A_1B, speed);
  analogWrite(B_1A, 0);     // 右モーターB：停止
  analogWrite(B_1B, 0);
}

void backRight(int speed) {
  analogWrite(A_1A, 0);     // 左モーターA：停止
  analogWrite(A_1B, 0);
  analogWrite(B_1A, 0);     // 右モーターB：後進
  analogWrite(B_1B, speed);
}
