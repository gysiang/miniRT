# miniRT
A humble ray tracer engine in C

Objective: To generate images with Raytracing protocol. Each image will represent a scene, seen from a given angle and position, defined by simple geometric objects with its own lighting system.

Features:
### Ray Tracing
-[] Handle at least 3 geometric objects: plane, sphere, cylinder.
-[] Able to resize the object properties: diameter for a sphere and width and height for a cylinder.
-[] Able to apply translation and rotation transformation to objects, lights and cameras.
-[] Light management. Spot brightness, hard shadows, ambiance lighting. Ambient and diffuse lighting.

### Program user features
-[] Program displays the image in a window.
-[] Pressing ESC must close the window and quit the program cleanly.
-[] Clicking on the cross must close the window and quit the program cleanly.
-[] The use of images of minilibX is strongly recommended.
-[] The first argument the program must take is a scene description file with .rt description.

### Settings required in the .rt file
-[] Each type of element can be sepearated by one or more line breaks(s).
-[] Each type of information can be seperated by one or more space(s).
-[] Each type of element can be set in any order in the file.
-[] Elements defined by a cpaital can be declared only once in a scene.
-[] If there is any misconfiguration in the file, the program must exit cleanly and return 'Error\n' followed by an error message.
