
#include "MidiMap.h"

#include <cstdlib>

MidiMap::MidiMap() {
	// TODO
}

MidiMap::~MidiMap() {
	// TODO
}

void MidiMap::assignChannel(unsigned char channel, unsigned char instrument) {
	// TODO
}

void MidiMap::reset(unsigned int size, unsigned int ticksPerQuarter) {
	// TODO
}

void MidiMap::insertNOP(unsigned int track, unsigned int delta) {
	// TODO
}

void MidiMap::insertEvent(unsigned int track, unsigned int delta, MidiEvent *event) {
	// TODO
	delete(event);
}

