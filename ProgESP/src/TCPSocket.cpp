#include "TCPSocket.h"

void TCPSocket::begin(){
    Serial.println("[+] Demarrage du serveur");
    server = new WiFiServer(9090);
    server->begin();
}

bool TCPSocket::handleConnection(){
    client  = server->available();   
    if(client){
        Serial.printf("[+] Client trouve: %s", client.localIP());
    }
}

void TCPSocket::sendData(void *data, size_t size){
    size_t bytes;
    bytes = client.write((uint8_t *)data, size);
    Serial.printf("[+] %d bytes sent\n", bytes);
}