#ifndef _APP_H_
#define _APP_H_

#include "mbed.h"
#include "USBMIDI.h"

class App 
{
public:
    App();
    void Init();

protected:
    void ThreadFunction();

    void MIDICallback();
    void ParseMessage( MIDIMessage::MIDIMessageType type, int note, int velocity, int pressure );
    void SetNote( int note, int active );
    Thread _thread;
    EventQueue _queue;

    USBMIDI _usb;
};

#endif // _APP_H_