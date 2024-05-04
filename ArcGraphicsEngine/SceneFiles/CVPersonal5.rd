Display "One Ring to Rule Them All" "Screen" "rgbsingle"


# The next three lines will be ignored by your renderer
CameraEye 8.0 -5.0 16.0
CameraAt  0.0 0.0 0.0
CameraUp  0.0 1.0 0.0
CameraFOV 45

FrameBegin 1
WorldBegin

PointLight 0 0 0 1.0 0.0 0.0 100
PointLight 0 0 5 1.0 0.0 0.0 100
PointLight 0 0 -5 1.0 0.0 0.0 100
FarLight 0 0 -1  1.0  1.0  1.0  1.0


Ka 0.5
Kd 1.0
Ks 0.5

Color 0.9 0.8 0.2

Specular 1.0 1.0 1.0 10

Surface "metal"

Halo 5.0 360.0 2.0 0.4

#Translate -5.0 0.0 -20.0
#
#Rotate "Z" 20
#Rotate "X" 40
#
#Halo 5.0 360.0 2.0 0.4

WorldEnd
FrameEnd