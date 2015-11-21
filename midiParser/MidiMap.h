
#include "MidiEvent.h"

class MidiMap
{
private:
	
public:
	MidiMap();
	
	~MidiMap();

	void assignChannel(unsigned char channel, unsigned char midiInstrument);

	void reset(unsigned int size, unsigned int ticksPerQuarter);

	void insertNOP(unsigned int track, unsigned int delta);

	void insertEvent(unsigned int track, unsigned int delta, MidiEvent *event);
};
