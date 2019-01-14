# Katana_MS3
Katana midi controller

I have a working prototype of a midi foot controller using an Arduino Uno and thought I'd port it to a Teensy board. I 
thought Teensy might be a good idea because I wanted to add more functionality and program memory was getting quite full. I 
also, though it would be fun to learn more about Teensys. 

Along with the Teensy 3.6, I was planning on using a Mini USB Host shield like this one: https://www.circuitsathome.com/usb-host-shield-hardware-manual/ along with the host shield library: https://github.com/felis/USB_Host_Shield_2.0.

Roland/Boss guitar gear uses a non-class compliant USB device for midi control. Additionally, there is a checksum included in each sysex message. I found this library made for the BOSS MS3: 
https://github.com/MrHaroldA/MS3.

I was able to modify one line of code in the MS3.h file in order to get it to work with a BOSS Katana amplifier. I changed 
part of the sysex header from 0x3b to 0x33 for Katana

   #ifndef MS3_HEADER

   const byte MS3_HEADER[6] = {0x41, 0x00, 0x00, 0x00, 0x00, 0x33};
   
The working Arduino prototype is using the https://github.com/felis/USB_Host_Shield_2.0 library and a USB host shield
(https://www.amazon.com/gp/product/B0777DR3T6/ref=ppx_yo_dt_b_asin_title_o03__o00_s00?ie=UTF8&psc=1)

I have stripped down my sketch to give a more bare bones example of the sort of things I want to do, which is basically 
to send sysex messages to the Katana.

Boss/Roland MS3 (which I am not using): https://www.boss.info/global/products/ms-3/
Boss/Roland Katana (which I am using): https://www.boss.info/us/products/katana-100/

Sending sysex messages straight to the USB midi in allows for a lot control more options.

What got me started on this porject is a forum thread created by the author of the MS3 library: 
https://www.vguitarforums.com/smf/index.php?topic=21864.0



