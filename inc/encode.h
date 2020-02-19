#ifndef ENCODE_H_CUSHMAN
#define ENCODE_H_CUSHMAN

#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

/***************************************************\
|	Taken from Beej's Guide to Network Programing	|
|	and modified to fit my needs.					|
\***************************************************/

#define pack754_16(f) (pack754((f), 16, 5))
#define pack754_32(f) (pack754((f), 32, 8))
#define pack754_64(f) (pack754((f), 64, 11))
#define unpack754_16(i) (unpack754((i), 16, 5))
#define unpack754_32(i) (unpack754((i), 32, 8))
#define unpack754_64(i) (unpack754((i), 64, 11))

uint64_t pack754(long double f, unsigned bits, unsigned expbits);
long double upack754(uint64_t i, unsigned bits, unsigned expbits);

void packi16(unsigned char *buf, unsigned int i);
void packi32(unsigned char *buf, unsigned long int i);
void packi64(unsigned char *buf, unsigned long long int i);
int unpacki16(unsigned char *buf);
unsigned int unpacku16(unsigned char *buf);
long int unpacki32(unsigned char *buf);
unsigned long int unpacku32(unsigned char *buf);
long long int unpacki64(unsigned char *buf);
unsigned long long int unpacku64(unsigned char *buf);

/*
** pack() -- store data dictated by the format string in the buffer
**
**   bits |signed   unsigned   float   string
**   -----+----------------------------------
**      8 |   c        C         
**     16 |   h        H         f
**     32 |   l        L         d
**     64 |   q        Q         g
**      - |                               s
**
**  (16-bit unsigned length is automatically prepended to strings)
*/ 

unsigned int pack(unsigned char *buf, char *format, ...);

/*
** unpack() -- unpack data dictated by the format string into the buffer
**
**   bits |signed   unsigned   float   string
**   -----+----------------------------------
**      8 |   c        C         
**     16 |   h        H         f
**     32 |   l        L         d
**     64 |   q        Q         g
**      - |                               s
**
**  (string is extracted based on its stored length, but 's' can be
**  prepended with a max length)
*/
void unpack(unsigned char *buf, char *format, ...);

#endif /* ENCODE_H_CUSHMAN */