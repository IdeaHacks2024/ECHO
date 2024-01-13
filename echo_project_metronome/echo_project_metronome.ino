const int motorPin = 3;

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
    int serial_bpm = Serial.parseInt();
    if (serial_bpm > 0) {
      bpm = serial_bpm;
      Serial.print("BPM set to: ");
      Serial.println(bpm);
    }
  }
  Serial.println(bpm);
  BPM(bpm);
}

void BPM(int bpmUpdate) {
  bpm = bpmUpdate;
  int delayTime = 30000 / bpm;
  digitalWrite(motorPin, HIGH);
  delay(delayTime);
  digitalWrite(motorPin, LOW);
  delay(delayTime);
}
