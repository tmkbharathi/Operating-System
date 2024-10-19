#include <stdio.h>
#include <pthread.h>

pthread_mutex_t errorcheck_mutex;

int main() {
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);  // Set as error-checking mutex
    pthread_mutex_init(&errorcheck_mutex, &attr);

    // Attempt to lock the mutex
    if (pthread_mutex_lock(&errorcheck_mutex) == 0) {
        printf("Mutex locked successfully.\n");
    }

    // Try locking again, should return an error since the same thread holds it
    if (pthread_mutex_lock(&errorcheck_mutex) != 0) {
        printf("Error: mutex is already locked by this thread.\n");
    }

    pthread_mutex_unlock(&errorcheck_mutex);  // Correctly unlock
    pthread_mutex_destroy(&errorcheck_mutex);
    pthread_mutexattr_destroy(&attr);

    return 0;
}

