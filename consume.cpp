// Operating Systems Assignment 1 - Lorenzo Bair

#include "producer.cpp"

using namespace std;

void* consume(void* arg) {
	while (true) {
		sleep(1);
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		int item = buffer[--index];
		cout << "Consumed: " << item << endl;
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
	}
}