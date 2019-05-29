# Mandelbrot image and gif generator #

![grab-landing-page](Eksempel.gif)

## Image:
Creates an image of a given size in a given area of the mandelbrot set. With a given number of iterations over z.

## Gif:
Creates a gif of user defined number of frames, which zooms into a given point into the mandelbrot set. The problem is that you can't zoom very deep without increasing the iterations, and when iterations > 1000, things start to get really slow. 

## Misc:
I'm sure the speed could have been helped with more efficient code, multithreading, and maybe in addition to iterating over z, one could have used one of the other algorithms to determine if z will explode.

At first i used std::complex, but i found that it was more efficient to just use to doubles for the real and imaginary part of z

## Libraries used:
[Lodepng](https://github.com/lvandeve/lodepng#lodepng)
[gif.h](https://github.com/ginsweater/gif-h)


Kent Odde, May 2019
