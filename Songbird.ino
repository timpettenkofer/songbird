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
MAX98357  to MKR Zero
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

// filename of wave file to play
const char filename1[] = "Twittr01.wav";
const char filename2[] = "Twittr02.wav";
const char filename3[] = "Twittr03.wav";
const char filename4[] = "Twittr04.wav";
const char filename7[] = "Twittr07.wav";
const char filename8[] = "Twittr08.wav";
const char filename10[] = "Twittr10.wav";
const char filename11[] = "Twittr11.wav";
const char filename12[] = "Twittr12.wav";
const char filename13[] = "Twittr13.wav";
const char filename16[] = "Twittr16.wav";
const char filename19[] = "Twittr19.wav";
const char filename20[] = "Twittr20.wav";
const char filename22[] = "Twittr22.wav";
const char filename23[] = "Twittr23.wav";
const char filename25[] = "Twittr25.wav";
const char filename26[] = "Twittr26.wav";
const char filename27[] = "Twittr27.wav";
const char filename28[] = "Twittr28.wav";
const char filename29[] = "Twittr29.wav";
const char filename30[] = "Twittr30.wav";
const char filename31[] = "Twittr31.wav";
const char filename32[] = "Twittr32.wav";

// variable representing the Wave File
SDWaveFile Twittr01;
SDWaveFile Twittr02;
SDWaveFile Twittr03;
SDWaveFile Twittr04;
SDWaveFile Twittr07;
SDWaveFile Twittr08;
SDWaveFile Twittr10;
SDWaveFile Twittr11;
SDWaveFile Twittr12;
SDWaveFile Twittr13;
SDWaveFile Twittr16;
SDWaveFile Twittr19;
SDWaveFile Twittr20;
SDWaveFile Twittr22;
SDWaveFile Twittr23;
SDWaveFile Twittr25;
SDWaveFile Twittr26;
SDWaveFile Twittr27;
SDWaveFile Twittr28;
SDWaveFile Twittr29;
SDWaveFile Twittr30;
SDWaveFile Twittr31;
SDWaveFile Twittr32;
RTC_PCF8523 rtc;


void setup() {
  
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  Serial.print("Warming up... wait for a min...");
  // delay execution of sketch for a min, to allow PIR sensor get stabilized
  for (int i = 1; i <= 40; i++) {  // LED blinks until PIR sensor is stabilized
    digitalWrite(ledPin, HIGH); 
    delay(300);         
    digitalWrite(ledPin, LOW); 
    delay(300); 
 }
  Serial.println("Sensor is ready");     

  pinMode(inputPin, INPUT);     // declare sensor as input
  LowPower.attachInterruptWakeup(inputPin, wakeUp, CHANGE);

// Check if the RTC is connected
  Serial.println("Checking if Real-Time-Clock is connected...");
    if (! rtc.begin()) {
    Serial.print("Couldn't find RTC!");
    Serial.flush();
    while (1) delay(10);
    }

// Set the RTC to the date & time this sketch was compiled
  Serial.println("Setting Real-Time-Clock if needed...");
  if (! rtc.initialized() || rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  rtc.start();		// Ensure the clock is running
  Serial.println("RTC is up and running.");

// setup the SD card, depending on your shield of breakout board	
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
  Twittr07 = SDWaveFile(filename7);
  Twittr08 = SDWaveFile(filename8);
  Twittr10 = SDWaveFile(filename10);
  Twittr11 = SDWaveFile(filename11);
  Twittr12 = SDWaveFile(filename12);
  Twittr13 = SDWaveFile(filename13);
  Twittr16 = SDWaveFile(filename16);
  Twittr19 = SDWaveFile(filename19);
  Twittr20 = SDWaveFile(filename20);
  Twittr22 = SDWaveFile(filename22);
  Twittr23 = SDWaveFile(filename23);
  Twittr25 = SDWaveFile(filename25);
  Twittr26 = SDWaveFile(filename26);
  Twittr27 = SDWaveFile(filename27);
  Twittr28 = SDWaveFile(filename28);
  Twittr29 = SDWaveFile(filename29);
  Twittr30 = SDWaveFile(filename30);
  Twittr31 = SDWaveFile(filename31);
  Twittr32 = SDWaveFile(filename32);
  
  // if the file didn't open, print an error and stop
  if (!Twittr01) {
    Serial.println("Error opening Twittr01.wav");
    while (true);
	}	
  if (!Twittr02) {
    Serial.println("Error opening Twittr02.wav");
    while (true);
	}
  if (!Twittr03) {
    Serial.println("Error opening Twittr03.wav");
    while (true);
	}
  if (!Twittr04) {
    Serial.println("Error opening Twittr04.wav");
    while (true);
	}	
  if (!Twittr07) {
    Serial.println("Error opening Twittr07.wav");
    while (true);
	}
  if (!Twittr08) {
    Serial.println("Error opening Twittr08.wav");
    while (true);
	}
  if (!Twittr10) {
    Serial.println("Error opening Twittr10.wav");
    while (true);
	}
  if (!Twittr11) {
    Serial.println("Error opening Twittr11.wav");
    while (true);
	}	
  if (!Twittr12) {
    Serial.println("Error opening Twittr12.wav");
    while (true);
	}
  if (!Twittr13) {
    Serial.println("Error opening Twittr13.wav");
    while (true);
	}
  if (!Twittr16) {
    Serial.println("Error opening Twittr16.wav");
    while (true);
	}	
  if (!Twittr19) {
    Serial.println("Error opening Twittr19.wav");
    while (true);
	}
  if (!Twittr20) {
    Serial.println("Error opening Twittr20.wav");
    while (true);
	}
  if (!Twittr22) {
    Serial.println("Error opening Twittr22.wav");
    while (true);
	}
  if (!Twittr23) {
    Serial.println("Error opening Twittr23.wav");
    while (true);
	}
  if (!Twittr25) {
    Serial.println("Error opening Twittr25.wav");
    while (true);
	}
  if (!Twittr26) {
    Serial.println("Error opening Twittr26.wav");
    while (true);
	}
  if (!Twittr27) {
    Serial.println("Error opening Twittr27.wav");
    while (true);
	}
  if (!Twittr28) {
    Serial.println("Error opening Twittr28.wav");
    while (true);
	}
  if (!Twittr29) {
    Serial.println("Error opening Twittr29.wav");
    while (true);
	}
  if (!Twittr30) {
    Serial.println("Error opening Twittr30.wav");
    while (true);
	}
  if (!Twittr31) {
    Serial.println("Error opening Twittr31.wav");
    while (true);
	}
  if (!Twittr32) {
    Serial.println("Error opening Twittr32.wav");
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
  if (!AudioOutI2S.canPlay(Twittr07)) {	
    Serial.println("Unable to play Twittr07.wav using I2S!");	
    while (1); // do nothing	
    }
  if (!AudioOutI2S.canPlay(Twittr08)) {	
    Serial.println("Unable to play Twittr08.wav using I2S!");	
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
  if (!AudioOutI2S.canPlay(Twittr16)) {	
    Serial.println("Unable to play Twittr16.wav using I2S!");	
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
  if (!AudioOutI2S.canPlay(Twittr22)) {	
    Serial.println("Unable to play Twittr22.wav using I2S!");	
    while (1); // do nothing	
    }
  if (!AudioOutI2S.canPlay(Twittr23)) {	
    Serial.println("Unable to play Twittr23.wav using I2S!");	
    while (1); // do nothing	
    }
  if (!AudioOutI2S.canPlay(Twittr25)) {	
    Serial.println("Unable to play Twittr25.wav using I2S!");	
    while (1); // do nothing	
    }
  if (!AudioOutI2S.canPlay(Twittr26)) {	
    Serial.println("Unable to play Twittr26.wav using I2S!");	
    while (1); // do nothing	
    }
  if (!AudioOutI2S.canPlay(Twittr27)) {	
    Serial.println("Unable to play Twittr27.wav using I2S!");	
    while (1); // do nothing	
    }
  if (!AudioOutI2S.canPlay(Twittr28)) {	
    Serial.println("Unable to play Twittr28.wav using I2S!");	
    while (1); // do nothing	
    }
  if (!AudioOutI2S.canPlay(Twittr29)) {	
    Serial.println("Unable to play Twittr29.wav using I2S!");	
    while (1); // do nothing	
    }
  if (!AudioOutI2S.canPlay(Twittr30)) {	
    Serial.println("Unable to play Twittr30.wav using I2S!");	
    while (1); // do nothing	
    }
  if (!AudioOutI2S.canPlay(Twittr31)) {	
    Serial.println("Unable to play Twittr31.wav using I2S!");	
    while (1); // do nothing	
    }
  if (!AudioOutI2S.canPlay(Twittr32)) {	
    Serial.println("Unable to play Twittr32.wav using I2S!");	
    while (1); // do nothing	
    }
}


void loop() {
  delay(1000);// wait 1 second
  DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.print(") ");
  
  Serial.println("Motion detected!");	// print on output change

  if (now.hour() >= 20 && now.hour() < 22) {

    // adjust the playback volume for dusk
	  AudioOutI2S.volume(13);
    Serial.println("It's dusk!");	

    switch (random(1,5)) {
      case 1:
        Serial.println("Playing Twittr10.wav");
        AudioOutI2S.play(Twittr10);
        break;
     
      case 2:
        Serial.println("Playing Twittr11.wav");
        AudioOutI2S.play(Twittr11);
        break;   
      
      case 3:
        Serial.println("Playing Twittr12.wav");
        AudioOutI2S.play(Twittr12);
        break;

      case 4:
        Serial.println("Playing Twittr13.wav");
        AudioOutI2S.play(Twittr13);
        break;
    }
  }	

  if (now.hour() >= 22 || now.hour() <= 6) {

    // adjust the playback volume for night time
	  AudioOutI2S.volume(5);
    Serial.println("It's night!");	

    switch (random(1,8)) {		
      case 1:
        Serial.println("Playing Twittr22.wav");
        AudioOutI2S.play(Twittr22);
        break;   
      
      case 2:
        Serial.println("Playing Twittr23.wav");
        AudioOutI2S.play(Twittr23);
        break;
     
      case 3:
        Serial.println("Playing Twittr28.wav");
        AudioOutI2S.play(Twittr28);
        break;

      case 4:
        Serial.println("Playing Twittr29.wav");
        AudioOutI2S.play(Twittr29);
        break;

      case 5:
        Serial.println("Playing Twittr30.wav");
        AudioOutI2S.play(Twittr30);
        break;

      case 6:
        Serial.println("Playing Twittr31.wav");
        AudioOutI2S.play(Twittr31);
        break;

      case 7:
        Serial.println("Playing Twittr32.wav");
        AudioOutI2S.play(Twittr32);
        break;
    }
  }
  
  if (now.hour() > 6 && now.hour() < 8) {

    // adjust the playback volume for dawn
	  AudioOutI2S.volume(8);
    Serial.println("It's dawn!");	

    switch (random(1,5)) {
      case 1:
        Serial.println("Playing Twittr10.wav");
        AudioOutI2S.play(Twittr10);
        break;
     
      case 2:
        Serial.println("Playing Twittr11.wav");
        AudioOutI2S.play(Twittr11);
        break;   
      
      case 3:
        Serial.println("Playing Twittr12.wav");
        AudioOutI2S.play(Twittr12);
        break;

      case 4:
        Serial.println("Playing Twittr13.wav");
        AudioOutI2S.play(Twittr13);
        break;
    }
  }	
	
  if (now.hour() >= 8 && now.hour() < 20) {
    // adjust the playback volume for day time
	  AudioOutI2S.volume(13);
    Serial.println("It's day!");	
    
    switch (random(1,22)) {
      case 1:
        Serial.println("Playing Twittr01.wav");
        AudioOutI2S.play(Twittr01);
        break;
     
      case 2:
        Serial.println("Playing Twittr02.wav");
        AudioOutI2S.play(Twittr02);
        break;

      case 3:
        Serial.println("Playing Twittr03.wav");
        AudioOutI2S.play(Twittr03);
        break;

      case 4:
        Serial.println("Playing Twittr04.wav");
        AudioOutI2S.play(Twittr04);
        break;

      case 5:
        Serial.println("Playing Twittr07.wav");
        AudioOutI2S.play(Twittr07);
        break;
		    
      case 6:
        Serial.println("Playing Twittr08.wav");
        AudioOutI2S.play(Twittr08);
        break;        

      case 7:
        Serial.println("Playing Twittr10.wav");
        AudioOutI2S.play(Twittr10);
        break;
		    
      case 8:
        Serial.println("Playing Twittr11.wav");
        AudioOutI2S.play(Twittr11);
        break;
     
      case 9:
        Serial.println("Playing Twittr12.wav");
        AudioOutI2S.play(Twittr12);
        break;

      case 10:
        Serial.println("Playing Twittr13.wav");
        AudioOutI2S.play(Twittr13);
        break;
        
      case 11:
        Serial.println("Playing Twittr16.wav");
        AudioOutI2S.play(Twittr16);
        break;         
        
      case 12:
        Serial.println("Playing Twittr19.wav");
        AudioOutI2S.play(Twittr19);
        break;          

      case 13:
        Serial.println("Playing Twittr20.wav");
        AudioOutI2S.play(Twittr20);
        break;

      case 14:
        Serial.println("Playing Twittr25.wav");
        AudioOutI2S.play(Twittr25);
        break;

      case 15:
        Serial.println("Playing Twittr26.wav");
        AudioOutI2S.play(Twittr26);
        break;
        
      case 16:
        Serial.println("Playing Twittr27.wav");
        AudioOutI2S.play(Twittr27);
        break;         
        
      case 17:
        Serial.println("Playing Twittr28.wav");
        AudioOutI2S.play(Twittr28);
        break;          

      case 18:
        Serial.println("Playing Twittr29.wav");
        AudioOutI2S.play(Twittr29);
        break;
		    
      case 19:
        Serial.println("Playing Twittr30.wav");
        AudioOutI2S.play(Twittr30);
        break;         
        
      case 20:
        Serial.println("Playing Twittr31.wav");
        AudioOutI2S.play(Twittr31);
        break;          

      case 21:
        Serial.println("Playing Twittr32.wav");
        AudioOutI2S.play(Twittr32);
        break;
    }      
}    
      
  delay(120000);// wait 120 seconds
  Serial.println("Motion ended!");	// print on output change
  Serial.println("Going to sleep...");	// uncomment for debugging    
   
 
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
