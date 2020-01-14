#include <stdio.h>
#include <libusb-1.0/libusb.h>
#include <stdlib.h> 
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int sendData(unsigned char sendData[],libusb_device_handle *handler,int size, uint8_t mwriteEndpointAddress);
uint8_t* receiveData(libusb_device_handle *handler,int size);
int manageRumble(libusb_device_handle *handler,unsigned int packet, unsigned int mwriteEndpointAddress);
uint8_t manageLights(libusb_device_handle *handler, unsigned int packet, unsigned int mwriteEndpointAddress);



struct  definePad
{
	unsigned int readEndpointAddress;
	unsigned int writeEndpointAddress;
	unsigned int wMaxPacketSize;
	unsigned int deviceVendorID;
	unsigned int deviceProductID;
};




int  controlxpad(unsigned int deviceVendorID, unsigned int deviceProductID, unsigned int mwriteEndpointAddress, unsigned int readEndpointAddress, unsigned int wMaxPacketSize)
{
	libusb_init(NULL);
	libusb_device_handle *h =NULL;	
	unsigned char receive[20];
	printf("New program\n");
	h = libusb_open_device_with_vid_pid(NULL, deviceVendorID,deviceProductID);

	if (h != NULL) {	
		while(1){
				
				int received;
				int r = libusb_interrupt_transfer(h, readEndpointAddress ,receive,sizeof(receive), &received, 0);				
				if(r == 0){
					if(receive[3] == 0x10){
						//printf("Pressed A \n");
						manageLights(h,(uint8_t)0x0A, mwriteEndpointAddress);
					}							
					else if(receive[3] == 0x20){
						//printf("Pressed B \n");
						manageLights(h,(uint8_t)0x04, mwriteEndpointAddress);
						
					}	
					else if(receive[3] == 0x40){
						//printf("Pressed X \n");
						manageLights(h,(uint8_t)0x09, mwriteEndpointAddress);
						return 1;
					}						
					else if(receive[3] == 0x80){
						//printf("Pressed Y \n");
						manageLights(h,(uint8_t)0x08, mwriteEndpointAddress);
					
					}
					else if(receive[3] == 0x10 && receive[2]==0x04){
						manageRumble(h,(uint8_t)0xFF, mwriteEndpointAddress);
					}
					printf("\n");
					printf("%x \t",receive[2]);					
				}
		}					
								
	}
	libusb_close(h);
    libusb_exit(NULL);
}





int sendData(unsigned char sendData[],libusb_device_handle *handler,int size, uint8_t writeEndpointAddress){
	int transferred;
	return libusb_interrupt_transfer(handler, writeEndpointAddress ,sendData,size, &transferred, 0);			
}

uint8_t manageLights(libusb_device_handle *handler, unsigned int packet, unsigned int mwriteEndpointAddress){
	unsigned char message[] = {1, 3,packet};
	// initialize();
	sendData(message,handler,sizeof(message), mwriteEndpointAddress);
	
	return 0;
}

int manageRumble(libusb_device_handle *handler,unsigned int packet, unsigned int mwriteEndpointAddress){
	unsigned char message[] = {0x0,0x8,0x0,packet,0xFF,0x0,0x0,0x0};
	return sendData(message,handler,sizeof(message), mwriteEndpointAddress);
}

