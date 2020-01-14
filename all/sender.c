#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>




char * shm;
char * s;
int shmid = -1;

int create(int mykey, int size);

int create(int mykey, int size)
{
	char flag[] = "1";
	key_t key;
	key = mykey;
   	shmid = shmget(key, size, IPC_CREAT | 0666);
	if(shmid == -1)
	{
		perror ("ERROR: shm_open() failed \n");
		exit(1);
	}
	shm = shmat(shmid, NULL, 0);
	if(shm == (char *) -1)
	{
		perror ("shmat \n");
		exit(1);
	}
	memcpy(shm, flag , 11);
	printf("key is %d and size is %d \n", mykey, size);
	return 0;
}


void controlXpad()
{
	int key;
	int size;
	printf("enter the key \n");
	scanf("%d", &key);
	printf("enter the size \n");
	scanf("%d", &size);
	create(key, size);
	s = shm;
	
	int val=1;
	//deleting the file in the memory
	while(val)
	{
		sleep(1);

        if(*shm == '0')
		{   
			printf("end of xpad1 and go to the xpad2 \n");
			int remove = shmctl(shmid, IPC_RMID, NULL);
			if(remove == -1)
			{
				perror("there was an error in removing \n");
			} 
			val =0;
		}
	}	
	
}
int main(int argc, char * argv[])
{
	controlXpad();
	return 0;
}