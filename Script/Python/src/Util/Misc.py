'''
Created on 2011/06/16

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Auxs as Auxs

def getVariantVector(baseVector, variantVector):
	rand = Ctrl.getRandom()
	vx = rand.getFloat(
		baseVector.x - variantVector.x, 
		baseVector.x + variantVector.x)
	vy = rand.getFloat(
		baseVector.y - variantVector.y, 
		baseVector.y + variantVector.y)
	return Std.Vector2DF(vx, vy)

def createExplosion(drawPri, num, pos, size, 
				frameItv = 1, 
				posVariance = Std.Vector2DF(), 
				sizeVarianceRate = 0, 
				frameItvVarianceRate = 0):
	rand = Ctrl.getRandom()
	expObjList = []
	for _ in range(num):
		sizeRate = rand.getFloat(
			-sizeVarianceRate, 
			sizeVarianceRate)
		correctedSize = size + size*sizeRate
		itv = rand.getFloat(
			frameItv - frameItv*frameItvVarianceRate, 
			frameItv + frameItv*frameItvVarianceRate)
		
		expObjList.append(Auxs.createExplosion2(
			getVariantVector(pos, posVariance), 
			Std.Vector2DF(correctedSize, correctedSize), 
			itv, 
			drawPri))
	return expObjList

class Enum:
	def __init__(self, *labels):
		for value, label in enumerate(labels):
			self.__dict__[label] = value

def loadBGM(path):
	file = Std.File.openSync("BGM/" + path, throwException = False)
	if not file:
		return Std.Sound.loadStream("DummyBGM.ogg")
	else:
		return Std.Sound.loadStream(file)

def loadSE(path, layerCount = 1):
	file = Std.File.openSync("SE/" + path, throwException = False)
	if not file:
		return Std.Sound.loadStatic("DummySE.wav", layerCount)
	else:
		return Std.Sound.loadStatic(file, layerCount)