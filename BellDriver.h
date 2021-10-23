#ifndef _BELL_DRIVER_H_
#define _BELL_DRIVER_H_

#include "mbed.h"

class BellDriver
{
public:
    BellDriver(PinName pin);
    virtual ~BellDriver();

    void SetPulseWidth( int32_t pulse_time_ms );
    uint32_t GetPulseWidth();

    void Fire();
    void Reset();

protected:
    DigitalOut _solenoid;
    Timeout _timeout;

    uint32_t _pulse_width_ms;

};


#endif // _BELL_DRIVER_H_