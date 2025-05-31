#include "Arduino.h"
#include "esp_camera.h"
#include <WiFi.h>
//#include <WiFiUdp.h>
//#include <NTPClient.h>

#include "env.h" // << here we add the wifi credit

#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

#include "FS.h"
#include "SD.h"
#include "SPI.h"


#include <time.h>                    // for time() ctime()

/* Globals */
time_t now;                          // this are the seconds since Epoch (1970) - UTC
tm tm;                             // the structure tm holds time information in a more convenient way *


const char *ntpServer = "de.pool.ntp.org"; // germany
const long gmtOffset_sec = 3600;
const int dalightOffset_sec = 3600;

WiFiUDP ntpUDP;


void listDir(fs::FS &fs, const char *dirname, uint8_t levels) {
    Serial.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if (!root) {
        Serial.println("Failed to open directory");
        return;
    }
    if (!root.isDirectory()) {
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while (file) {
        if (file.isDirectory()) {
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if (levels) {
                listDir(fs, file.path(), levels - 1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

void readFile(fs::FS &fs, const char *path) {
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if (!file) {
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.print("Read from file: ");
    while (file.available()) {
        Serial.write(file.read());
    }
    file.close();
}

void setup() {
    // WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

    Serial.begin(115200);
    Serial.setDebugOutput(true);
    Serial.println();

#ifdef REASSIGN_PINS
  SPI.begin(sck, miso, mosi, cs);
  if (!SD.begin(cs)) {
#else
    if (!SD.begin()) {
#endif
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD.cardType();

    if (cardType == CARD_NONE) {
        Serial.println("No SD card attached");
        return;
    }

    Serial.print("SD Card Type: ");
    if (cardType == CARD_MMC) {
        Serial.println("MMC");
    } else if (cardType == CARD_SD) {
        Serial.println("SDSC");
    } else if (cardType == CARD_SDHC) {
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);

    listDir(SD, "/", 0);

    // TIME NTP Time Server
    // Settings for the NTP-Server to get the local after internet connection
    Serial.println("\nNTP TZ DST - bare minimum");
    configTime(0, 0, MY_NTP_SERVER);  // 0, 0 because we will use TZ in the next line
    setenv("TZ", MY_TZ, 1);            // Set environment variable with your time zone
    tzset();

    // WI-FI
    // use the network conditionals and connect to the internet
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println(".");
    }
    Serial.println("Connected to Wi-Fi");



    //wait a second
    sleep(10);
}

void loop() {
    // update the time
    timeClient.update();

    // create the local time
    time_t now = timeClient.getEpochTime();
    struct tm tm = *localtime(&now);

    Serial.print(tm.tm_year + 1900);
}
