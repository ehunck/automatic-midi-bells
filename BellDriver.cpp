#include "BellDriver.h"

#define DEFAULT_PULSE_WIDTH_MS 20

BellDriver::BellDriver(PinName pin):
    _solenoid(pin, 0),
    _pulse_width_ms(DEFAULT_PULSE_WIDTH_MS)
{

}

BellDriver::~BellDriver()
{

}

void BellDriver::SetPulseWidth( int32_t pulse_time_ms )
{
    _pulse_width_ms = pulse_time_ms;
}

uint32_t BellDriver::GetPulseWidth()
{
    return _pulse_width_ms;
}

void BellDriver::Fire()
{
    _solenoid = 1;
    _timeout.attach(callback(this, &BellDriver::Reset), _pulse_width_ms);
}

void BellDriver::Reset()
{
    _solenoid = 0;
    _timeout.detach();
}