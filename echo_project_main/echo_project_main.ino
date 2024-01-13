const int unit = 500;

const int motorPin = 1;
int bpm = 120;

void setup() {
  // put your setup code here, to run once:
  pinMode(motorPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    bpm = Serial.parseInt();
    if (bpm > 0) {
      Serial.print("BPM set to: ");
      Serial.println(bpm);
    }
  }
  BPM(bpm);
}

void BPM(int bpmUpdate) {
  bpm = bpmUpdate;
  int delayTime = 30000 / bpm;
  analogWrite(motorPin, 150);
  delay(delayTime);
  analogWrite(motorPin, 0);
  delay(delayTime);
}

void a() {
  dit();
  dah();
  next_letter();
}

void b() {
  dah();
  dit();
  dit();
  dit();
  next_letter();
}

void c(){
  dah();
  dit();
  dah();
  dit();
  next_letter();
}

void d() {
  dah();
  dit();
  dit();
  next_letter();
}

void e() {
  dit();
  next_letter();
}

void f(){
  dit();
  dit();
  dah();
  dit();
  next_letter();
}

void g() {
  dah();
  dah();
  dit();
  next_letter();
}

void h() {
  dit();
  dit();
  dit();
  dit();
  next_letter();
}

void i(){
  dit();
  dit();
  next_letter();
}

void j() {
  dit();
  dah();
  dah();
  dah();
  next_letter();
}

void k() {
  dah();
  dit();
  dah();
  next_letter();
}

void l(){
  dit();
  dah();
  dit();
  dit();
  next_letter();
}

void m() {
  dah();
  dah();
  next_letter();
}

void n() {
  dah();
  dit();
  next_letter();
}

void o(){
  dah();
  dah();
  dah();
  next_letter();
}

void p() {
  dit();
  dah();
  dah();
  dit();
  next_letter();
}

void q() {
  dah();
  dah();
  dit();
  dah();
  next_letter();
}

void r(){
  dit();
  dah();
  dit();
  next_letter();
}

void s() {
  dit();
  dit();
  dit();
  next_letter();
}

void t() {
  dah();
  next_letter();
}

void u(){
  dit();
  dit();
  dah();
  next_letter();
}

void v() {
  dit();
  dit();
  dit();
  dah();
  next_letter();
}

void w() {
  dit();
  dah();
  dah();
  next_letter();
}

void x(){
  dah();
  dit();
  dit();
  dah();
  next_letter();
}

void y() {
  dah();
  dit();
  dah();
  dah();
  next_letter();
}

void z() {
  dah();
  dah();
  dit();
  dit();
  next_letter();
}

void num0(){
  dah();
  dah();
  dah();
  dah();
  dah();
  next_letter();
}

void num1() {
  dit();
  dah();
  dah();
  dah();
  dah();
  next_letter();
}

void num2() {
  dit();
  dit();
  dah();
  dah();
  dah();
  next_letter();
}

void num3(){
  dit();
  dit();
  dit();
  dah();
  dah();
  next_letter();
}

void num4() {
  dit();
  dit();
  dit();
  dit();
  dah();
  next_letter();
}

void num5(){
  dit();
  dit();
  dit();
  dit();
  dit();
  next_letter();
}

void num6() {
  dah();
  dit();
  dit();
  dit();
  dit();
  next_letter();
}

void num7(){
  dah();
  dah();
  dit();
  dit();
  dit();
  next_letter();
}

void num8() {
  dah();
  dah();
  dah();
  dit();
  dit();
  next_letter();
}

void num9(){
  dah();
  dah();
  dah();
  dah();
  dit();
  next_letter();
}

void dah() {
  analogWrite(motorPin, 150);
  delay(3 * unit);
  analogWrite(motorPin, 0);
  delay(1 * unit);
}

void dit() {
  analogWrite(motorPin, 150);
  delay(1 * unit);
  analogWrite(motorPin, 0);
  delay(1 * unit);
}


void next_letter(){
  delay(2 * unit);
  // already 1 unit delayed from dit or dah
}

void next_word(){
  delay(6 * unit);
  // already 1 unit delayed from dit or dah
}