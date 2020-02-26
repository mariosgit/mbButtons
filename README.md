# mbButtons

Arduino Lib, triggers a function on button release.

```
mbButtons buttons;
IntervalTimer buttonTimer; // Teensy Code ?

void serviceFunc()
{
    buttons.service();
}

void setup()
{
    buttonTimer.begin(serviceFunc, 1000);  // run every 1 miliseconds
}

void loop()
{
    buttons.loop();
}
```
