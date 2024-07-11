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
#define OCTAVE_OFFSET	60


App::App(EventQueue& queue) :
    _usb(false, 0x0700, 0x0101, 0x0001),
    _c_note(D0),
    _d_note(D1),
    _e_note(D2),
    _f_note(D3),
    _g_note(D4),
    _a_note(D5),
    _b_note(D6),
    _hi_c_note(D7),
    _led1(LED1),
    _queue(queue)
{

}

void App::Init()
{
	_usb.init();
	_usb.connect();
    _usb.attach( callback(this, &App::MIDICallback) );

    _queue.call_every( 1s, callback(this, &App::HeartBeat));
}

void App::HeartBeat()
{
    _led1 = !_led1;
}

void App::MIDICallback()
{
    _queue.call( callback(this, &App::RetrieveMessage));
}

void App::RetrieveMessage()
{
    if( _usb.configured() )
    {
        while( _usb.readable() )
        {
            MIDIMessage message;
            if( _usb.read( &message ) )
            {
                this->ParseMessage( message.type(), message.key(), message.velocity(), message.pressure() );
            }
        }
    }
}

void App::ParseMessage( MIDIMessage::MIDIMessageType type, int note, int velocity, int pressure )
{
    switch( type )
    {
        case MIDIMessage::NoteOffType:
            SetNote( note, 0 );
            break;
        case MIDIMessage::NoteOnType:
            SetNote( note, 1 );
            break;
        case MIDIMessage::AllNotesOffType:
            ResetNotes();
            break;
        case MIDIMessage::ErrorType:
        case MIDIMessage::SysExType:
        case MIDIMessage::PolyphonicAftertouchType:
        case MIDIMessage::ControlChangeType:
        case MIDIMessage::ProgramChangeType:
        case MIDIMessage::ChannelAftertouchType:
        case MIDIMessage::PitchWheelType:
        case MIDIMessage::ResetAllControllersType:
        default:
            _hi_c_note.Fire();
            break;
    }
}

void App::SetNote( int note, int active )
{
    if( active )
    {
        int key = note - OCTAVE_OFFSET;
        switch( key )
        {
            case C:
                _c_note.Fire();
                break;
            case Cs:
                break;
            case D:
                _d_note.Fire();
                break;
            case Ds:
                break;
            case E:
                _e_note.Fire();
                break;
            case F:
                _f_note.Fire();
                break;
            case Fs:
                break;
            case G:
                _g_note.Fire();
                break;
            case Gs:
                break;
            case A:
                _a_note.Fire();
                break;
            case As:
                break;
            case B:
                _b_note.Fire();
                break;
            case (C+OCTAVE):
				_hi_c_note.Fire();
            	break;
            default:
            {
            	// wrap missing keys back into the playable seciton.
            	switch( note % OCTAVE )
            	{
					case C:
						_c_note.Fire();
						break;
					case Cs:
						break;
					case D:
						_d_note.Fire();
						break;
					case Ds:
						break;
					case E:
						_e_note.Fire();
						break;
					case F:
						_f_note.Fire();
						break;
					case Fs:
						break;
					case G:
						_g_note.Fire();
						break;
					case Gs:
						break;
					case A:
						_a_note.Fire();
						break;
					case As:
						break;
					case B:
						_b_note.Fire();
						break;
					default:
						break;
            	}
            	break;
            }
        }
    }
}

void App::ResetNotes()
{
    _c_note.Reset();
    _d_note.Reset();
    _e_note.Reset();
    _f_note.Reset();
    _g_note.Reset();
    _a_note.Reset();
    _b_note.Reset();
    _hi_c_note.Reset();
}
