#ifndef WIFI_SETUP_HPP
#define WIFI_SETUP_HPP

#include <WiFi.h>

struct data_packet{
    uint8_t *data_ptr; 
    uint32_t len; 
    IPAddress remote_ip; 
};

void wifi_setup(void);
void setup_server(void);
data_packet get_latest_data(void);
bool free_packet(data_packet *packet);

#endif 