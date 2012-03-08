'''
Created on 2011/04/16

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Auxs as Auxs
import Util.NWay as NWay
from Util.Coroutine import Coroutine
from Util.Coroutine import createWait

from STG.Regulation.Hidamari.Regular.Stage1.Yuno import Phase1_1 as Regulation

class ChainGun:
	def __init__(self, core, rank = 1):
		self.core = core
		self.main = Coroutine(self._main)
		self.shooting = False
		
		self.regulation = Regulation.ChainGun(rank)
	
	@property
	def rank(self):
		return self._rank
	@rank.setter
	def rank(self, rank):
		self._rank = rank
	
	def update(self):
		if not self.main.alive:
			self.main = Coroutine(self._main)
		self.main.resume()
	
	def _getPos(self):
		return self.core.locator.position + Std.Vector2DF(0, 110)
	
	def _main(self):
		wait = createWait(self.regulation.firstWait)
		while wait():yield
		
		self.shooting = True
		
		for _ in range(int(self.regulation.launchRepeat)):
			pos = self._getPos()
			targetAngle = pos.getAngle(
				Ctrl.Actor.myShip.position)
			drawParam = Auxs.createBulletRedDrawParam(
				pos, Std.Vector2DF(24, 24*0.3))
			
			NWay.launchLinear(
				pos, 
				targetAngle, 
				self.regulation.angleInterval, 
				self.regulation.wayNum, 
				int(drawParam.dst.h), 
				drawParam, 
				self.regulation.speed)
			
			launchInterval = createWait(self.regulation.launchInterval)
			while launchInterval(): yield
		
		self.shooting = False