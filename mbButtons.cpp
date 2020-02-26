#include <mbButtons.h>

#include <ArduinoLog.h>

mbButtons::mbButtons()
{
    for(byte i = 0; i < _maxButtons; i++)
        _buttons[i] = nullptr;
    // _buttons.reserve(count);
    // _prevVal.reserve(count);
}

void mbButtons::add(byte pin, void(*target)(int8_t), int16_t offset)
{
    _buttons[_last++] = new mbButton(pin, target, offset);
    pinMode(pin, INPUT_PULLUP);
    digitalWrite(pin, 1);
}

void mbButtons::service()
{
    for(byte i = 0; i < _maxButtons; i++)
    {
        if(!_buttons[i])
            continue;
        // Log.notice("mbButtons::service 2 pin:%d\n", _buttons[i]->_pin);
        byte val = digitalRead(_buttons[i]->_pin);
        if(_buttons[i]->_prev == 0 && val == 1)
            _buttons[i]->_trigger = true;
        // Log.notice("mbButtons::service 3 val:%d prev:%d t:%d\n", val, _buttons[i]->_prev, _buttons[i]->_target);
        _buttons[i]->_prev = val;
    }
}

void mbButtons::loop()
{
    for(byte i = 0; i < _maxButtons; i++)
    {
        if(!_buttons[i])
            continue;
        if(_buttons[i]->_trigger)
        {
            Log.notice("mbButtons::loop pin:%d\n", _buttons[i]->_pin);
            _buttons[i]->_trigger = false;
            _buttons[i]->_target(_buttons[i]->_offset);
        }
    }
}
