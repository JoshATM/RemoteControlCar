#include <WiFi.h>

const char* ssid = "wifi name";
const char* password = "wifi pass";

const int motor1_forward = 2;
const int motor1_backward = 3;
const int motor2_forward = 4;
const int motor2_backward = 5;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  
  pinMode(motor1_forward, OUTPUT);
  pinMode(motor1_backward, OUTPUT);
  pinMode(motor2_forward, OUTPUT);
  pinMode(motor2_backward, OUTPUT);
  
  stopMotors();
  
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
  server.begin();
  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();
  
  if (client) {
    Serial.println("Client connected");
    
    while (client.connected()) {
      if (client.available()) {
        String command = client.readStringUntil('\n');
        command.trim();
        
        Serial.print("Command: ");
        Serial.println(command);
        
        if (command == "FORWARD") {
          moveForward();
        } else if (command == "BACKWARD") {
          moveBackward();
        } else if (command == "LEFT") {
          turnLeft();
        } else if (command == "RIGHT") {
          turnRight();
        } else if (command == "STOP") {
          stopMotors();
        }
        
        client.println("OK");
      }
    }
    
    client.stop();
    Serial.println("Client disconnected");
    stopMotors();
  }
}

void MoveForward() {
  digitalWrite(motor1_forward, LOW);
  digitalWrite(motor1_backward, HIGH);
  digitalWrite(motor2_forward, LOW);
  digitalWrite(motor2_backward, HIGH);
}

void MoveBackward() {
  digitalWrite(motor1_forward, HIGH);
  digitalWrite(motor1_backward, LOW);
  digitalWrite(motor2_forward, HIGH);
  digitalWrite(motor2_backward, LOW);
}

void TurnLeft() {
  digitalWrite(motor1_forward, HIGH);
  digitalWrite(motor1_backward, LOW);
  digitalWrite(motor2_forward, LOW);
  digitalWrite(motor2_backward, HIGH);
}

void TurnRight() {
  digitalWrite(motor1_forward, LOW);
  digitalWrite(motor1_backward, HIGH);
  digitalWrite(motor2_forward, HIGH);
  digitalWrite(motor2_backward, LOW);
}

void StopMotors() {
  digitalWrite(motor1_forward, LOW);
  digitalWrite(motor1_backward, LOW);
  digitalWrite(motor2_forward, LOW);
  digitalWrite(motor2_backward, LOW);
}
