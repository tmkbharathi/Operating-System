#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_CARS 5 // Number of cars trying to park

sem_t parking_spots; // Semaphore to represent parking spaces

void* park_car(void* car_id) {
    long id = (long)car_id;
    
    // Car arrives and waits to find an available parking spot
    printf("Car %ld is waiting to park...\n", id);
    sem_wait(&parking_spots); // Wait for an available parking spot
    
    // Critical Section: Parking the car
    printf("Car %ld has parked.\n", id);
    sleep(2); // Simulate the car being parked for a while
    
    // Car leaves the parking lot, freeing up a parking spot
    printf("Car %ld is leaving the parking lot.\n", id);
    sem_post(&parking_spots); // Signal that a parking spot is available
    
    pthread_exit(NULL);
}

int main() {
    pthread_t cars[NUM_CARS];
    long i;
    
    // Initialize semaphore to 2 parking spots
    sem_init(&parking_spots, 0, 2);
    
    // Create threads representing cars trying to park
    for (i = 0; i < NUM_CARS; i++) {
        pthread_create(&cars[i], NULL, park_car, (void*)i);
        sleep(1); // Cars arrive at different times
    }
    
    // Wait for all cars to finish parking and leaving
    for (i = 0; i < NUM_CARS; i++) {
        pthread_join(cars[i], NULL);
    }
    
    // Destroy the semaphore
    sem_destroy(&parking_spots);
    
    return 0;
}

