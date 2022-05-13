/*
 *Jared Migneco
 *Project 7
 *05/13/22
 *
 *Slave Class
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

int main (const int argc, char * argv)
{

        //matching the shared mem ID to be the same as in the master class
        shmid = shmget(0x080698, sizeof(int), 0666 | IPC_CREAT);
        int *shm = (int*)shmat(shmid, NULL, 0);

        //checks if shared memory is set to 0
        if (*shm == 0)
        {
                printf("Slave: shared memory is set to 0");
        }
        else
        {
                //worker class has an error and exits if shared memory is not 0
                printf("Slave: ERROR: shared memory not set to 0");
                exit(EXIT_FAILURE);
        }

        //unfinished so left at 0 so program can compile
        shm = 0;

        //code for handling critical section, uses semaphore to handle CR
        for (i = 0; i <5; i++)
        {

                //sleeping for random amount of time
                sleep(rand() % 5);

                //printing current system time
                printf("Slave: task completed at: %s", "$(date = '%r')");
                sleep(rand() % 5);
        }
        //waits for shared memory to reach 0
        while(*shm != 0)
        {
                sleep(1);
        }
        printf("Slave: Shared memory reset to 0");
        return(EXIT_FAILURE);

}
