#include <stdio.h>
#include <assert.h>
#include "tlsf.c"

tlsf_t tlsf;

int main()
{
    tlsf = tlsf_create_with_pool(malloc(1024 * 1024 * 128), 1024 * 1024 * 128);
    void *p1;
    void *p2;
    void *p3;
    int i;

    for (i = 0; i < 1000000; i++)
    {
        p1 = tlsf_malloc(tlsf, rand() % 100 + 1);
        p2 = tlsf_malloc(tlsf, rand() % 200 + 1);
        p3 = tlsf_malloc(tlsf, rand() % 300 + 1);

        // assert(!((unsigned long)p1 & 0xf));
        // assert(!((unsigned long)p2 & 0xf));
        // assert(!((unsigned long)p3 & 0xf));

        p1 = tlsf_realloc(tlsf, p1, rand() % 100 + 1);
        p2 = tlsf_realloc(tlsf, p2, rand() % 200 + 1);
        p3 = tlsf_realloc(tlsf, p3, rand() % 300 + 1);

#ifdef TLSF_64BIT
        if (((unsigned long)p1 & 0b1111))
        {
            printf("p1: %p\n", p1);
            assert(0);
        }
        if (((unsigned long)p2 & 0b1111))
        {
            printf("p2: %p\n", p2);
            assert(0);
        }
        if (((unsigned long)p3 & 0b1111))
        {
            printf("p3: %p\n", p3);
            assert(0);
        }
#else
        if (((unsigned long)p1 & 0b111))
        {
            printf("p1: %p\n", p1);
            assert(0);
        }
        if (((unsigned long)p2 & 0b111))
        {
            printf("p2: %p\n", p2);
            assert(0);
        }
        if (((unsigned long)p3 & 0b111))
        {
            printf("p3: %p\n", p3);
            assert(0);
        }
#endif
        tlsf_free(tlsf, p1);
        tlsf_free(tlsf, p2);
        tlsf_free(tlsf, p3);

        p1 = tlsf_memalign(tlsf, 1<<(rand() % 5 + 3), rand() % 100 + 1);
        p2 = tlsf_memalign(tlsf, 1<<(rand() % 5 + 3), rand() % 200 + 1);
        p3 = tlsf_memalign(tlsf, 1<<(rand() % 5 + 3), rand() % 300 + 1);

#ifdef TLSF_64BIT
        if (((unsigned long)p1 & 0b1111))
        {
            printf("p1: %p\n", p1);
            assert(0);
        }
        if (((unsigned long)p2 & 0b1111))
        {
            printf("p2: %p\n", p2);
            assert(0);
        }
        if (((unsigned long)p3 & 0b1111))
        {
            printf("p3: %p\n", p3);
            assert(0);
        }
#else
        if (((unsigned long)p1 & 0b111))
        {
            printf("p1: %p\n", p1);
            assert(0);
        }
        if (((unsigned long)p2 & 0b111))
        {
            printf("p2: %p\n", p2);
            assert(0);
        }
        if (((unsigned long)p3 & 0b111))
        {
            printf("p3: %p\n", p3);
            assert(0);
        }
#endif
        tlsf_free(tlsf, p1);
        tlsf_free(tlsf, p2);
        tlsf_free(tlsf, p3);
    }
#ifdef TLSF_64BIT
    printf("64bit pass\n");
#else
    printf("32bit pass\n");
#endif
    return 0;
}