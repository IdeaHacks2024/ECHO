#include <SPI.h>
#include <WiFiNINA.h>
#include <Servo.h>

/////// please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "handler";        // your network SSID (name)
char pass[] = "password";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

WiFiServer server(80);

// int base_pin = 2;
// int arm_pin = 3;
int led =  LED_BUILTIN;
int status = WL_IDLE_STATUS;

// int prev_base = 150;

// int ARM_DELAY = 15;
// int ARM_DEL = 1;
// int BASE_DELAY = 10;

const int motorPin = 3;

int unit = 500;
int bpm = 120;

int state = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Enter BPM:");

  Serial.println("Access Point Web Server");
  // pinMode(led, OUTPUT);

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);

  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // by default the local IP address of will be 192.168.4.1
  // you can override it with the following:
  WiFi.config(IPAddress(10, 0, 0, 1));

  // print the network name (SSID);
  Serial.print("Creating access point named: ");
  Serial.println(ssid);

  // Create open network. Change this line if you want to create an WEP network:
  status = WiFi.beginAP(ssid, pass);

  if (status != WL_AP_LISTENING) {
    Serial.println("Creating access point failed");
    // don't continue
    while (true);
  }

  // wait 10 seconds for connection:
  delay(10000);

  // start the web server on port 80
  server.begin();

  // you're connected now, so print out the status
  printWiFiStatus();

  // base.attach(base_pin);
  // arm.attach(arm_pin);

  // base.write(150);
  // arm.write(55);
}

void loop() {
  // put your main code here, to run repeatedly:
  // compare the previous status to the current status
  if (status != WiFi.status()) {

    // it has changed update the variable
    status = WiFi.status();

    if (status == WL_AP_CONNECTED) {
      // a device has connected to the AP
      Serial.println("Device connected to AP");
    } else {
      // a device has disconnected from the AP, and we are back in listening mode
      Serial.println("Device disconnected from AP");
    }

  }

  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client

    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor

        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Select <a href=\"/BUZZ\">Buzz Mode</a> <br><br>");
            client.print("Select <a href=\"/METRONOME\">Metronome Mode</a> <br>");
            client.print("Set Metronome BPM: <br>");
            client.print("<a href=\"/METRO60\">60 BPM</a> <br>");
            client.print("<a href=\"/METRO120\">120 BPM</a> <br>");
            client.print("<a href=\"/METRO180\">180 BPM</a> <br>");
            client.print("<a href=\"/METRO240\">240 BPM</a> <br><br>");
            client.print("Select <a href=\"/MORSE\">Morse Mode</a> <br>");
            client.print("Set Morse Code Time Unit: <br>");
            client.print("<a href=\"/MORSEHALF\">0.5 seconds</a> <br>");
            client.print("<a href=\"/MORSESINGLE\">1 second</a> <br><br>");
            client.print("Select <a href=\"/STOP\">Stop Mode</a> <br><br>");

            // The HTTP response ends with another blank line:
            client.println();

            // break out of the while loop:
            break;
          }

          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }

        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
        
        // sets to buzz mode
        if (currentLine.endsWith("GET /BUZZ")) {
            state = 1;
        }

        // sets to morse code mode
        if (currentLine.endsWith("GET /MORSE")) {
            state = 2;

        }

        if (currentLine.endsWith("GET /METRONOME")) {
          // Serial.print(currentLine);

          // String deg_string = currentLine.substring(currentLine.length()-10, currentLine.length()-7);
          // Serial.print("BPM: ");
          // Serial.println(deg_string);
          // int deg = deg_string.toInt();
          state = 3;
        }

        if (currentLine.endsWith("GET /STOP")) {
          state = -1;
        }

        if (currentLine.endsWith("GET /METRO60")){
          bpm = 60;
        }

        if (currentLine.endsWith("GET /METRO120")){
          bpm = 120;
        }
        
        if (currentLine.endsWith("GET /METRO180")){
          bpm = 180;
        }

        if (currentLine.endsWith("GET /METRO240")){
          bpm = 240;
        }

        if (currentLine.endsWith("GET /MORSEHALF")){
          unit = 500;
        }

        if (currentLine.endsWith("GET /MORSESINGLE")){
          unit = 1000;
        }
      }
    }
  }
  Serial.println(state);

  if (Serial.available() > 0) {
    int serial_bpm = Serial.parseInt();
    if (serial_bpm > 0) {
      bpm = serial_bpm;
      Serial.print("BPM set to: ");
      Serial.println(bpm);
    }
  }

  if (state == 3) {
    Serial.println(bpm);
    BPM(bpm);
  }
  if (state == -1) {
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

void BPM(int bpmUpdate) {
  bpm = bpmUpdate;
  int delayTime = 30000 / bpm;
  digitalWrite(motorPin, HIGH);
  delay(delayTime);
  digitalWrite(motorPin, LOW);
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