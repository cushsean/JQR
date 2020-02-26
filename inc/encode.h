#ifndef ENCODE_H_CUSHMAN
#define ENCODE_H_CUSHMAN

#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#include "util.h"

#define BUF_SIZE (1024)

/***************************************************\
|	FOllowing Beej's Guide to Network Programing	|
|	and modified to fit my needs.					|
\***************************************************/

union float32_t{    // float
    float frac;
    uint32_t whole;
};

union float64_t{    // double
    double frac;
    uint64_t whole;
};

void packi16(unsigned char *buf, uint16_t i);
void packi32(unsigned char *buf, uint32_t i);
void packi64(unsigned char *buf, uint64_t i);
int16_t unpacki16(unsigned char *buf);
uint16_t unpacku16(unsigned char *buf);
int32_t unpacki32(unsigned char *buf);
uint32_t unpacku32(unsigned char *buf);
int64_t unpacki64(unsigned char *buf);
uint64_t unpacku64(unsigned char *buf);

/*
** pack() -- store data dictated by the format string in the buffer
**
**   bits |signed   unsigned   float   string   binary
**   -----+-------------------------------------------
**      8 |   c        C         
**     16 |   h        H         
**     32 |   l        L         f
**     64 |   q        Q         d
**      - |                               s 	  b
**
**  NOTE:   32-bit unsigned length is automatically prepended to strings
**          and binaries in order to pack their len,
**          up to 4.29 GB, into the buffer. 
*/ 

unsigned int pack(unsigned char *buf, char *format, ...);

/*
** unpack() -- unpack data dictated by the format string into the buffer
**
**   bits |signed   unsigned   float   string   binary
**   -----+-------------------------------------------
**      8 |   c        C         
**     16 |   h        H         
**     32 |   l        L         f
**     64 |   q        Q         d
**      - |                               s 	  b
**
**  NOTE: strings and binaries are extracted based on their stored length,
**  but 's' and 'b' can be prepended with a max length
*/
void unpack(unsigned char *buf, char *format, ...);
void check_buf(unsigned int size);

#endif /* ENCODE_H_CUSHMAN */