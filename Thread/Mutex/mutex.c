#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>


int counter = 0;                         //shared Resource
pthread_mutex_t counterMutex;

long long currentTimeMillis() {
    struct timeval tv;
    gettimeofday(&tv, NULL);            //system calls
    return (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
}

void* incrementCounter(void* arg) {
    pthread_t threadId = pthread_self();

    for (int i = 0; i < 10; i++) {

        pthread_mutex_lock(&counterMutex);  
        counter++;
        printf("Time: %lld ms | Thread ID: %lu | Counter: %d\n", currentTimeMillis(), threadId, counter);
        pthread_mutex_unlock(&counterMutex);

        usleep(100);
    }
    return NULL;
}

int main() {
    pthread_mutex_init(&counterMutex, NULL);

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, incrementCounter, NULL);
    pthread_create(&thread2, NULL, incrementCounter, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&counterMutex);
    printf("Final counter value: %d\n", counter);

    return 0;
}

