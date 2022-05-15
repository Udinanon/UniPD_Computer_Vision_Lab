---
title: "Lab 6"
author: Martino Trapanotto
date: April 26, 2022
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
# Lab 6

## Task 1
** Write a program that opens two images (filenames provided as command-line arguments) and checks the content by: i) evaluating features on the images; ii) matching features of the two images. The matching strategy is at your choice.
Based on the feature match the program shall state whether:
 - the two images have similar content;
 - the two images have similar content processed by some strong transformation (e.g., the content is strongly rotated, or framed under a very different perspective);
-  the two images have different content.
Test your approach considering different features available in OpenCV: check on the documentation, list all the available features, select 2-3 features you consider suitable for the task. Test on different image couples - start from the images provided, but optionally you can test on other images taken from the internet or shot by yourself.**


serch in OpenCV for various features algorithms
 - SIFT Descriptors Scale Invariant Feature Transform
 - ORB Descriptors (Oriented FAST and Rotated BRIEF) 
 - Harris corner detection
 - Shi-Tomasi corner detection
 - SURF (Speeded-Up Robust Features) 
   - gives issues linked to being nonfree, something strange i do0t wanna deal with
 - FAST Features from Accelerated Segment Test
   - ONLY an extractor, not a descriptor
 - BRIEF (Binary Robust Independent Elementary Features) 
   - we use it as a descriptor


search for features comparators
 - FLANN
 - BFMatcher

documentation on the various versions is fragmented and hard to use, mostly in python with no regard for c++
some have different requirements and different values in output with no clear indication
our implementation uses FAST for the detection and BRIEF for descriprion, tentatively using FLANN with Hamming DIstance for the comparison.
The code works, with the only remaining issue being how to filter good and bad matches.

The lack of clear information is staggering
