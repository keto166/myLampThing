#include <FastLED.h>
#define NUM_LEDS 21
#define DATA_PIN 5
#define WAVELENGTH 768 // # of steps peak-to-peak 
#define MAXBRIGHT 255  // maximum brightness level (min is 0)
#define DELAY_MS 100   // delay before updating colors, in ms

/*
  we're going to use a triangle wave that's truncated below 0, like so:
  MAX |\                  /\
      | \                /  \
      |  \              /    \
      |   \            /      \
  0___|____\__________/________\_
      |

  but then overlay 3 of these, one each for R, G, B:
      R    G    B         R    G
  MAX |\   /\   /\  oops  /\   /\
      | \ /  \ /  \      /  \ /
      |  X    X    \    /    X
      | / \  / \    \  /    / \
  0___|/___\/___\____\/____/___\_
      |

  so really we want to cut off half of the negative (zero) part of the cycle:
  MAX |\             /\
      | \           /  \
      |  \         /    \
      |   \       /      \
  0___|____\_____/________\_
      |

  for this pattern:
      R    G    B    R    G    B
  MAX |\   /\   /\   /\   /\   /\
      | \ /  \ /  \ /  \ /  \ /
      |  X    X    X    X    X
      | / \  / \  / \  / \  / \
  0___|/___\/___\/___\/___\/___\/_
      |

  so, using WAVELENGTH and MAXBRIGHT, we precalculate an array of values sampled
  from the conceptual (dis)continuous function, then shift along those at each
  step, with a different offset for each color
*/

CRGB leds[NUM_LEDS];
int waveform[WAVELENGTH]
void setup() {
  FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS); 
  
  // TODO: delete most of this code by using the FastLED triwave8() func
  //       also look into other provided funcs
  //       (maybe beatsin8 would be even better?)

  /*
    start moving upward from the wave minimum, so we're going to generate this:
    MAX |     /\
        |    /  \
    0___|___/____\_
  */
  double slope = MAXBRIGHT / (WAVELENGTH / 3);
  int val = -1 * MAXBRIGHT;
  for (int i=0; i < WAVELENGTH; i++) {
    // TODO: probably going to be some errors in here
    // wrt int -> double -> int conversion
    
    // clamp to 0 while val is negative
    if (val >= 0) {
      waveform[i] = val;
    } else {
      waveform[i] = 0;
    }

    val = floor(val + slope);

    // once we hit max, start going down
    if (val >= MAXBRIGHT) {
      val = MAXBRIGHT;
      slope *= -1;
    }
  }
}

// these offsets will make the cycle start at 100% red,
// as in the diagram above
int Ridx = (2 * WAVELENGTH) / 3;
int Gidx = WAVELENGTH / 3;
int Bidx = 0;
void loop() {
  // scan through the full waveform to assign a different value
  // to each LED, looping back to the start as necessary
  for(int n=0; n < NUM_LEDS; n++) {
    leds[n].r = waveform[Ridx];
    leds[n].g = waveform[Gidx];
    leds[n].b = waveform[Bidx];

    Ridx = (Ridx + 1) % WAVELENGTH;
    Gidx = (Gidx + 1) % WAVELENGTH;
    Bidx = (Bidx + 1) % WAVELENGTH;
  }
  
  FastLED.show();
  delay(DELAY_MS);
}
