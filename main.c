#include <stdio.h>
#include <assert.h>
#include "tlsf.c"

tlsf_t tlsf;

#if 1
int main()
{
    tlsf = tlsf_create_with_pool(malloc(1024 * 1024 * 128), 1024 * 1024 * 128);
    void *p1;
    void *p2;
    void *p3;
    int i;

    for (i = 0; i < 1000; i++)
    {
        printf("#%d\n", i);
        p1 = tlsf_malloc(tlsf, rand() % 100 + 1);
        p2 = tlsf_malloc(tlsf, rand() % 200 + 1);
        p3 = tlsf_malloc(tlsf, rand() % 300 + 1);

        assert(!((unsigned long)p1 & 0xf));
        assert(!((unsigned long)p2 & 0xf));
        assert(!((unsigned long)p3 & 0xf));

        tlsf_free(tlsf, p1);
        tlsf_free(tlsf, p2);
        tlsf_free(tlsf, p3);
    }
    return 0;
}
#else
int main()
{
    tlsf = tlsf_create_with_pool(malloc(1024 * 1024 * 128), 1024 * 1024 * 128);
    void *p1;
    void *p2;
    void *p3;
    int i;

    printf("malloc p1\n");
    p1 = tlsf_malloc(tlsf, 100);
    printf("malloc p2\n");
    p2 = tlsf_malloc(tlsf, 100);
    printf("free p1\n");
    tlsf_free(tlsf, p1);
    printf("malloc p1\n");
    p1 = tlsf_malloc(tlsf, 50);
    printf("free p2\n");
    tlsf_free(tlsf, p2);
    printf("free p1\n");
    tlsf_free(tlsf, p1);
    return 0;
}

#endif