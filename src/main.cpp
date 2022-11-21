#include <WiFi.h>
#include <PubSubClient.h>

const char ssid[]="AX10 2.4Ghz"; //WiFi name
const char pwd[]="0932230966"; //WiFi password
const char* mqtt_server = "192.168.0.239";
const char* mqtt_id = "ESP32Client";
const char* mqtt_subscribe_topic = "home";

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
}

void wf_connect(){
  WiFi.begin(ssid,pwd); 

  Serial.print("\nWiFi connecting\n\n");

  //當WiFi連線時會回傳WL_CONNECTED，因此跳出迴圈時代表已成功連線
  while(WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
}

void setup(){
  Serial.begin(115200);

  WiFi.mode(WIFI_STA); //set WiFi mode
  wf_connect();
  Serial.print("\nIP:");
  Serial.println(WiFi.localIP()); //load IP
  Serial.print("WiFi RSSI:");
  Serial.println(WiFi.RSSI()); //load WiFi強度
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  client.subscribe(mqtt_subscribe_topic);
  printf("start listening\n");
  client.publish(mqtt_subscribe_topic, "pub test");
}

void loop(){
  client.loop();
}
