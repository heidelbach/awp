#include "MidiParser.h"

#include "MidiEvent.h"
#include "MidiNoteOffEvent.h"
#include "MidiNoteOnEvent.h"
#include "MidiTempoEvent.h"

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

MidiParser::MidiParser() {
	this->buffer.buf_size = 0x10;
	this->file = 0;
	this->tracks.titles = 0;
	this->buffer.buffer = (unsigned char *) malloc(this->buffer.buf_size);
	this->buffer.posW = 0;
	this->buffer.posR = 0;
}

MidiParser::~MidiParser() {
	if (this->file != 0) {
		fclose(this->file);
	}
	if (this->tracks.titles != 0) {
		while (this->tracks.nTracks > 0)
			if(this->tracks.titles[--this->tracks.nTracks] != 0)
				free(this->tracks.titles[this->tracks.nTracks]);
		free(this->tracks.titles);
	}
	if (this->buffer.buffer != 0)
		free(this->buffer.buffer);
}

void MidiParser::read(unsigned int size, FILE *file, bool check) {
	if (check && state.remaining < size) {
		std::cerr << "track is longer than announced in header"
				<< std::endl;
		abort();
	}
	state.remaining -= size;
	if (this->buffer.posW == this->buffer.posR)
		this->buffer.posW = this->buffer.posR = 0;
	if (this->buffer.buf_size - this->buffer.posW < size) {
		this->buffer.buf_size = (size & 0xf0) + 0x10;
		unsigned char *buffer = (unsigned char *) malloc(this->buffer.buf_size);
		if (this->buffer.posW != this->buffer.posR) {
			std::cerr << "buffer is not empty" << std::endl;
			abort();
		}
		free(this->buffer.buffer);
		this->buffer.buffer = buffer;
	}
	if (fread(&(this->buffer.buffer[this->buffer.posR]), sizeof(char), size, file) != size) {
		abort();
	}
	if (errno != 0) {
		std::cerr << "error reading file." << strerror(errno) << std::endl;
		abort();
	}
	this->buffer.posW += size;
}

int MidiParser::init(const char * const filename) {
	if (this->file != 0) {
		fclose(this->file);
		this->file = 0;
	}
	if (this->tracks.titles != 0) {
		while (this->tracks.nTracks > 0)
			if(this->tracks.titles[--this->tracks.nTracks] != 0)
				free(this->tracks.titles[this->tracks.nTracks]);
		free(this->tracks.titles);
		this->tracks.titles = 0;
	}
	FILE *file = fopen(filename, "rb");
	if (file == 0) {
		std::cerr << "Error opening file: " << strerror(errno) << ": \"" << filename << "\"" << std::endl;
		return -1;
	}
	read(4, file, false);
	int test = 0;
	while (this->buffer.posR < 4) {
		test = (test << 8) + this->buffer.buffer[this->buffer.posR++];
	}
	if (test != MIDI_FILE_HEADER) {
		fclose(file);
		std::cout << "read Header: 0x" << std::hex << test << std::endl;
		std::cout << "Midi-Header: 0x" << MIDI_FILE_HEADER << std::dec
				<< std::endl;
		std::cerr << "Error parsing midi \"" << filename
				<< "\": Wrong file-header" << std::endl;
		return -1;
	}

	// evluate the header
	read(10, file, false);
	test = 0;
	while (this->buffer.posR < 4)
		test = (test << 8) + this->buffer.buffer[this->buffer.posR++];
	if (test != 6) {
		fclose(file);
		std::cerr << "Error parsing midi \"" << filename
				<< "\": Wrong file-header" << std::endl;
		return -1;
	}
	test = 0;
	while (this->buffer.posR < 6)
		test = (test << 8) + this->buffer.buffer[this->buffer.posR++];
	unsigned int format = test;
	test = 0;
	while (this->buffer.posR < 8)
		test = (test << 8) + this->buffer.buffer[this->buffer.posR++];
	tracks.nTracks = test;
	tracks.n = 0x0;
	test = 0;
	while (this->buffer.posR < 10)
		test = (test << 8) + this->buffer.buffer[this->buffer.posR++];
	deltaTicksPerQuarter = test;
	
	std::cout << "format: " << format << std::endl;
	std::cout << "tracks: " << tracks.nTracks << std::endl;
	std::cout << "ticks per quarter: " << deltaTicksPerQuarter << std::endl;
	
	this->file = file;
	this->tracks.titles = (char **) malloc(sizeof(char *) * tracks.nTracks);
	if (this->tracks.titles == 0) {
		std::cerr << "Out of memory" << std::endl;
		abort();
	}
	test = 0;
	while (test < tracks.nTracks)
		this->tracks.titles[test++] = 0;
	map.reset(tracks.nTracks, deltaTicksPerQuarter);
	return tracks.nTracks;
	
}

void MidiParser::parse() {
	if (file == 0)
		return;
	while (tracks.n < tracks.nTracks) {
		parseTrack();
	}
}

void MidiParser::parseTrack() {
	if (file == 0)
		return;
	std::cout << (tracks.n + 1) << "/" << tracks.nTracks << std::endl;
	state.state = HEADER;
	while(state.state != EOT) {
		switch(state.state) {
			case STATE_8:
				parseState8();
				break;
			case STATE_9:
				parseState9();
				break;
			case STATE_a:
				parseStateA();
				break;
			case STATE_b:
				parseStateB();
				break;
			case STATE_c:
				parseStateC();
				break;
			case STATE_d:
				parseStateD();
				break;
			case STATE_e:
				parseStateE();
				break;
			case CHANNEL:
				parseChannel();
				break;
			case HEADER:
				parseHeader();
				break;
			case DELTA:
				parseDelta();
				break;
			case TIME:
				parseTime();
				break;
			case TEMPO:
				parseTempo();
				break;
			case NAME:
				parseName();
				break;
			case STATE:
				parseState();
				break;
			case META:
				parseMeta();
				break;
			case DISCARD_UNTIL:
				parseDiscardUntil();
				break;
			case OMIT:
				parseOmit();
				break;
			default:
				std::cerr << "missing implementation for state "
						<< state.state << std::endl;
		}
	}
}

void MidiParser::parseDelta() {
	state.delta = 0;
	while (true) {
		read(1, file);
		unsigned char value = this->buffer.buffer[this->buffer.posR++];
		state.delta = (state.delta << 7) | (value & 0x3f);
		if ((value & 0x80) == 0) {
			state.state = STATE; 
			return;
		}
	}
}

/* note off */
void MidiParser::parseState8() {
	unsigned char hByte, lByte;
	if (buffer.posR != buffer.posW) {
		hByte = buffer.buffer[buffer.posR++];
		read(1, file);
	} else {
		read(2, file);
		hByte = buffer.buffer[buffer.posR++];
	}
	lByte = buffer.buffer[buffer.posR++];
	MidiEvent *event = new MidiNoteOffEvent(state.delta, hByte, lByte);
	map.insertEvent(tracks.n, state.delta, event);
	state.state = DELTA;
}

/* note on */
void MidiParser::parseState9() {
	unsigned char hByte, lByte;
	if (buffer.posR != buffer.posW) {
		hByte = buffer.buffer[buffer.posR++];
		read(1, file);
	} else {
		read(2, file);
		hByte = buffer.buffer[buffer.posR++];
	}
	lByte = buffer.buffer[buffer.posR++];
	MidiEvent *event;
	if (lByte == 0) {
		event = new MidiNoteOffEvent(state.delta, hByte, lByte);
	} else {
		event = new MidiNoteOnEvent(state.delta, hByte, lByte);
	}
	map.insertEvent(tracks.n, state.delta, event);
	state.state = DELTA;
}

/* polyphonic aftertouch */
void MidiParser::parseStateA() {
	unsigned char hByte, lByte;
	if (buffer.posR != buffer.posW) {
		hByte = buffer.buffer[buffer.posR++];
		read(1, file);
	} else {
		read(2, file);
		hByte = buffer.buffer[buffer.posR++];
	}
	lByte = buffer.buffer[buffer.posR++];
	// create a new class if this event is needed
	map.insertNOP(tracks.n, state.delta);
	state.state = DELTA;
}

/* control change */
void MidiParser::parseStateB() {
	unsigned char hByte, lByte;
	if (buffer.posR != buffer.posW) {
		hByte = buffer.buffer[buffer.posR++];
		read(1, file);
	} else {
		read(2, file);
		hByte = buffer.buffer[buffer.posR++];
	}
	lByte = buffer.buffer[buffer.posR++];
	// create a new class if this event is needed
	map.insertNOP(tracks.n, state.delta);
	state.state = DELTA;
}

/* program change */
void MidiParser::parseStateC() {
	read(1, file);
	map.assignChannel(state.tmp, buffer.buffer[buffer.posR++]);
	state.state = DELTA;
}

/* channel pressure */
void MidiParser::parseStateD() {
	unsigned char byte;
	if (buffer.posR != buffer.posW) {
		byte = buffer.buffer[buffer.posR++];
	} else {
		read(1, file);
		byte = buffer.buffer[buffer.posR++];
	}
	// create a new class if this event is needed
	map.insertNOP(tracks.n, state.delta);
	state.state = DELTA;
}

void MidiParser::parseStateE() {
	// TODO
}

void MidiParser::parseTime() {
	read(1, file);
	unsigned char length = buffer.buffer[buffer.posR++];
	read(length, file);
	unsigned char n = buffer.buffer[buffer.posR++];
	unsigned char d = buffer.buffer[buffer.posR++];
	unsigned char c = buffer.buffer[buffer.posR++];
	unsigned char b = buffer.buffer[buffer.posR++];
	// create a new class if this event is needed
	map.insertNOP(tracks.n, state.delta);
	state.state = DELTA;
}

void MidiParser::parseTempo() {
	read(1, file);
	unsigned char length = buffer.buffer[buffer.posR++];
	unsigned int tempo = 0;
	read(length, file);
	while (buffer.posR < length) {
		tempo = (tempo << 8) | buffer.buffer[buffer.posR++];
	}
	MidiTempoEvent *event = new MidiTempoEvent(state.delta, tempo);
	map.insertEvent(tracks.n, state.delta, event);
	state.state = DELTA;
}

void MidiParser::parseName() {
	read(1, file);

	unsigned char length = buffer.buffer[buffer.posR++];
	char *buffer = (char *) malloc(length + 1);
	if (buffer == 0) {
		std::cerr << "Out of memory" << std::endl;
		abort();
	
	}
	if (tracks.titles[tracks.n] != 0) {
		std::cout << "titles not null" << std::endl;
	}
	tracks.titles[tracks.n] = buffer;
	read(length, file);
	state.tmp = 0;
	while (state.tmp < length) {
		buffer[state.tmp++] =
				(char) this->buffer.buffer[this->buffer.posR++];
	}
	buffer[state.tmp] = '\0';
	state.state = DELTA;
}

void MidiParser::parseChannel() {
	// TODO implement if channel is interesting
	parseOmit();
}

void MidiParser::parseOmit() {
	read(state.tmp, file);
	this->buffer.posR += state.tmp;
	state.state = DELTA;
	map.insertNOP(tracks.n, state.delta);
}

void MidiParser::parseDiscardUntil() {
	while (true) {
		read(1, file);
		unsigned char byte = this->buffer.buffer[this->buffer.posR++];
		if (byte == 0xf7)
			break;
	}
	state.state = DELTA;
	map.insertNOP(tracks.n, state.delta);
}

void MidiParser::parseHeader() {
	read(8, this->file, false);
	int test = 0;
	while (this->buffer.posR < 4)
		test = (test << 8) + this->buffer.buffer[this->buffer.posR++];
	if (test != MIDI_TRACK_HEADER) {
		std::cout << "invalid track header" << std::cerr;
		abort();
	}
	state.remaining = 0;
	while (this->buffer.posR < 8)
		state.remaining = (state.remaining << 8) 
				+ this->buffer.buffer[this->buffer.posR++];
	state.state = DELTA;
}

void MidiParser::parseMeta() {
	if (this->buffer.posR == this->buffer.posW)
		read(1, this->file);
	unsigned char value = this->buffer.buffer[this->buffer.posR++];
	switch (value) {
		case 0x03:
			state.state = NAME;
			break;
		case 0x20:
			state.state = CHANNEL;
			break;
		case 0x2f:
			state.state = EOT;
			read(1, this->file);
			state.tmp = this->buffer.buffer[
					this->buffer.posR++];
			if (state.tmp != 0) {
				read(state.tmp, this->file);
				this->buffer.posR += state.tmp;
			}
			++tracks.n;
			break;
		case 0x51:
			state.state = TEMPO;
			break;
		case 0x58:
			state.state = TIME;
			break;
		default:
			read(1, this->file);
			state.tmp = this->buffer.buffer[this->buffer.posR++];
			state.state = OMIT;
	}
}

void MidiParser::parseState() {
	read(1, this->file);
	unsigned char value = this->buffer.buffer[this->buffer.posR++];
	unsigned char state;
	if (value < 0x80) {
		state = this->state.runningState;
		--this->buffer.posR;
	} else {
		state = value;
		this->state.runningState = value;
	}
	switch (state & 0xf0) {
		case 0x80: // note off
			this->state.state = STATE_8;
			break;
		case 0x90: // note on
			this->state.state = STATE_9;
			break;
		case 0xa0: // polyphonic aftertouch
			this->state.state = STATE_a;
			break;
		case 0xb0: // control change
			this->state.state = STATE_b;
			break;
		case 0xc0: // program change
			this->state.state = STATE_c;
			this->state.tmp = state;
			break;
		case 0xd0: // channel pressure
			this->state.state = STATE_d;
			break;
		case 0xe0: // pitch bend
			this->state.state = STATE_e;
			break;
		case 0xf0:
			switch (state & 0x0f) {
			 case 0x00:
				this->state.state = DISCARD_UNTIL;
				break;
			case 0x0f:
				this->state.state = META;
				break;
			default:
				std::cerr << "invalid state" << std::endl;
				abort();
			}
			break;
	}
}

int main() {
	MidiParser parser;
	char *file = (char *) malloc(sizeof(char) * 256);
	char *buffer = (char *) malloc(sizeof(char) * 16);

	while(1)
	{
		printf("Please enter the file to parse: ");
		scanf("%s", file);
		printf("Is %s correct [N/y]? ", file);
		scanf("%s", buffer);
		if (!strcmp(buffer, "y") || !strcmp(buffer, "Y"))
			break;
	}
	parser.init(file);
	parser.parse();
	
	printf("\rdone\n");
	getchar();
	getchar();
	
	return 0;
}