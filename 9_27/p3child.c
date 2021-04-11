#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <semaphore.h>
struct memory
{
        int len;
        int buffer[1000];
};


int main(int argc,char *argv[])
{
        key_t shmkey;
        int shmid;
        struct memory *shared;
        shmkey = 567;
        shmid= shmget(shmkey,sizeof(struct memory), 0666);
        shared = (struct memory *) shmat(shmid,NULL,0);

        int n,d;
        int c=0;
        n = atoi(argv[1]);
        shared->buffer[c] = n;
        c = c + 1;
        while(n != 1)
        {
                if(c==atoi(argv[2]))
                break;
                if( n % 2 == 0)
                {
                        n = n / 2;

                }
                else
                {
                        n = (3 * n) + 1;

                }
                shared->buffer[c++] = n;
        }
        shared->len = c;
    return 0;
}