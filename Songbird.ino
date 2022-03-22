/*
-- NOTES --
The purpose of the device is to create a pleasant atmosphere 
in the bathroom (or wherever) when a person is entering. 
The device is powered by 4 AA batteries (each 1.2V), so for 
energy saving purposes, the deep sleep mode was integrated. 
Furthermore, by the means of an RTC, the songbird plays night birds
such es owls and nightingale at night at a reduced volume, 
while playing day birds like blackbirds or geese during the day.
Due to copyright issues, the wav files are not included.

The wav file must be stereo signed 16 bit 44100Hz 
and filename must be abcdefgh.wav (8-3) formatted.


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

PCF8523   to MKR Zero for RTC
GND       to GND
VCC       to VCC
SDA       to SDA (11)
SCL       to SCL (12)
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
const char filename1[] = "Twittr01.wav";
const char filename2[] = "Twittr02.wav";
const char filename3[] = "Twittr03.wav";
const char filename4[] = "Twittr04.wav";
const char filename5[] = "Twittr05.wav";
const char filename6[] = "Twittr06.wav";
const char filename7[] = "Twittr07.wav";
const char filename8[] = "Twittr08.wav";
const char filename9[] = "Twittr09.wav";
const char filename10[] = "Twittr10.wav";
const char filename11[] = "Twittr11.wav";
const char filename12[] = "Twittr12.wav";
const char filename13[] = "Twittr13.wav";
const char filename14[] = "Twittr14.wav";
const char filename15[] = "Twittr15.wav";
const char filename16[] = "Twittr16.wav";
const char filename17[] = "Twittr17.wav";
const char filename18[] = "Twittr18.wav";
const char filename19[] = "Twittr19.wav";
const char filename20[] = "Twittr20.wav";


// variable representing the Wave File
SDWaveFile Twittr01;
SDWaveFile Twittr02;
SDWaveFile Twittr03;
SDWaveFile Twittr04;
SDWaveFile Twittr05;
SDWaveFile Twittr06;
SDWaveFile Twittr07;
SDWaveFile Twittr08;
SDWaveFile Twittr09;
SDWaveFile Twittr10;
SDWaveFile Twittr11;
SDWaveFile Twittr12;
SDWaveFile Twittr13;
SDWaveFile Twittr14;
SDWaveFile Twittr15;
SDWaveFile Twittr16;
SDWaveFile Twittr17;
SDWaveFile Twittr18;
SDWaveFile Twittr19;
SDWaveFile Twittr20;
RTC_PCF8523 rtc;


void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  Serial.println("Warming up... wait for a min...");
 // delay execution of sketch for a min, to allow PIR sensor get stabilized
 for( int i = 1; i <= 120; i++) {  // LED blinks until PIR sensor is stabilized
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
  Twittr01 = SDWaveFile(filename1);
  Twittr02 = SDWaveFile(filename2);
  Twittr03 = SDWaveFile(filename3);
  Twittr04 = SDWaveFile(filename4);
  Twittr05 = SDWaveFile(filename5);
  Twittr06 = SDWaveFile(filename6);
  Twittr07 = SDWaveFile(filename7);
  Twittr08 = SDWaveFile(filename8);
  Twittr09 = SDWaveFile(filename9);
  Twittr10 = SDWaveFile(filename10);
  Twittr11 = SDWaveFile(filename11);
  Twittr12 = SDWaveFile(filename12);
  Twittr13 = SDWaveFile(filename13);
  Twittr14 = SDWaveFile(filename14);
  Twittr15 = SDWaveFile(filename15);
  Twittr16 = SDWaveFile(filename16);
  Twittr17 = SDWaveFile(filename17);
  Twittr18 = SDWaveFile(filename18);
  Twittr19 = SDWaveFile(filename19);
  Twittr20 = SDWaveFile(filename20);
 
  
  // if the file didn't open, print an error and stop
  if (!Twittr01) {
    Serial.println("Error opening Twitter01.wav");
    while (true);
	}	
  if (!Twittr02) {
    Serial.println("Error opening Twitter02.wav");
    while (true);
	}
  if (!Twittr03) {
    Serial.println("Error opening Twitter03.wav");
    while (true);
	}
  if (!Twittr04) {
    Serial.println("Error opening Twitter04.wav");
    while (true);
	}
  if (!Twittr05) {
    Serial.println("Error opening Twitter05.wav");
    while (true);
	}
  if (!Twittr06) {
    Serial.println("Error opening Twitter06.wav");
    while (true);
	}	
  if (!Twittr07) {
    Serial.println("Error opening Twitter07.wav");
    while (true);
	}
  if (!Twittr08) {
    Serial.println("Error opening Twitter08.wav");
    while (true);
	}
  if (!Twittr09) {
    Serial.println("Error opening Twitter09.wav");
    while (true);
	}
  if (!Twittr10) {
    Serial.println("Error opening Twitter10.wav");
    while (true);
	}
  if (!Twittr11) {
    Serial.println("Error opening Twitter11.wav");
    while (true);
	}	
  if (!Twittr12) {
    Serial.println("Error opening Twitter12.wav");
    while (true);
	}
  if (!Twittr13) {
    Serial.println("Error opening Twitter13.wav");
    while (true);
	}
  if (!Twittr14) {
    Serial.println("Error opening Twitter14.wav");
    while (true);
	}
  if (!Twittr15) {
    Serial.println("Error opening Twitter15.wav");
    while (true);
	}
  if (!Twittr16) {
    Serial.println("Error opening Twitter16.wav");
    while (true);
	}	
  if (!Twittr17) {
    Serial.println("Error opening Twitter17.wav");
    while (true);
	}
  if (!Twittr18) {
    Serial.println("Error opening Twitter18.wav");
    while (true);
	}
  if (!Twittr19) {
    Serial.println("Error opening Twitter19.wav");
    while (true);
	}
  if (!Twittr20) {
    Serial.println("Error opening Twitter20.wav");
    while (true);
	}


	// check if the I2S output can play the wave file	
	if (!AudioOutI2S.canPlay(Twittr01)) {	
	  Serial.println("Unable to play Twittr01.wav using I2S!");	
	  while (1); // do nothing	
	}    
	if (!AudioOutI2S.canPlay(Twittr02)) {	
	  Serial.println("Unable to play Twittr02.wav using I2S!");	
	  while (1); // do nothing	
	}
	if (!AudioOutI2S.canPlay(Twittr03)) {	
	  Serial.println("Unable to play Twittr03.wav using I2S!");	
	  while (1); // do nothing	
	} 
	if (!AudioOutI2S.canPlay(Twittr04)) {	
	  Serial.println("Unable to play Twittr04.wav using I2S!");	
	  while (1); // do nothing	
	}
	if (!AudioOutI2S.canPlay(Twittr05)) {	
	  Serial.println("Unable to play Twittr05.wav using I2S!");	
	  while (1); // do nothing	
	} 
	if (!AudioOutI2S.canPlay(Twittr06)) {	
	  Serial.println("Unable to play Twittr06.wav using I2S!");	
	  while (1); // do nothing	
	}    
	if (!AudioOutI2S.canPlay(Twittr07)) {	
	  Serial.println("Unable to play Twittr07.wav using I2S!");	
	  while (1); // do nothing	
	}
	if (!AudioOutI2S.canPlay(Twittr08)) {	
	  Serial.println("Unable to play Twittr08.wav using I2S!");	
	  while (1); // do nothing	
	} 
	if (!AudioOutI2S.canPlay(Twittr09)) {	
	  Serial.println("Unable to play Twittr09.wav using I2S!");	
	  while (1); // do nothing	
	}
	if (!AudioOutI2S.canPlay(Twittr10)) {	
	  Serial.println("Unable to play Twittr10.wav using I2S!");	
	  while (1); // do nothing	
	} 
	if (!AudioOutI2S.canPlay(Twittr11)) {	
	  Serial.println("Unable to play Twittr11.wav using I2S!");	
	  while (1); // do nothing	
	}    
	if (!AudioOutI2S.canPlay(Twittr12)) {	
	  Serial.println("Unable to play Twittr12.wav using I2S!");	
	  while (1); // do nothing	
	}
	if (!AudioOutI2S.canPlay(Twittr13)) {	
	  Serial.println("Unable to play Twittr13.wav using I2S!");	
	  while (1); // do nothing	
	} 
	if (!AudioOutI2S.canPlay(Twittr14)) {	
	  Serial.println("Unable to play Twittr14.wav using I2S!");	
	  while (1); // do nothing	
	}
	if (!AudioOutI2S.canPlay(Twittr15)) {	
	  Serial.println("Unable to play Twittr15.wav using I2S!");	
	  while (1); // do nothing	
	} 
	if (!AudioOutI2S.canPlay(Twittr16)) {	
	  Serial.println("Unable to play Twittr16.wav using I2S!");	
	  while (1); // do nothing	
	}    
	if (!AudioOutI2S.canPlay(Twittr17)) {	
	  Serial.println("Unable to play Twittr17.wav using I2S!");	
	  while (1); // do nothing	
	}
	if (!AudioOutI2S.canPlay(Twittr18)) {	
	  Serial.println("Unable to play Twittr18.wav using I2S!");	
	  while (1); // do nothing	
	} 
	if (!AudioOutI2S.canPlay(Twittr19)) {	
	  Serial.println("Unable to play Twittr19.wav using I2S!");	
	  while (1); // do nothing	
	}
	if (!AudioOutI2S.canPlay(Twittr20)) {	
	  Serial.println("Unable to play Twittr20.wav using I2S!");	
	  while (1); // do nothing	
	} 
	
}


void loop() {
  DateTime now = rtc.now();
  
  Serial.println("Motion detected!");	// print on output change

  if (now.hour() >= 22 && now.hour() <= 7) {

    // adjust the playback volume for night time
	  AudioOutI2S.volume(15);	

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
  }
  
  else {

    // adjust the playback volume	for day time
	  AudioOutI2S.volume(20);	
    
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
}


void wakeUp() {
  // This function will be called once on device wakeup
  // After this, loop() is called
  // You can do some little operations here (like changing variables which will be used in the loop)
  // Remember to avoid calling delay() and long running functions since this functions executes in interrupt context

}
