#include <Arduino.h>
#include "wifi_server.hpp"
#include "led_animations.h"
#include <FastLED.h>

Color current_color = {0, 0, 0}; 

// How many leds in your strip?
#define NUM_LEDS 40

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 3

// Define the array of leds
CRGB leds[NUM_LEDS];


void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  wifi_setup();
  setup_server(); 
}

void loop() {
  data_packet packet = get_latest_data();

  // If we have any new data coming in. 
  if((packet.data_ptr != nullptr) && packet.len){
    
    // Enumated list of animations
    if(packet.len == 1){
      led_animations animation = (led_animations)packet.data_ptr[0];
      switch(animation){
      // Update to current color
      case(STATIC):{
        CRGB col; 
        col.red = current_color.red;
        col.green = current_color.green;
        col.blue = current_color.blue;

        for(int n = 0; n < NUM_LEDS; n++)
          leds[n] = col; 
        FastLED.show(); 
      }
      break; 
      default:
      break; 
      }
    }
    // Set primary color
    if(packet.len == 3){
      current_color.red = packet.data_ptr[0];
      current_color.green = packet.data_ptr[1];
      current_color.blue = packet.data_ptr[2];
    }

  }
  free_packet(&packet); 
  delay(100);
}