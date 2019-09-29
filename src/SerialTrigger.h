#pragma once
/*

  SerialTrigger 0.1.0

  SerialTrigger

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

*/

#ifndef SERIAL_TRIGGER_H
#  define SERIAL_TRIGGER_H
#  include <Arduino.h>

namespace SerialTrigger {
  typedef void (*msgCallBack)(const char *key, const char *value);
  void init(Stream *serial);

  void setDebugger(Print *debug);

  void handle();
  void clear();
  void addKeyCallEvent_P(const char *command, msgCallBack callBack);
  void addKeyCallEvent(const char *key, msgCallBack callBack);
  void send(const char *string);
}; // namespace SerialTrigger

#endif
