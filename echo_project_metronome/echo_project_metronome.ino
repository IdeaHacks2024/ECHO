const int motorPin = 1;

int bpm = 120;

void setup() {
  // put your setup code here, to run once:
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Enter BPM:");
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
  analogWrite(motorPin, 150);
  delay(delayTime);
}
