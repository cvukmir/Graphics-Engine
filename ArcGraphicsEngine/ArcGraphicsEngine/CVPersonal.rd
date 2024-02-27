# This is a test/example rd file

Display "The Wheel" "PNM" "rgb"
Format 500 500

# Testing filling and double buffering

Background 1.0 1.0 1.0

# The next three lines will be ignored by your renderer
CameraEye 250 250 -250
CameraAt  250 250 0
CameraUp  0.0 -1.0 0.0

FrameBegin 1

WorldBegin


# Right Circle
Color 0.67 0.62 0.39

Circle 340 210 0 100
Circle 340 210 0 80

Fill 430 210 0


# Bottom Circle

Color 0.3 0.3 0.3
Circle 250 340 0 100
Circle 250 340 0 80
Circle 250 340 0 96
Circle 250 340 0 84

# Fill Bottom Circles
Color 0.47 0.48 0.44
Fill 250 430 0
Fill 250 250 0
Fill 290 260 0
Fill 325 290 0

Color 0.3 0.3 0.3
Fill 250 258 0
Fill 258 258 0
Fill 295 270 0
Fill 315 290 0
Fill 250 242 0
Fill 285 248 0
Fill 340 300 0
Fill 348 340 0


# Middle Bottom Circle

Color 0.2 0.2 0.2
Circle 250 340 0 30
Circle 250 340 0 27
Circle 250 340 0 10
Circle 250 340 0 13

Color 0.5 0.5 0.5
Fill 250 340 0
Color 0.47 0.48 0.44
Fill 261 340 0
Fill 265 340 0
Color 0.3 0.3 0.3
Fill 279 340 0


#Spokes
Color 0.47 0.48 0.44

Line 250 340 0 250 260 0
Line 250 340 0 291 408 0
Line 250 340 0 209 408 0
Line 250 340 0 172 352 0
Line 250 340 0 328 352 0
Line 250 340 0 202 302 0
Line 250 340 0 316 294 0


# Left Circle
Color 0.67 0.62 0.39

Circle 160 210 0 100
Circle 160 210 0 80

Fill 70 210 0
Fill 160 300 0
Fill 165 300 0
Fill 180 300 0
Fill 185 300 0
Fill 245 250 0
Fill 245 258 0
Fill 245 242 0
Fill 240 235 0
#Fill 230 270 0

WorldEnd
FrameEnd
