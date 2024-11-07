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

//Bitmap représentant le logo Bluetooth
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


static const unsigned char PROGMEM logo_wifi[] = {
  B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000,
  B00000000, B11111111, B00000000,
  B00000111, B00000000, B11100000,
  B00011000, B00111100, B00011000,
  B00000000, B11000011, B00000000,
  B00000000, B00000000, B00000000,
  B00000000, B00011000, B00000000,
};

void setup(){
	//Initialisation de la communication via le bus I2C à l'adresse 0x3C
	Ecran.begin(SSD1306_SWITCHCAPVCC, 0x3C);

	//Efface l'écran
	Ecran.clearDisplay();
	
	//Ecrit sur l'écran la bitmap "logo_bluetooth"
	Ecran.drawBitmap((Ecran.width()  - 24 ) / 2, // Position X
    (Ecran.height() - 8) / 2, 					 // Position Y
    logo_wifi, 24, 8, 1); // Bitmap, Longueur, Largeur, Couleur
	//Rafraichit l'écran affichant donc la bitmap
	Ecran.display();

	//Déstruction de l'objet écran
	Ecran.~Adafruit_SSD1306();
}

void loop(){

}

#endif

#ifdef ProgrPrincipal

BluetoothSerial SerialBT;
String nomWifi, mdpWifi;

//Demande à recevoir en bluetooth les logs du WiFi, se connecte à celui-ci 
//puis renvoie en bluetooth son adresse ip associée
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

	//PIN A0 Capteur vers PIN VP Board
    int in_analog_1;
    const int PIN = A0;

	//Convertion de la valeur du capteur en pourcentage
    in_analog_1 = analogRead(PIN);
    unsigned short int moisissure = (100-((in_analog_1/4095.00)*100));

    return moisissure;
}

void setup(){
	//Initialisation de la liaison série et du bluetooth
  	Serial.begin(115200);
  	SerialBT.begin("ESP32SENSOR");
  	
	//L'on se connecte au Wi-Fi
	connectToWifi();

	//Delai nécessaire pour que la transmission de l'adresse ip assignée par le réseau 
	//soit entierement envoyée sur le bluetooth
	delay(200);

	//Fin de la transmission bluetooth
	SerialBT.end();
}

void loop(){
	//Crée un Serveur TCP sur le port 9090
	TCPSocket leSocket;
	leSocket.begin();

	while(1) {
		Serial.println("Waiting for request...");

		//Si un client se connecte alors l'on lui envoie les valeurs du capteurs
		if(leSocket.handleConnection()){
			unsigned short int sensorValue = getSensorValue();
			leSocket.sendData(&sensorValue, sizeof(sensorValue));
		}

		delay(500);
	}
}

#endif
