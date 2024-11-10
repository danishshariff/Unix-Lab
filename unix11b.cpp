#include <iostream>
#include <pthread.h>
 
 void* printHello(void* threadNumber) {
 int* num = static_cast<int*>(threadNumber);
 std::cout << "Hello World from Thread " << *num << std::endl;
 pthread_exit(NULL);
 }
 int main() {
 
 const int numThreads = 5;
 
 for (int i = 1; i <= numThreads; ++i) {
 pthread_t thread;

 int threadNumber = i;
 int threadCreateStatus = pthread_create(&thread, NULL, printHello, &threadNumber);
 if (threadCreateStatus) {
 std::cerr << "Error creating thread: " << threadCreateStatus << std::endl;
 return-1;
 }
 
 pthread_join(thread, NULL);
 }
 return 0;
 }