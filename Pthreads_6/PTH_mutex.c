//**************************************************************
//	Demonstrates the usage of pthread mutex variables
//****************************************************************

#include <stdio.h>
#include <pthread.h>

// The PTHREAD_MUTEX_INITIALIZER macro initialise the static mutex
// Setting its attributes to default value. create a static mutex object 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int count = 0;

void *function1(void *arg)
{
    int tmp = 0;
    while (1)
    {
        pthread_mutex_lock(&mutex);
        tmp = count++;
        printf("Count is %d\n", tmp);
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
    return 0;
}

void *function2(void *arg)
{
    int tmp = 0;
    while (1)
    {
        pthread_mutex_lock(&mutex);
        tmp = count--;
        printf("** Count is %d\n", tmp);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return 0;
}

int main(void)
{
    pthread_create(NULL, NULL, &function1, NULL);
    pthread_create(NULL, NULL, &function2, NULL);

    /* Let the threads run for 20 seconds. */
    sleep(20);

    return 0;
}