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

#include "tiny_i2c.h"

#include <assert.h>
#include <stdio.h>

#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include <stdio.h>

// sudo i2cdetect -y 1

/**
 * e.g. "/dev/i2c-1"
 */
void tinyI2C_open(TinyI2C *o, const char *i2cFilename) {
  o->i2cDesc = open(i2cFilename, O_RDWR);
  if(o->i2cDesc < 0) {
    fprintf(stderr, "Could not open file '%s'\n", i2cFilename);
    assert(false);
  }
}

void tinyI2C_close(TinyI2C *o) {
  int ret = close(o->i2cDesc);
  if (ret < 0) {
     fprintf(stderr, "Could not close i2c file\n");
     assert(false);
  }
  o->i2cDesc = -1;
}

int tinyI2C_write(TinyI2C *o, uint8_t deviceAddress, uint8_t reg_addr, uint8_t data) {
  assert(o->i2cDesc >= 0);

  uint8_t buffer[2];
  buffer[0] = reg_addr;
  buffer[1] = data;

  struct i2c_rdwr_ioctl_data packets;
  struct i2c_msg messages[1];
  messages[0].addr = deviceAddress;
  messages[0].flags = 0;
  messages[0].len = sizeof(buffer);
  messages[0].buf = buffer;

  packets.msgs = messages;
  packets.nmsgs = 1;

  int ret = ioctl(o->i2cDesc, I2C_RDWR, &packets);
  if (ret < 0) {
    fprintf(stderr, "Write to I2C Device (dev/reg: 0x%x/0x%x) failed (ret=%i)\n",
        deviceAddress, reg_addr, ret);
  }

  return ret;
}
