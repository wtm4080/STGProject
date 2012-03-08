'''
Created on 2011/04/16

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Auxs as Auxs
import Util.NWay as NWay

from STG.Regulation.Hidamari.Regular.Stage1.Yuno import Phase1_1 as Regulation

class SideRandom:
	def __init__(self, left, core, rank = 1):
		self.left = left
		self.core = core
		
		self.regulation = Regulation.Side(rank)
		
		self.repCounter = Std.RepeatCounter()
		self.repCounter.interval = self.regulation.launchInterval
	
	def update(self):
		self.repCounter.update()
		
		rand = Ctrl.getRandom()
		for _ in range(self.repCounter.repeatCount):
			pos = self._getPos()
			baseAngle = 90 + rand.getFloat(-45, 45)
			
			drawParam = Auxs.createBulletBlueDrawParam(
				pos, Std.Vector2DF(16, 16))
			drawParam.dst = pos.makeRect(
				drawParam.dst.w, drawParam.dst.h, True)
			
			NWay.launchLinear(
				pos, 
				baseAngle, 
				self.regulation.angleInterval, 
				self.regulation.wayNum, 
				int(drawParam.dst.w/4), 
				drawParam, 
				self.regulation.speed)
	
	def _getPos(self):
		basePos = self.core.locator.position
		offsetX = 135
		offsetY = 70
		if self.left:
			return basePos + Std.Vector2DF(offsetX, offsetY)
		else:
			return basePos + Std.Vector2DF(-offsetX, offsetY)