# Wiring and Setup

This project needs no external wiring — everything runs on a bare ESP32 development board.

## Hardware

- Any ESP32 dev board (for example, ESP32 DevKit v1, NodeMCU-32S, WROOM-32 boards).
- A **data-capable** USB cable (charge-only cables will not work for flashing).

## Connections

| To | From | Notes |
|---|---|---|
| Computer USB port | ESP32 USB port | Powers the board and uploads firmware. |

No sensors, LEDs, or external modules are required. The board's onboard USB-to-serial chip handles programming.

## Power

- Power the ESP32 from the computer USB port during flashing.
- For standalone use, any 5 V USB power source works.

## First-time board setup (Arduino IDE)

1. Install **Arduino IDE 2.x**.
2. Open **File → Preferences** and add this additional Boards Manager URL:

   ```
   https://espressif.github.io/arduino-esp32/package_esp32_index.json
   ```

3. Open **Tools → Board → Boards Manager…**, search for `esp32` by **Espressif Systems**, and install it.
4. Select your board under **Tools → Board → ESP32 Arduino** (for example, `ESP32 Dev Module`).
5. Select the correct **Port** under **Tools → Port**.
6. Select a **Partition Scheme** that includes a LittleFS/Spiffs filesystem partition (for example, `Default 8MB with spiffs`).

## Uploading

1. Open `ESP32_Prank.ino`.
2. Set your desired hotspot name in the `AP_SSID` constant.
3. Upload the sketch (**Sketch → Upload**).
4. Install the [LittleFS Filesystem Uploader](https://github.com/earlephilhower/arduino-littlefs-upload) if you have not already.
5. Close the Serial Monitor and Serial Plotter.
6. Run **Tools → ESP32 LittleFS Data Upload** to upload `data/image.jpg`.
7. Press reset on the ESP32.

## Verifying

1. Open **Tools → Serial Monitor** at **115200 baud**.
2. You should see:

   ```
   Hotspot started!
   SSID: YOUR_WIFI_SSID
   URL: http://192.168.4.1
   ```

3. Connect a phone or computer to the hotspot and open `http://192.168.4.1`.

## Troubleshooting

- **Board not listed:** Reinstall the ESP32 board package and use a data USB cable.
- **Port missing:** Install your board's USB-to-serial driver (CH340, CP2102, or native USB).
- **Upload fails:** Close Serial Monitor, hold BOOT on some boards during flashing, and check the selected board/port.
