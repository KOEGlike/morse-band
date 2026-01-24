
# Morse Band
![image of a band on my arm](https://rawcdn.githack.com/KOEGlike/morse-band/10ea6d376f088f068a7faa55c1b2209cb9f8524f/images/morse-band.jpg)
A lil pair of bands that you can use to communicate in Morse code. If you press the button on one band, the other one vibrates.

## Why?

I made this project for Hack Club's [Alleyway](https://alley.hackclub.com); my two other projects were all really flashy with LEDs. With this one I wanted to make something more low-key.

## The process

I went with a pretty simple list of components:

- Xiao ESP32-C6: This basically does everything. My main reason for choosing an ESP chip for this project was the ESP-NOW protocol, which makes communicating between two ESPs really easy. And the Xiao has a built-in BMS.
- A choc low-profile switch
- A pouch lipo battery. I already had this lying around.
- A vibration motor
- A watch band

I designed the case in FreeCAD; the biggest part was my LiPo battery, so I designed everything around that. This is a "sandwich"-style design; everything is held in place by 4 screws that go through the whole body.

The firmware is some simple vibe-coded Arduino code; it's not that complex.

## It killed it self????

After I landed in LA for Supercon, I checked all three of my projects to see if they were still working properly. Two out of three worked; this one didn't. One of the bands just died; I couldn't upload new firmware or anything.

When I got home I disassembled it, and it turned out that the Xioa was just dead.
