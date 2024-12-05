## ESP32_Soil_Moisture_Sensor

This project set an ESP32-WROOM-32S based Bluetooth connection with a remote android application.
[Android Application Repository](https://github.com/nvonaesch/ESP_32_Android_Communication)
The ESP32 then connects to the WiFi network with the logs bluetooth provided.
Finally the ESP32 then sends over TCPSocket the soil measure sensor values.

## PINOUT ESP-WROOM-32S
![pinout](/ProgESP/include/PINOUT.png)

## SETUP

To setup PlatformIO run the following command:
`python3 -m pip install -U platformio`

To intall libraries dependencies run the following commands:
`pio lib -g install Adafruit SSD1306@^2.5.13` 
`pio lib -g install Adafruit BME280 Library@^2.2.4`

## WIRING
![cablage](/ProgESP/include/wiring.webp)
|    **BME280**    | **ESP32** |
|:----------------:|:---------:|
|        VCC       |    3.3V   |
|        GND       |    GND    |
|        SCL       |    D22    |
|        SDA       |    D21    |
|    **SSD1306**   |           |
|        VCC       |    3.3V   |
|        GND       |    GND    |
|        SCL       |    D22    |
|        SDA       |    D21    |
| **Light Sensor** |           |
|        VCC       |    3.3V   |
|        GND       |    GND    |
|        D0        |    D32    |
|  **Hygrometer**  |           |
|        VCC       |    3.3V   |
|        GND       |    GND    |
|        D0        |     NC    |
|        A0        |     VP    |




