/*
 * Copyright (c) 2015, Majenko Technologies
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 * 
 * * Neither the name of Majenko Technologies nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

/* Set these to your desired credentials. */
const char *ssid = "Lucky";
const char *password = "zainab09";

ESP8266WebServer server(80);

const char INDEX_HTML[] =
 "<h1>You are connected</h1> "
 "<FORM action=\"/test\" method=\"post\">"
  "ssid: <input name=\"ssid\" type=\"text\"> </br>"
  "Password: <input name=\"password\" type=\"text\"> </br>"
 "<INPUT type=\"submit\" value=\"Submit\">" 
  "</FORM>";

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
  Serial.println("1");
  if (server.hasArg("ssid")) {
    Serial.println("2");
     String inputValue;
  inputValue = server.arg("ssid");
    Serial.println("User entered" + inputValue);
   // handleSubmit();
  }
  else {
    Serial.println("3");
    server.send(200, "text/html", INDEX_HTML);
  }
  
}

void handleLow() {
  Serial.println("handleLow");
  digitalWrite(2, LOW); 
}

void handleHigh() {
  Serial.println("handleHigh");
  digitalWrite(2, HIGH); 
}
void handleTest() {
  Serial.println("in Test handler");

  
  /*String ssidlocal;
  String passwordlocal;
  ssidlocal = server.arg("ssid");
  passwordlocal = server.arg("password");
    Serial.println("User entered - ssid: "+ ssidlocal + "password: "+ passwordlocal);


char *ssidChar = new char[ssidlocal.length() + 1];
strcpy(ssidChar, ssidlocal.c_str());

char *pwdChar = new char[passwordlocal.length() + 1];
strcpy(pwdChar, passwordlocal.c_str());


     WiFi.softAP(ssidChar, pwdChar);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  
    server.send(200, "text/html", "User entered - ssid: "+ ssidlocal + "password: "+ passwordlocal + " <br> AP IP address: " + myIP);
*/
   
}

void WiFiEvent(WiFiEvent_t event) {
    Serial.printf("[WiFi-event] event: %d\n", event);
/*
    switch(event) {
        case WIFI_EVENT_STAMODE_GOT_IP:
            Serial.println("WiFi connected");
            Serial.println("IP address: ");
            Serial.println(WiFi.localIP());
            break;
        case WIFI_EVENT_STAMODE_DISCONNECTED:
            Serial.println("WiFi lost connection");
            break;

            case WIFI_EVENT_SOFTAPMODE_STACONNECTED:
            Serial.println("WiFi Connected - WIFI_EVENT_SOFTAPMODE_STACONNECTED");
            break;

            default:
            Serial.println("Default Wifi Event");
    }
    */
}

void setup() {
  pinMode(2, OUTPUT);
	delay(1000);
	Serial.begin(115200);
	Serial.println();
	Serial.print("Configuring access point...");
  
	/* You can remove the password parameter if you want the AP to be open. */
	WiFi.softAP(ssid, password);
WiFi.onEvent(WiFiEvent);
	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);
	server.on("/", handleRoot);
 server.on("/test", handleTest);
 server.on("/low", handleLow);
 server.on("/high", handleHigh);
	server.begin();
 digitalWrite(2, HIGH); 
	Serial.println("HTTP server started");
}

void loop() {
	server.handleClient();
}
