'''
Created on 2011/12/12

@author: t
'''

import Std
import STG.Ctrl as Ctrl
from Util.Sprite.Animation import createSequenceAnimation, updateDst

class SpAttack:
	SPBEGIN_SIZE = Std.Vector2DF(400, 400)
	SPFINISH_SIZE = Std.Vector2DF(500, 500)
	SPFINISHING_SIZE = Std.Vector2DF(800, 800)
	SPGAUGE_SIZE = Std.Vector2DF(96, 96)
	
	def __init__(self, core):
		self.core = core
		
		spBeginDrawParam = Std.Sprite.DrawParam()
		spBeginDrawParam.src = Std.RectF(0, 0, 200, 200)
		spBeginDrawParam.dst = core.position.makeRect(self.SPBEGIN_SIZE, True)
		spBeginDrawParam.priority = Ctrl.DrawPriority.myShipB1
		self.spBeginAnimation = createSequenceAnimation(
			core.resource.spBeginTexList, spBeginDrawParam)
		
		spFinishDrawParam = Std.Sprite.DrawParam()
		spFinishDrawParam.src = Std.RectF(0, 0, 200, 200)
		spFinishDrawParam.dst = core.position.makeRect(self.SPFINISH_SIZE, True)
		spFinishDrawParam.priority = Ctrl.DrawPriority.myShipB1
		self.spFinishAnimation = createSequenceAnimation(
			core.resource.spFinishTexList, spFinishDrawParam)
		
		spFinishingDrawParam = Std.Sprite.DrawParam()
		spFinishingDrawParam.src = Std.RectF(0, 0, 200, 200)
		spFinishingDrawParam.dst = core.position.makeRect(self.SPFINISHING_SIZE, True)
		spFinishingDrawParam.priority = Ctrl.DrawPriority.myShipB1
		self.spFinishingAnimation = createSequenceAnimation(
			core.resource.spFinishingTexList, spFinishingDrawParam)
		
		spGaugeDrawParam = Std.Sprite.DrawParam()
		spGaugeDrawParam.src = Std.RectF(0, 0, 64, 64)
		spGaugeDrawParam.dst = core.position.makeRect(self.SPGAUGE_SIZE, True)
		spGaugeDrawParam.priority = Ctrl.DrawPriority.myShipB1
		self.spGaugeAnimation = createSequenceAnimation(
			core.resource.spGaugeTexList, spGaugeDrawParam)
	
	def update(self):
		if self.spBeginAnimation.playing:
			self.spBeginAnimation.update()
			updateDst(self.spBeginAnimation, self.core.position, self.SPBEGIN_SIZE)
		if self.spFinishAnimation.playing:
			self.spFinishAnimation.update()
			updateDst(self.spFinishAnimation, self.core.position, self.SPFINISH_SIZE)
		if self.spFinishingAnimation.playing:
			self.spFinishingAnimation.update()
			updateDst(self.spFinishingAnimation, self.core.position, self.SPFINISHING_SIZE)
		if self.spGaugeAnimation.playing:
			self.spGaugeAnimation.update()
			updateDst(self.spGaugeAnimation, self.core.position, self.SPGAUGE_SIZE)
	def draw(self):
		if self.spBeginAnimation.playing:
			self.spBeginAnimation.draw()
		if self.spFinishAnimation.playing:
			self.spFinishAnimation.draw()
		if self.spFinishingAnimation.playing:
			self.spFinishingAnimation.draw()
		if self.spGaugeAnimation.playing:
			self.spGaugeAnimation.draw()
	
	def begin(self, frameNum):
		self.spBeginAnimation.play()
		
		interval = frameNum / self.spGaugeAnimation.frameHolder.frameNum
		self.spGaugeAnimation.frameInterval = interval
		self.spGaugeAnimation.play()
	def finishing(self):
		self.spFinishingAnimation.play()
	def finish(self):
		self.spFinishAnimation.play()
		self.spGaugeAnimation.stop()
	def stop(self):
		self.spGaugeAnimation.stop()