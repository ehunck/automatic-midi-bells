#include "BellDriver.h"

#define DEFAULT_PULSE_WIDTH_MS 20ms

BellDriver::BellDriver(PinName pin):
    _solenoid(pin, 0)
{

}

BellDriver::~BellDriver()
{

}

void BellDriver::Fire()
{
    _solenoid = 1;
    _timeout.attach(callback(this, &BellDriver::Reset), DEFAULT_PULSE_WIDTH_MS);
}

void BellDriver::Reset()
{
    _solenoid = 0;
    _timeout.detach();
}