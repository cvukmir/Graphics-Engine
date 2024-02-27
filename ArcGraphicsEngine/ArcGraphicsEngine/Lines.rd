# This is a test/example rd file

Display "Lines" "PNM" "rgb"
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

Line 250 250 0 250 200 0
Line 250 250 0 225 225 0
Line 250 250 0 275 225 0
Line 250 250 0 275 250 0
Line 250 250 0 225 250 0

Line 250 260 0 250 300 0
Line 250 260 0 275 285 0
Line 250 260 0 225 285 0
Line 250 260 0 250 285 0




WorldEnd
FrameEnd