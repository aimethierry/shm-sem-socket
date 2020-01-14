#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

#include "usb.c"

char * shm;
char * s;
int shmid = -1;


int openfile(int mykey, int size);

int openfile(int mykey, int size)
{
	
	key_t key;
	key = mykey;
	
	shmid = shmget(key, size, 0666);
	
	if(shmid < 0)
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
	return 0;
}

int main(int argc, char * argv[])
{
	int key;
	int size;
	printf("enter a location to read \n");
	scanf("%d", &key);
	
	printf("enter size  \n");
	scanf("%d", &size);
	


	openfile(key, size);
	int val = 0;
	// printf("%c \n", *shm);
		
if(*shm == '1'){	
	
	printf("am in the control 1");
	struct definePad d;
	d.deviceProductID = 0x028e;
	d.deviceVendorID = 0x045e;
	d.writeEndpointAddress = 0x01;
	d.readEndpointAddress = 0x81;
	d.wMaxPacketSize = 0x0020;
		
	if( controlxpad(d.deviceVendorID, d.deviceProductID, d.writeEndpointAddress, d.readEndpointAddress, d.wMaxPacketSize) == 1)
	{
		printf("use the xpad 1 \n");
		*shm = '0';	
	}
  }
  return 0;
}