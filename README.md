# ESP32 Prank Captive Portal

A small ESP32 project that creates an **open Wi-Fi hotspot** and serves a single image through a **captive portal**. Any device that connects is redirected via DNS to the ESP32 web server, which displays the image directly from flash storage.

> **Warning:** This is an educational/demo project. Use it only on networks and with devices you own or have explicit permission to use. Creating rogue access points or captive portals on networks you do not control may violate local laws and network policies.

## Features

- Open ESP32 Wi-Fi access point (no password).
- DNS-based captive portal redirection (wildcard `*` → ESP32).
- Static IP: `192.168.4.1`.
- Image served directly from LittleFS as `image/jpeg`.
- No external internet connection required — everything runs on the ESP32.

## Hardware requirements

- ESP32 development board.
- USB data cable.
- Computer with Arduino IDE 2.x.

## Software requirements

- [Arduino IDE 2.x](https://www.arduino.cc/en/software).
- Espressif ESP32 Arduino board package (installed via the Board Manager).
- [LittleFS Filesystem Uploader](https://github.com/earlephilhower/arduino-littlefs-upload).

The following libraries are **included with the ESP32 Arduino core** and do not need separate installation:

| Library | Purpose |
|---|---|
| `WiFi.h` | Wi-Fi access point |
| `LittleFS.h` | Flash filesystem |
| `WebServer.h` | HTTP server |
| `DNSServer.h` | Captive portal DNS |

## Installation

1. Clone or download this repository.
2. Open `ESP32_Prank.ino` in Arduino IDE 2.x.
3. Install the Espressif ESP32 board package if it is not already installed:
   - **Tools → Board → Boards Manager…**
   - Search for `esp32` by Espressif Systems and install the latest version.
4. Select the correct ESP32 board under **Tools → Board**.
5. Select the correct COM port under **Tools → Port**.
6. Check the partition scheme (**Tools → Partition Scheme**) and ensure it includes a LittleFS filesystem partition (for example, `Default 8MB with spiffs` or any scheme with a `littlefs`/`spiffs` partition).
7. Compile and upload the Arduino sketch (**Sketch → Upload**).
8. Upload the filesystem separately using the LittleFS uploader (see below).
9. Restart the ESP32 (press the reset button or re-plug the board).

## LittleFS upload instructions

The `data/` directory **must remain beside the `.ino` file**, and the image must be located at `data/image.jpg`.

> **Important:** Uploading the Arduino sketch does **not** upload the image. The LittleFS filesystem must be uploaded separately.

1. Ensure the image is at `data/image.jpg`.
2. Close the **Serial Monitor** and **Serial Plotter** to avoid COM port conflicts.
3. Run the LittleFS Filesystem Uploader (**Tools → ESP32 LittleFS Data Upload**).
4. Ensure the selected partition scheme has sufficient filesystem space for the image.

Uploader reference: [arduino-littlefs-upload](https://github.com/earlephilhower/arduino-littlefs-upload)

## Usage

1. Power on the ESP32.
2. Connect a phone or computer to the hotspot (SSID set in the sketch, default placeholder `YOUR_WIFI_SSID`).
3. Open the captive portal if it appears automatically.
4. If it does not appear automatically, navigate to:

   `http://192.168.4.1`

Captive portal auto-detection depends on the connected device (iOS, Android, Windows behave differently) and is **not guaranteed**. If the portal does not pop up, open a browser manually and go to the URL above.

## Configuration

All configuration lives at the top of `ESP32_Prank.ino`:

| Setting | Location | Description |
|---|---|---|
| Access point SSID | `AP_SSID` constant | Change `"YOUR_WIFI_SSID"` to your desired hotspot name. |
| Static IP | `portalIP` | The ESP32 AP IP (`192, 168, 4, 1`) and the DNS redirect target. |
| Image path | `server.on("/", ...)` handler | The file opened from LittleFS: `"/image.jpg"`. |
| Web server behavior | Route handlers | `/` serves the image; unknown paths redirect to `http://192.168.4.1/`. |

## Troubleshooting

| Problem | Solution |
|---|---|
| COM port busy or unavailable | Close Serial Monitor/Plotter and any other program using the port. Select the correct port under **Tools → Port**. |
| Image not found in LittleFS | Verify `data/image.jpg` exists (case-sensitive on LittleFS) and that the filesystem was uploaded. |
| LittleFS upload failure | Close all serial tools, check the partition scheme has a filesystem partition, and re-run the data upload. |
| Wrong partition scheme | Select a scheme that includes a LittleFS/Spiffs partition with enough space for the image. |
| Captive portal not opening automatically | Open a browser manually and go to `http://192.168.4.1`. |
| ESP32 not appearing in Arduino IDE | Install the ESP32 board package, use a data-capable USB cable, and install/refresh the USB-to-serial driver for your board. |

## Project limitations

- The open Wi-Fi network has **no password** — anyone nearby can connect.
- Captive portal auto-opening is **device-dependent** and not guaranteed.
- The image is stored in ESP32 flash and is limited by the partition size.
- This project is intended for **authorized demonstrations and educational use only**.

## License

This project is licensed under the MIT License — see [LICENSE](LICENSE).
