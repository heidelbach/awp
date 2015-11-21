#include "MidiTempoEvent.h"

MidiTempoEvent::MidiTempoEvent(unsigned int delta, unsigned int tempo)
		: MidiEvent(delta) {
	this->tempo = tempo;
}

MidiTempoEvent::~MidiTempoEvent() {
}

