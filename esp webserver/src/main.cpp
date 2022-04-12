#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "index.h"

//SSID and Password
const char* ssid = "LCC";
const char* password = "Sonnenuhr";

//Define Outputs
#define GPIO0 0 

ESP8266WebServer server(80); //Server on port 80

void setup(void){
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  //Onboard LED port Direction output
  pinMode(GPIO0,OUTPUT); 
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/setColor", setColor);
  server.on("/readColor", readColor);

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();   //handle Client request
}

void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void readColor() {
 
}

void setColor() {
 
}