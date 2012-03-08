'''
Created on 2011/01/21

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Auxs as Auxs
from Util.Sprite.Animation import createSequenceAnimation
from Util.Sprite.Animation import updateDst

class Drawing:
	BASE_SIZE = Std.Vector2DF(380, 220)
	
	def __init__(self, core):
		self.core = core
		self.faceNumber = 0
		self.sideL_valid = True
		self.sideR_valid = True
		
		self.baseDrawParam = Std.Sprite.DrawParam()
		self.baseDrawParam.texture = core.resource.st1_YunoBase
		self.baseDrawParam.src = Std.RectF(0, 0, 
			self.BASE_SIZE.x, self.BASE_SIZE.y)
		self.baseDrawParam.dst = core.locator.position.makeRect(
			self.BASE_SIZE, True)
		self.baseDrawParam.priority = Ctrl.DrawPriority.enemy
		
		rotorDrawParam = Std.Sprite.DrawParam()
		rotorDrawParam.src = Std.RectF(0, 0, 
			self.BASE_SIZE.x, self.BASE_SIZE.y)
		rotorDrawParam.dst = core.locator.position.makeRect(
			self.BASE_SIZE, True)
		rotorDrawParam.priority = Ctrl.DrawPriority.enemy3
		self.rotorAnimation = createSequenceAnimation(
			self.core.resource.st1_YunoRotorTexList, rotorDrawParam)
		self.rotorAnimation.play()
		
		self.sideLDrawParam = Std.Sprite.DrawParam(self.baseDrawParam)
		self.sideLDrawParam.texture = core.resource.st1_YunoSide_L
		self.sideLDrawParam.priority = Ctrl.DrawPriority.enemy2
		
		self.sideRDrawParam = Std.Sprite.DrawParam(self.baseDrawParam)
		self.sideRDrawParam.texture = core.resource.st1_YunoSide_R
		self.sideRDrawParam.priority = Ctrl.DrawPriority.enemy2
		
		self.smokeRepCounter = Std.RepeatCounter(2)
	
	def getVariantVector(self, baseVector, variantVector):
		rand = Ctrl.getRandom()
		vx = rand.getFloat(
			baseVector.x - variantVector.x, 
			baseVector.x + variantVector.x)
		vy = rand.getFloat(
			baseVector.y - variantVector.y, 
			baseVector.y + variantVector.y)
		return Std.Vector2DF(vx, vy)
	
	def update(self):
		self.baseDrawParam.dst = self.core.locator.position.makeRect(
			self.BASE_SIZE, True)
		if self.faceNumber == 0:
			self.baseDrawParam.texture = self.core.resource.st1_YunoBase
		elif self.faceNumber == 1:
			self.baseDrawParam.texture = self.core.resource.st1_YunoBase_1
		elif self.faceNumber == 2:
			self.baseDrawParam.texture = self.core.resource.st1_YunoBase_2
		elif self.faceNumber == 3:
			self.baseDrawParam.texture = self.core.resource.st1_YunoBase_3
		elif self.faceNumber == 4:
			self.baseDrawParam.texture = self.core.resource.st1_YunoBase_4
		elif self.faceNumber == 5:
			self.baseDrawParam.texture = self.core.resource.st1_YunoBase_5
		else:
			self.baseDrawParam.texture = self.core.resource.st1_YunoBase
		
		updateDst(self.rotorAnimation, self.core.locator.position, self.BASE_SIZE)
		if not self.rotorAnimation.playing:
			self.rotorAnimation.play()
		self.rotorAnimation.update()
		
		self.smokeRepCounter.update()
		def createSmoke(left):
			rand = Ctrl.getRandom()
			for _ in range(self.smokeRepCounter.repeatCount):
				pos = self.getVariantVector(
					self.core.locator.position, 
					Std.Vector2DF(6, 24))
				if left:
					pos.x += 150 - 76/2
				else:
					pos.x -= 150 - 76/2
				pos.y += 40
				
				baseSize = Std.Vector2DF(48, 48)
				sizeRate = rand.getFloat(-0.5, 0.5)
				correctedSize = baseSize + baseSize*sizeRate
				
				smoke = Auxs.createSmoke(
					pos, 
					correctedSize, 
					1, 
					Ctrl.DrawPriority.enemy2, 
					0.2)
				smoke.locator.speed.y = 2
		if self.sideL_valid:
			self.sideLDrawParam.dst = self.core.locator.position.makeRect(
				self.BASE_SIZE, True)
		elif self.core.hp > 0:
			createSmoke(True)
		if self.sideR_valid:
			self.sideRDrawParam.dst = self.core.locator.position.makeRect(
				self.BASE_SIZE, True)
		elif self.core.hp > 0:
			createSmoke(False)
	
	def draw(self):
		Std.Sprite.draw(self.baseDrawParam)
		self.rotorAnimation.draw()
		if self.sideL_valid:
			Std.Sprite.draw(self.sideLDrawParam)
		if self.sideR_valid:
			Std.Sprite.draw(self.sideRDrawParam)
	
	def createExplosion(self, drawPri, num, pos, size, 
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
				self.getVariantVector(pos, posVariance), 
				Std.Vector2DF(correctedSize, correctedSize), 
				itv, 
				drawPri))
		return expObjList