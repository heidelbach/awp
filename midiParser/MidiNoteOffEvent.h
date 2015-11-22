
#include "MidiEvent.h"

class MidiNoteOffEvent : public MidiEvent
{
public:
	MidiNoteOffEvent(unsigned int delta, unsigned char key, unsigned char v);

	~MidiNoteOffEvent();
};
