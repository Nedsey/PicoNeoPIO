# NeoPicoDriver

An efficient and lightweight NeoPixel driver library for the Raspberry Pi Pico, leveraging the PIO functionality of the RP2040 microcontroller for precise and flexible control of WS2812B LEDs.

## Requirements

This library is developed using the C/C++ SDK for the Raspberry Pi Pico (pico-sdk). You will need to install the pico-sdk to compile and run the code. Installation instructions can be found [here](https://github.com/raspberrypi/pico-sdk).

Note: The library is currently compatible with the pico-sdk only. A MicroPython version will be made available soon.

## Installation

1. Clone the repository to your local machine:
```git clone https://github.com/nedsey/NeoPicoDriver.git```
2. Navigate to the folder containing the repository:
```cd NeoPicoDriver```
3. Add the `PICO_SDK_PATH` to your path:
```export PICO_SDK_PATH=path/to/your/pico-sdk```
Replace `path/to/your/pico-sdk` with the actual path to your `pico-sdk` folder.

4. Build the project:
```
mkdir build
cd build
cmake ..
make
```

# Usage

Include the `NeoPicoDriver` library in your project and initialize the pixels:

```c
#include "NeoPicoDriver.h"

int main() {
    initPixels(0, 17);
    ...
}
```