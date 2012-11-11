#include <pthread.h>
#include <stdio.h>

void* hello(void *arg)
{
    printf("%s\n", (char *)arg);
    pthread_exit(0);
}

int main()
{
    pthread_t pt;
    pthread_attr_t pat;
    int retval;

    pthread_attr_init(&pat);
    pthread_attr_setdetachstate(&pat, PTHREAD_CREATE_DETACHED);
    retval = pthread_create(&pt, NULL, hello, (void *)"hello");
    pthread_attr_destroy(&pat);
    return 0;
}
