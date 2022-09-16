# Filter (more)

Implement a program that applies filters to BMPs, per the below.
```
$ ./filter -r image.bmp reflected.bmp
```

## Specification
Implement the functions in ```helpers.c``` such that a user can apply grayscale, re??ection, blur, or edge detection filters to their images.

- The function ```grayscale``` should take an image and turn it into a black-and-white version ? of the same image.
- The ```reflect``` function should take an image and reflect it horizontally.
- Finally, the ```blur``` function should take an image and turn it into a box-blurred version of the same image.
- The ```edges``` function should take an image and highlight the edges between objects, according to the Sobel operator.

You should not modify any of the function signatures, nor should you modify any other files other than ```helpers.c```.