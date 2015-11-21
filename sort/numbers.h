#ifndef JMH_NUM_H
#define JMH_NUM_H

/*
 * Wandelt angebenen string in entsprechenden integer um.
 * Gibt 0 bei Fehler zurueck
 */
signed int toInt(char const *);

void sortInt(unsigned int, signed int *const);

void const print(unsigned int const, signed int *const);

#endif
