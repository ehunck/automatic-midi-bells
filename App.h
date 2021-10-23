#ifndef _APP_H_
#define _APP_H_

#include "mbed.h"
#include "USBMIDI.h"
#include "BellDriver.h"

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
    void ResetNotes();
    Thread _thread;
    EventQueue _queue;

    USBMIDI _usb;

    BellDriver _c_note;
    BellDriver _d_note;
    BellDriver _e_note;
    BellDriver _f_note;
    BellDriver _g_note;
    BellDriver _a_note;
    BellDriver _b_note;
    BellDriver _hi_c_note;
};

#endif // _APP_H_