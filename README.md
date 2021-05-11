# ddelements
Detecting and isolating disturbing element from a clean surface.

Test image: water with a leaf.
Implementation detail: the detection of the leaf is made basing on k-means clustering. This means that every element different from the water can be detected, unless they are blue.
Look at the other repository (ddelements_shape) to check the version of the code where disturbing elements are detected basing pn their shape.

Results:
Original image
![image](https://user-images.githubusercontent.com/73488839/117808400-1e995500-b25d-11eb-833e-89a7bfe96860.png)

Final detection: 
![image](https://user-images.githubusercontent.com/73488839/117808446-2ce77100-b25d-11eb-9d0e-1769017c6d11.png)
