# RCRam
Full project for turning a toy RC truck (New Bright Dodge RAM) into a more advanced remote vehicle with a FPV camera, partial self-driving capabilities, and light effects.

## Status

I joined the [Binghamton University Rover Team](https://github.com/BinghamtonRover) shortly after starting this project, so I did not maintain any personal rover projects during my tenure there. This project barely has any concrete functionality, is out-of-date, and doesn't meet my modern standards for code testing and quality. Though I've resumed some personal rover projects, this software stack will no longer be updated.

## Components
This repository has multiple modules which run in different places and target different platforms.
### Control Station
Intended to be flexible and connect with multiple types of remote-operated vehicles. Connects with remote vehicles to view video, configure, and control. Sends universal commands that can be implemented on the vehicle computer as needed. The Control Station uses cross-platform libraries. The program will be tested on Windows 10 and Linux, but should work on more.

After experimenting with different options for building the Control Station, the best option appears to be NanoGUI, which runs on GLFW. Here's why:
* Runs on GLFW, which provides great keyboard/controller/mouse support in a videogame-like format (+ for vehicle control)
* NanoGUI has useful/common dependencies (NanoVG, GLFW)
    * NanoVG can draw shapes, load and draw Free/TrueType fonts, which are good for custom elements of the GUI
* Very simple but intuitive design, great for adding modern-looking and functional menus to the basic GLFW elements (Video stream, key capture, control)
### RC Hardware Driver
Arduino sketch for real-time control of hardware on the remote vehicle. The Arduino connects to the vehicle computer. This is the least portable module, as the code is specific to this RC truck setup. Future plans include an Arduino library format that enforces a universal serial information protocol, but offers custom implmentation of the required functions.
### Vehicle Computer Program(s)
No started programs yet, but video, driving, effects, etc. may be handled by separate programs. Targets a Raspberry Pi Zero W. Other platforms not supported.
## Ongoing Steps
* Refactoring (separating common libraries, better namespaces)
* (organize the) CMake build system
* Start GUI with NanoGUI
* Documentation
