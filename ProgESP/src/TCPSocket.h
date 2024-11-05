#include <WiFiServer.h>
class WiFiServer;
class WiFiClient;

class TCPSocket {

    private:
        WiFiServer *server = NULL;
        WiFiClient client;

    public:
        void begin();
        void handleConnection();
        void sendData(void *data, size_t size);

};

