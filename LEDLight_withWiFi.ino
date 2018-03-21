#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "4CE676F701EA";
const char* password = "116mt8vyhx91w";

// Create an instance of the server
// specify the port to listen on as an argument
ESP8266WebServer server(80);

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

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Print the IP address
  Serial.println(WiFi.localIP());
  
  if(MDNS.begin("LED_WIFI"))
      Serial.println("MDNS responder started\nLet's access http://LED_WIFI.local");

  // Start the server
  server.on("/",root);
  server.on("/on",on_LED);
  server.on("/off",off_LED);
  server.begin();
  Serial.println ( "HTTP server started" );
  
}

//    digitalWrite(BLUELED,HIGH);
//    digitalWrite(REDLED,HIGH);
//    analogWrite(PWMOUT1,i);    max value 0xFF
//    analogWrite(PWMOUT2,i);

void root(void)
{
  String s = server.arg("Status");
  int val1 = server.arg("blight1").toInt();
  int val2 = server.arg("blight2").toInt();
   if (s == "on")
    {
       analogWrite(PWMOUT1, val1);
       analogWrite(PWMOUT2, val2);
     } 
     else
     {
       analogWrite(PWMOUT1, val1);
       analogWrite(PWMOUT2, val2);
     }
  char temp[2000];
  snprintf(temp, 2000,

 "<html>\
  <head>\
    <!--<meta http-equiv='refresh' content='5'/>-->\
    <title>ESP8266 test page</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <form action='http://LED_WIFI.local' method='post'>\
        <input type='radio' name='Status'value='on' />\
        <input type='range' name='blight1' max='255' min='0' value='0'/><br>\
        <input type='radio' name='Status'value='off'/>\
        <input type='range' name='blight2' max='255' min='0' value='0'/><br>\
        <input type='submit' value='send'>\
    </form>\
</body>\
</html>");

  server.send(200,"text/html",temp);
}

void on_LED(void)
{
  // Set GPIO2 according to the request
  analogWrite(PWMOUT1, 255);
  analogWrite(PWMOUT2, 255);
}

void off_LED(void)
{
  // Set GPIO2 according to the request
  analogWrite(PWMOUT1, 0);
  analogWrite(PWMOUT2, 0);
}
void loop(void)
{
  server.handleClient();

}

