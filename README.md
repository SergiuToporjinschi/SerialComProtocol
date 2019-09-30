[![GitHub repo size in bytes](https://img.shields.io/github/repo-size/badges/shields.svg)](https://github.com/SergiuToporjinschi/SerialComProtocol)
[![GitHub last commit](https://img.shields.io/github/last-commit/SergiuToporjinschi/SerialComProtocol.svg)](https://github.com/SergiuToporjinschi/SerialComProtocol/commits/master)
[![GitHub stars](https://img.shields.io/github/stars/SergiuToporjinschi/SerialComProtocol.svg)](https://github.com/SergiuToporjinschi/SerialComProtocol/stargazers)
[![GitHub watchers](https://img.shields.io/github/watchers/SergiuToporjinschi/SerialComProtocol.svg)](https://github.com/SergiuToporjinschi/SerialComProtocol/watchers)
[![GitHub license](https://img.shields.io/github/license/SergiuToporjinschi/SerialComProtocol.svg)](https://github.com/SergiuToporjinschi/SerialComProtocol/blob/master/LICENSE)
[![Code Climate](https://codeclimate.com/github/codeclimate/codeclimate/badges/gpa.svg)](https://codeclimate.com/github/SergiuToporjinschi/SerialComProtocol)
[![Build Status](https://travis-ci.org/SergiuToporjinschi/SerialComProtocol.svg?branch=master)](https://travis-ci.org/SergiuToporjinschi/SerialComProtocol)

# Serial comunication protocol
Implements a communication protocol for communication between two SOC's through Serial;


# Dependency 
- none

# Macros 
For customizing protocol you can define the following macros before including SerialComProtocol.h;
```CPP
#define SERIAL_TRIGGER_TERMINATE_CHAR '\n' //the termination character for a line 
#define SERIAL_TRIGGER_COMPLEATE_CHAR '|'  //the termination character for a command
#define SERIAL_TRIGGER_LINE_BUFFER 200     //the maximum lenght of a line )
#define SERIAL_TRIGGER_KEY_SPLITTER '.'    //splitter character for a command 
#define SERIAL_TRIGGER_VAL_SPLITTER '='    //delimitor for value
#define SERIAL_TRIGGER_MAX_KEYS 10         //maximum ammout of registered listeners
```

# Implementation
**Examples**:
`conf.temp.cmd=pause|\n`
* `conf` - key - is used to register a call back for a specific command;
* `temp.cmd` - cmd - is passed as parameter for the registered event;
* `paused` - value - is passed as parameter for the registered event;


`Ready|\n`
* `Ready` - key - is used to register a call back for a specific command;

A received command is splitted at first `SERIAL_TRIGGER_KEY_SPLITTER` and the first part is considered key on which the listener will be registered. The following text delimitated by `SERIAL_TRIGGER_VAL_SPLITTER` will be considered as command 
## Initialisation
  Passing the serial to SerialComProtocol. This serial will be used to send/receive commands. Serial needs to be already initialized(call to `Serial.begin(<boundrate>)` allready called)  
  ```cpp 
  SerialComProtocol::init(&Serial); 
  ```
## Register listeneres
  Registers a method; When a line starts with a specific key, the corresponding function will be called with  the `cmd` and `value` received;
  ```cpp 
  SerialComProtocol::addKeyCallEvent("conf", [](const char *cmd, const char *value) {
    DBGLN("cmd: %s; value: %s", cmd == nullptr ? "null" : cmd, value == nullptr ? "null" : value);
  });
  ```