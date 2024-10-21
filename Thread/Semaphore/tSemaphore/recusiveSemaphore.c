#include <stdio.h>
#include <pthread.h>

pthread_mutex_t recursive_mutex;

void nested_function(int level) {
    pthread_mutex_lock(&recursive_mutex);
    printf("Locking at level %d\n", level);
    if (level > 0) {
        nested_function(level - 1);  // Recursive lock
    }
    pthread_mutex_unlock(&recursive_mutex);
    printf("Unlocking at level %d\n", level);
}

void* thread_function(void* arg) {
    nested_function(3);
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

    pthread_mutex_init(&recursive_mutex, &attr);

    pthread_create(&thread, NULL, thread_function, NULL);
    pthread_join(thread, NULL);

    pthread_mutex_destroy(&recursive_mutex);
    pthread_mutexattr_destroy(&attr);

    return 0;
}

