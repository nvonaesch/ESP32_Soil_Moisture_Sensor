#include "TCPSocket.h"

//Démarre le serveur sur le port 9090
void TCPSocket::begin(){
    Serial.println("\n[+] Demarrage du serveur");
    server = new WiFiServer(9090);
    server->begin();
}

//Renvoie vrai si un client est trouvé
bool TCPSocket::handleConnection(){
    client  = server->available();   
    if(client){
        Serial.printf("[+] Client trouve: %s\n", client.localIP().toString());
        return true;
    }
    return false;
}

//Envoie les données au client
void TCPSocket::sendData(void *data, size_t size){
    size_t bytes;
    bytes = client.write((uint8_t *)data, size);
    Serial.printf("[+] %d bytes sent\n", bytes);
}