#ifndef JMH_IO_H
#define JMH_IO_H

#include <cstdio>

signed int getInt();

#define printText(a) printf("%s", a)

#define printNum(a) printf("%d", a)

#define printNumf(f, a) printf(f, a)

#define printError(a) fprintf(stderr, "%s\n", a);

#endif
