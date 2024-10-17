#include <FastLED.h>
#define NUM_LEDS 21
#define DATA_PIN 5
CRGB leds[NUM_LEDS];
int halfWaveLength = 8; //the number of segments ahead and behind a moving peak until the
int numColorPeaks = 5; //NUM_LEDS / halfWaveLength (Round down) + 2
long cylcleTime = 30000; //How many ms it takes a color to move one halfWaveLength
float peakPosition[numColorPeaks];
int peakColors[numColorPeaks][3];
int delayTime = 500;




void setup() { FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS); 
  for (int i = 0; i <numColorPeaks; i++) {
    resetColor(i);
    peakPosition[i] = (i - 1) * halfWaveLength;
  }
}

void resetColor(int i) [
  
  peakColors[i][0] = random(0,254); //red value
  peakColors[i][1] = random(0,254); //grn value
  peakColors[i][2] = random(0,254); //blu value
  
]
void loop() {

  //Move peaks by time
  for (int i = 0; i <numColorPeaks; i++) {
    peakPosition[i] = peakPosition[i] + delayTime / cylcleTime * halfWaveLength;

    //Check if any peaks are past (numColorPeaks - 2 ) * halfWaveLength.  If so, move them back by numColorPeaks * halfWaveLength (sent back to beginning)
    if (peakPosition[i] > ((numColorPeaks - 2 ) * halfWaveLength))) {
      peakPosition[i] =peakPosition[i] - numColorPeaks * halfWaveLength;
      resetColor(i);
    }
  }
    

  //Calculate all segment color mixes
  for (int n = 0; n < NUM_LEDS; n++) {
    //set all colors to off
    leds[n].r = 0;
    leds[n].g = 0;
    leds[n].b = 0;
    
  }
  //cycle through the peaks
  int segStart;
  float distanceProp;
  for (int i = 0; i <numColorPeaks; i++) { //cycling through the peaks
      segStart = ((int) peakPosition[i]) +1;
      for (int j = segStart; j < (segStart + 2 * halfWaveLength - 1); j++) { //cycling through the segments attached to that peak
      if ((j > 0) && (j <= NUM_LEDS) ) {//Check if this is an actual led
        distanceProp = abs((peakPosition[i] - j) / halfWaveLength);
        leds[n].r = leds[n].r + (int) (distanceProp * peakColors[i][0]);
        leds[n].g = leds[n].g + (int) (distanceProp * peakColors[i][1]);
        leds[n].b = leds[n].b + (int) (distanceProp * peakColors[i][2]);
        }
      }
  }

  FastLED.show();
  delay(delayTime);

}
