#include <Arduino.h>
#include <WiFi.h>
#include <BluetoothSerial.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BME280.h>
#include "TCPSocket.h"

// #define TestBluetooth
// #define TestCapteur
// #define TestEcran
// #define TestGarderLogs
// #define TestBouton
// #define TestCapteurLuminosite
#define ProgrPrincipal
// #define TestBME280

#ifdef ProgrPrincipal

BluetoothSerial SerialBT;
String nomWifi, mdpWifi;
TCPSocket leSocket;
Adafruit_BME280 bme;
Adafruit_SSD1306 Ecran;

static const unsigned char PROGMEM logo_bluetooth[] =
	{
		B00000000,
		B00000000,
		B00111111,
		B11000000,
		B00000000,
		B00000000,
		B00000000,
		B00111100,
		B00111000,
		B00000000,
		B00000000,
		B00000000,
		B00111100,
		B00000111,
		B00000000,
		B00000000,
		B00000000,
		B00111100,
		B00000000,
		B11100000,
		B00000000,
		B00000000,
		B00111100,
		B00000000,
		B00011100,
		B00000000,
		B00000000,
		B00111100,
		B00000000,
		B00000111,
		B00000000,
		B00000000,
		B00111100,
		B00000000,
		B00000111,
		B00011110,
		B00000000,
		B00111100,
		B00000000,
		B00011100,

		B00000011,
		B10000000,
		B00111100,
		B00000000,
		B11100000,
		B00000000,
		B01110000,
		B00111100,
		B00001111,
		B00000000,
		B00000000,
		B00011100,
		B00111100,
		B00111000,
		B00000000,
		B00000000,
		B00000111,
		B11111111,
		B11100000,
		B00000000,
		B00000000,
		B00000000,
		B11111111,
		B11100000,
		B00000000,
		B00000000,
		B00000111,
		B00111100,
		B00111000,
		B00000000,
		B00000000,
		B00011100,
		B00111100,
		B00001111,
		B00000000,
		B00000000,
		B01110000,
		B00111100,
		B00000000,
		B11100000,

		B00000011,
		B10000000,
		B00111100,
		B00000000,
		B00011100,
		B00011110,
		B00000000,
		B00111100,
		B00000000,
		B00000111,
		B00000000,
		B00000000,
		B00111100,
		B00000000,
		B00000111,
		B00000000,
		B00000000,
		B00111100,
		B00000000,
		B00011100,
		B00000000,
		B00000000,
		B00111100,
		B00000000,
		B11100000,
		B00000000,
		B00000000,
		B00111100,
		B00000111,
		B00000000,
		B00000000,
		B00000000,
		B00111100,
		B00111000,
		B00000000,
		B00000000,
		B00000000,
		B00111111,
		B11000000,
		B00000000,
};

static const unsigned char PROGMEM logo_wifi[] = {
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00111100,
	B00000000,
	B00000000,
	B00000000,
	B00001111,
	B11111111,
	B11110000,
	B00000000,
	B00000000,
	B11111100,
	B00000000,
	B00111111,
	B00000000,
	B00001111,
	B11000000,
	B00000000,
	B00000011,
	B11110000,
	B11111111,
	B00000000,
	B00000000,
	B00000000,
	B11111111,

	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00111100,
	B00000000,
	B00000000,
	B00000000,
	B00001111,
	B11111111,
	B11110000,
	B00000000,
	B00000000,
	B11111100,
	B00000000,
	B00111111,
	B00000000,
	B00001111,
	B11000000,
	B00000000,
	B00000011,
	B11110000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,

	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B11111111,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B11111111,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B11111111,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
};

void afficheLogoWIFI()
{
	// Ecrit sur l'écran la bitmap "logo_bluetooth" ecran 128x64, pos départ haut gauche (0,0)
	Ecran.drawBitmap((Ecran.width() - 130) / 2, // Position X
					 (Ecran.height() - 24) / 2, // Position Y
					 logo_wifi, 40, 24, 1);		// Bitmap, Longueur, Largeur, Couleur
												// Rafraichit l'écran affichant donc la bitmap
}

void affichageBluetooth()
{

	Ecran.clearDisplay();
	// Ecrit sur l'écran la bitmap "logo_bluetooth" ecran 128x64, pos départ huat gauche (0,0)
	Ecran.drawBitmap((Ecran.width() - 130) / 2,	 // Position X
					 (Ecran.height() - 24) / 2,	 // Position Y
					 logo_bluetooth, 40, 24, 1); // Bitmap, Longueur, Largeur, Couleur
	// Rafraichit l'écran affichant donc la bitmap

	Ecran.setTextSize(1);
	Ecran.setTextColor(WHITE);
	Ecran.setCursor(60, 3);
	Ecran.println("Connexion");
	Ecran.setCursor(60, 13);
	Ecran.println("bluetooth");
	Ecran.setCursor(60, 23);
	Ecran.println("active");

	Ecran.display();
}

void printHeap() {
    Serial.print("Free heap: ");
    Serial.println(ESP.getFreeHeap());
}

void connectToWifi(Adafruit_SSD1306 Ecran)
{

	Ecran.clearDisplay();
	afficheLogoWIFI();

	Ecran.setTextSize(1);
	Ecran.setTextColor(WHITE);
	Ecran.setCursor(55, 3);
	Ecran.println(F("Attente"));
	Ecran.setCursor(55, 13);
	Ecran.println(F("informations"));
	Ecran.setCursor(55, 23);
	Ecran.println(F("WIFI"));
	// Serial.println("Envoyez le nom du wifi via bluetooth");
	Ecran.display();

	while (nomWifi.length() == 0)
	{
		nomWifi = SerialBT.readStringUntil('\n');
	}

	nomWifi.trim();

	Serial.println("Envoyez le mot de passe wifi via bluetooth");

	while (mdpWifi.length() == 0)
	{
		mdpWifi = SerialBT.readStringUntil('\n');
	}

	mdpWifi.trim();

	WiFi.mode(WIFI_STA);
	WiFi.begin(nomWifi.c_str(), mdpWifi.c_str());

	Ecran.clearDisplay();
	afficheLogoWIFI();
	Ecran.setTextSize(1);
	Ecran.setTextColor(WHITE);
	Ecran.setCursor(60, 3);
	Ecran.println(F("Connexion"));
	Ecran.setCursor(60, 13);
	Ecran.println(F("WIFI"));
	Ecran.setCursor(60, 23);
	Ecran.println(F("en cours"));
	// Serial.println("Envoyez le nom du wifi via bluetooth");
	Ecran.display();

	// Serial.println("[+] Connexion en cours");
	while (WiFi.status() != WL_CONNECTED)
	{
		Serial.print(".");
		delay(200);
	}

	SerialBT.print(WiFi.localIP());
}

void waitingText()
{
	Ecran.clearDisplay();
	afficheLogoWIFI();
	Ecran.setTextSize(1);
	Ecran.setTextColor(WHITE);
	Ecran.setCursor(60, 3);
	Ecran.println("Waiting");
	Ecran.setCursor(60, 13);
	Ecran.println("for request");
	Ecran.setCursor(60, 23);
	Ecran.println("...");
	Ecran.display();
}

unsigned short int getSoilMoistureSensor()
{
	int in_analog_1;
	const int PIN = A0; // PIN A0 Capteur vers PIN VP Board

	in_analog_1 = analogRead(PIN);
	unsigned short int moisissure = (100 - ((in_analog_1 / 4095.00) * 100));

	return moisissure;
}

int getLuminosityLevel()
{
	const int sensorPin = 32;
	return digitalRead(sensorPin);
}


float getHumidity(Adafruit_BME280& bme) {
	delay(1000);
	return bme.readHumidity();
}

float getTemperature(Adafruit_BME280& bme) {
	delay(1000);
	return bme.readTemperature();
}

void setup()
{
	Serial.begin(115200);
	Serial.println("AHUAIUZUIUIZIUAZ!");
	Ecran.begin(SSD1306_SWITCHCAPVCC, 0x3C);

	//affichageBluetooth();
	sleep(2);
	if (!bme.begin(0x76)) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
	
	while(!SerialBT.begin("ESP32TEST")){
		delay(100);
		Serial.println("Bluetooth bug ??");
	}

	connectToWifi(Ecran);

	delay(200); // NECESSAIRE

	SerialBT.end();
	leSocket.begin();
	//waitingText();
}

void loop()
{

	delay(1000);
	if (leSocket.handleConnection())
	{
		printHeap();
		char luminosityLevel[10], soilMoisture[10], temperature[10], humidity[10];
		snprintf(soilMoisture, sizeof(soilMoisture), "%hu", getSoilMoistureSensor());
		snprintf(temperature, sizeof(temperature), "%.2f", getTemperature(bme));
		snprintf(humidity, sizeof(humidity), "%.2f", getHumidity(bme));
		snprintf(luminosityLevel, sizeof(luminosityLevel), "%d", getLuminosityLevel());

		char values[50];
		snprintf(values, sizeof(values), "%s,%s;%s/%s\n",  soilMoisture, temperature, humidity, luminosityLevel);
		Serial.print(values);
		leSocket.sendData(values, strlen(values));
	}
}

#endif

#ifdef TestBME280

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;

unsigned long delayTime;

void setup()
{
	Serial.begin(115200);
	Serial.println(F("BME280 test"));

	unsigned status;

	status = bme.begin(0x76);

	if (!status)
	{
		Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
		Serial.print("SensorID was: 0x");
		Serial.println(bme.sensorID(), 16);
		Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
		Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
		Serial.print("        ID of 0x60 represents a BME 280.\n");
		Serial.print("        ID of 0x61 represents a BME 680.\n");
		while (1)
			delay(10);
	}

	Serial.println("-- Default Test --");
	delayTime = 1000;

	Serial.println();
}

void printValues()
{
	Serial.print("Temperature = ");
	Serial.print(bme.readTemperature());
	Serial.println(" °C");

	Serial.print("Pressure = ");

	Serial.print(bme.readPressure() / 100.0F);
	Serial.println(" hPa");

	Serial.print("Approx. Altitude = ");
	Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
	Serial.println(" m");

	Serial.print("Humidity = ");
	Serial.print(bme.readHumidity());
	Serial.println(" %");

	Serial.println();
}

void loop()
{
	printValues();
	delay(delayTime);
}

#endif

#ifdef TestBluetooth
BluetoothSerial SerialBT;
String nomWifi, mdpWifi;

void setup()
{
	Serial.begin(115200);
	SerialBT.begin("ESP32TEST");

	Serial.println("Envoyez l'id wifi via bluetooth");
	while (nomWifi.length() == 0)
	{
		nomWifi = SerialBT.readStringUntil('\n');
	}

	nomWifi.trim();

	Serial.println("Envoyez le mot de passe wifi via bluetooth");

	while (mdpWifi.length() == 0)
	{
		mdpWifi = SerialBT.readStringUntil('\n');
	}

	mdpWifi.trim();

	WiFi.mode(WIFI_STA);
	WiFi.begin(nomWifi.c_str(), mdpWifi.c_str());

	while (WiFi.status() != WL_CONNECTED)
	{
		Serial.print(".");
		delay(200);
	}

	Serial.println("Conneciton Succesfull");

	SerialBT.print(WiFi.localIP());
	SerialBT.print("\n");
	Serial.println(WiFi.localIP());
}

void loop()
{

	delay(2000);
}
#endif

#ifdef TestCapteur

int moisissure, in_analog_1;
const int PIN = A0;

void setup()
{
	Serial.begin(115200);
	Serial.println("[+] Liaison Serie initialisee");
}

void loop()
{
	in_analog_1 = analogRead(PIN);
	moisissure = (100 - ((in_analog_1 / 4095.00) * 100));
	Serial.print("Moisissure:");
	Serial.print(moisissure);
	Serial.print("%\n");
}
#endif

#ifdef TestEcran

Adafruit_SSD1306 Ecran;

// Bitmap représentant le logo Bluetooth
static const unsigned char PROGMEM logo_bluetooth[] =
	{
		B00000000,
		B00000000,
		B00111111,
		B11000000,
		B00000000,
		B00000000,
		B00000000,
		B00111100,
		B00111000,
		B00000000,
		B00000000,
		B00000000,
		B00111100,
		B00000111,
		B00000000,
		B00000000,
		B00000000,
		B00111100,
		B00000000,
		B11100000,
		B00000000,
		B00000000,
		B00111100,
		B00000000,
		B00011100,
		B00000000,
		B00000000,
		B00111100,
		B00000000,
		B00000111,
		B00000000,
		B00000000,
		B00111100,
		B00000000,
		B00000111,
		B00011110,
		B00000000,
		B00111100,
		B00000000,
		B00011100,

		B00000011,
		B10000000,
		B00111100,
		B00000000,
		B11100000,
		B00000000,
		B01110000,
		B00111100,
		B00001111,
		B00000000,
		B00000000,
		B00011100,
		B00111100,
		B00111000,
		B00000000,
		B00000000,
		B00000111,
		B11111111,
		B11100000,
		B00000000,
		B00000000,
		B00000000,
		B11111111,
		B11100000,
		B00000000,
		B00000000,
		B00000111,
		B00111100,
		B00111000,
		B00000000,
		B00000000,
		B00011100,
		B00111100,
		B00001111,
		B00000000,
		B00000000,
		B01110000,
		B00111100,
		B00000000,
		B11100000,

		B00000011,
		B10000000,
		B00111100,
		B00000000,
		B00011100,
		B00011110,
		B00000000,
		B00111100,
		B00000000,
		B00000111,
		B00000000,
		B00000000,
		B00111100,
		B00000000,
		B00000111,
		B00000000,
		B00000000,
		B00111100,
		B00000000,
		B00011100,
		B00000000,
		B00000000,
		B00111100,
		B00000000,
		B11100000,
		B00000000,
		B00000000,
		B00111100,
		B00000111,
		B00000000,
		B00000000,
		B00000000,
		B00111100,
		B00111000,
		B00000000,
		B00000000,
		B00000000,
		B00111111,
		B11000000,
		B00000000,
};

static const unsigned char PROGMEM logo_wifi[] = {
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B11111111,
	B00000000,
	B00000111,
	B00000000,
	B11100000,
	B00011000,
	B00111100,
	B00011000,
	B00000000,
	B11000011,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00000000,
	B00011000,
	B00000000,
};

void setup()
{
	// Initialisation de la communication via le bus I2C à l'adresse 0x3C
	Ecran.begin(SSD1306_SWITCHCAPVCC, 0x3C);

	// Efface l'écran
	Ecran.clearDisplay();

	// Ecrit sur l'écran la bitmap "logo_bluetooth" ecran 128x64, pos départ huat gauche (0,0)
	Ecran.drawBitmap((Ecran.width() - 130) / 2,	 // Position X
					 (Ecran.height() - 24) / 2,	 // Position Y
					 logo_bluetooth, 40, 24, 1); // Bitmap, Longueur, Largeur, Couleur
	// Rafraichit l'écran affichant donc la bitmap
	Ecran.display();

	// Déstruction de l'objet écran
	Ecran.~Adafruit_SSD1306();
}

void loop()
{
}

#endif

#ifdef TestGarderLogs

String nomWifi, mdpWifi;
Preferences prefLogs;
bool logsSet = false;

void setup()
{

	prefLogs.begin("logs", false);
	logsSet = prefLogs.getBool("logsSet", false);

	if (!logsSet)
	{
		// connectToWifi();
		prefLogs.putString("nomWifi", nomWifi);
		prefLogs.putString("mdpWifi", mdpWifi);
		prefLogs.putBool("logsSet", true);
	}

	nomWifi = prefLogs.getString("nomWifi", "NULL");
	mdpWifi = prefLogs.getString("mdpWifi", "NULL");

	prefLogs.end();
}

void loop()
{
}

#endif

#ifdef TestBouton

const int buttonPin = 23;
int buttonState = 0;

void setup()
{
	Serial.begin(115200);
	pinMode(buttonPin, INPUT_PULLUP);
}

void loop()
{
	buttonState = digitalRead(buttonPin);
	if (buttonState == LOW)
	{
		Serial.println("btn on");
	}
	else
	{
		Serial.println("btn off");
	}
	delay(2000);
}

#endif

#ifdef TestCapteurLuminosite

const int sensorPin = 23;

void setup()
{
	Serial.begin(115200);
}

void loop()
{
	Serial.println(digitalRead(sensorPin));
	delay(300);
}

#endif
