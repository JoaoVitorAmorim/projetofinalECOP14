/* ########################################################################

   PICsim - PIC simulator http://sourceforge.net/projects/picsim/

   ########################################################################

   Copyright (c) : 2015  Luis Claudio Gamb?a Lopes

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   For e-mail suggestions :  lcgamboa@yahoo.com
   ######################################################################## */

#ifndef _18F4550
#include "i2c.h"

void delay(void) {
    unsigned int i;
    volatile unsigned char j, k;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 41; j++) {
            for (k = 0; k < 3; k++);
        }
    }
}

void i2c_init(void) {
    TIDAT = 0;
    ICLK = 1;
    IDAT = 1;
}

void i2c_start(void) {
    ICLK = 1;
    IDAT = 1;
    delay();
    IDAT = 0;
    delay();
}

void i2c_stop(void) {
    ICLK = 1;
    IDAT = 0;
    delay();
    IDAT = 1;
    delay();
}

void i2c_wb(unsigned char val) {
    unsigned char i;
    ICLK = 0;
    for (i = 0; i < 8; i++) {
        IDAT = ((val >> (7 - i))& 0x01);
        ICLK = 1;
        delay();
        ICLK = 0;
    }
    IDAT = 1;
    delay();
    ICLK = 1;
    delay();
    ICLK = 0;
}

unsigned char i2c_rb(unsigned char ack) {
    char i;
    unsigned char ret = 0;

    ICLK = 0;
    TIDAT = 1;
    IDAT = 1;
    for (i = 0; i < 8; i++) {
        ICLK = 1;
        delay();
        ret |= (IDAT << (7 - i));
        ICLK = 0;
    }
    TIDAT = 0;
    if (ack)
        IDAT = 0;
    else
        IDAT = 1;
    delay();
    ICLK = 1;
    delay();
    ICLK = 0;

    return ret;
}

#endif


