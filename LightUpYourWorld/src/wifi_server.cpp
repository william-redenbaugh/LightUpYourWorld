#include "wifi_server.hpp"

WiFiServer wifiServer(80);

void setup_server(void){
    wifiServer.begin();
}

data_packet get_latest_data(void){
    WiFiClient client = wifiServer.available();
    data_packet packet; 
    memset(&packet, 0, sizeof(data_packet));
    // If there is data, create a buffer for the packet and output to it. 
    if(!client.available())
        goto end; 

    packet.len = client.available(); 
    packet.remote_ip = client.remoteIP(); 
    client.read(packet.data_ptr, packet.len);
    packet.data_ptr = (uint8_t*)malloc(sizeof(uint8_t) * packet.len);
    
end: 
    return packet; 

}

bool free_packet(data_packet *packet){
    if(packet->data_ptr != nullptr)
        free(packet->data_ptr);
    
    return true; 
}