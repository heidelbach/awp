
#include "MidiEvent.h"

class MidiTempoEvent  : public MidiEvent
{
private:
	unsigned int tempo;

public:
	MidiTempoEvent(unsigned int delta, unsigned int tempo);

	~MidiTempoEvent();
};
