#include <core.h>
#include <unix.h>

static table symbol_table;

u64 shash(unsigned char *content, int length)
{
    unsigned h = 0;
    
    for (int i = 0; i < length; i++) {
        h += content[i];
        h += (h << 10);
        h ^= (h >> 6);
    }
    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);
    return h;
}

u64 string_hash(void *x)
{
    buffer b = x;
    return shash(bref(b, 0), buffer_length(b));
}

boolean string_equal(void *a, void *b)
{
    buffer ba = a;
    buffer bb = b;
    if (buffer_length(ba) != buffer_length(bb)) return false;
    return memcmp(bref(ba, 0), bref(bb, 0), buffer_length(ba))?false:true;
}


