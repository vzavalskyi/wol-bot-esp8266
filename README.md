# WoL Bot for ESP8266

This project is a fork of [daniele-salvagni's](https://github.com/daniele-salvagni/wol-bot-esp32) **Wake-on-LAN Telegram Bot for ESP32**. The purpose of this fork is to port the original ESP32-based project to work with the **ESP8266** module, enabling you to wake up a PC via a magic packet (Wake-on-LAN) sent through a Telegram bot.

## Features

- Wake up any device that supports **Wake-on-LAN (WoL)** using a Telegram bot command.
- Simple interface with basic commands:
  - `/wol` — Sends a WoL magic packet to wake up the target machine.
  - `/ping` — Check the bot status.
  - `/start` — Displays a welcome message and available commands.
- Secure communication using **Telegram Bot API** and **SSL/TLS** over Wi-Fi.

## Credits

The original project was created by **[Daniele Salvagni](https://github.com/daniele-salvagni)** and was designed to run on **ESP32**. You can find the original repository [here](https://github.com/daniele-salvagni/wol-bot-esp32).

This fork adapts the project to run on the **ESP8266** platform while maintaining the core functionality of sending Wake-on-LAN magic packets through a Telegram bot.

## Hardware Requirements

- **ESP8266** module (such as NodeMCU or Wemos D1 Mini)
- A device with **Wake-on-LAN (WoL)** capabilities (usually a PC with a compatible network card).
- **Wi-Fi** network with access to the target device.
- **Telegram Bot API** token (instructions below).

## Installation

### 1. Prerequisites

- Install the **ESP8266 Board Package** in Arduino IDE:
  - Open Arduino IDE and go to **File > Preferences**.
  - Add this URL in **Additional Boards Manager URLs**:  
    `https://arduino.esp8266.com/stable/package_esp8266com_index.json`
  - Go to **Tools > Board > Boards Manager** and install the **ESP8266** package.

- Install the required Arduino libraries:
  - **WakeOnLan**: Install via **Library Manager**.
  - **UniversalTelegramBot**: Install via **Library Manager**.
  - **ArduinoJson**: Install via **Library Manager**.

### 2. Configure Your ESP8266

1. Clone or download this repository.
2. Open the `wol-bot-esp8266.ino` file in the Arduino IDE.
3. Configure the Wi-Fi credentials in the code:
    ```cpp
    #define WIFI_SSID "your_wifi_ssid"
    #define WIFI_PASS "your_wifi_password"
    ```
4. Set your **Telegram Bot Token**:
    ```cpp
    #define BOT_TOKEN "your_telegram_bot_token"
    ```
5. Set the **MAC Address** of the target PC that you want to wake up:
    ```cpp
    #define MAC_ADDR "FF:FF:FF:FF:FF:FF"
    ```
6. Upload the code to your ESP8266.

### 3. Get Your Telegram Bot Token

1. Create a bot using **BotFather** on Telegram.
2. Copy the token provided by **BotFather** and add it to the code.

### 4. Running the Bot

Once the ESP8266 is connected to your Wi-Fi and the bot is running, you can use your Telegram app to send the following commands to the bot:
- `/wol` — Wake up your PC.
- `/ping` — Test if the bot is online.
- `/start` — Display a welcome message and list of commands.

## License

This project is released under the **MIT License**.
