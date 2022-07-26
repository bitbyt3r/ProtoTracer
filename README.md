# **ProtoTracer: 3D Rendering and Animation Engine**
This project is a live 3D rendering and animation engine designed for use on the RPI4 and CM4. It's configured to run only 64x32 HUB75 LED panels. 
This code base uses Hzeller's LED matrix driver to handle the bit banging( https://github.com/hzeller/rpi-rgb-led-matrix ).

Things to do:
  * Write an I2C, I2S, and SPI driver for the most common proto peripherals
  * Offload the hub75 signal generation to a microprocessor either via SPI, Ethernet, or High Speed USB.
  * Optimizations
  
## Demonstration:
As a quick way to showcase the capabilities of this software, here is a demo showing a live rendering of a rotating and textured .OBJ file:

![SpyroExample](https://user-images.githubusercontent.com/77935580/130149757-41306da9-5296-42f5-86bc-87f785d9e56b.gif)

This codebase has been tested on an Arduino Mega (smaller .OBJ file with a 89 pixel matrix) and on a Teensy 4.0 (2000 triangle scene with a 2,804 pixel matrix).

# Usage:
The following links give a detailed description on how to import files, set up controllers, manipulate objects, and render to displays:
- [Creating a controller](https://github.com/coelacant1/ProtoTracer/wiki/Creating-a-custom-controller)
- [Using an existing controller](https://github.com/coelacant1/ProtoTracer/wiki/Using-an-Existing-Controller)
- [Creating an animation](https://github.com/coelacant1/ProtoTracer/wiki/Creating-an-Animation)
  - [Adding (.OBJ) objects with UV maps](https://github.com/coelacant1/ProtoTracer/wiki/Adding-.OBJ-Objects-with-UV-Maps)
  - [Adding (.FBX) objects with blend shapes](https://github.com/coelacant1/ProtoTracer/wiki/Adding-.FBX-objects-with-Blend-Shapes)
  - [Adding image materials](https://github.com/coelacant1/ProtoTracer/wiki/Adding-Image-Materials)
  - [Adding gif materials](https://github.com/coelacant1/ProtoTracer/wiki/Adding-GIF-Materials)
  - [Creating a shader material](https://github.com/coelacant1/ProtoTracer/wiki/Creating-a-Shader-Material)
  - [Modifying 3D objects](https://github.com/coelacant1/ProtoTracer/wiki/Modifying-3D-Objects)
  - [Keyframing animations](https://github.com/coelacant1/ProtoTracer/wiki/Keyframing-Animations)

# Questions?
Any recommendations on additional information to add can be requested in the discussions tab. If you have additional questions, you can @ me in my [Discord server](https://discord.gg/YwaWnhJ) or direct message me on [Twitter](https://twitter.com/Coelacant1).

# Contributing:
Pull requests are very welcome. Any issues found should be reported first to open a discussion. Any recommendations can be requested in the discussions tab.

If you would like to help me keep this project going, any support on Patreon would be greatly appreciated: https://www.patreon.com/coelacant1

# License Agreement:
For this project, [AGPL-3.0](https://choosealicense.com/licenses/agpl-3.0/) is used for licensing as a means to make sure any contributions or usage of the software can benefit the community. If you use and modify this software for a product, you must make the modified code readily available as per the license agreement.
