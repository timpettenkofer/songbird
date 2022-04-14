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

// code to reduce power consumption
// disable ADC
ADCSRA = 0;  

// turn off brown-out enable in software
MCUCR = bit (BODS) | bit (BODSE);  // turn on brown-out enable select
MCUCR = bit (BODS);        // this must be done within 4 clock cycles of above
interrupts ();             // guarantees next instruction executed
sleep_cpu ();              // sleep within 3 clock cycles of above

int ledPin = LED_BUILTIN;       // choose the pin for the LED
int inputPin = 7;               // choose the digital input pin (for PIR sensor)

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
const char filename15[] = "Twittr15.wav";
const char filename16[] = "Twittr16.wav";
const char filename17[] = "Twittr17.wav";
const char filename18[] = "Twittr18.wav";
const char filename19[] = "Twittr19.wav";
const char filename20[] = "Twittr20.wav";
const char filename21[] = "Twittr21.wav";
const char filename22[] = "Twittr22.wav";
const char filename23[] = "Twittr23.wav";
const char filename24[] = "Twittr24.wav";

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
SDWaveFile Twittr15;
SDWaveFile Twittr16;
SDWaveFile Twittr17;
SDWaveFile Twittr18;
SDWaveFile Twittr19;
SDWaveFile Twittr20;
SDWaveFile Twittr21;
SDWaveFile Twittr22;
SDWaveFile Twittr23;
SDWaveFile Twittr24;
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
  Serial.print("Sensor is ready");     

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
  Serial.print("RTC is up and running.");

// setup the SD card, depending on your shield of breakout board	
  Serial.println("Initializing SD card...");	

  if (!SD.begin()) {	
    Serial.print("initialization failed!");	
    return;	
    }	
    Serial.print("initialization done.");	
  
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
  Twittr15 = SDWaveFile(filename15);
  Twittr16 = SDWaveFile(filename16);
  Twittr17 = SDWaveFile(filename17);
  Twittr18 = SDWaveFile(filename18);
  Twittr19 = SDWaveFile(filename19);
  Twittr20 = SDWaveFile(filename20);
  Twittr21 = SDWaveFile(filename21);
  Twittr22 = SDWaveFile(filename22);
  Twittr23 = SDWaveFile(filename23);
  Twittr24 = SDWaveFile(filename24);
  
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
  if (!Twittr21) {
    Serial.println("Error opening Twitter21.wav");
    while (true);
	}
  if (!Twittr22) {
    Serial.println("Error opening Twitter22.wav");
    while (true);
	}
  if (!Twittr23) {
    Serial.println("Error opening Twitter23.wav");
    while (true);
	}
  if (!Twittr24) {
    Serial.println("Error opening Twitter24.wav");
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
  if (!AudioOutI2S.canPlay(Twittr21)) {	
    Serial.println("Unable to play Twittr21.wav using I2S!");	
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
  if (!AudioOutI2S.canPlay(Twittr24)) {	
    Serial.println("Unable to play Twittr24.wav using I2S!");	
    while (1); // do nothing	
    }
}


void loop() {
  DateTime now = rtc.now();
  
  Serial.println("Motion detected!");	// print on output change

  if (now.hour() >= 22 || now.hour() <= 6) {

    // adjust the playback volume for night time
	  AudioOutI2S.volume(5);	

    switch (random(1,6)) {		//play Twittr21 with a higher possiblity
      case 1:
        Serial.println("Playing Twittr21.wav");
        AudioOutI2S.play(Twittr21);
        break;
     
      case 2:
        Serial.println("Playing Twittr21.wav");
        AudioOutI2S.play(Twittr21);
        break;
		    
      case 3:
        Serial.println("Playing Twittr22.wav");
        AudioOutI2S.play(Twittr22);
        break;   
      
      case 4:
        Serial.println("Playing Twittr23.wav");
        AudioOutI2S.play(Twittr23);
        break;
     
      case 5:
        Serial.println("Playing Twittr24.wav");
        AudioOutI2S.play(Twittr24);
        break;   
    }
  }
  
  if (now.hour() > 6 && now.hour() < 8) {

    // adjust the playback volume for dawn
	  AudioOutI2S.volume(10);	

    switch (random(1,4)) {
      case 1:
        Serial.println("Playing Twittr10.wav");
        AudioOutI2S.play(Twittr21);
        break;
     
      case 2:
        Serial.println("Playing Twittr11.wav");
        AudioOutI2S.play(Twittr22);
        break;   
      
      case 3:
        Serial.println("Playing Twittr12.wav");
        AudioOutI2S.play(Twittr21);
        break;
    }
  }	
	
  else {
    // adjust the playback volume for day time
	  AudioOutI2S.volume(15);	
    
    switch (random(1,21)) {
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
        Serial.println("Playing Twittr05.wav");
        AudioOutI2S.play(Twittr05);
        break;
        
      case 6:
        Serial.println("Playing Twittr06.wav");
        AudioOutI2S.play(Twittr06);
        break;          

      case 7:
        Serial.println("Playing Twittr07.wav");
        AudioOutI2S.play(Twittr07);
        break;
		    
      case 8:
        Serial.println("Playing Twittr08.wav");
        AudioOutI2S.play(Twittr08);
        break;
        
      case 9:
        Serial.println("Playing Twittr09.wav");
        AudioOutI2S.play(Twittr09);
        break;          

      case 10:
        Serial.println("Playing Twittr10.wav");
        AudioOutI2S.play(Twittr10);
        break;
		    
      case 11:
        Serial.println("Playing Twittr11.wav");
        AudioOutI2S.play(Twittr11);
        break;
     
      case 12:
        Serial.println("Playing Twittr12.wav");
        AudioOutI2S.play(Twittr12);
        break;

      case 13:
        Serial.println("Playing Twittr13.wav");
        AudioOutI2S.play(Twittr13);
        break;
          
      case 15:
        Serial.println("Playing Twittr15.wav");
        AudioOutI2S.play(Twittr15);
        break;
        
      case 16:
        Serial.println("Playing Twittr16.wav");
        AudioOutI2S.play(Twittr16);
        break;          

      case 17:
        Serial.println("Playing Twittr17.wav");
        AudioOutI2S.play(Twittr17);
        break;
		    
      case 18:
        Serial.println("Playing Twittr18.wav");
        AudioOutI2S.play(Twittr18);
        break;
        
      case 19:
        Serial.println("Playing Twittr19.wav");
        AudioOutI2S.play(Twittr19);
        break;          

      case 20:
        Serial.println("Playing Twittr20.wav");
        AudioOutI2S.play(Twittr20);
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
