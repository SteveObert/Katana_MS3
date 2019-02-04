# Katana_MS3
Katana midi controller

This is working prototype of a MIDI foot controller for a BOSS Katana using a Teensy 3.2.  The foot controller uses the USB port on the Katana to send MIDI sysex. The way I have it programed it emulates a GA-FC without a Tap Tempo switch and without additional footswitch connections (although there doesn’t seem to be any reason that’s not possible). The controller can also listen to a 5 pin MIDI IN port and can be programed to translate MIDI messages (PC, CC, etc.) to sysex and forward those to a Katana. However, you must know the Katana sysex. Sending MIDI out from the footswitch is also possible.

Along with the Teensy 3.2, I use a Mini USB Host shield like this one: https://www.circuitsathome.com/usb-host-shield-hardware-manual/ along with the host shield library: https://github.com/felis/USB_Host_Shield_2.0.

Roland/Boss guitar gear uses a non-class compliant USB device for midi control. Additionally, there is a checksum included in each sysex message. I found this library made for the BOSS MS3:  https://github.com/MrHaroldA/MS3.

I was able to modify one line of code in the MS3.h file in order to get it to work with a BOSS Katana amplifier. I changed 
part of the sysex header from 0x3b to 0x33 for Katana

   #ifndef MS3_HEADER

   const byte MS3_HEADER[6] = {0x41, 0x00, 0x00, 0x00, 0x00, 0x33};
   
   
The working prototype usesthe library https://github.com/felis/USB_Host_Shield_2.0 and a USB host shield
(https://www.amazon.com/gp/product/B0777DR3T6/ref=ppx_yo_dt_b_asin_title_o03__o00_s00?ie=UTF8&psc=1)

Aditionally I used a MIDI break out board but there no reason not to build your own MIDI in/out circuit. https://www.amazon.com/ubld-it-MIDI-Breakout-Board/dp/B00YDLVLVO/ref=sr_1_fkmr0_2?ie=UTF8&qid=1549302443&sr=8-2-fkmr0&keywords=midi+host+shield

What got me started on this project is a forum thread created by the author of the MS3 library: 
https://www.vguitarforums.com/smf/index.php?topic=21864.0

