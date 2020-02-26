#include "encode.h"

/***************************************************\
|	Following Beej's Guide to Network Programing	|
|	and modified to fit my needs.					|
\***************************************************/

void packi16(unsigned char *buf, uint16_t i)
{
    *buf++ = i>>8; *buf++ = i;
}

void packi32(unsigned char *buf, uint32_t i)
{
    *buf++ = i>>24; *buf++ = i>>16;
    *buf++ = i>>8;  *buf++ = i;
}

void packi64(unsigned char *buf, uint64_t i)
{
    *buf++ = i>>56; *buf++ = i>>48;
    *buf++ = i>>40; *buf++ = i>>32;
    *buf++ = i>>24; *buf++ = i>>16;
    *buf++ = i>>8;  *buf++ = i;
}

int16_t unpacki16(unsigned char *buf)
{
    uint16_t i2 = ((uint16_t)buf[0]<<8) | buf[1];
    int16_t i;

    // change unsigned numbers to signed
    if (i2 <= 0x7fffu) { i = i2; }
    else { i = -1 - (int16_t)(0xffffu - i2); }

    return i;
}

uint16_t unpacku16(unsigned char *buf)
{
    return ((uint16_t)buf[0]<<8) | buf[1];
}

int32_t unpacki32(unsigned char *buf)
{
    uint32_t i2 =   ((uint32_t)buf[0]<<24) |
                    ((uint32_t)buf[1]<<16) |
                    ((uint32_t)buf[2]<<8)  |
                    buf[3];
    int32_t i;

    // change unsigned numbers to signed
    if (i2 <= 0x7fffffffu) { i = i2; }
    else { i = -1 - (int32_t)(0xffffffffu - i2); }

    return i;
}
 
uint32_t unpacku32(unsigned char *buf)
{
    return ((uint32_t)buf[0]<<24) |
           ((uint32_t)buf[1]<<16) |
           ((uint32_t)buf[2]<<8)  |
           buf[3];
}
 
int64_t unpacki64(unsigned char *buf)
{
    uint64_t i2 =   ((uint64_t)buf[0]<<56) |
                    ((uint64_t)buf[1]<<48) |
                    ((uint64_t)buf[2]<<40) |
                    ((uint64_t)buf[3]<<32) |
                    ((uint64_t)buf[4]<<24) |
                    ((uint64_t)buf[5]<<16) |
                    ((uint64_t)buf[6]<<8)  |
                    buf[7];
    int64_t i;

    // change unsigned numbers to signed
    if (i2 <= 0x7fffffffffffffffu) { i = i2; }
    else { i = -1 -(int64_t)(0xffffffffffffffffu - i2); }

    return i;
}

uint64_t unpacku64(unsigned char *buf)
{
    return ((uint64_t)buf[0]<<56) |
           ((uint64_t)buf[1]<<48) |
           ((uint64_t)buf[2]<<40) |
           ((uint64_t)buf[3]<<32) |
           ((uint64_t)buf[4]<<24) |
           ((uint64_t)buf[5]<<16) |
           ((uint64_t)buf[6]<<8)  |
           buf[7];
}

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

uint32_t pack(unsigned char *buf, char *format, ...)
{
    va_list ap;

    signed char c;      // 8-bit
    unsigned char C;

    int16_t h;          // 16-bit
    uint16_t H;

    int32_t l;          // 32-bit
    uint32_t L;

    int64_t q;          // 64-bit
    uint64_t Q;

    union float32_t f;  // float

    union float64_t d;  // double 

    char* s;            // strings & binary
    char* b;
    uint32_t len;

    unsigned int size = 0;
    unsigned int prev_size = size;

    va_start(ap, format);

    for(; *format != '\0'; format++) {
        switch(*format) {
        case 'c': // 8-bit
            size += 1;
            check_buf(size);
            c = va_arg(ap, int); //PROMOTED
            *buf++ = c;
            break;

        case 'C': // 8-bit unsigned
            size += 1;
            check_buf(size);
            C = va_arg(ap, int); //PROMOTED
            *buf++ = C;
            break;

        case 'h': // 16-bit
            size += 2;
            check_buf(size);
            h = va_arg(ap, int); //PROMOTED
            packi16(buf, h);
            buf += 2;
            break;

        case 'H': // 16-bit unsigned
            size += 2;
            check_buf(size);
            H = va_arg(ap, int); //PROMOTED
            packi16(buf, H);
            buf += 2;
            break;

        case 'l': // 32-bit
            size += 4;
            check_buf(size);
            l = va_arg(ap, int32_t);
            packi32(buf, l);
            buf += 4;
            break;

        case 'L': // 32-bit unsigned
            size += 4;
            check_buf(size);
            L = va_arg(ap, uint32_t);
            packi32(buf, L);
            buf += 4;
            break;

        case 'q': // 64-bit
            size += 8;
            check_buf(size);
            q = va_arg(ap, int64_t);
            packi64(buf, q);
            buf += 8;
            break;

        case 'Q': // 64-bit unsigned
            size += 8;
            check_buf(size);
            Q = va_arg(ap, uint64_t);
            packi64(buf, Q);
            buf += 8;
            break;

        case 'f': // float-32
            size += 4;
            check_buf(size);
            f.frac = va_arg(ap, double); //PROMOTED
            packi32(buf, f.whole);
            buf += 4;
            break;

        case 'd': // float-64
            size += 8;
            check_buf(size);
            d.frac = va_arg(ap, double); //PROMOTED
            packi64(buf, d.whole);
            buf += 8;
            break;

        case 's': // string
            s = va_arg(ap, char*);
            len = strlen(s);
            size += len + 4;
            check_buf(size);
            packi32(buf, (uint32_t)len);
            buf += 4;
            memcpy(buf, s, len);
            buf += len;
            break;
        
        case 'b': // binary
            b = va_arg(ap, char*);
            len = va_arg(ap, uint32_t);
            size += len + 4;
            check_buf(size);
            packi32(buf, (uint32_t)len);
            buf += 4;
            memcpy(buf, b, len);
            buf += len;
            break;

        default:
            perror("Invalid Format String. Serialization Terminated.");
            return 0;
            break;
        }
    }

    va_end(ap);

    return size;
}

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
**  but 's' can be prepended with a max length
*/
void unpack(unsigned char *buf, char *format, ...)
{
    va_list ap;

    signed char *c;     // 8-bit
    unsigned char *C;

    int16_t *h;         // 16-bit
    uint16_t *H;

    int32_t *l;         // 32-bit
    uint32_t *L;

    int64_t *q;         // 64-bit
    uint64_t *Q;

    float *f;
    double *d;
    union float32_t uf; //float
    union float64_t ud;

    char *s;            // strings & binary
    char *b;
    uint32_t len, maxlen=0, count;

    va_start(ap, format);

    for(; *format != '\0'; format++) {
        switch(*format) {
        case 'c': // 8-bit
            size += 1;
            check_buf(size);
            c = va_arg(ap, signed char*);
            if (*buf <= 0x7f) { *c = *buf;} // re-sign
            else { *c = -1 - (unsigned char)(0xffu - *buf); }
            buf++;
            break;

        case 'C': // 8-bit unsigned
            size += 1;
            check_buf(size);
            C = va_arg(ap, unsigned char*);
            *C = *buf++;
            break;

        case 'h': // 16-bit
            size += 2;
            check_buf(size);
            h = va_arg(ap, int16_t*);
            *h = unpacki16(buf);
            buf += 2;
            break;

        case 'H': // 16-bit unsigned
            size += 2;
            check_buf(size);
            H = va_arg(ap, uint16_t*);
            *H = unpacku16(buf);
            buf += 2;
            break;

        case 'l': // 32-bit
            size += 4;
            check_buf(size);
            l = va_arg(ap, int32_t*);
            *l = unpacki32(buf);
            buf += 4;
            break;

        case 'L': // 32-bit unsigned
            size += 4;
            check_buf(size);
            L = va_arg(ap, uint32_t*);
            *L = unpacku32(buf);
            buf += 4;
            break;

        case 'q': // 64-bit
            size += 8;
            check_buf(size);
            q = va_arg(ap, int64_t*);
            *q = unpacki64(buf);
            buf += 8;
            break;

        case 'Q': // 64-bit unsigned
            size += 8;
            check_buf(size);
            Q = va_arg(ap, uint64_t*);
            *Q = unpacku64(buf);
            buf += 8;
            break;

        case 'f': // float
            size += 4;
            check_buf(size);
            f = va_arg(ap, float*);
            uf.whole = unpacku32(buf);
            *f = uf.frac;
            buf += 4;
            break;

        case 'd': // double
            size += 8;
            check_buf(size);
            d = va_arg(ap, double*);
            ud.whole = unpacku64(buf);
            *d = ud.frac;
            buf += 8;
            break;

        case 's': // string
            s = va_arg(ap, char*);
            len = unpacku32(buf);
            size += len + 4;
            check_buf(size);
            buf += 4;
            if (maxlen > 0 && len >= maxlen) count = maxlen - 1;
            else count = len;
            memcpy(s, buf, count);
            s[count] = '\0';
            buf += len;
            break;

        case 'b': //binary
            b = va_arg(ap, char*);
            len = unpacku32(buf);
            size += len + 4;
            check_buf(size);
            buf += 4;
            if (maxlen > 0 && len >= maxlen) count = maxlen - 1;
            else count = len;
            memcpy(b, buf, count);
            buf += len;
            break;

        default:
            if (isdigit(*format)) { // track max len for 's' and 'b'
                maxlen = maxlen * 10 + (*format-'0');
            }
        }

        if (!isdigit(*format)) maxlen = 0; //resets maxlen after use.
    }

    va_end(ap);
}

void check_buf(unsigned int size){
    if(size > BUF_SIZE/8){
        fprintf(stderr, "Exceeding size of buffer. Terminating.\n");
        exit(1);
    }
    return;
}