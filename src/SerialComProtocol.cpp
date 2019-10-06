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

#include "SerialComProtocol.h"
#include <Arduino.h>

#undef SERIAL_RX_BUFFER_SIZE
#define SERIAL_RX_BUFFER_SIZE 256

#ifndef SERIAL_TRIGGER_TERMINATE_CHAR
#  define SERIAL_TRIGGER_TERMINATE_CHAR '\n'
#endif
#ifndef SERIAL_TRIGGER_COMPLEATE_CHAR
#  define SERIAL_TRIGGER_COMPLEATE_CHAR '|'
#endif
#ifndef SERIAL_TRIGGER_LINE_BUFFER
#  define SERIAL_TRIGGER_LINE_BUFFER 200
#endif
#ifndef SERIAL_TRIGGER_KEY_SPLITTER
#  define SERIAL_TRIGGER_KEY_SPLITTER '.'
#endif
#ifndef SERIAL_TRIGGER_VAL_SPLITTER
#  define SERIAL_TRIGGER_VAL_SPLITTER '='
#endif
#ifndef SERIAL_TRIGGER_MAX_KEYS
#  define SERIAL_TRIGGER_MAX_KEYS 10
#endif

namespace SerialComProtocol {
  struct keyCallItem {
    msgCallBack callBack;
    const char *key;
  };

  Stream *_serial;
  keyCallItem keyCallMap[SERIAL_TRIGGER_MAX_KEYS];
  byte _keyCount = 0;

  byte processLines(char *line) {
    DBGLN("lineToProcess: %s", line);

    char *value = nullptr;
    char *cmd = nullptr;

    char *pozEq = strrchr(line, SERIAL_TRIGGER_VAL_SPLITTER);
    if (pozEq != nullptr) {
      value = pozEq + 1;
      *pozEq = 0; //conf.test.tempo=233 => conf.test.tempo|233
    }

    char *pozDot = strchr(line, SERIAL_TRIGGER_KEY_SPLITTER);
    if (pozDot != nullptr) {
      cmd = pozDot + 1;
      *pozDot = 0; //conf.test.tempo => conf|test.tempo
    }

    char *key = line; //conf
    DBGLN("key:%s, cmd: %s, value: %s", key == nullptr ? "null" : key, cmd == nullptr ? "null" : cmd, value == nullptr ? "null" : value);

    for (int i = 0; i < _keyCount; i++) {
      if (strcmp(keyCallMap[i].key, key) == 0) {
        keyCallMap[i].callBack(cmd, value); //DO NOT BREAK HERE, I KNOW YOU ARE TEMPTED, CAND BE SAME FUNCTION MULTIPLE TIME IN STACK
      }
    }
    return 1;
  }

  void init(Stream *serial) {
    _serial = serial;
    _serial->setTimeout(100);
  }

  void handle() {
    char _line[SERIAL_TRIGGER_LINE_BUFFER] = {0};
    size_t numChars = 0;
    if (_serial->available() > 0) {
      numChars = _serial->readBytesUntil(SERIAL_TRIGGER_TERMINATE_CHAR, _line, SERIAL_TRIGGER_LINE_BUFFER);
      DBGLN("available %i", numChars);
      if (numChars > 0 && _line[numChars - 1] == SERIAL_TRIGGER_COMPLEATE_CHAR) {
        _line[numChars - 1] = 0;
        char *line = strdup(_line);
        processLines(line);
        free(line);
      }
    }
  }

  void addKeyCallEvent_P(const char *command, msgCallBack callBack) {
    char str[15] = {0};
    size_t i = 0;
    while (1) {
      uint8_t c = pgm_read_byte(command++);
      if (c == 0)
        break;
      str[i++] = c;
    }
    str[i++] = 0;
    DBGLN("str: %s", str);
    addKeyCallEvent(str, callBack);
  }

  void addKeyCallEvent(const char *command, msgCallBack callBack) {
    struct keyCallItem item;
    item.key = strdup(command);
    item.callBack = callBack;
    keyCallMap[_keyCount++] = item;
  }

  void send(const char *msg) {
    DBGLN("Send: %s", msg);
    if (msg == NULL)
      return;

    char *lastNl = strrchr(msg, 10);
    if (lastNl != nullptr) {
      char dest[100] = {0};
      strncpy(dest, msg, lastNl - msg);
      _serial->write(dest);
    } else {
      _serial->write(msg);
    }
    _serial->write(SERIAL_TRIGGER_COMPLEATE_CHAR); //adding |
    _serial->write(SERIAL_TRIGGER_TERMINATE_CHAR); //adding \ns
    _serial->flush();
  }
} // namespace SerialComProtocol