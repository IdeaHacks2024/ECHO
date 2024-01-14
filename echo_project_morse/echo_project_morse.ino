// can set output pin to 13 for testing with builtin LED
const int motorPin = 1;

const int unit = 500;

void setup() {
  // put your setup code here, to run once:
  pinMode(motorPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  String test = "test";
  convert_morse(test);
}

void convert_morse(String audio){
  for(int i = 0; i < audio.length(); i++){
    switch (audio[i]){
      case 'a':
        a();
        break;
      case 'b':
        b();
        break;
      case 'c':
        c();
        break;
      case 'd':
        d();
        break;
      case 'e':
        e();
        break;
      case 'f':
        f();
        break;
      case 'g':
        g();
        break;
      case 'h':
        h();
        break;
      case 'i':
        letter_i();
        break;
      case 'j':
        j();
        break;
      case 'k':
        k();
        break;
      case 'l':
        l();
        break;
      case 'm':
        m();
        break;
      case 'n':
        n();
        break;
      case 'o':
        o();
        break;
      case 'p':
        p();
        break;
      case 'q':
        q();
        break;
      case 'r':
        r();
        break;
      case 's':
        s();
        break;
      case 't':
        t();
        break;
      case 'u':
        u();
        break;
      case 'v':
        v();
        break;
      case 'w':
        w();
        break;
      case 'x':
        x();
        break;
      case 'y':
        y();
        break;
      case 'z':
        z();
        break;
      case ' ':
        next_word();
        break;
      default:
        break;
    }

  }
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

void letter_i(){
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
  digitalWrite(motorPin, HIGH);
  delay(3 * unit);
  digitalWrite(motorPin, LOW);
  delay(1 * unit);
}

void dit() {
  digitalWrite(motorPin, HIGH);
  delay(1 * unit);
  digitalWrite(motorPin, LOW);
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