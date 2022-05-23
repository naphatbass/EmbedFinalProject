#include <MicroGear.h>
#include <ESP8266WiFi.h>
#include <Wire.h>

const char* ssid     = "BASS";
const char* password = "uwiz8455";

#define APPID   "ConnectionTest"
#define KEY     "zU6E7PNF4PxoWNs"
#define SECRET  "LtIQNOri7vjQS0pfsRgAHtHhK"

#define ALIAS   "esp"
#define TargetWeb "htmlKey2"

WiFiClient client;
MicroGear microgear(client);

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) 
{
  Serial.print("Incoming message --> ");
  Serial.print(topic);
  Serial.print(" : ");
  char strState[msglen];
  for (int i = 0; i < msglen; i++) 
  {
    strState[i] = (char)msg[i];
    Serial.print((char)msg[i]);
  }
  Serial.println();

  String stateStr = String(strState).substring(0, msglen);

  if(stateStr == "ON") 
  {
    //Serial.println(stateStr);
  } 
  else if (stateStr == "OFF") 
  {
    //Serial.println(stateStr);
  }
}

void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) 
{
  Serial.println("Connected to NETPIE...");
  microgear.setAlias(ALIAS);
}
void setup()
{
  /* Event listener */
    microgear.on(MESSAGE,onMsghandler);
    microgear.on(CONNECTED,onConnected);

    Serial.begin(9600);
    Serial.println("Starting...");

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
       delay(250);
       Serial.print(".");
    }

    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    microgear.init(KEY,SECRET,ALIAS);

    Serial.println("microgear init");
    
    microgear.connect(APPID);

    Serial.println("AppID connected");
    
  Wire.begin();
 
}
char button_state='0';
 
void loop()
{
  /*if(microgear.connected()) 
  {
    microgear.loop();
    Serial.println("connect...");
  } 
  else 
  {
    Serial.println("connection lost, reconnect...");
    microgear.connect(APPID);
  }
  */

  Wire.requestFrom(1, 7);    // request 7 bytes from peripheral device #1

  while (Wire.available()) { // peripheral may send less than requested
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
    button_state=c;
  }
  Serial.println();
  if(button_state=='0')microgear.chat(TargetWeb,"0");
  else microgear.chat(TargetWeb,"1");
  delay(1000);
}
