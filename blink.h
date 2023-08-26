#ifndef BLINK.H
#define BLINK.H

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "signal_gen.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    int redColor;
    int blueColor;
    int greenColor;
} Pixel;

extern int pixelCount;
extern Pixel *arrayPixels;
extern uint pin;
extern PIO pio;
extern uint offset;
extern uint sm;

void declares();
void initPixels(int GPIO, int pixelCounts);
int convColor(int red, int blue, int green);
void setPixel(int pixel, int red, int green, int blue);
void fillPixels(int red, int green, int blue);
void resetPixels();
int randColor();
int getPixelValue(int pixel, char value[]);

#endif /* BLINK_H */
