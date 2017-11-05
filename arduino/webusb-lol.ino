/*
  LOL Shield for WebUSB

  Copyright 20017 Edwin Martin <edwin@bitstorm.org> https://bitstorm.org/

  Contains code from Benjamin Sonntag:
  Copyright 2009/2010 Benjamin Sonntag <benjamin@sonntag.fr> http://benjamin.sonntag.fr/
  
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330,
  Boston, MA 02111-1307, USA.
*/

#include <WebUSB.h>
#include <EEPROM.h>
#include "Charliplexing.h"
#include "Font.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

WebUSB WebUSBSerial(1, "bitstorm.org/webusb/lol/");

#define Serial WebUSBSerial

const int maxLength = 100;
int lolPosition = 0;
int i = 0;
bool serialInitialised = false;
int8_t x = DISPLAY_COLS;
const char magic[] = "LolS";
const int magicSize = 4;
char json[200];

char lolText[maxLength];

void setup() {
    byte c;

    if (EEPROM.read(0) == magic[0] && EEPROM.read(1) == magic[1] && EEPROM.read(2) == magic[2] && EEPROM.read(3) == magic[3]) {
        for (int i = 0; c; i++) {
            c = EEPROM.read(i + magicSize);
            lolText[i] = c;
        }
    } else {
        strcpy(lolText, "HELLO WORLD!   ");
    }

    LedSign::Init();
}

void loop() {
    if (Serial && !serialInitialised) {
        Serial.begin(9600);
        serialInitialised = true;
    }

    while (Serial && Serial.available()) {
        int byte = Serial.read();

        if (byte == '\n' || lolPosition == maxLength - 1) {
            if (lolPosition == 0) {
                Serial.write(lolText);
                Serial.write("\r\n");
                Serial.flush();
            } else {
                lolText[lolPosition] = '\0';
                EEPROM.write(lolPosition + magicSize, '\0');
                lolPosition = 0;
            }
        } else {
            if (lolPosition == 0) {
                EEPROM.write(0, magic[0]);
                EEPROM.write(1, magic[1]);
                EEPROM.write(2, magic[2]);
                EEPROM.write(3, magic[3]);
            }
            lolText[lolPosition] = byte;
            EEPROM.write(lolPosition + magicSize, byte);
            lolPosition++;
        }
        Serial.flush();
    }

    LedSign::Clear();
    for (int8_t x2 = x, i2 = i; x2 < DISPLAY_COLS;) {
        int8_t w = Font::Draw(lolText[i2], x2, 0);
        x2 += w;
        i2 = (i2 + 1) % strlen(lolText);
        if (x2 <= 0) {	// off the display completely?
            x = x2;
            i = i2;
        }
    }
    x--;
    delay(80);
}
