#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){

    int pid,p;
   p = fork();
   if(p==0){
        printf("This is the Chile Process\n");
        printf("PID:%d\n",getpid());
        printf("Parent's Process ID:%d\n\n",getppid());
   }
   else{
        
        sleep(5);//this will make the parent statement to fall asleep , while the child process gets executed
        // to avoid the zombie child process situation we cacn use wait(NULL) which will make parent process aware that 
        // the child process has been terminated 
        printf("This is the Parent Process\n");
        printf("PID:%d\n",getpid());
        printf("Child's Process ID:%d\n\n",p);
   }


    return 0;
}

/*
soham@LAPTOP-VCSHPE1S:/mnt/d/COLLEGE/TE/OS/OS PRAX$ gcc 2A2.c -o a2
soham@LAPTOP-VCSHPE1S:/mnt/d/COLLEGE/TE/OS/OS PRAX$ ./a2 &
[1] 10575
soham@LAPTOP-VCSHPE1S:/mnt/d/COLLEGE/TE/OS/OS PRAX$ This is the Chile Process
PID:10576
Parent's Process ID:10575

ps
    PID TTY          TIME CMD
    360 pts/0    00:00:00 bash
  10575 pts/0    00:00:00 a2
  10576 pts/0    00:00:00 a2 <defunct>
  10577 pts/0    00:00:00 ps
soham@LAPTOP-VCSHPE1S:/mnt/d/COLLEGE/TE/OS/OS PRAX$ This is the Parent Process
PID:10575
Child's Process ID:10576
*/
