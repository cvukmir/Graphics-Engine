Display "Axis System" "Screen" "rgbsingle"

# Testing filling and double buffering

Background 1.0 1.0 1.0

ObjectBegin "Axis"

Color 0.5 0.5 0.5

Cube

# Z-Axis
XformPush
Color 0.0 0.0 1.0
Cylinder 0.1 0.0 5.0 360
Translate 0.0 0.0 5.0
Cone 1 .3 360
XformPop

# X-Axis
XformPush
Rotate "Y" 90
Color 1.0 0.0 0.0
Cylinder 0.1 0.0 5.0 360
Translate 0.0 0.0 5.0
Cone 1 .3 360
XformPop

# Y-Axis
XformPush
Rotate "X" -90
Color 0.0 1.0 0.0
Cylinder 0.1 0.0 5.0 360
Translate 0.0 0.0 5.0
Cone 1 .3 360
XformPop

ObjectEnd

# The next three lines will be ignored by your renderer
CameraEye 2.0 2.0 5.0
CameraAt  0.0 0.0 0.0
CameraUp  0.0 0.0 1.0

FrameBegin 1
WorldBegin

ObjectInstance "Axis"

WorldEnd
FrameEnd