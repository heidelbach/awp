
#include "MidiNoteOnEvent.h"
#include "MidiNoteOffEvent.h"

MidiNoteOnEvent::MidiNoteOnEvent(unsigned int delta, unsigned char key,
		unsigned char v) : MidiEvent(delta) {
}

MidiNoteOffEvent::MidiNoteOffEvent(unsigned int delta, unsigned char key,
		unsigned char v) : MidiEvent(delta) {
}

MidiNoteOnEvent::~MidiNoteOnEvent() {
}

MidiNoteOffEvent::~MidiNoteOffEvent() {
}
