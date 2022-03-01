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

10k Poti  to MKR Zero for volume control (optional)
Pin1      to GND
Pin2      to DAC0/A0
Pin3      to VCC

Note: The wav file must be stereo signed 16 bit 44100Hz and filename must be abcdefgh.wav (8-3) formatted.
*/

int ledPin = LED_BUILTIN;       // choose the pin for the LED
int inputPin = 7;               // choose the digital input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int pirValue = 0;               // variable for reading the pin status

#include <SD.h>	
#include <Adafruit_ZeroI2S.h>
#include <ArduinoSound.h>	

// filename of wave file to play
const char filename1[] = "Twittr1.wav";
const char filename2[] = "Twittr2.wav";
const char filename3[] = "Twittr3.wav";
const char filename4[] = "Twittr4.wav";
const char filename5[] = "Twittr5.wav";

// variable representing the Wave File
SDWaveFile Twittr1;
SDWaveFile Twittr2;
SDWaveFile Twittr3;
SDWaveFile Twittr4;
SDWaveFile Twittr5;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);     // declare sensor as input
 
  Serial.begin(9600);
  while (!Serial) {	
	    ; // wait for serial port to connect. Needed for native USB port only	
	  }	
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

 // adjust the playback volume	
	AudioOutI2S.volume(15);	
    
}

void loop() {
    pir();
//  vol();
}

void pir() {
  
  pirValue = digitalRead(inputPin);  // read input value
  if (pirValue == HIGH) {	// check if the input is HIGH
          
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
        
      Serial.println("Motion detected!");	// print on output change

      switch (random(1,6)) {
        case 1:
          Serial.println("Playing Twittr1.wav");
          AudioOutI2S.play(Twittr1);
          if (!AudioOutI2S.isPlaying()) {
            break; // end case after finishing playback
          }          
        case 2:
          Serial.println("Playing Twittr2.wav");
          AudioOutI2S.play(Twittr2);
          if (!AudioOutI2S.isPlaying()) {
            break; // end case after finishing playback
          }
        case 3:
          Serial.println("Playing Twittr3.wav");
          AudioOutI2S.play(Twittr3);
          if (!AudioOutI2S.isPlaying()) {
            break; // end case after finishing playback
          }
        case 4:
          Serial.println("Playing Twittr5.wav");
          AudioOutI2S.play(Twittr5);
          if (!AudioOutI2S.isPlaying()) {
            break; // end case after finishing playback
          } 
        case 5:
          Serial.println("Playing Twittr5.wav");
          AudioOutI2S.play(Twittr5);
          if (!AudioOutI2S.isPlaying()) {
            break; // end case after finishing playback
          } 
      }
      delay(1000);// wait 1 second
      pirState = HIGH;
    
  } 
  else 
  {
    digitalWrite(ledPin, LOW); // turn LED OFF
	
    if (pirState == HIGH)
	{
      Serial.println("Motion ended!");	// print on output change
      pirState = LOW;
    }
  }

}
}

/* UNCOMMENT HERE FOR VOLUME CONTROL AND BELOW "VOID LOOP": VOL();

void vol() {
  // read analog in
  int sensorReading = analogRead(A0);
  // map to a 0-100 range:
  int loudness = map(sensorReading, 0, 1023, 0, 100);
  // set the volume:
  AudioOutI2S.volume(loudness);
  Serial.print("loudness: ");
  Serial.println(loudness);
}
*/
