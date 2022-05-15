---
title: "Lab 5"
author: Martino Trapanotto
date: April 12, 2022
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
# Lab 5

# TODO 

## Task 1
**Write a program that segments cracks in the asphalt. You can choose one of the segmentation techniques discussed in the course, or find a new one available in OpenCV. To assess the generality of your approach, test your algorithm on the three images provided - the two segments are: crack vs non-crack. Every pixel of the image shall belong to one of the two categories.**

to do this, i wanted to use Region Growing, first by filtering the image to recognize points that were likely to be parts of the cracks, quite simply though a threshold, them eroding and dilating these resukting seeds until we had a stable segmentation of the cracks

## Task 2
**Write a program that segments i) the asphalt and ii) the sky in the image provided for Lab 4 (street_scene.png). The three categories are: asphalt, sky, everything else.**

we can try a different segmentation method, perhaps watershed?



## Task 3
**Write a program that segments the T-shirt worn by the robots in the image provided for Lab 1. The categories are: T-shirt, everything else.**

This probably needs to be watershed or maybe MeanShift using onòy colors?

## Discussion
**While completing the tasks, discuss with your peers about:
 - the segmentation technique you have used, verifying if a single technique was effective in solving the three tasks or you needed to develop different approaches;
 - the image features you considered for segmenting the image (or the vector representation, if you used it).**

Unhappily i ddin0t so much during the Lab5 so I didn0t have much of a discussion wiht my peers about the techniquies

There seems to be a lack of preimplemented segmentation techniques in OpenCV
Are we supposed to rewrite them by ourselves?

Perhaps the best idea is to try and impement mulitple methods and test them with the various images and see which perform the best

so:
 - otsu 
    Nice only for 2 segments, then it becomes very complicated to implement
    not sure hot to use it for color images
    https://learnopencv.com/otsu-thresholding-with-opencv/#viewSource
 - region growing
    interesting and potentially effective for some, but can0t find decent c++ implementation of it
 - watershed
    can0t find decent c++ implementation of it
 - Mean Shift Clustering 
    can0t find decent c++ implementation of it
 - Markov Random Fields
    can0t find decent c++ implementation of it


    USE THE BOOK!
    it has a watershed example, some tutorils for otsu, meanshift and some more
    deosn0t have it all but still pretty good
    we might want to find another OPencv book to copy from