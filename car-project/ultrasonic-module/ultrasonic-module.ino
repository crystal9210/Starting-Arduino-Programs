// プログラム仕様:車を壁の方向に向けてください。距離が遠すぎると前進し、近すぎると後退し、安全な距離であれば停止します
// https://docs.sunfounder.com/projects/3in1-kit-v2/ja/latest/car_project/car_ultrasonic.html
const int A_1B = 5;
const int A_1A = 6;
const int B_1B = 9;
const int B_1A = 10;

const int trigPin = 3;
const int echoPin = 4;

void setup() {
  Serial.begin(9600);  // シリアル通信を初期化

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

  // 超音波センサーのピン設定
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

// loop関数
// readSensorData()：超音波センサーで距離を測定する関数を呼び出し
// Serial.println(distance);：測定した距離をシリアルモニタに表示
// 条件分岐（if文）：
// distance > 25：距離が25cmより大きい場合、前進。
// distance < 10 && distance > 2：距離が2cmより大きく、10cm未満の場合、後退。
// その他の場合：停止。
void loop() {
  float distance = readSensorData();
  if (distance > 25) {
    moveForward(200);
  }
  else if (distance < 10 && distance > 2) {
    moveBackward(200);
  } else {
    stopMove();
  }
}

// トリガーピンに10マイクロ秒のパルス波を送信し、超音波を発信
// エコーピンで反射波の戻り時間を測定
// 音速を利用して距離を計算
float readSensorData() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float distance = pulseIn(echoPin, HIGH) / 58.00; //Equivalent to (340m/s*1us)/2
  return distance;
}


void moveForward(int speed) {
  analogWrite(A_1B, 0);
  analogWrite(A_1A, speed);
  analogWrite(B_1B, 0);
  analogWrite(B_1A, speed);
}

void moveBackward(int speed) {
  analogWrite(A_1B, speed);
  analogWrite(A_1A, 0);
  analogWrite(B_1B, speed);
  analogWrite(B_1A, 0);
}

void stopMove() {
  analogWrite(A_1B, 0);
  analogWrite(A_1A, 0);
  analogWrite(B_1B, 0);
  analogWrite(B_1A, 0);
}
