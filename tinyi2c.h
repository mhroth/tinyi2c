/**
 * Copyright (c) 2017, Martin Roth (mhroth@gmail.com)
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

// http://hertaville.com/interfacing-an-i2c-gpio-expander-mcp23017-to-the-raspberry-pi-using-c.html

#include <stdint.h>

#if __cplusplus
extern "C" {
#endif

typedef struct {
  int32_t i2cDesc;  // i2c device descriptor
} TinyI2C;

/** Open the I2C bus. */
void tinyI2C_open(TinyI2C *o, const char *i2cFilename);

/** Close the I2C bus. */
void tinyI2C_close(TinyI2C *o);

/**
 * This function writes a byte of data "data" to a specific register
 * "reg_addr" in the I2C device This involves sending these two bytes
 * in order to the i2C device by means of the ioctl() command. Since
 * both bytes are written (no read/write switch), both pieces
 * of information can be sent in a single message (i2c_msg structure)
 *
 * @param o  Pointer to the tinyI2C object
 * @param deviceAddress  The address of the target i2c device e.g. 0x20 + [0-127] (i.e. the chip address)
 * @param reg_addr  The register to write to [0-15] (i.e. the local GPIO pin)
 * @param data  The (char) data to write (e.g. 0 or 1) (i.e. ON or OFF)
 *
 * @return 0 if successful, negative error code otherwise.
 */
int tinyI2C_write(TinyI2C *o, uint8_t deviceAddress, uint8_t reg_addr, uint8_t data);

#if __cplusplus
}
#endif
