Display "Axis System" "Screen" "rgbsingle"
Format 500 500

# Testing filling and double buffering

Background 1.0 1.0 1.0

ObjectBegin "Axis"

Color 0.5 0.5 0.5

Cube

# Z-Axis
Color 0.0 0.0 1.0
Cylinder 0.1 0.0 5.0 360

# X-Axis
Rotate "X" 90
Color 1.0 0.0 0.0
Cylinder 0.1 0.0 5.0 360

# Y-Axis
Rotate "Y" 90
Color 0.0 1.0 0.0
Cylinder 0.1 0.0 5.0 360

ObjectEnd

# The next three lines will be ignored by your renderer
CameraEye 5.0 5.0 10.0
CameraAt  0.0 0.0 -1.0
CameraUp  0.0 1.0 0.0

FrameBegin 1
WorldBegin

ObjectInstance "Axis"

WorldEnd
FrameEnd