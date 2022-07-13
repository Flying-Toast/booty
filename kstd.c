#include "kstd.h"

void *memset(void *s, uint8_t c, size_t n)
{
	while (n--)
		*((uint8_t *)s++) = c;
	return s;
}

void *memcpy(void *dest, void *src, size_t n)
{
	while (n--)
		((uint8_t *)dest)[n] = ((uint8_t *)src)[n];
	return dest;
}
