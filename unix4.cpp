 #include <iostream>
 #include <cstdlib>
 #include <cstring>
 #include <sys/types.h>
 #include <sys/ipc.h>
 #include <sys/shm.h>
 #include <unistd.h>
 #include <sys/wait.h>
 
 #define SHM_KEY 1234
 
 #define SHM_SIZE 1024
 int main() {
 
 key_t key = ftok(".", SHM_KEY);
 if (key ==-1) {
 perror("ftok"); 
}
 exit(1);
 
 int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
 if (shmid ==-1) {
 perror("shmget"); 
 exit(1);
 }
 
 char *shm_ptr = (char *)shmat(shmid, NULL, 0);
 if (shm_ptr == (char *)(-1)) {
 perror("shmat"); 
 exit(1);
 }
 
 std::string message = "Hello, shared memory!";
 std::strcpy(shm_ptr, message.c_str());
 
 pid_t child_pid = fork();
 if (child_pid ==-1) {
 perror("fork"); 
 exit(1);
 }
 if (child_pid == 0) {
 
 std::cout << "Child process reads: " << shm_ptr << std::endl;
 
 if (shmdt(shm_ptr) ==-1) {
 perror("shmdt"); 
 exit(1);
 }
 } else {
 
 wait(NULL);
 
 if (shmdt(shm_ptr) ==-1) {
 perror("shmdt"); 
 exit(1);
 }
 
 if (shmctl(shmid, IPC_RMID, NULL) ==-1) {
 perror("shmctl"); 
 exit(1);
 }
 }
 return 0;
 }
