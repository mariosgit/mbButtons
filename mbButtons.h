#pragma once

#include <Arduino.h>
#include <functional>
#include <map>
#include <vector>

// C:\Program Files (x86)\Arduino\hardware\teensy\avr\cores\teensy3

class mbButton
{
public:
    friend class mbButtons;
    mbButton(byte pin, void(*target)(int8_t), int16_t offset) :
        _pin(pin), _target(target), _offset(offset), _trigger(false)  {}
private:
    byte _pin;
    byte _prev;
    void(*_target)(int8_t);
    int16_t _offset;
    bool _trigger; // true when activity seen
};

class mbButtons
{
public:
    mbButtons();
    void add(byte pin, void(*target)(int8_t), int16_t offset);
    void service(); // checks buttons, quick turn around.. (interrupt service)
    void loop();    // calls assigned function, can take time...
private:
    mbButton* _buttons[8];
    byte _last = 0;
    const byte _maxButtons = 8;
};
