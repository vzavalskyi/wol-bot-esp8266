#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>
#include <WakeOnLan.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// WiFi configuration
#define WIFI_SSID ""
#define WIFI_PASS ""

// Telegram Bot Token
#define BOT_TOKEN  "0000000000:xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define ALLOWED_ID "000000000"  // Your allowed Telegram user ID

// MAC address of the target device
#define MAC_ADDR "FF:FF:FF:FF:FF:FF"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
WiFiUDP UDP;
WakeOnLan WOL(UDP);

const unsigned long BOT_MTBS = 1000;  // Mean time between scan messages
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime;  // Last time messages' scan has been done

// Function to send the Wake-on-LAN magic packet
void sendWOL() {
  WOL.sendMagicPacket(MAC_ADDR);  // Send WOL on default port (9)
  Serial.println("Magic Packet sent to wake up PC.");
}

// Handle incoming Telegram messages
void handleNewMessages(int numNewMessages) {
  Serial.print("Handling new messages: ");
  Serial.println(numNewMessages);

  for (int i = 0; i < numNewMessages; i++) {
    if (bot.messages[i].from_id != ALLOWED_ID) continue;

    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";

    if (text == "/wol") {
      sendWOL();
      bot.sendMessage(chat_id, "Magic Packet sent!", "");
    } else if (text == "/ping") {
      bot.sendMessage(chat_id, "Pong.", "");
    } else if (text == "/start") {
      String welcome = "Welcome to **WoL Bot**, " + from_name + ".\n";
      welcome += "Use is restricted to the bot owner.\n\n";
      welcome += "/wol : Send the Magic Packet\n";
      welcome += "/ping : Check the bot status\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
}

// Setup function
void setup() {
  Serial.begin(115200);
  
  // Configure WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi.");

  // Add root certificate for api.telegram.org
  secured_client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org

  // Calculate the broadcast address for Wake-on-LAN
  WOL.calculateBroadcastAddress(WiFi.localIP(), WiFi.subnetMask());

  // Get UTC time via NTP
  configTime(0, 0, "pool.ntp.org");
  time_t now = time(nullptr);
  while (now < 24 * 3600) {
    delay(150);
    now = time(nullptr);
  }
  Serial.println("Time synchronized.");
}

// Main loop
void loop() {
  // Check for new messages from Telegram
  if (millis() - bot_lasttime > BOT_MTBS) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    bot_lasttime = millis();
  }

  delay(10);
}
