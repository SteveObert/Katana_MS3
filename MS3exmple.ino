// Uncomment this to enable verbose debug messages.
#define MS3_DEBUG_MODE
#define TOTAL_LED 4

#include "Arduino.h"
#include "MS3.h"

const int SW1 = 2; // assign button pin to variable
const int SW2 = 3; // assign button pin to variable
const int SW3 = 4; // assign button pin to variable
const int SW4 = 5; // assign button pin to variable
const int SW5 = 6; // assign button pin to variable
const int SW6 = 7; // assign button pin to variable
const int ledPin1 = A0;   // led pin -> LED-> 220k R-> ground
const int ledPin2 = A1;  // led pin -> LED-> 220k R-> ground
const int ledPin3 = A2;   // led pin -> LED-> 220k R-> ground
const int ledPin4 = A3;  // led pin -> LED-> 220k R-> ground
byte ledArray[] = {ledPin1, ledPin2, ledPin3, ledPin4};

unsigned long db = 500; // Variable for debounce
unsigned long lastRead = millis();
int effects = 0;  // set effects sw to off -- buttons 1-4 send PC
int bank = 1;     // Set to send PCs 1-4
int effectsState1 = 0;
int effectsState2 = 0;
int effectsState3 = 0;
byte chn = 3;     // Midi channel

// Initialize the MS3 class. MS3 library is used for a Roland/BOSS MS3 effects pedal.
// I modified the MS3.h file by changing the sysex hedaer to work with a BOSS Katana amplifer instead.
//  **** Changed last from 0x3b to 0x33 for katana
//  **** #ifndef MS3_HEADER
//  **** const byte MS3_HEADER[6] = {0x41, 0x00, 0x00, 0x00, 0x00, 0x33};
//
MS3 katana;

// sysex define ################################
const unsigned long PC = 0x00010000; // change channel (PC mesage)  MS3.write(P_PATCH, 1, 2) second byte is channel number 3rd is length
const unsigned long CC16 = 0x60000030; //turn button 1 on  MS3.write(P_PATCH, 1, 1) second byte 0 = off 1 = on
const unsigned long CC17 = 0x6000034C; //turn button 2 on  MS3.write(P_PATCH, 1, 1) second byte 0 = off 1 = on
const unsigned long CC18 = 0x60000610; //turn reverb on  MS3.write(P_PATCH, 1, 1) second byte 0 = off 1 = on
const unsigned long Loop = 0x60000655;   // turn loop off on
const unsigned long rvbRed = 0x60001214; // set reverb type to red  MS3.write(P_PATCH, 1, 1)
// end sysex define ##############################
const unsigned long msg = 0;


//LiquidCrystal_I2C lcd1(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
//LiquidCrystal_I2C lcd2(0x26, 16, 2); // set the LCD address to 0x26 for a 16 chars and 2 line display

// Loop to turn all LEDs off
void setAllLEDs(int type) {
  for (int i = 0; i < TOTAL_LED - 2; i++) {
    digitalWrite(ledArray[i], type);
  }
}



void setup() {

  //  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  //  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
  //    Serial.println(F("SSD1306 allocation failed"));
  //    for (;;); // Don't proceed, loop forever
  //  }
  //  // Clear the buffer
  //  display.clearDisplay();
  //  display.display();

  pinMode(SW1, INPUT_PULLUP); // setup button as input
  pinMode(SW2, INPUT_PULLUP); // setup button as input
  pinMode(SW3, INPUT_PULLUP); // setup button as input
  pinMode(SW4, INPUT_PULLUP); // setup button as input
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);

  // set to PC 0 and set LEDS
  setAllLEDs(LOW);
  digitalWrite (ledPin1, HIGH);


  Serial.begin(115200);
  while (!Serial) {}

  if (!katana.begin()) {
    Serial.println(F("*** USB / MS3 init error! ***"));
    while (true);
  }

  Serial.println(F("Ready!"));
  Serial.println();
  unsigned long parameter = 0;
  byte data = 0;
  switch (katana.update(parameter, data)) {
    //
    // Fetch the current active patch on the MS-3.
    case MS3_READY:
      katana.setEditorMode();
      katana.read(PC, 0x02);
      break;
  }
}

void parseData(unsigned long parameter, byte data) {
  switch (parameter) {
    case msg:
      break;
    default:
      ;
  }

}


void loop() {

  // Check for incoming data or send a queued item.
  unsigned long parameter = 0;
  byte data = 0;

  switch (katana.update(parameter, data)) {
    // Fetch the current active patch on the MS-3.
    case MS3_READY:
      katana.setEditorMode();
      katana.read(PC, 0x02);
      break;
    case MS3_DATA_RECEIVED:
      //parseData(parameter, data);
      break;
  }

  if (digitalRead(SW3) == LOW  && millis() - lastRead > db) {
    if (bank == 1) {
      bank = 2;
      digitalWrite(ledPin3, HIGH);
      lastRead = millis();
     }

    else {
      bank = 1;
      digitalWrite(ledPin3, LOW);
      lastRead = millis();
    }
  }

  if (digitalRead(SW4) == LOW  && millis() - lastRead > db) {
    if (effects == 0) {
      effects = 1;
      digitalWrite(ledPin4, HIGH);
      lastRead = millis();
    }

    else {
      effects = 0;
      digitalWrite(ledPin4, LOW);
      lastRead = millis();
    }
  }


  if (bank == 1 && effects == 0) {
    if (digitalRead(SW1) == LOW && millis() - lastRead > db) {
      //setEdit;
      setAllLEDs(LOW);
      digitalWrite(ledPin1, HIGH);
      data = 1;
      katana.write(PC, data, 2);
      lastRead = millis();
    }

    if (digitalRead(SW2) == LOW && millis() - lastRead > db) {
      //    case MS3_READY:
      //setEdit;
      setAllLEDs(LOW);
      digitalWrite(ledPin2, HIGH);
      data = 2;
      katana.write(PC, data, 2);
    }
  }

  if (bank == 2 && effects == 0) {
    if (digitalRead(SW1) == LOW && millis() - lastRead > db) {
      setAllLEDs(LOW);
      digitalWrite(ledPin1, HIGH);
      data = 5;
      katana.write(PC, data, 2);
    }

    if (digitalRead(SW2) == LOW && millis() - lastRead > db) {
      setAllLEDs(LOW);
      digitalWrite(ledPin2, HIGH);
      //midiOut.sendProgramChange(5, chn); // Send PC
      data = 6;
      katana.write(PC, data, 2);
      lastRead = millis();
    }
  }


  if (effects == 1) {
    if (digitalRead(SW1) == LOW && millis() - lastRead > db) {
      if (effectsState1 == 0) {
        digitalWrite(ledPin1, HIGH);
        //midiOut.sendControlChange(16, 127, chn); // Send CC on message
        katana.write(CC16, 1, 1);
        lastRead = millis();
        effectsState1 = 1;
      }
      else {
        digitalWrite(ledPin1, LOW);
        //midiOut.sendControlChange(16, 0, chn); // Send CC on message
        katana.write(CC16, 0, 1);
        lastRead = millis();
        effectsState1 = 0;
      }
    }
    if (digitalRead(SW2) == LOW && millis() - lastRead > db) {
      if (effectsState2 == 0) {
        digitalWrite(ledPin2, HIGH);
        //midiOut.sendControlChange(17, 127, chn); // Send CC on message
        katana.write(CC17, 1, 1);
        lastRead = millis();
        effectsState2 = 1;
      }

      else {
        digitalWrite(ledPin2, LOW);
        //midiOut.sendControlChange(17, 0, chn); // Send CC on message
        katana.write(CC17, 0, 1);
        lastRead = millis();
        effectsState2 = 0;
      }
    }
  }
}
