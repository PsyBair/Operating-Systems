// Operating Systems Assignment 1 - Lorenzo Bair

#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <random>
#include "consume.cpp"

using namespace std;

#define BUFFER_SIZE 2
int index = 0;
int buffer[BUFFER_SIZE];
sem_t full, empty;
pthread_mutex_t mutex;

void* produce(void* arg) {
	while (true) {
		sleep(1);
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		int item = rand() % 10;
		buffer[index++] = item;
		cout << "Produced: " << item << endl;
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
	}
}

int main() {
	pthread_t producer, consumer;
	sem_init(&empty, 0, BUFFER_SIZE);
	sem_init(&full, 0, 0);
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&producer, NULL, produce, NULL);
	pthread_create(&consumer, NULL, consume, NULL);
	pthread_exit(NULL);
}