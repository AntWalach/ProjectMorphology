# ProjectMorphology
The project is intended to illustrate the operation of basic morphological filters.

  A binary image (or bitmap for short) is an image in which each pixel is either black or white. In the
recognition and analysis of binary images, so-called morphological operations (filters) are often used. By
default, these filters are defined very generally.


  For example, consider a 7 by 7 pixel bitmap. Each pixel of the bitmap can be represented in the computer's
memory as a logical variable. For the purposes of this task, we assume that the value of black pixels in
the bitmap is true and the value of white pixels is false. The figure below is used to illustrate the operation
of basic morphological filters.


![image](https://user-images.githubusercontent.com/64771436/177344588-b490f9f1-08dd-4e74-8ccb-cbd3e6b0623c.png)



For a fixed pixel by its neighbors we understand:
1.Pixel directly above it.
2.The pixel directly below it.
3.Pixel directly to the left of it.
4.Pixel directly to the right of it.

Below, we will discuss in turn the morphological filters that should be implemented:


1. Inversion - or simply negation - converts black pixels to white pixels and white pixels to black

![image](https://user-images.githubusercontent.com/64771436/177344644-02c601de-eb2b-4085-a0ec-29863031b5fc.png)






2.Erosion. By an edge pixel of an image we mean a black pixel, one of its neighbors is a white
pixel. The erosion operation first locates all edge pixels in an image and then sets them to
white. The erosion effect can be seen below:

![image](https://user-images.githubusercontent.com/64771436/177344684-57209f92-c977-48b6-ab8a-2a04a9fb331d.png)

3.Dilation - is in a sense an operation the opposite of erosion. As a result of dilatation, all white
pixels that are adjacent to the black pixel are changed to black.

![image](https://user-images.githubusercontent.com/64771436/177344835-c4293154-a5fc-4e34-ae5f-5a2fb189740e.png)



4.Reset - total reset, tabula rasa - set all pixels to white:

![image](https://user-images.githubusercontent.com/64771436/177344894-dbb881af-14d6-44fb-acf8-2be47a0b9564.png)


5. Averaging - for each pixel p of the image we check the number of neighboring white and black
pixels. If it has more than 2 neighbors in the color k, then the new color of the pixel p is the color
k. Please note that we consider the neighbors in the original image, not in the partially averaged
image.

![image](https://user-images.githubusercontent.com/64771436/177345036-6505564a-027b-4ce8-beca-afd8bedfd780.png)






