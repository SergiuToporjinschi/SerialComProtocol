/*

  SettingsManager

  Copyright (C) 2017 by Sergiu Toporjinschi <sergiu dot toporjinschi at gmail dot com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  
  dependency:
  ArduinoJson: https://arduinojson.org/
  
*/
#include "SoftwareSerial.h"
#include "debug_macro.h"

#include "SerialTrigger.h"
#include <Arduino.h>

SoftwareSerial *dbg;
void setup() {
  // pinMode(13, INPUT);
  // pinMode(A3, OUTPUT);
  // dbg = new SoftwareSerial(A4, A3);
  pinMode(13, INPUT);
  pinMode(15, OUTPUT);
  dbg = new SoftwareSerial(13, 15);

  Serial.begin(74880);
  dbg->begin(74880);


  SerialTrigger::init(&Serial);

  SerialTrigger::addKeyCallEvent("conf", [](const char *cmd, const char *value) {
    DBGLN("cmd: %s; value: %s", cmd == nullptr ? "null" : cmd, value == nullptr ? "null" : value);
  });
}

void loop() {
  SerialTrigger::handle();
}
