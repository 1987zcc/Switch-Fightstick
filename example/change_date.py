from NXController import Controller

ctr = Controller()

for i in range(30):
	ctr.A()
	if i == 0:
		ctr.r()
		ctr.r()
	else:
		ctr.l()
		ctr.l()
		ctr.l()
	ctr.u()
	ctr.r(0.4)
	ctr.A()

ctr.close()