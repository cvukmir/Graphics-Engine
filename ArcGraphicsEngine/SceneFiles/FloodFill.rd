# This is a test/example rd file

Display "Flood Fill" "Screen" "rgbsingle"
Format 500 500

# Testing filling and double buffering

Background 1.0 1.0 1.0

# The next three lines will be ignored by your renderer
CameraEye 250 250 -250
CameraAt  250 250 0
CameraUp  0.0 -1.0 0.0

FrameBegin 1

WorldBegin

# Square

Color 1.0 0.0 0.0

Line 20 20 0 20 80 0
Line 20 80 0 80 80 0
Line 80 80 0 80 20 0
Line 80 20 0 20 20 0

Line 50 20 0 50 80 0
Line 20 50 0 80 50 0

Color 1.0 1.0 1.0

Point 50 50 0

Color 0.0 1.0 1.0
Fill 30 30 0

Color 1.0 1.0 0.0
Fill 30 60 0

Color 0.0 0.0 1.0
Fill 60 30 0

Color 1.0 0.0 1.0
Fill 60 60 0

Color 0.0 0.0 0.0
Circle 300 300 0 15
Circle 300 300 0 30
Circle 300 300 0 45
Circle 300 300 0 60
Circle 300 300 0 75
Circle 300 300 0 90
Circle 300 300 0 105
Circle 300 300 0 120
Circle 300 300 0 135
Circle 300 300 0 150

Color 0.45 0.22 0.05
Fill 300 300 0
Color 0.23 0.23 0.23
Fill 300 320 0
Color 0.83 0.83 0.83
Fill 300 335 0
Color 1.0 0.3 1.0
Fill 300 350 0
Color 1.0 0.0 0.22
Fill 300 365 0
Color 1.0 0.5 0.22
Fill 300 380 0
Color 0.95 0.95 0.1
Fill 300 395 0
Color 0.1 0.95 0.0
Fill 300 410 0
Color 0.07 0.0 0.8
Fill 300 425 0
Color 0.58 0.11 0.81
Fill 300 440 0


WorldEnd
FrameEnd