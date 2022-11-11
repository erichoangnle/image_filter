# Image Filter
A simple program that applies filter to images. Written in C.

### Usage
General usage in terminal:
```
$ ./filter -<filter_method> <source_image.bmp> <output_image.bmp>
```

##### Grayscale
Usage:
```
$ ./filter -g <source_image.bmp> <output_image.bmp>
```
One common filter is the “grayscale” filter, where we take an image and want to convert it to black-and-white. How does that work?

Recall that if the red, green, and blue values are all set to 0x00 (hexadecimal for 0), then the pixel is black. And if all values 
are set to 0xff (hexadecimal for 255), then the pixel is white. So long as the red, green, and blue values are all equal, the result 
will be varying shades of gray along the black-white spectrum, with higher values meaning lighter shades (closer to white) and lower 
values meaning darker shades (closer to black).

So to convert a pixel to grayscale, we just need to make sure the red, green, and blue values are all the same value. But how do we 
know what value to make them? Well, it’s probably reasonable to expect that if the original red, green, and blue values were all 
pretty high, then the new value should also be pretty high. And if the original values were all low, then the new value should also be low.

In fact, to ensure each pixel of the new image still has the same general brightness or darkness as the old image, we can take the 
average of the red, green, and blue values to determine what shade of grey to make the new pixel.

If you apply that to each pixel in the image, the result will be an image converted to grayscale.

##### Sepia
Usage
```
$ ./filter -s <source_image.bmp> <output_image.bmp>
```
Most image editing programs support a “sepia” filter, which gives images an old-timey feel by making the whole image look a bit reddish-brown.
An image can be converted to sepia by taking each pixel, and computing new red, green, and blue values based on the original values of the three.
There are a number of algorithms for converting an image to sepia, but for this problem, we’ll ask you to use the following algorithm. For each 
pixel, the sepia color values should be calculated based on the original color values per the below.
```
  sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
  sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
  sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
  ```
Of course, the result of each of these formulas may not be an integer, but each value could be rounded to the nearest integer. It’s also possible 
that the result of the formula is a number greater than 255, the maximum value for an 8-bit color value. In that case, the red, green, and blue 
values should be capped at 255. As a result, we can guarantee that the resulting red, green, and blue values will be whole numbers between 0 and 
255, inclusive.

##### Reflection
Usage:
```
$ ./filter -r <source_image.bmp> <output_image.bmp>
```
Some filters might also move pixels around. Reflecting an image, for example, is a filter where the resulting 
image is what you would get by placing the original image in front of a mirror. So any pixels on the left side 
of the image should end up on the right, and vice versa.

Note that all of the original pixels of the original image will still be present in the reflected image, it’s 
just that those pixels may have rearranged to be in a different place in the image.

##### Blur
Usage:
```
$ ./filter -b <source_image.bmp> <output_image.bmp>
```
There are a number of ways to create the effect of blurring or softening an image. For this problem, we’ll use 
the “box blur,” which works by taking each pixel and, for each color value, giving it a new value by averaging 
the color values of neighboring pixels.

Consider the following grid of pixels, where we’ve numbered each pixel.

$$
\left(\begin{array}{cc} 
1 & 2 & 3 & 4\\
5 & 6 & 7 & 8\\
9 & 10 & 11 & 12\\
13 & 14 & 15 & 16
\end{array}\right)
$$ 

The new value of each pixel would be the average of the values of all of the pixels that are within 1 row and 
column of the original pixel (forming a 3x3 box). For example, each of the color values for pixel 6 would be 
obtained by averaging the original color values of pixels 1, 2, 3, 5, 6, 7, 9, 10, and 11 (note that pixel 6 
itself is included in the average). Likewise, the color values for pixel 11 would be be obtained by averaging 
the color values of pixels 6, 7, 8, 10, 11, 12, 14, 15 and 16.

For a pixel along the edge or corner, like pixel 15, we would still look for all pixels within 1 row and column: 
in this case, pixels 10, 11, 12, 14, 15, and 16.
