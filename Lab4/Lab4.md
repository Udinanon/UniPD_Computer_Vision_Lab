---
title: "Lab4"
author: Martino Trapanotto
date: March 29, 2022
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
# Lab 4 - Edge and line detection

## Task 1
**Write a program that loads the image provided (street_scene.png), shows it and evaluates the Canny image. Employ one or more trackbar(s) to control the parameters of the Canny edge detector and check their influence on the resulting image. The Canny image shall be refreshed every time a trackbar is modified.**

This was relatively easy to implement thanks to the OpenCV examples. My biggest issue is an uncertainty about types, as the function requires double types but the trackbar only handles Ints, and this leads to some doubts about precision and value ranges

In the end, a range of 0 to 10 000 and a precision of 0.01 seemed reasonable, comparing the various results we got

## Task 2
**You now need to detect the white markings on the road. How could you tackle this problem?
Some suggestions:
 consider edge orientation;
 consider colors close to edge points.**

I deicided to start from the resukts of Canny and filter only the results that are very string, that the angles are -45 to 45 degreees from the vertical and that the underlying color is white.

So, the first step is to first remove all pixels that are not white, with some threshold, then apply Canny to it and keep only the lines at some orientation

This was pretty easy, but the next part became very hard, I could not implement it in time. I could not figure out how to filter edges by their orientation using only Canny.


## Task 3
**Detect white markings using the Hough transform. Check online sources and apply it using the cv::HoughLines() function. Suggestion: consider the two strongest lines detected, and select their orientation. Color in red the area between the lines - example below.**

To select the relevant lines, it was easiest to filter by angle as hypothesized in the previous task. From that, after constructing the necessary structures, it was a matter of finding the coorindates of the varuous points and filling in the polygon created using fillPoly(). 

## Task 4
**Detect the road sign using the Hough circular transform - function cv::HoughCircles().**

In conjunction with the HughCircles() function, the image ws also blurred with a gaussian filter.

Through careful adjustment of the parameters, the desired result was acheived