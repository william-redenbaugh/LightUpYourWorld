#include "wifi_server.hpp"

// Replace with your network credentials
const char* ssid = "GoogleWatchesUsAll";
const char* password = "rapidpiano738";

void wifi_setup(void){
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    // Wait until we are connected
    while(WiFi.status() != WL_CONNECTED)
        vTaskDelay(100 / portTICK_PERIOD_MS);
}