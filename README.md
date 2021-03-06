# prod_disaster_counter
## Rev 2.0
See a guide on how to unlock the digikey spark Rev 3.0 [here](https://www.instructables.com/How-to-unlock-Digispark-ATtiny85-and-convert-it-to/). They list another guide with an example sketch they use [here](http://www.rickety.us/2010/03/arduino-avr-high-voltage-serial-programmer/). 

I did the high voltage programming example with a PC817 Octoupler.

Then I had to install this core for the attiny85. I used AtTiny core from SpenceKonde (here)[https://github.com/SpenceKonde/ATTinyCore/]. Then the ISP example first flashing bootloader at 8mhz.

Used tiny i2c from adafruit, and 4k oled [here](https://github.com/datacute/Tiny4kOLED). 

## Rev 1.0
This was a project I did for a friend who works in software. I thought it could be fun for them to visualize days without an incident, and maybe they can talk the boss into a pizza party when the days make it past milestones! You can find a video demo [here](https://www.youtube.com/shorts/DNOm6Y0vupc).  
![demo_gif](demo_assets/6grrx0.gif)  

You can find the code in the arduino_prod_disaster_counter subfolder. There's a submodule for the display, as well as for the disaster count logic, as well as for the button.  

I built this in an afternoon, and the wires got a bit messy. I'd like to get into PCBs in the future, and may revisit this and design a pcb for it.  
![demo_perfboard1](demo_assets/20220508_153044.jpg)  

![demo_perfboard2](demo_assets/20220508_153058.jpg)  

Some of the tricky stuff: for the LCD i didnt have a potentiometer to set the contrast, so i wired it to a digital pin and did analog write with a value of 10. You can read it, but its not so clear. If i were to do this again I would add a potentiometer, or try with an analog pin.  
