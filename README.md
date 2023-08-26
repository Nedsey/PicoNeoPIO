# NeoPicoDriver

An efficient and lightweight NeoPixel driver library for the Raspberry Pi Pico, leveraging the PIO functionality of the RP2040 microcontroller for precise and flexible control of WS2812B LEDs. This results in a much faster and more efficent way to speak to the WS2812B's, without making the CPU unavailable for other instructions. 

## Requirements

This library is developed using the C/C++ SDK for the Raspberry Pi Pico (pico-sdk). You will need to install the pico-sdk to compile and run the code. Installation instructions can be found [here](https://github.com/raspberrypi/pico-sdk).

Note: The library is currently compatible with the pico-sdk only. A MicroPython version will be made available soon.

## Installation

1. Clone the repository to your local machine:

```
git clone https://github.com/Nedsey/PicoNeoPIO.git
```

2. Navigate to the folder containing the repository:

```
cd NeoPicoDriver
```

3. Add the `PICO_SDK_PATH` to your path:

```
export PICO_SDK_PATH=path/to/your/pico-sdk
```

Replace `path/to/your/pico-sdk` with the actual path to your `pico-sdk` folder.

4. Build the project:

```
mkdir build
cd build
cmake ..
make
```

## Usage

Include the `NeoPicoDriver` library in your project and initialize the pixels:
(if you don't initialize the pixels, no other functions will work.)
```c
#include "NeoPicoDriver.h"

int main() {
    initPixels(0, 17);
    ...
}
```

### Functions

#### `void initPixels(int GPIO, int pixelCount)`

Initializes the desired GPIO pin and creates an array of the specified size. Must be run before any other process.

Parameters:
- `GPIO`: The GPIO pin on the RP2040 that will be used for sending data to the WS2812B LEDs.
- `pixelCount`: The number of pixels to be controlled.

#### `void setPixel(int pixel, int red, int green, int blue)`

Sets the color of a specified pixel and updates the colors on the NeoPixels.

Parameters:
- `pixel`: The index of the pixel to be set.
- `red`: The red component of the color (0-255).
- `green`: The green component of the color (0-255).
- `blue`: The blue component of the color (0-255).

#### `void fillPixels(int red, int green, int blue)`

Sets all pixels to a specified color.

Parameters:
- `red`: The red component of the color (0-255).
- `green`: The green component of the color (0-255).
- `blue`: The blue component of the color (0-255).

#### `void resetPixels()`

Resets all pixels to (0,0,0), making all the NeoPixels appear off and removing all array data.

#### `int getPixelValue(int pixel, char value[])`

Retrieves the specified color component of a pixel.

Parameters:
- `pixel`: The index of the pixel.
- `value`: The color component to be retrieved ("red", "green", or "blue").

Returns:
- The specified color component of the pixel.

### Example

```c
#include "NeoPicoDriver.h"

int main(){
    initPixels(0,17);
    while (true){
        for (int i = 0; i < pixelCount; i++){
            sleep_ms(35);
            setPixel(i, 255, 0, 0);
         }
        for (int i = pixelCount - 1; i >= 0; i--){
            sleep_ms(35);
            for(int f = 0; f <= 100; f += 5){
                sleep_ms(1);
                setPixel(i, getPixelValue(i, "red") - 5, getPixelValue(i, "green") + 5, getPixelValue(i, "blue") + 5);
            }
         }
    }
    return 0;
}
```

## Credits

Developed by [Nathan Edsey](https://github.com/nedsey)

## License

[MIT License](https://opensource.org/license/mit/)
