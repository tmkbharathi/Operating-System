#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_rwlock_t rwlock;

void* reader(void* arg) {
    pthread_rwlock_rdlock(&rwlock);
    printf("Reader %ld is reading.\n", (long)arg);
    sleep(1);  // Simulate reading
    pthread_rwlock_unlock(&rwlock);
    printf("Reader %ld finished reading.\n", (long)arg);
    return NULL;
}

void* writer(void* arg) {
    pthread_rwlock_wrlock(&rwlock);
    printf("Writer %ld is writing.\n", (long)arg);
    sleep(2);  // Simulate writing
    pthread_rwlock_unlock(&rwlock);
    printf("Writer %ld finished writing.\n", (long)arg);
    return NULL;
}

int main() {
    pthread_t readers[3], writers[2];
    pthread_rwlock_init(&rwlock, NULL);

    for (long i = 0; i < 3; i++) {
        pthread_create(&readers[i], NULL, reader, (void*)i);
    }
    for (long i = 0; i < 2; i++) {
        pthread_create(&writers[i], NULL, writer, (void*)i);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock);
    return 0;
}

