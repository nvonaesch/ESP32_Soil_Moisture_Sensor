#include <Arduino.h>
#include <WiFi.h>
#include <BluetoothSerial.h>

//#define TestBluetooth
//#define TestCapteur
#define ProgrPrincipal


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

#ifdef ProgrPrincipal

BluetoothSerial SerialBT;
String nomWifi, mdpWifi;

void setup(){
  	Serial.begin(115200);
  	SerialBT.begin("ESP32SENSOR");
  	Serial.println("Envoyez le nom du wifi via bluetooth");

	while(nomWifi.length() == 0){
		nomWifi = SerialBT.readStringUntil('\n');
	}
	
	Serial.println(nomWifi);
  	Serial.println("Envoyez le mot de passe wifi via bluetooth");

	while(mdpWifi.length() == 0){
  		mdpWifi = SerialBT.readStringUntil('\n');
	}

	Serial.println(mdpWifi);
	WiFi.mode(WIFI_STA);
	WiFi.begin(nomWifi.c_str(), mdpWifi.c_str());

	while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(200);
    }

	Serial.println("Bien connecte au WiFi");
}

void loop(){

}

#endif
