#include <Arduino.h>
#include <dht.h>
#include <ESP8266WiFi.h>
#include <SECRETS.h>
#include <WiFiUdp.h>
#include <WiFi.h>

#define DHT11_PIN 1

/* Global Variables */
WiFiClient client;
dht dht;

/* Function declarations */
void connectToWiFi(void);
void fillWeatherData(char[]);
void sendWeatherData(char[]);

/* Function definitions */
void
connectToWiFi(void)
{
        int retries = 0;

        Serial.println();
        Serial.println();
        Serial.print("Connecting to WiFi");
        Serial.println("...");

        WiFi.begin(ssid, password);

        while ((WiFi.status() != WL_CONNECTED) && (retries < 15)) {
                retries++;
                delay(500);
                Serial.print(".");
        }

        if (retries > 14) {
            Serial.println(F("WiFi connection FAILED"));
        }

        if (WiFi.status() == WL_CONNECTED) {
            Serial.println(F("WiFi connected!"));
            Serial.println("IP address: ");
            Serial.println(WiFi.localIP());
        }       

        Serial.println(F("Setup ready"));
}

void
fillWeatherData(char * weatherData)
{
        weatherData[0] = dht.getTemperature();
        weatherData[1] = dht.getHumidity();
}

void
sendWeatherData(char * weatherData)
{
        Serial.println("Sending");
}

void
setup(void)
{
        Serial.begin(115200);
        dht.setup(1);
        connectToWiFi();
        WiFiUDP.begin(7000);
}

void
loop(void)
{
        char weatherData[3] = { NULL };

        delay(dht.getMinimumSamplingPeriod() * 2);
        fillWeatherData(&weatherData[0]);
        sendWeatherData(&weatherData[0]);
}
