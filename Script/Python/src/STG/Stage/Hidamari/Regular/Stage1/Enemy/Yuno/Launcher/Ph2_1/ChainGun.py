'''
Created on 2011/04/16

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Auxs as Auxs
from Util.Coroutine import Coroutine
from Util.Coroutine import createWait
import Util.NWay as NWay

from STG.Regulation.Hidamari.Regular.Stage1.Yuno import Phase2_1 as Regulation

class ChainGun:
	def __init__(self, core, rank = 1):
		self.core = core
		self.main = Coroutine(self._main)
		self.shooting = False
		
		self.regulation = Regulation.BitTask0_Aiming.ChainGun(rank)
	
	@property
	def alive(self):
		return self.main.alive
	
	def update(self):
		if self.main.alive:
			self.main.resume()
	def _main(self):
		self.shooting = True
		
		speed = self.regulation.speed
		for i in range(int(self.regulation.launchSetNum)):
			targetAngle = self._getPos().getAngle(
				Ctrl.Actor.myShip.position)
			
			for _ in range(i + 1):
				drawParam = Auxs.createBulletBlueDrawParam(
					self._getPos(), Std.Vector2DF(16, 16))
				NWay.launchLinear(
					self._getPos(), 
					targetAngle, 
					self.regulation.firstAngleInterval, 
					self.regulation.firstWayNum, 
					int(drawParam.dst.w/2), 
					drawParam, 
					speed)
					
				wait = createWait(self.regulation.launchInterval)
				while wait(): yield
				
				angleList = NWay.getAngleList(
					targetAngle, 
					self.regulation.secondAngleInterval, 
					self.regulation.secondWayNum)
				drawParam = Auxs.createBulletBlueDrawParam(
					self._getPos(), Std.Vector2DF(14, 14))
				for angle in angleList:
					NWay.launchLinear(
						self._getPos(), 
						angle, 
						self.regulation.secondAngleIntervalPerWay, 
						self.regulation.secondWayNumPerWay, 
						int(drawParam.dst.w/2), 
						drawParam, 
						speed)
				
				wait = createWait(self.regulation.launchInterval)
				while wait(): yield
			
			wait = createWait(self.regulation.setInterval)
			while wait(): yield
		
		self.shooting = False
	
	def _getPos(self):
		return self.core.locator.position + Std.Vector2DF(0, 110)