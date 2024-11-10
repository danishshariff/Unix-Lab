 #include <iostream>
 #include <pthread.h>
 #include <semaphore.h>
 #include <unistd.h>
 #include <vector>
 #define MAX_BUFFER_SIZE 5
 #define NUM_PRODUCERS 2
 #define NUM_CONSUMERS 2
 std::vector<int> buffer; 
 sem_t mutex;
 sem_t empty;
 sem_t full;
 
 void* producer(void* arg) {
 int item = *((int*)arg);
 while (true) {
 sleep(1);
 sem_wait(&empty); 
 sem_wait(&mutex); 
 buffer.push_back(item); 
 std::cout << "Produced: " << item << ", Buffer size: " << buffer.size() << std::endl;
 sem_post(&mutex); 
 sem_post(&full); 
 }
 return NULL;
 }
 
 void* consumer(void* arg) {
 while (true) {
 sleep(1); 
 sem_wait(&full); 
 sem_wait(&mutex); 
 int item = buffer.back(); 
 buffer.pop_back();
 std::cout << "Consumed: " << item << ", Buffer size: " << buffer.size() << std::endl;
 sem_post(&mutex); 
 sem_post(&empty); 
 }
 return NULL;}
 int main() {
 
 sem_init(&mutex, 0, 1);
 
 sem_init(&empty, 0, MAX_BUFFER_SIZE); 
 sem_init(&full, 0, 0);
 
 pthread_t producer_threads[NUM_PRODUCERS];
pthread_t consumer_threads[NUM_CONSUMERS];
 for (int i = 0; i < NUM_PRODUCERS; ++i) {
 int* item = new int(i);
 pthread_create(&producer_threads[i], NULL, producer, (void*)item);
 }
 for (int i = 0; i < NUM_CONSUMERS; ++i) {
 pthread_create(&consumer_threads[i], NULL, consumer, NULL);
 }
 // Join threads
 for (int i = 0; i < NUM_PRODUCERS; ++i) {
 pthread_join(producer_threads[i], NULL);
 }
 for (int i = 0; i < NUM_CONSUMERS; ++i) {
 pthread_join(consumer_threads[i], NULL);
 }
 
 sem_destroy(&mutex);
 sem_destroy(&empty);
 sem_destroy(&full);
 return 0;
 }
