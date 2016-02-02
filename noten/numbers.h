#ifndef JMH_NUM_H
#define JMH_NUM_H

/*
 * Wandelt angebenen string in entsprechenden integer um.
 * Gibt 0 bei Fehler zurueck
 */
signed int toInt(char const *);

/**
 * Gibt integer array mit count elementen aus
 */
void print(unsigned int const count, signed int *const array);

#endif
