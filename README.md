# ESP32 Cam Modul Bilder Upload via FTP

Mit diesem Programm ist es möglich mit dem ESP32-Cam Modul Bilder regelmässig in einem Zeitfenster auszulösen und 
zu einem FTP Server hochzuladen. Dabei wir eine SFTP Verbindung genutzt.

### Probleme
##### 1. LED-Flashlight
Leider ist das Abschalten, des LED-Blitzlichtes nicht möglich ausser man 
stellt bei der Verbindung zur SD-Card auf den 1-Bitmodus ein.
##### 2. External Wi-Fi antenna
Leider ist eine externe Wi-Fi-Antenne nicht ohne Umlöten eines Wiederstandes 
möglich (oder anderer Lötarbeiten). Auch wenn die Lieferanten ein Set mit 
Antenne anbieten heist es nicht, das es umgelötet ist.

### Was passiert im einzelnen

- Aufbau einer Internet verbindung über Wi-FI.
- Abfragen der aktuellen Uhrzeit von einem NPT Server.
- Bilder machen und auf den FTP Server hochladen.
- Die Einstellung für das Netzwerk, FTP und Bilder Intervall wird mit einer Configurations-Datei auf der SD-Card gemacht.


### Für die verbindung über SFTP (SSH und FTP)
Für eine sichere verbindung zum Server wird ein Schlüssel benötigt.
https://learn.microsoft.com/de-de/viva/glint/setup/sftp-ssh-key-gen#create-an-ssh-key-pair-on-microsoft-windows

Diesen wohlen wir im Filesystem des ESP32 Boards Speichern unter:
`/spiffs/.ssh/`

Eine erstellung des schlüssels ist euch mit einem ESP32 Board möglich sie dazu bitte hier:
https://github.com/ewpa/LibSSH-ESP32/blob/master/examples/keygen2/keygen2.ino

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

### Problems with the PlatformIO Serial Monitor show nothing
https://community.platformio.org/t/noob-stuck-on-esp32-cam-mb-with-pio-vscode/19117/5

Well a few ESP32 boards have a mechanism that connects RTS/DTR to the EN/GPIO0 lines – if these are driven the wrong way when the serial monitor opens, it might shut down the ESP32.

Add the following lines to the platformio.ini one of this:
```
monitor_rts = 0
monitor_dtr = 0
```
or
```
monitor_rts = 0
monitor_dtr = 1
```
or
```
monitor_rts = 1
monitor_dtr = 0
```
or
```
monitor_rts = 1
monitor_dtr = 1
```

