#include <FastLED.h>
#define NUM_LEDS 21
#define DATA_PIN 5
CRGB leds[NUM_LEDS];
int halfWaveLength = 8; //the number of segments ahead and behind a moving peak until the
int numColorPeaks = 5; //NUM_LEDS / halfWaveLength (Round down) + 2
long cylcletime = 30000; //How many ms it takes a color to move halfWaveLength
float peakPosition[numColorPeaks];
int peakColors[numColorPeaks][3];
int delayTime = 500;



void setup() { FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); 
  for (int i = 0; i <numColorPeaks; i++) {
    resetColor(i);
    peakPosition[i] = (i - 1) * halfWaveLength;
  }
}

void resetColor(int i) [
  for (int rgb = 0; i < 2; rgb++) {
    peakColors[i][rgb] = random(0,254);
  }
]
void loop() {

  //Move peaks by time
    //Check if any peaks are past (numColorPeaks - 2 ) * halfWaveLength.  If so, move them back by numColorPeaks * halfWaveLength

  //Calculate all segment color mixes
  FastLED.show();
  delay(delayTime);

  leds[0] = CRGB::White; FastLED.show(); delay(30);
  leds[0] = CRGB::Black; FastLED.show(); delay(30);
}