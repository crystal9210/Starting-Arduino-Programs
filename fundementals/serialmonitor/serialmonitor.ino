// setupルーチンはリセットを押すと一度実行されます:
void setup() {
    // 9600ビット毎秒でシリアル通信を初期化:
    Serial.begin(9600);
}

// loopルーチンは永遠に繰り返し実行されます:
void loop() {
    int number = 100;
    Serial.println(number);
    Serial.println("Hello world");
    delay(100);         // 安定した読み取りのための遅延
}
