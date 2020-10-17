from NXController import Controller

ctr = Controller()
N = 90	# Number of Pokemon

for ii in range(N):
	print(f'{ii+1}/{N} released')
	ctr.A()
	ctr.pause(0.1)
	ctr.u()
	ctr.u()
	ctr.A()
	ctr.pause(0.7)
	ctr.u()
	ctr.A()
	ctr.pause(1.3)
	ctr.A()

	# Move to next
	ctr.r()

	# Change row
	if ii % 6 == 5:
		ctr.r()
		ctr.d()

	# Change boxs
	if ii % 30 == 29:
		ctr.R()
		ctr.d()
		ctr.d()

ctr.close()