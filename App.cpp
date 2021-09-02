#include "App.h"

#define C  0
#define Cs 1
#define D  2
#define Ds 3
#define E  4
#define F  5
#define Fs 6
#define G  7
#define Gs 8
#define A  9
#define As 10
#define B  11

#define OCTAVE 12

App::App() :
    _thread( osPriorityNormal, OS_STACK_SIZE, nullptr, "APP" ),
    _usb(false, 0x0700, 0x0101, 0x0001)
{

}

void App::Init()
{
    _usb.attach( callback(this, &App::MIDICallback) );

    _thread.start( callback(this, &App::ThreadFunction ));
}

void App::ThreadFunction()
{

    _queue.dispatch_forever();
}

void App::MIDICallback()
{
    if( _usb.readable() )
    {
        MIDIMessage message;
        if( _usb.read( &message ) )
        {
            _queue.call( callback(this, &App::ParseMessage), 
                message.type(), message.key(), message.velocity(), message.pressure() );
        }
    }
}

void App::ParseMessage( MIDIMessage::MIDIMessageType type, int note, int velocity, int pressure )
{
    int key = note % OCTAVE;
    switch( type )
    {
        case MIDIMessage::NoteOffType:
            SetNote( key, 0 );
            break;
        case MIDIMessage::NoteOnType:
            SetNote( key, 1 );
            break;
        case MIDIMessage::AllNotesOffType:
            SetNote( C, 0 );
            SetNote( Cs, 0 );
            SetNote( D, 0 );
            SetNote( Ds, 0 );
            SetNote( E, 0 );
            SetNote( F, 0 );
            SetNote( Fs, 0 );
            SetNote( G, 0 );
            SetNote( Gs, 0 );
            SetNote( A, 0 );
            SetNote( As, 0 );
            SetNote( B, 0 );
            break;
        case MIDIMessage::ErrorType:
            break;
        case MIDIMessage::SysExType:
            break;
        case MIDIMessage::PolyphonicAftertouchType:
            break;
        case MIDIMessage::ControlChangeType:
            break;
        case MIDIMessage::ProgramChangeType:
            break;
        case MIDIMessage::ChannelAftertouchType:
            break;
        case MIDIMessage::PitchWheelType:
            break;
        case MIDIMessage::ResetAllControllersType:
            break;
    }
}