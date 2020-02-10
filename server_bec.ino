#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

char ssid[] = "***";
char pass[] = "***";

int led = 2;   // led connected to GPIO2 (D4)
int relay = 5; //d1
int onOff = 0;
String label;

void handleRoot() {
  server.send(200, "text / plain", "Hello world");
}

void setup() {
  Serial.begin(115200); 

  pinMode(led, OUTPUT); 
  pinMode(relay, OUTPUT); 
  digitalWrite(led, LOW);
  digitalWrite(relay, HIGH);
  
  WiFi.begin(ssid, pass); 
  Serial.println("Connecting .");
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  server.on("/", handleRootPath); 
  server.on("/other", []() {
    server.send(200, "text/html", "Other URL");
  });

  server.begin(); 
  Serial.println(WiFi.localIP());
}

void loop() {
  server.handleClient();
}

void handleRootPath() {    
  if(onOff == 0){
     digitalWrite(led, HIGH);
     digitalWrite(relay, LOW);  
     onOff = 1;  
     label = "aprins"; 
  } else {
    digitalWrite(led, LOW);
    digitalWrite(relay, HIGH);
    onOff = 0;
    label = "stins";
  }
  server.send(200, "text/html", "<div style='color: #00f;'>" + label + "</div>");

}
