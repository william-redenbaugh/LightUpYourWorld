#include <Arduino.h>
#include "wifi_server.hpp"
#include <FastLED.h>

void setup() {
  wifi_setup();
  setup_server(); 
}

void loop() {
  data_packet packet = get_latest_data();

  // If we have any new data coming in. 
  if((packet.data_ptr != nullptr) && packet.len){
    
    // Enumated list of animations
    if(packet.len == 1){

    }
    // Set primary color
    if(packet.len == 3){
    }

  }
  free_packet(&packet); 
  delay(100);
}