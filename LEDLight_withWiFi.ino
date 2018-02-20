#include <ESP8266WiFi.h>

const char* ssid = "aterm-912afc-g";
const char* password = "39f9398943819";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

#define BLUELED  4
#define REDLED    5

#define PWMOUT1   12
#define PWMOUT2   13

void setup(void)
{
  pinMode(BLUELED, OUTPUT);
  pinMode(REDLED, OUTPUT);

  analogWrite(PWMOUT1, 0x00);
  analogWrite(PWMOUT2, 0x00);
  
  Serial.begin(115200);
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

//    digitalWrite(BLUELED,HIGH);
//    digitalWrite(REDLED,HIGH);
//    analogWrite(PWMOUT1,i);    max value 0xFF
//    analogWrite(PWMOUT2,i);

void loop(void)
{
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client)return;
  

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available())delay(1);

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // Match the request
  int val;
  if (req.indexOf("/gpio/0") != -1)
    val = 0;
  else if (req.indexOf("/gpio/1") != -1)
    val = 1;
  else 
  {
    Serial.println("invalid request");
    client.stop();
    return;
  }

  // Set GPIO2 according to the request
  analogWrite(PWMOUT1, val*255);
  analogWrite(PWMOUT2, val*255);

  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  s += (val) ? "high" : "low";
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected
  // when the function returns and 'client' object is detroyed

}

