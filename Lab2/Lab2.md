---
title: "Lab2"
author: Martino Trapanotto
date: March 20, 2022
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

# Lab 2  - Filters and histogram equalization

## TODO
test if all work with basic compilation technique
add secion on compilation
ask prof if we get feedback on lab code 

## Task 1
**Write a program that loads the image provided (image.jpg) and shows it. It then converts the image to grayscale cv::cvtColor() function) and saves it with the image_grayscale.jpg name. Consider this last image for the next tasks**

This was relatively easy and posed no issues, especially in loight of the exoperiences in doing exactly this in the previous Lab

## Task 2
**Expand Task 1 implementing a max filter and a min filter in two dedicated functions
(implemented by you in a separate source file) that manipulate the pixels directly. Such
functions accept an integer representing the size of the kernel, and check that it is an odd
number. If it is even, the function does not process the image. Apply the filters using several
kernel sizes and find the best option that removes the electric cables in the background
without corrupting the image too much**

This proved much more troublesome.
Implementing the functions inside a different `.cpp` file was not easy but after understanding the basics of a header file and understanding how to send both `.cpp` files to the compiler, it was done

Then it was accounted for the missing pixels that would come from the filter reduginc the output matrix. So the output matrix was generated smaller, just enought for the image after the filtering. No rescaling

The real issue was in manipulating the image:
while reading the pixels, creating an empty image that had the correct size and moving along the input image to apply the filter was easy enough, an issue of only a third of the image shwoing in the results presented itself. The solution was found two days later to be linked to OpenCV automatically loading the input image as BGR instead of Grayscale. Editing the relevant flag in `imread()` fixed the problem. 

Using the `MaxFilter()` it was easy to filter the cables out using a kernel size of 5, as the lighter background easily covered the dark lines.

![kernel size 5](/assets/image_grayscale_max_5.jpg){width="300px" title="kernel size 5"}


Using `MinFilter()` instead we get different results. Even at a kernel of 15, where the iage becomes more and more blocky, the cables still linger as a darker line, although very hard to distinguish. 

![kernel size 15](/assets/image_grayscale_min_15.jpg){width="300px" title="kernel size 15"}

![kernel size 21](/assets/image_grayscale_min_21.jpg){width="300px" title="kernel size 21"}

![kernel size 37](/assets/image_grayscale_min_37.jpg){width="300px" title="kernel size 37"}

It's also notable how the code seems to be slower and slower as the filter grows, becoming noticeably slow at sizes over 20. This is not completely unecxpected as the work grows a lot with the filter size but its still relevant.

## Task 3
**Expand Task 2 using the median filter and the gaussian smoothing filter provided by
OpenCV. Show the results.**

Esaily implemented in the `main.cpp` file suing the `GaussianBlur()` and `medianBlur()` functions.

![gaussian kernel size 5](/assets/image_grayscale_gauss_5.jpg){width="300px" title="gaussian kernel size 5"}

![median kernel size 11](/assets/image_grayscale_med_11.jpg){width="300px" title="median kernel size 11"}

## Task 4
**Expand Task 1 plotting the histogram of the image using 256 bins and range [0, 255]. Try
also other values for the number of bins**

Easily achieved using the `calcHist()` function of OpenCV and some example code to understand how to use and visualize the results.

The images show how smaller numbers of bins give smoother results.

![hitstogram bins 256](/assets/image_grayscale_hist_256.jpg){width="300px" title="hitstogram bins 256"}

![hitstogram bins 32](/assets/image_grayscale_hist_32.jpg){width="300px" title="hitstogram bins 256"}


## Task 5
**Expand Task 4 including histogram equalization using the dedicated OpenCV function and
visualize the result.**

Easily acheived through `equalizeHist()`, with resukts that correct fr the darkness of the image. The histogram is visibly streched out.

![normalized image](/assets/image_grayscale_norm.jpg){width="300px" title="hitstogram bins 256"}

![normalized hitstogram bins 256](/assets/image_grayscale_norm_hist_256.jpg){width="300px" title="hitstogram bins 256"}

