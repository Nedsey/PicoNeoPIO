#include "blink.h"
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

int pixelCount; 
Pixel *arrayPixels;
uint pin; //the GPIO pin on the RP2040 that will be used for sending DATA (the middle pin) to the WS2812B's. Must be assigned with initPixels method
PIO pio = pio0; //choose pio0 or pio1 
uint offset; //adds the PIO assembly program to memory and returns the offset in the var
uint sm; //automatically finds a state machine not in use, there are 4 state machines in each PIO. You can manually allocate one but it's not reccomended

//simply sets the variables to their needed values, 
void declares() { 
    offset = pio_add_program(pio, &neopxl_program);
    sm = pio_claim_unused_sm(pio, true);
    neopxl_program_init(pio, sm, offset, pin); //view signal_gen.pio to see contents of this method
}

//instalizes the desired GPIO pin and creates array of specified size. Must be run before any other process
void initPixels(int GPIO, int pixelCounts){ 
    pin = GPIO;
    pixelCount = pixelCounts;
    declares();
    arrayPixels = malloc(pixelCount * sizeof(Pixel));

    if (arrayPixels == NULL) {
        exit(1);
    }

    for (int i = 0; i < pixelCount; i++) {
        arrayPixels[i].redColor = 0;
        arrayPixels[i].blueColor = 0;
        arrayPixels[i].greenColor = 0;
    }
}

//converts our RGB decimal values, (255,255,255) to binary for the PIO assembly script to understand. Sends 3 8 bit values, totaling 24 bits.
int convColor(int red, int blue, int green) {
    int output = 0;
    int colors[3] = {blue, red, green};
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 8; j++) {
            if(colors[i] & (1 << (7 - j))) {
                output |= 1 << (i * 8 + j);
            }
        }
    }
    return output;
}

//edits arrayPixels array to set new color for the specified pixel, then runs a for loop to update the colors on the neopixels.
void setPixel(int pixel, int red, int green, int blue){
    sleep_us(300);
    arrayPixels[pixel].redColor = red;
    arrayPixels[pixel].greenColor = green;
    arrayPixels[pixel].blueColor = blue;

    for(int i=0; i< pixelCount; i++){
        pio_sm_put_blocking(pio, sm, convColor(arrayPixels[i].redColor,  arrayPixels[i].greenColor, arrayPixels[i].blueColor));
    }


}

//runs a for loop on the setPixel function with a singular color. Useful for checking if the neopixels are connected correctly.
void fillPixels(int red, int green, int blue){
    sleep_us(210);
    for(int i=0; i< pixelCount; i++){
        setPixel(i,red,green,blue);
}
}


//resets all pixels to (0,0,0). Makes all the neopixels appear off and removes all array data. Useful for resetting pixels after running a previous program without resetting the power.
void resetPixels(){
    for(int i=0; i< pixelCount; i++){
        pio_sm_put_blocking(pio, sm, convColor(arrayPixels[i].redColor = 0,  arrayPixels[i].greenColor = 0, arrayPixels[i].blueColor = 0));
    }
}

int randColor(){
    int r = rand() % 256;
    return r;
}


int getPixelValue(int pixel, char value[]){
    if (strcmp(value,"red") == 0){
        return arrayPixels[pixel].redColor;
    }
    if (strcmp(value,"green") == 0){
        return arrayPixels[pixel].greenColor;
    }
    if (strcmp(value,"blue") == 0){
        return arrayPixels[pixel].blueColor;
    }
}

//control panel for actually editing the neopixels. Always run initPixels first. 
int main(){
    initPixels(0,17);
    while (true){
        for(int i=0; i<pixelCount; i++){
            int r = getPixelValue(i, "red");
            int g = getPixelValue(i, "green");
            int b = getPixelValue(i, "blue");
            int nextR = (r + 1) % 256;
            int nextG = (g + 1) % 256;
            int nextB = (b + 1) % 256;
            setPixel(i, nextR, nextG, nextB);
            sleep_ms(10);
        }
    }
    return 0;
}
