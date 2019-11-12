# raycer

This is a raytracing library that is focused on speed and interactive rendering. It uses multiple threads to render parts of an image in parallel.

I made this primarily to learn about Qt, graphics in general (to supplement my Graphics course), and the Google Test framework. Turns out you CAN write tests in C++ :-)

## prerequisites

To compile, you need ruby and rake. You also need a development version of Qt5 installed on your system.

## compile

To compile, simply type:

    rake

You might have to adjust some variables to make things work on your system.

A couple of examples will be compiled. The most important one is

    examples/SceneBrowser/SceneBrowser

## features

* Templatized library
* Pluggable cameras:
  * Pinhole camera
  * Orthographic camera
  * Spherical camera
  * Fish eye camera
* Pluggable materials
  * Matte
  * Phong
  * Reflective
  * Transparent
  * Portal (like in the game)
* Pluggable view planes for different interactive experiences (mostly for fun)
* Pluggable shapes
  * Sphere, Box, Plane, Disk, Rectangle, Triangle, Mesh
* Shape compositions
  * Composition, Union, Intersection, Difference, Instancing
* Support for the PLY mesh format
* SSE3 optimizations

