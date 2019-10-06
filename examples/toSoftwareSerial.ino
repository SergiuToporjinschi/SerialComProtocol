/*

  SerialComProtocol

  Copyright (C) 2019 by Sergiu Toporjinschi <sergiu dot toporjinschi at gmail dot com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation version 3.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  
  All rights reserved

*/
#include "SoftwareSerial.h"
#include "debug_macro.h"

#include "SerialComProtocol.h"
#include <Arduino.h>

Print *dbg;
void setup() {
  // pinMode(13, INPUT);
  // pinMode(A3, OUTPUT);
  // SoftwareSerial softSerial(A4, A3);
  pinMode(13, INPUT);
  pinMode(15, OUTPUT);
  SoftwareSerial softSerial(13, 15);

  Serial.begin(74880);
  softSerial.begin(74880);
  dbg = &softSerial;

  SerialComProtocol::init(&Serial);

  SerialComProtocol::addKeyCallEvent("conf", [](const char *cmd, const char *value) {
    DBGLN("cmd: %s; value: %s", cmd == nullptr ? "null" : cmd, value == nullptr ? "null" : value);
  });
}

void loop() {
  SerialComProtocol::handle();
}
