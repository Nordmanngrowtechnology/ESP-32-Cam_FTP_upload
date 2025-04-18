# ESP32 Cam Modul Bilder Upload via FTP

Mit diesem Programm ist es möglich mit dem ESP32-Cam Modul Bilder regelmässig in einem Zeitfenster auszulösen und 
mit einer Internet verbindung zu einem FTP Server hochzuladen.

### Was passiert im einzelnen

- Aufbau einer Internet verbindung über Wi-FI.
- Abfragen der aktuellen Uhrzeit von einem NPT Server.
- Bilder machen und auf den FTP Server hochladen.
- Die Einstellung für das Netzwerk, FTP und Bilder Intervall wird mit einer Configurations-Datei aus SD-Card gemacht.


# English description

# ESP-32-Cam_FTP_upload
Upload images to FTP server with ESP-32CAM modul.  What the script do:

1. Load SD Card config file
2. Build Wi-Fi-Connection
3. Take a picture
4. Submit image to FTP server

### The Script
Use the ESP32-CAM modul to submit images to FTP server.  The script load the Wi-Fi and FTP credentials.

---

##### Configuration option in file on sd-card
The ESP32-CAM need a SD-Card with a folder config and a textfile in it.
```
/config/config.txt

picture_time_from=6
picture_time_to=24
picture_interval_time_ms=

img_name_prefix=

wifi_ssid=
wifi_pass=

ftp_server=
ftp_port=
ftp_user=
ftp_pass=
ftp_directory=
```

### Help for pinout of Cam Modul SD slot

More on https://github.com/espressif/arduino-esp32/tree/master/libraries/SD_MMC

| Micro SD-Card slot | ESP32-CAM |
|--------------------|-----------|
| CLK                | GIPO 14   |
| CMD                | GIPO 15   |
| DATA0              | GIPO 2    |
| DATA1 / Flashlight | GIPO 4    |
| DATA2              | GIPO 12   |
| DATA3              | GIPO 13   |

### Used Libs as inspiration
https://github.com/tzapu/WiFiManager
https://github.com/alanesq/CameraWifiMotion/tree/master
https://randomnerdtutorials.com/esp32-microsd-card-arduino/
