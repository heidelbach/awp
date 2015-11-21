
#include "MidiEvent.h"

class MidiNoteOnEvent : public MidiEvent
{
public:
	MidiNoteOnEvent(unsigned int delta, unsigned char key, unsigned char v);

	~MidiNoteOnEvent();
};
