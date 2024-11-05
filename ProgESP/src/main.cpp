#include <Arduino.h>
#include <WiFi.h>
#include <BluetoothSerial.h>
#include <Adafruit_SSD1306.h>
#include "TCPSocket.h"

//#define TestBluetooth
//#define TestCapteur
#define TestEcran
//#define ProgrPrincipal

#ifdef TestBluetooth
BluetoothSerial SerialBT;

void setup() {
  	Serial.begin(115200);
  	SerialBT.begin("ESP32TEST");
}


void loop() {
  	if (Serial.available() > 0) {
   		String line = Serial.readStringUntil('\n');
    
    	SerialBT.print(line);
    	Serial.println("Envoyé via Bluetooth : " + line);
  	}

  	delay(20); 
}
#endif

#ifdef TestCapteur

int moisissure, in_analog_1;
const int PIN = A0;

void setup(){
  	Serial.begin(115200);
  	Serial.println("[+] Liaison Serie initialisee");
}

void loop(){
  	in_analog_1 = analogRead(PIN);
  	moisissure = (100-((in_analog_1/4095.00)*100));
  	Serial.print("Moisissure:");
  	Serial.print(moisissure);
  	Serial.print("%\n");
}
#endif

#ifdef TestEcran


Adafruit_SSD1306 Ecran;

static const unsigned char PROGMEM logo_bluetooth[] = 
{
  B00000011, B10000000,
  B00000011, B11000000,
  B01100011, B01100000,
  B00110011, B00110000,
  B00011011, B00011000,
  B00001111, B00110000,
  B00000111, B01100000,
  B00000011, B11000000,

  B00000011, B11000000,
  B00000111, B01100000,
  B00001111, B00110000,
  B00011011, B00011000,
  B00110011, B00110000,
  B01100011, B01100000,
  B00000011, B11000000,
  B00000011, B10000000,
};


void setup(){

	Ecran.begin(SSD1306_SWITCHCAPVCC, 0x3C);

	Ecran.clearDisplay();
	Ecran.drawBitmap((Ecran.width()  - 16 ) / 2,
    (Ecran.height() - 16) / 2,
    logo_bluetooth, 16, 16, 1);
	Ecran.display();

	Ecran.~Adafruit_SSD1306();
}

void loop(){

}

#endif

#ifdef ProgrPrincipal

BluetoothSerial SerialBT;
String nomWifi, mdpWifi;

void connectToWifi(){
	Serial.println("Envoyez le nom du wifi via bluetooth");

	while(nomWifi.length() == 0){
		nomWifi = SerialBT.readStringUntil('\n');
	}

	nomWifi.trim();

  	Serial.println("Envoyez le mot de passe wifi via bluetooth");

	while(mdpWifi.length() == 0){
  		mdpWifi = SerialBT.readStringUntil('\n');
	}

	mdpWifi.trim();

	WiFi.mode(WIFI_STA);
	WiFi.begin(nomWifi.c_str(), mdpWifi.c_str());

	Serial.println("[+] Connexion en cours");
	while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(200);
    }

	SerialBT.print(WiFi.localIP());
}

unsigned short int getSensorValue() {

    int in_analog_1;
    const int PIN = A0;

    in_analog_1 = analogRead(PIN);
    unsigned short int moisissure = (100-((in_analog_1/4095.00)*100));

    return moisissure;
}

void setup(){
  	Serial.begin(115200);
  	SerialBT.begin("ESP32SENSOR");
  	
	connectToWifi();
	delay(200);

	SerialBT.end();
}

void loop(){
	TCPSocket leSocket;

	leSocket.begin();

	while(1) {
		Serial.println("Waiting for request...");

		if(leSocket.handleConnection()){
			unsigned short int sensorValue = getSensorValue();
			leSocket.sendData(&sensorValue, sizeof(sensorValue));
		}

		delay(500);
	}
}

#endif
