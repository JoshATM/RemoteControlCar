#include <WiFi.h>

const char* ssid = "WIFI NAME";
const char* password = "WIFI PASSWORD";

WiFiServer server(80);

const int motor1_forward = 3;
const int motor1_backward = 2;
const int motor2_forward = 5;
const int motor2_backward = 4;

void setup() {
  Serial.begin(115200);
  
  pinMode(motor1_forward, OUTPUT);
  pinMode(motor1_backward, OUTPUT);
  pinMode(motor2_forward, OUTPUT);
  pinMode(motor2_backward, OUTPUT);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConnected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  
  if (client) {
    String command = "";
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {
          command.trim();
          executeCommand(command);
          client.println("OK");
          command = "";
        } else {
          command += c;
        }
      }
    }
    client.stop();
  }
}

void executeCommand(String cmd) {
  digitalWrite(motor1_forward, LOW);
  digitalWrite(motor1_backward, LOW);
  digitalWrite(motor2_forward, LOW);
  digitalWrite(motor2_backward, LOW);
  
  if (cmd == "FORWARD") {
    digitalWrite(motor1_forward, HIGH);
    digitalWrite(motor2_forward, HIGH);
  } 
  else if (cmd == "BACKWARD") {
    digitalWrite(motor1_backward, HIGH);
    digitalWrite(motor2_backward, HIGH);
  } 
  else if (cmd == "LEFT") {
    digitalWrite(motor1_backward, HIGH);
    digitalWrite(motor2_forward, HIGH);
  } 
  else if (cmd == "RIGHT") {
    digitalWrite(motor1_forward, HIGH);
    digitalWrite(motor2_backward, HIGH);
  }
  
  Serial.println(cmd);
}
