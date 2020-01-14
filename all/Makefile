#Xbox controller compiler
#
#
#Author:Nshuti Yvan CHristian

.PHONY:clean

appRas:sender.o receive.o receive2.o
	arm-linux-gcc -o senderApp sender.o -lusb-1.0 -lrt
	arm-linux-gcc -o receiveApp receive.o -lusb-1.0 -lrt
	arm-linux-gcc -o receiveApp2 receive2.o -lusb-1.0 -lrt
	@echo Done compiling for target	



# appRas.o:usb.c
# 	arm-linux-gcc -c -o appRas.o usb.c
# 	@echo Done making object file code	



sender.o:sender.c
	arm-linux-gcc -c -o sender.o sender.c
	@echo done making send


receive.o:receiver1.c usb.c 
	arm-linux-gcc -c -o receive.o receiver1.c
	@echo done making receive


receive2.o:receiver2.c usb.c 
	arm-linux-gcc -c -o receive2.o receiver1.c
	@echo done making receive


send:appRas
	# scp appRas root@10.0.0.42:/root
	sudo scp senderApp root@10.0.0.42:/root
	sudo scp receiveApp root@10.0.0.42:/root
	sudo scp receiveApp2 root@10.0.0.42:/root
	sudo ssh root@10.0.0.42		


clean:
	# rm -rf appRas.o app appRas
	rm -rf receive.o app receiveApp
	rm -rf senderApp.o app senderApp
	rm -rf receive2.o app receiveApp2
	@echo Done cleaning up
