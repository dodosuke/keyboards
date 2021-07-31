/*
Copyright 2020 sekigon-gonnoc

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "rev1.h"

#ifdef OLED_DRIVER_ENABLE

#include "oled_driver.h"
#include "progmem.h"

void render_logo(void) {
    static const char PROGMEM logo[] = {
        0x00, 0x00, 0x00, 0x00, 0xa0, 0x40, 0x10, 0x00, 0x14, 0x04, 0x10, 0x04, 0x10, 0x08, 0x00, 0x10,
        0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x40, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,
        0x14, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x48, 0x02, 0xd2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x21, 0xcb, 0x12, 0x28, 0x00, 0x00, 0x00, 0x42, 0x2d, 0xa2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x04, 0x56, 0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8a, 0x04, 0x41, 0x04, 0x40, 0x22, 0x00, 0x6c,
        0x04, 0x90, 0x00, 0x00, 0x00, 0x00, 0xd4, 0x21, 0x8c, 0x04, 0x02, 0x00, 0x06, 0x0a, 0x09, 0x06,
        0xd0, 0x10, 0x80, 0x00, 0x00, 0x04, 0x01, 0x48, 0xa2, 0x10, 0x06, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x46, 0x10, 0x25, 0x00, 0x00, 0x00, 0x05, 0x00, 0x03, 0x00, 0x82, 0x45, 0x20, 0x12, 0x0c, 0x06,
        0x01, 0x00, 0x00, 0xa0, 0x48, 0x10, 0x96, 0x00, 0xc2, 0x81, 0x41, 0x82, 0x40, 0x8c, 0xc0, 0x20,
        0x00, 0x00, 0x00, 0x95, 0x24, 0xf1, 0x08, 0x00, 0x05, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x04, 0x02, 0x18, 0x00, 0x20, 0x00, 0x08, 0x0c, 0x24, 0x10, 0x00, 0x24,
        0x4e, 0x00, 0x42, 0x00, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x16, 0x60, 0x10, 0x30, 0x00, 0x08, 0x08,
        0x01, 0x22, 0x04, 0x00, 0x00, 0x00, 0x02, 0x09, 0x10, 0x01, 0x18, 0x30, 0x04, 0x0c, 0x04, 0x20,
        0x12, 0x28, 0x00, 0x00, 0x00, 0x00, 0x08, 0x12, 0x21, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14,
        0x02, 0x18, 0x21, 0x00, 0x00, 0x00, 0x00, 0x11, 0x0a, 0x24, 0x28, 0x00, 0x58, 0x00, 0x00, 0x00,
        0x31, 0x07, 0x29, 0x00, 0x00, 0x20, 0x08, 0x20, 0x24, 0x00, 0x12, 0x00, 0x20, 0x30, 0x00, 0x10,
        0x08, 0x00, 0x00, 0x01, 0x00, 0x17, 0x00, 0x2c, 0x00, 0x10, 0x08, 0x10, 0x10, 0x08, 0x04, 0x00,
        0x00, 0x00, 0x00, 0x2a, 0x29, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    oled_write_raw_P(logo, sizeof(logo));
}
#endif

