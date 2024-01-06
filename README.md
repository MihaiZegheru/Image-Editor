<!--  -->
<!-- Copyright (c) 2023-2024 | Mihai Zegheru | 312CAb -->
<!--  -->

# Image Editor

This is a C project for my PCLP course homework, designed to edit images in the
NetPBM format and perform various operations on them using the cli.

## About

This is my homework for my Computer Programming and Programming Languages
course, that I took in my first semester of university, in 2023. Its main goal
is to sum up everything that I learnt this semester into a project that has some
nice practical applications.

This project facilitates editing images and perferoming various operations on
them from the cli, like applying filters. The main concept that it uses is
having an active selection that is going to be affected by the operations.

The operations that can be performed are listed here:

* [Load an image](#Loading-an-image)
* [Select a working area](#Selecting-a-working-area)
* [Print the histogram](#Printing-the-histogram)
* [Equalize](#Equalizing)
* [Rotate](#Rotating)
* [Crop](#Cropping)
* [Apply a filter](#Applying-a-filter)
* [Save the image](#Saving)
* [Exit the app](#Exiting)

The operations are going to stack on one another, such that the image currently
loaded is going to change after every active operation.

### Loading an image

Load a new image from a file.

Supports P2, P3, P5 and P6 from the NetPBM format.

**Calling**
```sh
LOAD <file_path>
```

**Example**

*Input*
```sh
LOAD res/image.ppm
```

<br><br>

### Selecting a working area

Select an area from the image that is going to act as an active selection for
the following opperations to be applied on:

- ROTATE
- CROP
- APPLY

There are 2 ways of selecting:

#### The whole image

**Calling**
```sh
SELECT ALL
```

<br>

#### A section of the image

**Calling**
```sh
SELECT <x1 y1 x2 y2>
```

**Example**

*Input*
```sh
SELECT 45 60 200 200
```

The order of the selection points is not fixed. That means you can first provide
the down right corner, rather than the up left corner.

<br><br>

### Printing the histogram

Print the histogram of an image of P2 or P5 format.

**Calling**
```sh
HISTOGRAM <x> <y>
```

**Example**

*Input*
```sh
HISTOGRAM 32 32
```

`x` is the maximum value of the histogram.

`y` is the number of bins. It has to be a power of 2, from [2, 256].

<br><br>

### Equalizing

Equalize an image of P2 or P5 format.


**Calling**
```sh
EQUALIZE
```

<br><br>

### Rotating

Rotate a square selection of an image or the whole image if it is selected. It
supports only angles that are divisible by 90.

**Calling**
```sh
ROTATE <angle>
```

**Example**

*Input*
```sh
ROTATE -270
```

<br><br>

### Cropping

Crop the image to match the active selection.

The active selection is going to be set to the whole image.

**Calling**
```sh
CROP
```

<br><br>

### Applying a filter

Apply a filter of choice onto the active selection.

If the active selection is the whole image, it will leave the outter most pixels
unaffected by the filter.

The supported filters are:

- EDGE
- SHARPEN
- BLUR
- GAUSSIAN_BLUR

**Calling**
```sh
APPLY <filter>
```

**Example**

*Input*
```sh
APPLY GAUSSIAN_BLUR
```

BLUR filter reffers to a simple box blur.

<br><br>

### Saving

Save the current image with all the previous operations done.

The image can be saved in binary or ASCII form, depending on wether it is
specified so. By default, the image is saved in binary form.

**Calling**
```sh
SAVE <file_path> [ascii]
```

**Example**

*Input* - binary form
```sh
SAVE res/image.ppm
```

*Input* - ASCII form
```sh
SAVE res/image.ppm ascii
```

<br><br>

### Exiting

Exit the app and free all the memory.

This will not save the current progress!

**Calling**
```sh
EXIT
```

## Possible ouputs

- `Loaded <file_path>` : Loading was successful

- `Failed to load <file_path` : Loading failed (file not found?)

- `No image loaded` : No image was loaded for the operation to take place

- `Selected <x1 y1 x2 y2>` : Custom selection was successful

- `Invalid set of coordinates` : You have entered wrong coordinates

- `Selected ALL` : Selecting all was successful

- `Rotated <angle>` : Rotating was successful

- `The selection must be sqaure` : Custom selection of the image must be square
for rotating

- `Unsupported roatation angle` : Rotation angle must be divisible by 90

- `Equalize done` : Equalization was successful

- `Black and white image needed` : The operation needs a black and white image
(P2 or P5)

- `Image cropped` : Crop was successful

- `Apply <filter> done` : Filter was applied

- `Easy, Chrlie Chaplin` : Image is black and white (no filter was applied)

- `APPLY parameter invalid` : That filter does not exist

- `Saved <file_path>` : Saving was successful

- `Invalid set of parameters` : The operation parameters were invalid

- `Invalid command` : The operation/command does not exist

## What I have learnt
For developing this project I wanted to make it as scalable and modularised as
I could. There are a lot of improvements that could be done, some of which I
marked down in TO DO's throughout the project.

Developing this project, I came to realise more about how I should write a cli
interpretor, about structuring my sources and headers and about how I should use
returning values, as error codes or as actual values i.e. getters. I am still
not happy that they are a bit mixed up, but this project has had enough
attention given to.

I also felt that making this project in C required a lot more naming conventions
than making it in C++, because things can get convoluted, but I think that I
found the ones that suit me best.

To sum up, I think that this project combined everything that I have learnt this
semester pretty nicely and it is great because it has visual feedback.
