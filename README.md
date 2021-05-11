# ddelements
Detecting and isolating disturbing element from a clean surface.

Test image: water with a leaf.
Implementation detail: the detection of the leaf is made basing on k-means clustering. This means that every element different from the water can be detected, unless they are blue.
Look at the other repository (ddelements_shape) to check the version of the code where disturbing elements are detected basing pn their shape.
