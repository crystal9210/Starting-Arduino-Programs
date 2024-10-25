// デジタルライト:デジタル信号をデジタルピンに出力または書き込む
// デジタル信号には0or1 i.e. 0[V]or5[V]の二つの状態しかないため、LED・ブザーなどのコンポーネントをオン/オフにできる

// the number of the LED pin
const int ledPin = 9;

void setup() {
  pinMode(ledPin, OUTPUT); // デジタルピンを出力として設定
}

// the loop routine runs over and over again forever
void loop() {
  digitalWrite(ledPin, HIGH); // デジタルピンをオンに設定
  delay(1000); // wait for a second
  digitalWrite(ledPin, LOW); // set the status of the digital pin as off
  delay(1000); // wait for a second
}