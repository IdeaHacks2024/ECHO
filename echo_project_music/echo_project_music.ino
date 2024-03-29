/*
  by Tom Igoe
  adapted to WiFi AP by Adafruit
*/

#include <SPI.h>
#include <WiFiNINA.h>
// #include <Servo.h>

/////// please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "hand";        // your network SSID (name)
char pass[] = "password";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                // your network key Index number (needed only for WEP)

// int base_pin = 2;
int buzz = 3;
// Servo base;
// Servo arm;
int led =  LED_BUILTIN;
int status = WL_IDLE_STATUS;

int prev_base = 150;

int ARM_DELAY = 15;
// int ARM_DEL = 1;
int BASE_DELAY = 10;

WiFiServer server(80);

void setup() {

  Serial.println("Access Point Web Server");
  pinMode(led, OUTPUT);      // set the LED pin mode
  pinMode(buzz, OUTPUT);

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

//   base.attach(base_pin);
//   arm.attach(arm_pin);

//   base.write(150);
//   arm.write(55);
}

void loop() {

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
            client.print("Click <a href=\"/BUZZ\">here</a> BUZZ<br>");
            client.print("Click <a href=\"/LOWER\">here</a> turn the LED off<br>");

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
        
        // raise arm
        if (currentLine.endsWith("GET /BUZZ")) {
            digitalWrite(buzz, HIGH);
            delay(100);
            digitalWrite(buzz, LOW);
        }

        // lower arm
        if (currentLine.endsWith("GET /LOWER")) {
            // TODO: next action

        }

        // base rotate to X degree
        // Serial.print("cur line: ");
        // Serial.println(currentLine);
        // Serial.print("request: ");
        // Serial.println(currentLine.startsWith(currentLine.substring(16)));
        if (currentLine.endsWith("_ROTATE"))
        {
          Serial.print(currentLine);

          String deg_string = currentLine.substring(currentLine.length()-10, currentLine.length()-7);
          Serial.print("degree: ");
          Serial.println(deg_string);
          int deg = deg_string.toInt();

          // TODO: action afterwards

        }
      }
    }

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