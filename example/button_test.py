from NXController import Controller

ctr = Controller()
## Or use your serial port if you have many
# ctr = Controller('/dev/tty.usbserial-AO0099VT'); 
ctr.A()
ctr.B()
ctr.X()
ctr.Y()
ctr.L()
ctr.R()
ctr.ZL()
ctr.ZR()
ctr.LS()
ctr.RS()
ctr.p()
ctr.m()
## long press to quit
ctr.B(5)
ctr.close()