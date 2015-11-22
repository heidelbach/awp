
#ifndef __MIDI_EVENT_H__
#define __MIDI_EVENT_H__

class MidiEvent
{
protected:
	unsigned int delta;

public:
	MidiEvent(unsigned int delta);

	virtual ~MidiEvent();
};

#endif
