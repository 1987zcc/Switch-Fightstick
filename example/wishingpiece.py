from NXController import Controller

ctr = Controller()

ctr.LS()
ctr.A()
ctr.pause(1)
ctr.A()
ctr.pause(1)
ctr.A()
ctr.pause(0.3)
ctr.h()

response = input("Restart(y/n): ")
while response == 'y':
	ctr.X()
	ctr.A()
	ctr.pause(3)
	ctr.A()
	ctr.pause(1)
	ctr.A()
	ctr.pause(15)
	ctr.A()

	ctr.pause(7)

	ctr.A()
	ctr.pause(1)
	ctr.A()
	ctr.pause(1)
	ctr.A()
	ctr.pause(0.3)
	ctr.h()

	response = input("Restart(y/n): ")

ctr.A()

ctr.close()