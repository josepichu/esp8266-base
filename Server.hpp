#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

AsyncWebServer server(80);

// send sensor info
void getData(AsyncWebServerRequest *request)
{

   AsyncResponseStream *response = request->beginResponseStream("application/json");
    
   int data = getSensorData();
   StaticJsonDocument<300> jsonDoc;
   jsonDoc["id"] = random(0,10);
   jsonDoc["data"] = data;
   serializeJson(jsonDoc, *response);
   
   request->send(response);
}

void InitServer() 
{

// Route for root / web page
//   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
//     request->send(SPIFFS, "/index.html", String(), false, processor);
//   });

   server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

   server.on("/getData", HTTP_GET, getData);

	server.onNotFound([](AsyncWebServerRequest *request) {
		request->send(400, "text/plain", "Not found");
	});

	server.begin();

   Serial.println("HTTP server started");
}