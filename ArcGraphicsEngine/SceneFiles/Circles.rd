# This is a test/example rd file

Display "Circles" "PNM" "rgb"
Format 500 500

# Testing filling and double buffering

Background 1.0 1.0 1.0

# The next three lines will be ignored by your renderer
CameraEye 250 250 -250
CameraAt  250 250 0
CameraUp  0.0 -1.0 0.0

FrameBegin 1

WorldBegin

Color 0.0 0.0 0.0

Circle 20 10 0 1
Color 1.0 0.0 0.0
Circle 20 20 0 3
Color 1.0 1.0 0.0
Circle 20 30 0 5
Color 1.0 0.0 1.0
Circle 20 40 0 7
Color 0.0 1.0 1.0
Circle 20 50 0 9
Color 0.0 0.0 0.5
Circle 20 60 0 11

Color 0.5 0.0 0.5
Circle 480 10 0 2
Color 0.5 0.5 0.0
Circle 480 20 0 4
Color 0.5 0.5 0.5
Circle 480 30 0 6
Color 0.1 0.6 0.9
Circle 480 40 0 8
Color 0.4 0.7 0.5
Circle 480 50 0 10
Color 0.1 0.1 0.8
Circle 480 60 0 12
Color 0.0 0.5 0.9


WorldEnd
FrameEnd