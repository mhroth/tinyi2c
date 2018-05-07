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

#include <stdbool.h>

#include "tinyi2c.h"

#if __cplusplus
extern "C" {
#endif

typedef struct {
  TinyI2C ti2c;
  uint8_t gpio[16]; // alternating GPIOA/GPIOB for up to 8 MCP23017
} TinyMCP23017;

void tmcp23017_open(TinyMCP23017 *o, const char *i2cFilename);

void tmcp23017_close(TinyMCP23017 *o);

/**
 * Update the state of a logical pin. The state is not written to the device.
 *
 * @param o  Pointer to the tinyMCP23017 object
 * @param pin  The pin index to write to [0-127]
 * @param state  The state (ON or OFF) to assign to the pin
 *
 * @return 0 if successful, negative error code otherwise.
 */
void tmcp23017_set_pin(TinyMCP23017 *o, uint8_t pin, bool state);

/**
 * Update the state of a logical pin and write it to the device.
 *
 * @param o  Pointer to the tinyMCP23017 object
 * @param pin  The pin index to write to [0-127]
 * @param state  The state (ON or OFF) to assign to the pin
 *
 * @return 0 if successful, negative error code otherwise.
 */
int tmcp23017_write_pin(TinyMCP23017 *o, uint8_t pin, bool state);

/**
 * Write all pin state to the attached devices.
 *
 * @param o  Pointer to the tinyMCP23017 object
 *
 * @return 0 if successful, negative error code otherwise.
 */
int tmcp23017_write(TinyMCP23017 *o);

/**
 * Reset all pins to zero.
 *
 * @param o  Pointer to the tinyMCP23017 object
 *
 * @return 0 if successful, negative error code otherwise.
 */
int tmcp23017_clear(TinyMCP23017 *o);

#if __cplusplus
}
#endif
