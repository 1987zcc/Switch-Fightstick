from NXController import Controller

ctr = Controller()
N = 30	# Number of Pokemon in the box
ctr.buttondelay = 0.2
for i in range(N):
	print(f'{i+1}/{N}')
	ctr.A()
	ctr.d(0.7)
	ctr.r(0.7)
	ctr.A()
	ctr.R()
	ctr.R()
	ctr.A()
	ctr.L()
	ctr.L()
	ctr.L()
#ctr.p()
ctr.close()