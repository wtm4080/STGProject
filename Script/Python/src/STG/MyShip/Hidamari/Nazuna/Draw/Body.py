'''
Created on 2011/06/14

@author: t
'''

import math
import Std
import STG.Ctrl as Ctrl
from Util.Sprite.Animation import createSequenceAnimation
from Util.Sprite.Animation import updateDst

class Body:
	SIZE = Std.Vector2DF(80, 64) * 1.5
	FRAME_NUM = 3
	ROLL_SPEED = 0.7
	HIT_MARKER_SIZE = Std.Vector2DF(24, 24)
	
	def __init__(self, core):
		self.core = core
		
		self.rollAmount = 0
		self.frameCount = 0
		self.drawParam = Std.Sprite.DrawParam()
		self.drawParam.src = Std.RectF(0, 0, 80, 64)
		self.drawParam.priority = Ctrl.DrawPriority.myShip
		self._setDrawParam()
		
		hitMarkerDrawParam = Std.Sprite.DrawParam()
		hitMarkerDrawParam.src = Std.RectF(0, 0, 32, 32)
		hitMarkerDrawParam.dst = core.position.makeRect(self.HIT_MARKER_SIZE, True)
		hitMarkerDrawParam.priority = Ctrl.DrawPriority.myShip4
		hitMarkerDrawParam.color.a = 0.8
		self.hitMarkerAnimation = createSequenceAnimation(
			core.resource.hitMarkerTexList, hitMarkerDrawParam)
		self.hitMarkerAnimation.play()
	
	def _setDrawParam(self):
		rollTexListIndex = math.floor(abs(self.rollAmount))
		self.drawParam.texture = (
			self.core.resource.bodyTexLists[rollTexListIndex]
			[self.frameCount])
		
		self.drawParam.dst = self.core.locator.position.makeRect(
			self.SIZE, True)
		if self.rollAmount < 0 and not self.drawParam.flipedX:
			self.drawParam.flipX()
		elif self.rollAmount >= 0 and self.drawParam.flipedX:
			self.drawParam.flipX()
	
	@property
	def rollAmount(self):
		return self._rollAmount
	@rollAmount.setter
	def rollAmount(self, value):
		self._rollAmount = value
		amountMax = len(self.core.resource.bodyTexLists) - 1
		if self._rollAmount > amountMax:
			self._rollAmount = amountMax
		elif self._rollAmount < -amountMax:
			self._rollAmount = -amountMax
	
	@property
	def frameCount(self):
		return self._frameCount
	@frameCount.setter
	def frameCount(self, value):
		self._frameCount = value
		if self._frameCount < 0:
			self._frameCount = self.FRAME_NUM - 1
		elif self._frameCount > self.FRAME_NUM - 1:
			self._frameCount = 0
	
	def update(self):
		dirX = Ctrl.getController().direction.x
		if dirX > 0 and not self.core.moveForbidFlag:
			self.rollAmount += self.ROLL_SPEED
		elif dirX < 0 and not self.core.moveForbidFlag:
			self.rollAmount -= self.ROLL_SPEED
		else:
			if self.rollAmount < 0:
				self.rollAmount += self.ROLL_SPEED
				if self.rollAmount > 0:
					self.rollAmount = 0
			elif self.rollAmount > 0:
				self.rollAmount -= self.ROLL_SPEED
				if self.rollAmount < 0:
					self.rollAmount = 0
		
		if self.rollAmount > 0:
			self.frameCount += 1
		else:
			self.frameCount -= 1
		
		self._setDrawParam()
		
		if not self.hitMarkerAnimation.playing:
			self.hitMarkerAnimation.play()
		self.hitMarkerAnimation.update()
		updateDst(self.hitMarkerAnimation, self.core.position, self.HIT_MARKER_SIZE)
	
	def draw(self):
		Std.Sprite.draw(self.drawParam)
		self.hitMarkerAnimation.draw()