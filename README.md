# Cape
Arduino code for my fiber optic cape.

Uploading the code is not complicated but there are many steps involved, like installing the driver that suits your computer's operating system, installing the Arduino development environment, and pressing the onboard reset button at just the right moment.

Just follow the instructions and tutorials Adafruit provides here: https://learn.adafruit.com/getting-started-with-flora.

I will share some tips that were hard to find: 

* If you are using the Gemma and not the Flora, be aware that it does not work with a USB 3 port. That was a problem for me because my Mac only has USB3 ports. Luckily you can use an older USB splitter that will downgrade your port and make the Gemma behave. 
* At the beginning whenever I tried to upload a new version of the code I disconnected the power from the Flora so that only the USB will be connected. Otherwise, the Arduino IDE wouldn't succeed in connecting. After a while, I realized that pressing the onboard reset button puts the Flora(and the Gemma) in a boot mode for some seconds and in that mode, it can receive code being uploaded to it. So if you get a repeating error line after pressing the upload button try pressing the reset button.

I played around with all the demo code I found online and came up with something I liked, you are free to use it. It's not high-class programming cause I really had no energy left at that stage but it sure works :]

There are many functions that are commented out but you can use them to test other color effects you may like more. Some of them (I don't remember which) probably throw exceptions cause they cause the LED strip to restart. 

Code is provided as is, and is mostly coppied from the internet, so don't have any complaints for me please : ] 

Have fun.
