#Xbox controller compiler
#
#
#Author:Nshuti Yvan CHristian

.PHONY:clean

appRas:appRas.o sender.o receive.o 
	arm-linux-gcc -o appRas appRas.o -lusb-1.0 -lrt
	arm-linux-gcc -o senderApp sender.o -lusb-1.0 -lrt
	arm-linux-gcc -o receiveApp receive.o -lusb-1.0 -lrt
	@echo Done compiling for target	



appRas.o:usb.c
	arm-linux-gcc -c -o appRas.o usb.c
	@echo Done making object file code	



sender.o:sender.c
	arm-linux-gcc -c -o sender.o sender.c
	@echo done making send


receive.o:receive.c
	arm-linux-gcc -c -o receive.o receive.c
	@echo done making receive


send:appRas
	scp appRas root@10.0.0.42:/root
	ssh root@10.0.0.42		
clean:
	rm -rf appRas.o app appRas
	@echo Done cleaning up
