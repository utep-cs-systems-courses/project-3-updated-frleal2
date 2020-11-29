First you have to run "make install" in order to intsall the timerlib library correctly
in the directory. 

Then to install the program on to the msp430 you have to run make load.

You will see the device will start to blink as the vm prints output to intall
the program.

The First button plays a quick buzzy note, while it also turns on only the green led on.

The Second button plays another quick note, while it turns on only the red led on.

The third button will play another quick note while it turns on both red and green leds.

The fourth button will play and ending note while it turns off both leds. 

If you hold any of the butttons down it will buzz until you let it off.