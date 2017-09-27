#!/usr/bin/env python

import json, Image, ImageDraw

f = file("persmats_CarAS22_FieldLingGang.cfg");
s = json.load(f)
corner = s["CornerPoints_auto"]
print corner

index = -1
w = 2
# front
index = index + 1
im = Image.open('calibFront.jpg')
drawSurface = ImageDraw.Draw(im)
index2 = 0
for i in range(0,8):
    x = corner[index*16 + index2]
    y = corner[index*16 + 8 + index2]
    point = (x, y)
    point1 = (x-w, y-w)
    point2 = (x+w, y+w)
    drawSurface.ellipse((point1, point2))
    im.putpixel(point, (255,0,255))
    index2 = index2 + 1
im.show()
im.save('calibFront_Corner.jpg')

# right
index = index + 1
im = Image.open('calibRight.jpg')
drawSurface = ImageDraw.Draw(im)
index2 = 0
for i in range(0,8):
    x = corner[index*16 + index2]
    y = corner[index*16 + 8 + index2]
    point = (x, y)
    point1 = (x-w, y-w)
    point2 = (x+w, y+w)
    drawSurface.ellipse((point1, point2))
    im.putpixel(point, (255,0,255))
    index2 = index2 + 1
im.show()
im.save('calibRight_Corner.jpg')
# rear
index = index + 1
im = Image.open('calibRear.jpg')
drawSurface = ImageDraw.Draw(im)
index2 = 0
for i in range(0,8):
    x = corner[index*16 + index2]
    y = corner[index*16 + 8 + index2]
    point = (x, y)
    point1 = (x-w, y-w)
    point2 = (x+w, y+w)
    drawSurface.ellipse((point1, point2))
    im.putpixel(point, (255,0,255))
    index2 = index2 + 1
im.show()
im.save('calibRear_Corner.jpg')
# left
index = index + 1
im = Image.open('calibLeft.jpg')
drawSurface = ImageDraw.Draw(im)
index2 = 0
for i in range(0,8):
    x = corner[index*16 + index2]
    y = corner[index*16 + 8 + index2]
    point = (x, y)
    point1 = (x-w, y-w)
    point2 = (x+w, y+w)
    drawSurface.ellipse((point1, point2))
    im.putpixel(point, (255,0,255))
    index2 = index2 + 1
im.show()
im.save('calibLeft_Corner.jpg')
