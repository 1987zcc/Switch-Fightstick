import colorsys
import numpy,math
from PIL import Image

Filename = "129s.png"

image = Image.open(Filename).convert('RGBA')
h = image.height
w = image.width
pixels = numpy.array(image)
hsv_array = numpy.empty(shape=(h, w, 5), dtype=float)
for row in range(h):
	for column in range(w):
		rgb = pixels[row, column]
		hsv = colorsys.rgb_to_hsv(rgb[0]/255, rgb[1]/255, rgb[2]/255)
		hsv_array[row, column, 0] = hsv[0]
		hsv_array[row, column, 1] = hsv[1]
		hsv_array[row, column, 2] = hsv[2]
		hsv_array[row, column, 3] = rgb[3]

# Crop the image
if h > 32:
	top = (h - 32) // 2
	bottom = h - 32 - top
	if hsv_array[:top,:,3].any() or hsv_array[-bottom:,:,3].any():
		print("Image is too large")
	hsv_array = hsv_array[top:-bottom, : , :]
	h = 32

if w > 32:
	left = (w - 32) // 2
	right = w - 32 - left
	if hsv_array[:,:left,3].any() or hsv_array[:,-right:,3].any():
		print("Image is too large")
	hsv_array = hsv_array[:,left:-right, :]
	w = 32

def Convert2HVB(hsv):
	H = min(29,math.floor(hsv[0] * 30))
	V = min(14,math.floor(hsv[1] * 15))
	B = min(14,math.floor(hsv[2] * 15))
	return [H,V,B]

def findinlist(hsl):
	for ii in range(len(Colorlist)):
		if numpy.array_equal(Colorlist[ii],hsl):
			return ii
	return -1

# Find all colors
Colorlist = numpy.empty((0,3),int)
for r in range(h):
	if not hsv_array[r,:,3].any():
		continue
	for c in range(w):
		hsv = hsv_array[r,c]
		if hsv[3] == 0:
			continue
		HVB = Convert2HVB(hsv)
		idx = findinlist(HVB)
		if idx < 0:
			Colorlist = numpy.append(Colorlist,[HVB], axis = 0)
			hsv_array[r,c,4] = len(Colorlist) - 1
		else:
			hsv_array[r,c,4] = idx
if len(Colorlist) > 15:
	print("Too many colors")

def ResetCanvas():
	ctr.X() # Tool
	ctr.L() # Transparent
	ctr.d()
	ctr.d()
	ctr.d()
	ctr.d()
	ctr.A()
	ctr.A() # Clear Canvas

	ctr.X()
	ctr.u()
	ctr.u()
	ctr.u()
	ctr.u()
	ctr.A() # Choose pen

	ctr.l(3) # Move cursor to top-left
	ctr.u(3)

def SetPalette():
	ctr.X()
	ctr.u()
	ctr.r()
	ctr.A()
	ctr.pause(0.5)
	for ii in range(len(Colorlist)):
		if ii > 0:
			ctr.L()
			ctr.l(2)
			ctr.d()
			ctr.l(2)
			ctr.d()
			ctr.l(2)
			ctr.d()
		C = Colorlist[ii]
		for V in C:
			for jj in range(V):
				ctr.r()
			ctr.d()
	ctr.A()
	ctr.pause(0.5)
	ctr.B()
	for ii in range(1,len(Colorlist)):
		ctr.R()

def MoveToNextPixel(direction):
	if direction > 0:
		ctr.r()
	else:
		ctr.l()

def Move2NextRow():
	ctr.d()

def PrintPIX():
	ctr.A()

def ChooseColor(last_hsv, hsv):
	Diff = int(last_hsv[4] - hsv[4])
	if Diff > 0:
		for jj in range(Diff):
			ctr.R()
	else:
		for jj in range(-Diff):
			ctr.L()

# # Reset
from NXController import Controller
ctr = Controller()
ctr.LS()
ResetCanvas()
SetPalette()

# Print
direction = +1
last_hsv = [0,0,0,255,0]
for r in range(h):
	if not hsv_array[r,:,3].any(): # Skip transparent row
		Move2NextRow()
		continue
	for c in range(w):
		if direction < 0:
			c = w - c - 1
		hsv = hsv_array[r,c]
		if hsv[3] == 0:	# Skip transparent pixel
			MoveToNextPixel(direction)
			continue
		ChooseColor(last_hsv,hsv)
		last_hsv = hsv
		PrintPIX()
		MoveToNextPixel(direction)
	Move2NextRow()
	direction = - direction

