# TinyI2C
Tiny I2C is a small C library implementing a simple interface to the [Inter-Integrated Circuit](https://en.wikipedia.org/wiki/I%C2%B2C) bus (I2C), such as is available on a Raspberry Pi. A further extension is included to use the [MCP23017 I2C 16-IO Expander](https://cdn-shop.adafruit.com/datasheets/mcp23017.pdf) available at [Adafruit](https://www.adafruit.com/product/732).

## Usage
```c
// for a raw interface to I2C
// #include "tinyi2c.h"

#include "tinymcp23017.h"

// declare the structure
TinyMCP23017 ti2c;

// open the i2c interface
tmcp23017_open(&ti2c, "/dev/i2c-1");

// turn off all outputs
tmcp23017_clear(&ti2c);

// write an on/off value to a specific pin
tmcp23017_write_pin(&ti2c, pin_index, false);

// close the interface
tmcp23017_close(&ti2c);
```

## License
This code is released under the [ISC License](https://opensource.org/licenses/ISC).
