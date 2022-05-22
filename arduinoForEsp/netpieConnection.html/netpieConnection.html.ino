#include <MicroGear.h>
#include <ESP8266WiFi.h>

// constants won't change. They're used here to 
// set pin numbers:
#define D1 5  
#define Switch D1        // the number of the switch pin

#define D2 4 // USER LED Wake
#define LedPin D2 

const char* ssid     = "BASS";
const char* password = "uwiz8455";

#define APPID   "ConnectionTest"
#define KEY     "zU6E7PNF4PxoWNs"
#define SECRET  "LtIQNOri7vjQS0pfsRgAHtHhK"

#define ALIAS   "esp"
#define TargetWeb "htmlKey2"

String state = "0";
int long_press = 0;
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
    digitalWrite(LedPin, HIGH);
    state="1";
    //microgear.chat(TargetWeb, "10");
  } 
  else if (stateStr == "OFF") 
  {
    digitalWrite(LedPin, LOW);
    state="0";
    //microgear.chat(TargetWeb, "900");
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

    Serial.begin(115200);
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

    pinMode(Switch,INPUT_PULLUP);
    pinMode(LedPin,OUTPUT);
    digitalWrite(LedPin,LOW); // Turn off LED
}

void loop() 
{
  if(microgear.connected()) 
  {
    microgear.loop();
    Serial.println("connect...");

    if(digitalRead(D1)==1){
      if(state=="0"&&long_press==0)state="1";
      else if(state=="1" && long_press==0) state="0";
      long_press=1;
      microgear.chat(TargetWeb,state);
      Serial.println(state);
    }
    else
    {
      long_press=0;
    }
    
  } 
  else 
  {
    Serial.println("connection lost, reconnect...");
    microgear.connect(APPID);
  }
  delay(250);
}
