/*
 *Jared Migneco
 *Project 7
 *05/13/22
 *
 *
 *
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

int main (int argc, int* argv[])
{
        //command line counter variable
        int commmandNConquer, i, n;

        n = *argv[3];
        //checking that three parameters are passed
        if (argc != 3)
        {
                printf("Master: ERROR: please pass three arguments");
        }
        else if (n > 20)
        {
                n = 20;
                printf("Master: passed n value should be max of 20, set to 20 instead");

        }

        //creating shared memory address
        int shmid = shmget (0x080698, sizeof(int), 0666 | IPC_CREAT);
        int* shm = (int*)shmat(shmid, NULL, 0);


        for(i = 0, i < n, i++)
        //forking here
        int processID = fork();

        //I think the joke is funny for an error message and refuse to take it out
        //error message if master does not fork
        if(processID < 0)
        {
                perror("ERROR: you might have spooned instead of forking\n");
                exit(EXIT_FAILURE);
        }
        //slave is executed so long as master successfully forked
        else if(processID == 0)
        {
                execl("./slave.c", n, NULL);
        }




        //resetting shared memory
        *shm = 0;
        printf("Master: shared memory has been reset\n");
        wait(NULL);

        //killing and signalling exit with a success message
        shmctl(shmid, IPC_RMID, NULL);
        printf("Master has been slain\n");

        return(EXIT_SUCCESS);
}
