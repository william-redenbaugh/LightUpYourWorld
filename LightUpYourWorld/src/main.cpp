#include <Arduino.h>
#include "wifi_server.hpp"
#include "led_animations.h"
#include <FastLED.h>

Color current_color = {0, 30, 0}; 
led_animations current_animation = BREATHING; 
volatile bool update_animation = false; 

// How many leds in your strip?
#define NUM_LEDS 4

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 4

// Define the array of leds
CRGB leds[NUM_LEDS];

void static_color_update(void){
  CRGB col; 
  col.red = current_color.red;
  col.green = current_color.green;
  col.blue = current_color.blue;
  for(int n = 0; n < NUM_LEDS; n++)
    leds[n] = col; 
  FastLED.show(); 
}

void set_all_hsv(CHSV col){
  for(int n = 0; n < NUM_LEDS; n++)
    leds[n] = col; 

  FastLED.show(); 
}

TaskHandle_t led_thread_handler; 
void led_thread(void *parameters){
  
  CHSV current_col; 
  CHSV primary_col; 

  bool breathing_up = false; 
  update_animation = true; 
  for(;;){
      
      for
  }
}

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  // Start blue light indicating that we are booting up. 
  CRGB col; 
  memset(&col, 0, sizeof(CRGB)); 
  col.blue = 30;
  for(int n = 0; n < NUM_LEDS; n++)
    leds[n] = col; 
  FastLED.show(); 

  // For logging
  Serial.begin(115200); 
  wifi_setup();
  setup_server();
  
  static_color_update();
  delay(1000);

  // Generate the LED animation thread.  
  xTaskCreate(led_thread, "LED Thread", 15000, NULL, 0, &led_thread_handler); 
}

void loop() {
  data_packet packet = get_latest_data();

  // If we have any new data coming in. 
  if((packet.data_ptr != nullptr) && packet.len){
    
    // Enumated list of animations
    if(packet.len == 1){
      led_animations animation = (led_animations)packet.data_ptr[0];
      current_animation = animation; 
      switch(animation){
      // Update to current color
      case(STATIC):
      static_color_update(); 
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

