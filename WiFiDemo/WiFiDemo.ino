#include "WiFi.h"
#include "ArduinoJson.h"
#include "HTTPClient.h"
static DynamicJsonDocument doc(1024);
HTTPClient http;

const char* ssid = "AE86";
const char* password = "Ydhs857878318";
const char* apiServer = "https://api.map.baidu.com/weather/v1/?district_id=510116&data_type=all&ak=lf4xE60gV2B9SwMBexugoZFGrKbwxEij";

static String weathertext;
static int temp;
static int count;

void getWeather(){
  http.begin(apiServer);
  int httpCode = http.GET();
  delay(500);
  if(httpCode == HTTP_CODE_OK){
    String responseData = http.getString();
    deserializeJson(doc, responseData);

    JsonObject result = doc["result"];
    JsonObject now= result["now"];

    weathertext = now["text"].as<String>();
    temp = now["temp"].as<int>();
    Serial.println(weathertext);
    Serial.println(temp);
    Serial.println(responseData);
  }
  http.end();
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("开始连接WiFi！");
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(100);
  }
  Serial.println(WiFi.localIP());
  getWeather();
}

void loop() {
  // put your main code here, to run repeatedly:
  // if(digitalRead(0) == HIGH){
  //   if(WiFi.status() == WL_CONNECTED){
  //     getWeather();
  //     count ++;
  //     Serial.println("\n/n");
  //      Serial.println(count);
  //   }
  //   delay(200);
  // }
  // delay(200);
}
