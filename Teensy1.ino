#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 0
#define RST_PIN 6
#define LEDREDPIN 19



MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.


#define rxPin 7 // Teensy pin 7 <--> HC-05 Tx
#define txPin 8 // Teensy pin 8 <--> HC-05 Rx

void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
   pinMode(LEDREDPIN, OUTPUT);
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

  // Setup Serial1 for BlueTooth
  Serial1.begin(9600); // Default communication rate of the Bluetooth module

}
void loop() 
{
   if (Serial1.available()) { 
       String cm = Serial1.readStringUntil('\n');
       
       if (cm.equals ("Grandpa In")){
        Serial.println("Turn off LED");
           digitalWrite(LEDREDPIN, LOW);
          }
       else if(cm.equals ("Admin In")){
        Serial.println("Turn off LED");
           digitalWrite(LEDREDPIN, LOW);
          }
   }
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "FC EB 6D 6E") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Son out 1");
    Serial1.println(F("Son out 1"));
    Serial.println();
    delay(500);
  }
 else if (content.substring(1) == "2C E5 75 6D") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Grandpa out 2");
    Serial1.println(F("Grandpa out 2"));
    Serial.println();
    delay(500);
    Serial.println("Turn on LED");
    digitalWrite(LEDREDPIN, HIGH);
  }
  else if (content.substring(1) == "23 67 09 07") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Admin out 3");
    Serial1.println(F("Admin out 3"));
    Serial.println();
    delay(500);
  }
 
 else   {
    Serial.println(" Access denied 0");
    Serial1.println(F("Access denied 0"));
    Serial.println();
    delay(500);
    
  }


  
} 
