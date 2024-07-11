#ifndef _BELL_DRIVER_H_
#define _BELL_DRIVER_H_

#include "mbed.h"

class BellDriver
{
public:
    BellDriver(PinName pin);
    virtual ~BellDriver();

    void Fire();
    void Reset();

protected:
    DigitalOut _solenoid;
    Timeout _timeout;

};


#endif // _BELL_DRIVER_H_