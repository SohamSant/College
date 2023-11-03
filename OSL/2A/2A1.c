#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
    int pid ,p;
    pid=getpid();
    printf("Current Process ID :%d\n\n",pid);

    printf("Forking for Creating Child Process .......\n\n");
    p=fork();//returns Pid of the child process;

    if(p<0)
    printf("ERROR");
    else if (p==0){
        sleep(3);// the child process is put to sleep and the parent process is terminated before it wakes up
        printf("In Child Process\n");
        printf("Child Process having pid:%d\n\n",getpid());
        printf("My Parent Process id:%d\n\n",getppid());// Orphan child process cannot get the correct pid of its parent process
    }
    else{
        
        printf("In Parent Process\n");
        printf("Parent Process having pid:%d\n\n",getpid());
        printf("My Child process id:%d\n\n",p);
    }


    return 0;

}