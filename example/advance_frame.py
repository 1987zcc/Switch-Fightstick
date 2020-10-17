from NXController import Controller

ctr = Controller()
## Or use your serial port if you have many
# ctr = Controller('/dev/tty.usbserial-AO0099VT');
ctr.LS()
# Advance raid seed FrameCycle times
FrameCycle = 5
ReturntoStartDate = True
N = FrameCycle + 1 if ReturntoStartDate else FrameCycle

for ii in range (N):
	# enter the raid
	ctr.A()
	ctr.pause(2)

	# quit the game and go to settings
	ctr.h()
	ctr.pause(1)
	ctr.d()
	for jj in range(4):
		ctr.r()
	ctr.A()
	ctr.d(2)
	ctr.r()
	for jj in range(4):
		ctr.d()
	ctr.A()

	# change the date
	ctr.d(0.4) # Scroll down to bottom
	ctr.A()
	ctr.r()
	ctr.r()
	if ii < FrameCycle:
		ctr.u()
	else:
		for jj in range(FrameCycle):
			ctr.d()
	ctr.r(0.4)
	ctr.A()

	# enter the game, quit the raid
	ctr.h()
	ctr.pause(0.2)
	ctr.u()
	ctr.A()
	ctr.pause(1.1)
	ctr.B()
	ctr.pause(0.6)
	ctr.A()
	ctr.pause(4.5)

	# collect Watts
	if ii < FrameCycle:
		ctr.A()
		ctr.pause(0.5)
		ctr.A()
		ctr.pause(0.5)

	# Check den
	ctr.A()
	ctr.pause(2)

ctr.close()