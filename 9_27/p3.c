#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

struct memory
{
        int len;
        int buf[1000];
};

int main(int argc,char *argv[])
{
        if(argc!=3)
        {
                perror("Expected two arguments\n");
                return 0;
        }
        struct memory *shared;
        key_t shkey;
        int shid;
        shkey= 567;

        shid = shmget(shkey , sizeof(struct memory), IPC_CREAT | 0666);
        printf("Shared memory of 1000 integers \n");
        shared = (struct memory *) shmat(shid,NULL,0);

        int n,status,i;
        n=atoi(argv[1]);
        pid_t pid;
        char *args[] ={"./c_child",argv[1],argv[2],NULL};

        if( n < 2)
        {
                printf("Invalid argument passed");
                exit(1);
        }

        if ((pid = fork()) < 0)
        {
                printf("forking child process failed\n");
        }

        if (pid == 0)
        {
                execvp(args[0],args);
        }
        else
        {
                wait(NULL);
                n=shared->len;
                for(int i=0;i<n;++i)
                {
                        printf("%d ", shared->buf[i]);
                }
        }
        printf("\n");
        shmdt((void *)shared);
        shmctl(shid,IPC_RMID,NULL);
        exit(0);
}