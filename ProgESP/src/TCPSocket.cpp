#include "TCPSocket.h"

void TCPSocket::begin(){
    Serial.println("[+] Demarrage du serveur");
    server = new WiFiServer(9090);
    server->begin();
}

void TCPSocket::handleConnection(){
    client  = server->available();   
    if(client){
        Serial.println("[+] Client connecte:");
        Serial.print(client.localIP());
    }
}

void TCPSocket::sendData(void *data, size_t size){
    size_t bytes;
    bytes = client.write((uint8_t *)data, size);
    Serial.printf("%d bytes sent", bytes);
}