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
	SIZE = Std.Vector2DF(80, 64) * 1.2
	ROLL_SPEED = 0.7
	HIT_MARKER_SIZE = Std.Vector2DF(24, 24)
	BACK_FIRE_SIZE = Std.Vector2DF(64, 32)
	
	def __init__(self, core):
		self.core = core
		
		self.rollAmount = 0
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
		
		backFireDrawParam = Std.Sprite.DrawParam()
		backFireDrawParam.src = Std.RectF(0, 0, 128, 128)
		backFireDrawParam.dst = self.backFirePos.makeRect(self.BACK_FIRE_SIZE, True)
		backFireDrawParam.priority = Ctrl.DrawPriority.myShipB2
		backFireDrawParam.color.a = 0.8
		backFireDrawParam.rotDegree = 180
		self.backFireAnimation = createSequenceAnimation(
			core.resource.backFireTexList, backFireDrawParam)
		self.backFireAnimation.play()
	
	def _setDrawParam(self):
		rollTexListIndex = math.floor(abs(self.rollAmount))
		self.drawParam.texture = self.core.resource.bodyTexList[rollTexListIndex]
		self.drawParam.dst = self.core.locator.position.makeRect(self.SIZE, True)
		if self.rollAmount < 0 and not self.drawParam.flipedX:
			self.drawParam.flipX()
		elif self.rollAmount >= 0 and self.drawParam.flipedX:
			self.drawParam.flipX()
	
	@property
	def backFirePos(self):
		return self.core.position + Std.Vector2DF(0, 24)
	
	@property
	def rollAmount(self):
		return self._rollAmount
	@rollAmount.setter
	def rollAmount(self, value):
		self._rollAmount = value
		amountMax = len(self.core.resource.bodyTexList) - 1
		if self._rollAmount > amountMax:
			self._rollAmount = amountMax
		elif self._rollAmount < -amountMax:
			self._rollAmount = -amountMax
	
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
		
		self._setDrawParam()
		
		if not self.hitMarkerAnimation.playing:
			self.hitMarkerAnimation.play()
		else:
			self.hitMarkerAnimation.update()
		updateDst(self.hitMarkerAnimation, self.core.position, self.HIT_MARKER_SIZE)
		
		if not self.backFireAnimation.playing:
			self.backFireAnimation.play()
		else:
			self.backFireAnimation.update()
		updateDst(self.backFireAnimation, self.backFirePos, self.BACK_FIRE_SIZE)
	
	def draw(self):
		Std.Sprite.draw(self.drawParam)
		self.hitMarkerAnimation.draw()
		self.backFireAnimation.draw()