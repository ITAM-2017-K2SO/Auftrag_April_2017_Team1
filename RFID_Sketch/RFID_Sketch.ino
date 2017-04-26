/* 
  RFID - Chip (Schreiben und lesen)

  (c)2017 Louis Janosch, Oliver Wawer, Mike Kamps
*/
#include <arduino.h>
#include <SPI.h> // SPI-Bibiothek hinzufügen
#include <MFRC522.h> // RFID-Bibiothek hinzufügen

#define SDA_Pin 10
#define SCK_Pin 13
#define MOSI_Pin 11
#define MISO_Pin 12
#define RST_Pin 5 


MFRC522 mfrc522(SDA_Pin, RST_Pin); // RFID-Empfänger benennen


void setup() // Beginn des Setups:
{
  pinMode(SDA_Pin, OUTPUT);
  
  Serial.begin(9600); // Serielle Verbindung starten (Monitor)
  SPI.begin(); // SPI-Verbindung aufbauen
  mfrc522.PCD_Init(); // Initialisierung des RFID-Empfängers
}



void loop() // Hier beginnt der Loop-Teil
{

  if ( ! mfrc522.PICC_IsNewCardPresent()) // Wenn eine Karte in Reichweite ist...
  {
    return; // gehe weiter...
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) // Wenn ein RFID-Sender ausgewählt wurde
  {
    return; // gehe weiter...
  }

  Serial.print("Die ID des RFID-TAGS lautet:"); // "Die ID des RFID-TAGS lautet:" wird auf den Serial Monitor geschrieben.

  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i], HEX); // Dann wird die UID ausgelesen, die aus vier einzelnen Blöcken besteht und der Reihe nach an den Serial Monitor gesendet. Die Endung Hex bedeutet, dass die vier Blöcke der UID als HEX-Zahl (also auch mit Buchstaben) ausgegeben wird
    Serial.print(" "); // Der Befehl „Serial.print(" ");“ sorgt dafür, dass zwischen den einzelnen ausgelesenen Blöcken ein Leerzeichen steht.
  }

  Serial.println(); // Mit dieser Zeile wird auf dem Serial Monitor nur ein Zeilenumbruch gemacht.
}
