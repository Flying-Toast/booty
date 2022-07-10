#include "kstd.h"

void *memset(void *s, uint8_t c, size_t n)
{
	while (n--)
		*((uint8_t *)s++) = c;
	return s;
}
