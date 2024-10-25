// LEDライトが一定間隔で強くなり、消えて、また、弱い光から強くなる、の繰り返し処理
int ledPin = 9;

void setup() {

}

void loop() {
  for(int value=0;value<=255;value+=10){
    analogWrite(ledPin, value);
    delay(30);
  }
}
