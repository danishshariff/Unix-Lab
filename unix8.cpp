 //Sender.cpp
 #include <iostream>
 #include <cstring>
 #include <cstdlib>
 #include <unistd.h>
#include <sys/types.h>
 #include <sys/ipc.h>
 #include <sys/msg.h>
 using namespace std;
 
 struct Message {
 long mtype;
 char mtext[100];
 };
 int main() {
 key_t key;
 int msgid;
 Message message;

 key = ftok("/tmp", '1');
 if (key ==-1) {
 perror("ftok");
 exit(1);
 }
 
 msgid = msgget(key, 0666 | IPC_CREAT);
 if (msgid ==-1) {
 perror("msgget");
 exit(1);
 }

 message.mtype = 1; 
 strcpy(message.mtext, "Hello, this is a message from the sender!");
 
 if (msgsnd(msgid, &message, sizeof(message.mtext), 0) ==-1) {
 perror("msgsnd");
 exit(1);
 }
 cout << "Data sent to message queue." << endl;
 return 0;
 }
 
 //Receiver.cpp
 #include <iostream>
 #include <cstring>
 #include <cstdlib>
 #include <unistd.h>
 #include <sys/types.h>
 #include <sys/ipc.h>
 #include <sys/msg.h>
 using namespace std;
 
struct Message {
 long mtype;
 char mtext[100];
 };
 int main() {
 key_t key;
 int msgid;
 Message message;
 
 key = ftok("/tmp", '1');
 if (key ==-1) {
 perror("ftok");
 exit(1);
 }
 
 msgid = msgget(key, 0666 | IPC_CREAT);
 if (msgid ==-1) {
 perror("msgget");
 exit(1);
 }
 
 if (msgrcv(msgid, &message, sizeof(message.mtext), 1, 0) ==-1) {
 perror("msgrcv");
 exit(1);
 }
 cout << "Data received gmessage queue: " << message.mtext << endl;
 return 0;
 }