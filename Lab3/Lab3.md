---
title: "Lab3"
author: Martino Trapanotto
date: March 22, 2022
output: pdf_document
document:
export_on_save:
  html: true
  pandoc: true
html:
  embed_local_images: true
  embed_svg: true
  offline: true
  toc: undefined

print_background: false
---
# Lab 3 - Mouse callback and color segmentation

## Task 1
**Write a program that loads the image provided (robocup.jpg) and shows it.**

Trivial

![Robocup](/assets/robocup.jpg)

## Task 2
**Expand Task 1 adding a callback function reacting to the mouse click. The callback prints the
BGR color triplet of the pixel where the click occurred.**

Relatively easy to achieve using setMouseCallback(), and then implemented using pointers to avoid global variables

## Task 3
**Modify the callback in Task 2: the new version calculates the mean of the B, G and R values
(separately) in a 9x9 neighborhood around the clicked pixel and prints such values.**

Conceptually easy, trickery was mostly in reusing code from the last lab to loop in the neighborhood and fighting aganist types and other implementational details

## Task 4
**Expand Task 3 in order to segment (i.e., “select”) the T-shirts of the robot soccer players.
Such selection operates by reading the average calculated in Task 3, taken as a reference
color, setting a threshold T, and creating a new image, called mask, having:
a white pixel if the corresponding pixel in the input image has all the three B, G and R
values having a distance from the reference color not greater than T;
a black pixel otherwise.
Visualize the mask on the screen. The mask is generated from scratch at every new click on
the original image.**

The main issue here was working with Vecs and understanding that the usual Vec3b does not allow for negative numbers, so taking the difference from the refence value does not work as expected. After that, it's relatively simple.

![Clicked on the ball](../assets/robocup_mask.jpg)

## Task 5
**Expand Task 4 by creating a new image whose pixels are:
equal to the input image if the corresponding pixel in the mask is black;
equal to a given color otherwise.
Choose the triplet (92, 37, 201) as the new color. This image is generated from scratch at
every new click on the original image.
Are you able to change the color of the T-shirts?
Are you able to change the color of the ball?**

Easy to achieve using the previous code, It's hard to get a perfect selection of the objects, as it's either too sensitive or not enough. It also required to raise the threshold well beyond my expectations, from 15 in Task 4 to 50 here

Perhaps using not a BGR color represenrarion but a HSV, as it better represents colors in different light conditions

I was able to change the color of the shirts and the ball, but only partially. The difference between the light and dark areas is too strong compared to the difference between different colors to achieve better results 

![Edited shirts](../assets/robocup_edited_shirt.jpg)

![Edited ball](../assets/robocup_edited_ball.jpg)
