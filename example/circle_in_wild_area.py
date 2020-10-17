from NXController import Controller

ctr = Controller()
## Or use your serial port if you have many
# ctr = Controller('/dev/tty.usbserial-AO0099VT');

# Hold two stick in the oppsite direction
ctr.ls_r(-1)
ctr.rs_l(-1)
ctr.pause(5)
ctr.release()
# Backwards
ctr.ls_l(-1)
ctr.rs_r(-1)
ctr.pause(5)
ctr.release()

ctr.close()