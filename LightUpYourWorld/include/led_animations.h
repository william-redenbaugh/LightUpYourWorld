#ifndef _LED_ANIMATIONS_H
#define _LED_ANIMATIONS_H 

enum  led_animations{
    STATIC, 
    FLOATING, 
    BREATHING
};

struct Color{
    uint8_t red; 
    uint8_t green; 
    uint8_t blue; 
}; 


#endif 