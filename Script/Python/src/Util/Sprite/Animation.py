'''
Created on 2010/10/26

@author: t
'''

import Std

def loadSequenceFrame(name, frameNum, mipmap = True, 
					precision = 5, ext = "dds"):
	textureList = []
	formatStr = "{0}%0{1}d.{2}".format(name, precision, ext)
	for i in range(frameNum):
		texture = Std.Sprite.loadTexture(formatStr % i, mipmap)
		textureList.append(texture)
	return textureList

def createSequenceAnimation(texList, drawParam, interval = 1.0):
	animeHolder = Std.Sprite.Animation.FrameHolder.Sequence(
		texList, drawParam)
	return Std.Sprite.Animation.Manager(animeHolder, interval)

def updateDst(animation, position, size, center = True):
	drawParam = animation.frameHolder.drawParameter
	drawParam.dst = position.makeRect(size, center)
	animation.frameHolder.drawParameter = drawParam