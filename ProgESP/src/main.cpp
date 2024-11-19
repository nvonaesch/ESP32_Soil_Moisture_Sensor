//Utiliser git:
//git add .
//git commit -m "le message"
//git push https://github.com/nvonaesch/ESP32_Soil_Moisture_Sensor main

#include <Arduino.h>
#include <WiFi.h>
#include <BluetoothSerial.h>
#include <Adafruit_SSD1306.h>
#include <Preferences.h>
#include "TCPSocket.h"


//#define TestBluetooth
//#define TestCapteur
//#define TestEcran
//#define  TestGarderLogs
#define TestAppuiBouton
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
  B00000000, B00000000, B00111111, B11000000,B00000000,
  B00000000, B00000000, B00111100, B00111000,B00000000,
  B00000000, B00000000, B00111100, B00000111,B00000000,
  B00000000, B00000000, B00111100, B00000000,B11100000,
  B00000000, B00000000, B00111100, B00000000,B00011100,
  B00000000, B00000000, B00111100, B00000000,B00000111,
  B00000000, B00000000, B00111100, B00000000,B00000111,
  B00011110, B00000000, B00111100, B00000000,B00011100,

  B00000011, B10000000, B00111100, B00000000,B11100000,
  B00000000, B01110000, B00111100, B00001111,B00000000,
  B00000000, B00011100, B00111100, B00111000,B00000000,
  B00000000, B00000111, B11111111, B11100000,B00000000,
  B00000000, B00000000, B11111111, B11100000,B00000000,
  B00000000, B00000111, B00111100, B00111000,B00000000,
  B00000000, B00011100, B00111100, B00001111,B00000000,
  B00000000, B01110000, B00111100, B00000000,B11100000,

  B00000011, B10000000, B00111100, B00000000,B00011100,
  B00011110, B00000000, B00111100, B00000000,B00000111,
  B00000000, B00000000, B00111100, B00000000,B00000111,
  B00000000, B00000000, B00111100, B00000000,B00011100,
  B00000000, B00000000, B00111100, B00000000,B11100000,
  B00000000, B00000000, B00111100, B00000111,B00000000,
  B00000000, B00000000, B00111100, B00111000,B00000000,
  B00000000, B00000000, B00111111, B11000000,B00000000,
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
	
	//Ecrit sur l'écran la bitmap "logo_bluetooth" ecran 128x64, pos départ huat gauche (0,0)
	Ecran.drawBitmap((Ecran.width()-130) / 2, // Position X
    (Ecran.height() - 24) / 2, 					 // Position Y
    logo_bluetooth, 40, 24, 1); // Bitmap, Longueur, Largeur, Couleur
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

Adafruit_SSD1306 Ecran;

//Bitmap représentant le logo Bluetooth
static const unsigned char PROGMEM logo_bluetooth[] = 
{
  B00000000, B00000000, B00111111, B11000000,B00000000,
  B00000000, B00000000, B00111100, B00111000,B00000000,
  B00000000, B00000000, B00111100, B00000111,B00000000,
  B00000000, B00000000, B00111100, B00000000,B11100000,
  B00000000, B00000000, B00111100, B00000000,B00011100,
  B00000000, B00000000, B00111100, B00000000,B00000111,
  B00000000, B00000000, B00111100, B00000000,B00000111,
  B00011110, B00000000, B00111100, B00000000,B00011100,

  B00000011, B10000000, B00111100, B00000000,B11100000,
  B00000000, B01110000, B00111100, B00001111,B00000000,
  B00000000, B00011100, B00111100, B00111000,B00000000,
  B00000000, B00000111, B11111111, B11100000,B00000000,
  B00000000, B00000000, B11111111, B11100000,B00000000,
  B00000000, B00000111, B00111100, B00111000,B00000000,
  B00000000, B00011100, B00111100, B00001111,B00000000,
  B00000000, B01110000, B00111100, B00000000,B11100000,

  B00000011, B10000000, B00111100, B00000000,B00011100,
  B00011110, B00000000, B00111100, B00000000,B00000111,
  B00000000, B00000000, B00111100, B00000000,B00000111,
  B00000000, B00000000, B00111100, B00000000,B00011100,
  B00000000, B00000000, B00111100, B00000000,B11100000,
  B00000000, B00000000, B00111100, B00000111,B00000000,
  B00000000, B00000000, B00111100, B00111000,B00000000,
  B00000000, B00000000, B00111111, B11000000,B00000000,
};

static const unsigned char PROGMEM logo_wifi[] = {
  B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00111100,B00000000,B00000000,
  B00000000,B00001111,B11111111,B11110000,B00000000,
  B00000000,B11111100,B00000000,B00111111,B00000000,
  B00001111,B11000000,B00000000,B00000011,B11110000,
  B11111111,B00000000,B00000000,B00000000,B11111111,

  B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00111100,B00000000,B00000000,
  B00000000,B00001111,B11111111,B11110000,B00000000,
  B00000000,B11111100,B00000000,B00111111,B00000000,
  B00001111,B11000000,B00000000,B00000011,B11110000,
  B00000000,B00000000,B00000000,B00000000,B00000000,

  B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B11111111,B00000000,B00000000,
  B00000000,B00000000,B11111111,B00000000,B00000000,
  B00000000,B00000000,B11111111,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,
};

void afficheLogoWIFI(Adafruit_SSD1306 Ecran){
	//Ecrit sur l'écran la bitmap "logo_bluetooth" ecran 128x64, pos départ haut gauche (0,0)
	Ecran.drawBitmap((Ecran.width()-130) / 2, 	 // Position X
    (Ecran.height() - 24) / 2, 					 // Position Y
    logo_wifi, 40, 24, 1); 						 // Bitmap, Longueur, Largeur, Couleur
												 //Rafraichit l'écran affichant donc la bitmap
}

//Demande à recevoir en bluetooth les logs du WiFi, se connecte à celui-ci 
//puis renvoie en bluetooth son adresse ip associée
void connectToWifi(Adafruit_SSD1306 Ecran){
	
	Ecran.clearDisplay();
	afficheLogoWIFI(Ecran);

	Ecran.setTextSize(1);
	Ecran.setTextColor(WHITE);
	Ecran.setCursor(60,3);
	Ecran.println("Attente");
	Ecran.setCursor(60,13);
	Ecran.println("informations");
	Ecran.setCursor(60,23);
	Ecran.println("WIFI");
	//Serial.println("Envoyez le nom du wifi via bluetooth");
	Ecran.display();

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

	afficheLogoWIFI(Ecran);
	Ecran.setTextSize(1);
	Ecran.setTextColor(WHITE);
	Ecran.setCursor(60,3);
	Ecran.println("Connexion");
	Ecran.setCursor(60,13);
	Ecran.println("WIFI");
	Ecran.setCursor(60,23);
	Ecran.println("en cours");
	//Serial.println("Envoyez le nom du wifi via bluetooth");
	Ecran.display();

	//Serial.println("[+] Connexion en cours");
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

void affichageBluetooth(){

	Ecran.clearDisplay();
	//Ecrit sur l'écran la bitmap "logo_bluetooth" ecran 128x64, pos départ huat gauche (0,0)
	Ecran.drawBitmap((Ecran.width()-130) / 2, // Position X
    (Ecran.height() - 24) / 2, 					 // Position Y
    logo_bluetooth, 40, 24, 1); // Bitmap, Longueur, Largeur, Couleur
	//Rafraichit l'écran affichant donc la bitmap

	Ecran.setTextSize(1);
	Ecran.setTextColor(WHITE);
	Ecran.setCursor(60,3);
	Ecran.println("Connexion");
	Ecran.setCursor(60,13);
	Ecran.println("bluetooth");
	Ecran.setCursor(60,23);
	Ecran.println("active");

	Ecran.display();
}

void waitingText(){

	Ecran.clearDisplay();
	Ecran.setTextSize(1);
	Ecran.setTextColor(WHITE);
	Ecran.setCursor(60,3);
	Ecran.println("Waiting");
	Ecran.setCursor(60,13);
	Ecran.println("for request");
	Ecran.setCursor(60,23);
	Ecran.println("...");
	Ecran.display();
}


void setup(){
	//Initialisation de la liaison série et du bluetooth
	
	//Initialisation de la communication via le bus I2C à l'adresse 0x3C
	Ecran.begin(SSD1306_SWITCHCAPVCC, 0x3C);

	//Affichage du logo bluetooth
	affichageBluetooth();

  	Serial.begin(115200);
  	SerialBT.begin("ESP32SENSOR");
  	
	//L'on se connecte au Wi-Fi
	connectToWifi(Ecran);

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
		//Serial.println("Waiting for request...");
		waitingText();

		//Si un client se connecte alors l'on lui envoie les valeurs du capteurs
		if(leSocket.handleConnection()){
			unsigned short int sensorValue = getSensorValue();
			leSocket.sendData(&sensorValue, sizeof(sensorValue));
		}

		delay(500);
	}
	Ecran.~Adafruit_SSD1306();
}

#endif

#ifdef TestGarderLogs

String nomWifi, mdpWifi;
Preferences prefLogs;
bool logsSet = false;

void setup(){
	
	prefLogs.begin("logs", false);
	logsSet = prefLogs.getBool("logsSet", false);

	if(!logsSet){
		//connectToWifi();
		prefLogs.putString("nomWifi",nomWifi);
		prefLogs.putString("mdpWifi",mdpWifi);
		prefLogs.putBool("logsSet", true);
	} 

	nomWifi = prefLogs.getString("nomWifi", "NULL");
	mdpWifi = prefLogs.getString("mdpWifi", "NULL");

	prefLogs.end();
}

void loop(){

}

#endif

#ifdef TestAppuiBoutton


#endif