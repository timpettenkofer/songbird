/*
-- WIRING --
MAX98735  to MKR Zero
LRCLK     to -3
BCLK      to -2
DIN       to A6
GND       to GND
VIN       to VCC

PIR       to MKR Zero for motion detection
Pin1      to GND
Pin2      to 7
Pin3      to 5V

Note: The wav file must be stereo signed 16 bit 44100Hz and filename must be abcdefgh.wav (8-3) formatted.
*/

#include "ArduinoLowPower.h"
#include <SD.h>	
#include <Adafruit_ZeroI2S.h>
#include <ArduinoSound.h>
#include <RTClib.h>

int ledPin = LED_BUILTIN;       // choose the pin for the LED
int inputPin = 7;               // choose the digital input pin (for PIR sensor)
//int pirState = LOW;             // we start, assuming no motion detected
//int pirValue = 0;               // variable for reading the pin status

// filename of wave file to play
const char filename1[] = "Twittr1.wav";
const char filename2[] = "Twittr2.wav";
const char filename3[] = "Twittr3.wav";
const char filename4[] = "Twittr4.wav";
const char filename5[] = "Twittr5.wav";
const char filename6[] = "Night1.wav";
const char filename7[] = "Night2.wav";
const char filename8[] = "Night3.wav";
const char filename9[] = "Night4.wav";

// variable representing the Wave File
SDWaveFile Twittr1;
SDWaveFile Twittr2;
SDWaveFile Twittr3;
SDWaveFile Twittr4;
SDWaveFile Twittr5;
SDWaveFile Night1;
SDWaveFile Night2;
SDWaveFile Night3;
SDWaveFile Night4;
RTC_PCF8523 rtc;


void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  Serial.println("Warming up... wait for a min...");
 // delay execution of sketch for a min, to allow PIR sensor get stabilized
 for( int i = 1; i <= 120; i++){  // LED blinks until PIR sensor is stabilized
    digitalWrite(ledPin, HIGH); 
    delay(100);         
    digitalWrite(ledPin, LOW); 
    delay(100); 
 }
  Serial.println("Sensor is ready");     

  pinMode(inputPin, INPUT);     // declare sensor as input
  LowPower.attachInterruptWakeup(inputPin, wakeUp, CHANGE);

// Check if the RTC is connected
  Serial.print("Checking if Real-Time-Clock is connected...");
    if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
    }

// Set the RTC to the date & time this sketch was compiled
  Serial.print("Setting Real-Time-Clock if needed...");
  if (! rtc.initialized() || rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  Serial.print("RTC is up and running.");

	// setup the SD card, depending on your shield of breakout board	
	// you may need to pass a pin number in begin for SS	
	Serial.print("Initializing SD card...");	

	if (!SD.begin()) {	
	  Serial.println("initialization failed!");	
	  return;	
	}	
	Serial.println("initialization done.");	
  
  // create a SDWaveFile	
  Twittr1 = SDWaveFile(filename1);
  Twittr2 = SDWaveFile(filename2);
  Twittr3 = SDWaveFile(filename3);
  Twittr4 = SDWaveFile(filename4);
  Twittr5 = SDWaveFile(filename5);
  Night1 = SDWaveFile(filename6);
  Night2 = SDWaveFile(filename7);
  Night3 = SDWaveFile(filename8);
  Night4 = SDWaveFile(filename9);   
  
  // if the file didn't open, print an error and stop
  if (!Twittr1) {
    Serial.println("Error opening Twitter1.wav");
    while (true);
	}	
  if (!Twittr2) {
    Serial.println("Error opening Twitter2.wav");
    while (true);
	}
  if (!Twittr3) {
    Serial.println("Error opening Twitter3.wav");
    while (true);
	}
  if (!Twittr4) {
    Serial.println("Error opening Twitter4.wav");
    while (true);
	}
  if (!Twittr5) {
    Serial.println("Error opening Twitter5.wav");
    while (true);
	}
  if (!Night1) {
    Serial.println("Error opening Night1.wav");
    while (true);
	}	
  if (!Night2) {
    Serial.println("Error opening Night2.wav");
    while (true);
	}
  if (!Night3) {
    Serial.println("Error opening Night3.wav");
    while (true);
	}
  if (!Night4) {
    Serial.println("Error opening Night4.wav");
    while (true);
	}

	// check if the I2S output can play the wave file	
	if (!AudioOutI2S.canPlay(Twittr1)) {	
	  Serial.println("Unable to play Twittr1.wav using I2S!");	
	  while (1); // do nothing	
	}    
	if (!AudioOutI2S.canPlay(Twittr2)) {	
	  Serial.println("Unable to play Twittr2.wav using I2S!");	
	  while (1); // do nothing	
	}
	if (!AudioOutI2S.canPlay(Twittr3)) {	
	  Serial.println("Unable to play Twittr3.wav using I2S!");	
	  while (1); // do nothing	
	} 
	if (!AudioOutI2S.canPlay(Twittr4)) {	
	  Serial.println("Unable to play Twittr4.wav using I2S!");	
	  while (1); // do nothing	
	}
	if (!AudioOutI2S.canPlay(Twittr5)) {	
	  Serial.println("Unable to play Twittr5.wav using I2S!");	
	  while (1); // do nothing	
	} 
	if (!AudioOutI2S.canPlay(Night1)) {	
	  Serial.println("Unable to play Night1.wav using I2S!");	
	  while (1); // do nothing	
	}    
	if (!AudioOutI2S.canPlay(Night2)) {	
	  Serial.println("Unable to play Night.wav using I2S!");	
	  while (1); // do nothing	
	}
	if (!AudioOutI2S.canPlay(Night3)) {	
	  Serial.println("Unable to play Night3.wav using I2S!");	
	  while (1); // do nothing	
	} 
	if (!AudioOutI2S.canPlay(Night4)) {	
	  Serial.println("Unable to play Night4.wav using I2S!");	
	  while (1); // do nothing	
	}
}


void loop() {
  DateTime now = rtc.now();
  
  Serial.println("Motion detected!");	// print on output change

  if (now.hour() >= 22 && now.hour() <= 6) {

    // adjust the playback volume	for night time
	  AudioOutI2S.volume(25);	

    switch (random(1,8)) {
      case 1:
        Serial.println("Playing Night1.wav");
        AudioOutI2S.play(Night1);
        break;
     
      case 2:
        Serial.println("Playing Night2.wav");
        AudioOutI2S.play(Night2);
        break;

      case 3:
        Serial.println("Playing Night3.wav");
        AudioOutI2S.play(Night3);
        break;

      case 4:
        Serial.println("Playing Night4.wav");
        AudioOutI2S.play(Night4);
        break;
          
    }
  
  else {

    // adjust the playback volume	for day time
	  AudioOutI2S.volume(40);	
    
    switch (random(1,8)) {
      case 1:
        Serial.println("Playing Twittr1.wav");
        AudioOutI2S.play(Twittr1);
        break;
     
      case 2:
        Serial.println("Playing Twittr2.wav");
        AudioOutI2S.play(Twittr2);
        break;

      case 3:
        Serial.println("Playing Twittr3.wav");
        AudioOutI2S.play(Twittr3);
        break;

      case 4:
        Serial.println("Playing Twittr4.wav");
        AudioOutI2S.play(Twittr4);
        break;
          
      case 5:
        Serial.println("Playing Twittr5.wav");
        AudioOutI2S.play(Twittr5);
        break;
        
      case 6:
        Serial.println("Playing Night1.wav");
        AudioOutI2S.play(Night1);
        break;          

      case 7:
        Serial.println("Playing Night2.wav");
        AudioOutI2S.play(Night2);
        break;
    }      
    
      
  delay(120000);// wait 120 seconds
  Serial.println("Motion ended!");	// print on output change    
   
 
  // Triggers an infinite sleep (the device will be woken up only by the registered wakeup sources)
  // The power consumption of the chip will drop consistently
  LowPower.deepSleep();
}

void wakeUp() {
  // This function will be called once on device wakeup
  // After this, loop() is called
  // You can do some little operations here (like changing variables which will be used in the loop)
  // Remember to avoid calling delay() and long running functions since this functions executes in interrupt context

}
