/*
   Pin layout used:
   --------------------------------------
               MFRC522      Arduino      
               Reader/PCD   Uno/101       
   Signal      Pin          Pin           
   -------------------------------------    
   ------------Shared Pins--------------     
   RST/Reset   RST          9             
   SPI MOSI    MOSI         11 / ICSP-4   
   SPI MISO    MISO         12 / ICSP-1  
   SPI SCK     SCK          13 / ICSP-3 
  ------------Unshared Pins-------------
   SS_1        SDA          10
   SS_2        SDA          8
   SS_3        SDA          7

*/

//Libraries:
#include <SPI.h>
#include <MFRC522.h>

// PIN Numbers : RESET + SDAs
#define RST_PIN         9
#define SS_1_PIN        10
#define SS_2_PIN        8
#define SS_3_PIN        7

#define PIN_PIEZO         3 

#define NR_OF_READERS   3

byte ssPins[] = {SS_1_PIN, SS_2_PIN, SS_3_PIN};

static String UIDs[] = {"A4784985", "BF1DD902", "FC436CCD"}; // our tags' UIDs
String reading; 
// Create an MFRC522 instance :
MFRC522 mfrc522[NR_OF_READERS];

/**
   Initialize.
*/
void setup() {

  Serial.begin(9600);           // Initialize serial communications with the PC
  while (!Serial);              // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

  SPI.begin();                  // Init SPI bus

  /* looking for MFRC522 readers */
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN);
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
    mfrc522[reader].PCD_SetAntennaGain(mfrc522[reader].RxGain_max);
  }
}

/*
   Main loop.
*/

void loop() {

  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {

    // Looking for new cards
    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {
      Serial.print(F("Reader "));
      Serial.print(reader);

      // Show some details of the PICC (that is: the tag/card)
      Serial.print(F(": Card UID:"));
      dump_byte_array(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size); //UID sent to dump_byte_array
      Serial.println();

      mfrc522[reader].PICC_HaltA();
      // Stop encryption on PCD
      mfrc522[reader].PCD_StopCrypto1();
    }
  } 
}

/**
   Helper routine to dump a byte array as hex values to Serial.
*/
void dump_byte_array(byte * buffer, byte bufferSize) { // prints hex UID
  for (byte i = 0; i < bufferSize; i++) {
    reading = 
    Serial.print(buffer[i], HEX);
  }
}

void playBuzzer(){
  
}
