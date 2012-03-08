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

from STG.Regulation.Hidamari.Regular.Stage1.Yuno import Phase1_3 as Regulation

class ChainGun:
	def __init__(self, core, rank = 1):
		self.core = core
		self.main = Coroutine(self._main)
		self.shooting = False
		
		self.regulation = Regulation.ChainGun(rank)
	
	def update(self):
		if not self.main.alive:
			self.main = Coroutine(self._main)
		self.main.resume()
	def _main(self):
		self.shooting = True
		
		targetAngle = self._getPos().getAngle(
				Ctrl.Actor.myShip.position)
		for _ in range(int(self.regulation.launchRepeat)):
			pos = self._getPos()
			drawParam = Auxs.createBulletRedDrawParam(
				pos, Std.Vector2DF(24, 24))
			NWay.launchLinear(
				pos, 
				targetAngle, 
				self.regulation.angleInterval, 
				self.regulation.wayNum, 
				int(drawParam.dst.w/4), 
				drawParam, 
				self.regulation.speed)
			
			wait = createWait(self.regulation.launchInterval)
			while wait(): yield
		
		self.shooting = False
		
		wait = createWait(self.regulation.launchWait)
		while wait(): yield
	
	def _getPos(self):
		return self.core.locator.position + Std.Vector2DF(0, 110)