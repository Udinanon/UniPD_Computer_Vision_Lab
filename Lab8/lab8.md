---
title: "Lab 7"
author: Martino Trapanotto
date: May 3, 2022
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
# Lab 8
## Task 1

Due to having a mediocre camera, I preferred using the available imageset.

## Task 2

Mean Reprojection error is obtained by computing the reprojection error for all images, squaring it, summing them and then computing the square root of the total average.

The reprojection error of each image, obtained by `projectPoints(objpoints[i], rvecs[i], tvecs[i], cameraMatrix, distCoeffs, imagePoints2); err = norm(imgpoints[i], imagePoints2, NORM_L2);` is the difference between the computed position of the object points (in our case the corner of the checkerboard) in the image space and the results from the corner finding algorithm `findChessboardCorners()`. 

This value allows us to judge the quality of our estimation for the distortion parameters, as the closer it is to zero, the closer our reprojection is to reality.
