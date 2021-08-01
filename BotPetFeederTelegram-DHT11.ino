#include<Servo.h>
#include "CTBot.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "DHT.h"

// DHT11
#define DHTPIN D4    // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "0.id.pool.ntp.org", 25200,60000);
Servo servo;
CTBot myBot;

String ssid = "xxxx";     // REPLACE mySSID WITH YOUR WIFI SSID
String pass = "xxxx"; // REPLACE myPassword YOUR WIFI PASSWORD, IF ANY
String token = "xxxx";

int SERVO_PIN = D3;    // The pin which the servo is attached to
int CLOSE_ANGLE = 0;  // The closing angle of the servo motor arm asli 0
int OPEN_ANGLE = 180;  // The opening angle of the servo motor arm asli 60

void setup() {
	// initialize the Serial
	Serial.begin(115200);

  servo.attach(SERVO_PIN);
  servo.write(CLOSE_ANGLE);

	Serial.println("Memulai Telegram Bot...");

	// connect the ESP8266 to the desired access point
	myBot.wifiConnect(ssid, pass);

	// set the telegram bot token
	myBot.setTelegramToken(token);

	// check if all things are ok
	if (myBot.testConnection())
		Serial.println("\n Koneksi OK Gan!");
	else
		Serial.println("\n Koneksi Bermasalah .. hiks..");
}

void loop() {
  // blue led off
  // pinMode (LED_BUILTIN, OUTPUT); // Define LED as output
  // digitalWrite (LED_BUILTIN, HIGH); // Turn off

  timeClient.begin();
  timeClient.update();

 // DHT11
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  String humid = "Kelembapan / Humidity : " + String(h) + " % \n";
  String temp = "Suhu / Temperature : " + String(t) + "°C ";
 // --- begin telegram bot

   // a variable to store telegram message data
  TBMessage msg;
  // if there is an incoming message...
  if (myBot.getNewMessage(msg)) {

      if (msg.text.equalsIgnoreCase("/status")) {
      myBot.sendMessage(msg.sender.id, "KuDa melaporkan, terpantau..");
      delay (500);
      myBot.sendMessage(msg.sender.id, temp);
      delay (500);
      myBot.sendMessage(msg.sender.id, humid);
    }

    // DHT11 RESPONSE
      else if (msg.text.equalsIgnoreCase("Lembap")) {
      myBot.sendMessage(msg.sender.id, "KuDa melaporkan, Kelembapan terpantau pada..");
      delay (1000);
      myBot.sendMessage(msg.sender.id, humid);
    }
      else if (msg.text.equalsIgnoreCase("/lembap")) {
      myBot.sendMessage(msg.sender.id, "KuDa melaporkan, Kelembapan terpantau pada..");
      delay (1000);
      myBot.sendMessage(msg.sender.id, humid);
    }
      else if (msg.text.equalsIgnoreCase("Suhu")) {
      myBot.sendMessage(msg.sender.id, "KuDa melaporkan, Suhu terpantau pada..");
      delay (1000);
      myBot.sendMessage(msg.sender.id, temp);
    }
      else if (msg.text.equalsIgnoreCase("/suhu")) {
      myBot.sendMessage(msg.sender.id, "KuDa melaporkan, Suhu terpantau pada..");
      delay (1000);
      myBot.sendMessage(msg.sender.id, temp);
    }

    // if pertama original
     else if (msg.text.equalsIgnoreCase("Mamam")) {                   //Perintah dari telegram ke perangkat
      open_door();
      delay(1500);
      close_door();
      myBot.sendMessage(msg.sender.id, "Makaciihhh, aku udah dikasih Mamam, cus gasak dulu ya, monggo ndoro joget dulu pakai video ini https://youtu.be/3diXZnsW2E4"); //Balasan dari perangkat ke Bot Telegram
      Serial.println("Mamam Sukses");
    }
    else if (msg.text.equalsIgnoreCase("Makan")) {              //Perintah dari telegram ke perangkat
      open_door();
      delay(2000);
      close_door();
      myBot.sendMessage(msg.sender.id, "Kami segenap KuDa alias Kucing Dagul, Mocca - Chino - Krimpi mengucapkan, terima kasih banyak atas makanan yang diberikan ke kami hari ini, semoga Ndoro selalu dijaga kesehatannya, dilancarkan rezekinya, dan diberkahi oleh Allah SWT, Amin Amin Ya Rabbal Alamin.. "); //Balasan dari perangkat ke Bot Telegram
      Serial.println("Makan Sukses");
    }
    else if (msg.text.equalsIgnoreCase("Mangan")) {              //Perintah dari telegram ke perangkat
      open_door();
      delay(1500);
      close_door();
      myBot.sendMessage(msg.sender.id, "Suwun wis dikei mangan, kulo mangan riyin nggiih Ndoro.."); //Balasan dari perangkat ke Bot Telegram
      Serial.println("Mangan ben wareg");
    }
    else if (msg.text.equalsIgnoreCase("Madang")) {              //Perintah dari telegram ke perangkat
      open_door();
      delay(1500);
      close_door();
      myBot.sendMessage(msg.sender.id, "Suwun wis dikei madang, kulo madang riyin nggiih Ndoro.."); //Balasan dari perangkat ke Bot Telegram
      Serial.println("Madang ben wareg");
    }
    else if (msg.text.equalsIgnoreCase("Mbadok")) {              //Perintah dari telegram ke perangkat
      open_door();
      delay(2500);
      close_door();
      delay(500);
      open_door();
      delay(1500);
      close_door();
      delay(500);
      open_door();
      delay(100);
      close_door();
      myBot.sendMessage(msg.sender.id, "Suwun mpun diparingi badokan sing gadah, kulo mbadok riyin nggiih Ndoro, Mugi Barokah..Amin Ya Rabbal alamin.."); //Balasan dari perangkat ke Bot Telegram
      Serial.println("Mbadok ben wareg");
    }
    // kalibrasi
    else if (msg.text.equalsIgnoreCase("goyang")) {              //Perintah dari telegram ke perangkat
      open_door();
      delay(500);
      close_door();
      delay(500);
      open_door();
      delay(500);
      close_door();
      delay(500);
      open_door();
      delay(500);
      close_door();
      delay(500);
      open_door();
      delay(500);
      close_door();
      delay(500);
      open_door();
      delay(500);
      close_door();
      myBot.sendMessage(msg.sender.id, "Goyang Kalibrasi 5x"); //Balasan dari perangkat ke Bot Telegram
      Serial.println("Goyang Kalibrasi 5x");
    }
    //
    else {                                                    // otherwise...
      // generate the message for the sender
      String reply;
      reply = (String)"Met dateng ya " + msg.sender.username + (String)". Jika mau kasih makan, kata kuncinya adalah Makan, Mamam, Madang, Mangan, dan Mbadok. Untuk cek lainnya : /suhu untuk cek suhu, /lembap untuk cek kelembapan dan /status untuk cek semua status";
      myBot.sendMessage(msg.sender.id, reply);             // and send it
    }
  }

  /// -- end telegram bot

}

void open_door(){
  servo.write(OPEN_ANGLE);   // Send the command to the servo motor to open the trap door
}

void close_door(){
  servo.write(CLOSE_ANGLE);   // Send te command to the servo motor to close the trap door
}
