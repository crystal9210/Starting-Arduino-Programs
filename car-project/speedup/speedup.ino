const int A_1B = 5;
const int A_1A = 6;
const int B_1B = 9;
const int B_1A = 10;

void setup() {
  pinMode(A_1B, OUTPUT);
  pinMode(A_1A, OUTPUT);
  pinMode(B_1B, OUTPUT);
  pinMode(B_1A, OUTPUT);
}

void loop() {
  for(int i=0;i<=255;i+=5){
    moveForward(i);
    delay(500);
  }
  for(int i=255;i>=0;i-=5){
    moveForward(i);
    delay(500);
  }
}

void moveForward(int speed) {
  analogWrite(A_1B, 0);     // モーターAの一方をLOW
  analogWrite(A_1A, speed); // モーターAの他方をHIGH（speed）
  analogWrite(B_1B, 0);     // モーターBの一方をLOW（修正）
  analogWrite(B_1A, speed); // モーターBの他方をHIGH（speed）（修正）
}

