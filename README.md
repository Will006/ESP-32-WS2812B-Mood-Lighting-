# ESP-32-WS2812B-Mood-Lighting-
ESP-32 WS2812B Mood Lighting 

I have tested and used this with a Node32s.

This uses the FastLED library (https://github.com/FastLED/FastLED) to control the WS2812B LED's. 

Currently without modification to get this code working, you plug in your LED data line into pin 4, the power pin to 5 volts, and the grd to ground. Then it would be a good idea to change NUM_LEDS to the number of LED's you are using. 

For the BlueTooth input currently I have just been testing with a BlueTooth serial input Android app. This sends char's serialy (one at a time). The format of the line I am using is 
hex color of R,hex color of G,hex color of B
ie: 
255,255,255
1,50,232
