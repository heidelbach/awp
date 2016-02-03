#ifndef JMH_NUM_H
#define JMH_NUM_H

/*
 * Wandelt angebenen string in entsprechenden integer um.
 * Gibt 0 bei Fehler zurueck
 */
signed int toInt(char const *);


void sortInt(unsigned int count, signed int *const array);

/**
 * Gibt integer array mit count elementen aus
 */
void print_array(unsigned int const count, signed int *const array);

/**
 * Zeigt werte als Histogramm an
 */
void display_array(unsigned int const count, signed int *const array);

#endif
