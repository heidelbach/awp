
#ifndef __MIDI_PARSER__
#define __MIDI_PARSER__

#include "MidiMap.h"

#include <cstdio>

const unsigned int MIDI_FILE_HEADER = 0x4d546864;
const unsigned int MIDI_TRACK_HEADER = 0x4d54726b;
	

class MidiParser
{
private:
	
	enum parser_state { HEADER, DELTA, STATE, META, NAME, TIME, TEMPO,
			CHANNEL, OMIT, DISCARD_UNTIL, EOT, STATE_8, STATE_9,
			 STATE_a, STATE_b, STATE_c, STATE_d, STATE_e };

	struct {
		unsigned char *buffer;
		unsigned int buf_size, posR, posW;
	} buffer;


	struct {
		unsigned int n : 16;
		unsigned int nTracks : 16;
		char **titles;
	} tracks;
	
	unsigned int deltaTicksPerQuarter;
	FILE *file;
	MidiMap map;

	struct {
		enum parser_state state;
		unsigned int remaining;
		unsigned int delta;
		unsigned char runningState;
		unsigned char tmp;
	 } state;

	void read(unsigned int, FILE *file, bool check = true);

	void parseTrack();

	void parseDelta();
	void parseDiscardUntil();
	void parseHeader();
	void parseMeta();
	void parseOmit();
	void parseState();
	void parseState8();
	void parseState9();
	void parseStateA();
	void parseStateB();
	void parseStateC();
	void parseStateD();
	void parseStateE();
	void parseTime();
	void parseTempo();
	void parseName();
	void parseChannel();

public:
	MidiParser();

	~MidiParser();

	int init(const char *const file);

	MidiMap *createMap();

	void parse();
};

#endif
