from NXController import Controller

ctr = Controller()
## Or use your serial port if you have many
# ctr = Controller('/dev/tty.usbserial-AO0099VT'); 
for i in range (10):
	ctr.A()
ctr.close()