'''
Created on 2011/04/16

@author: t
'''

import Std
import STG.Ctrl as Ctrl
from Util.Coroutine import Coroutine
from Util.Coroutine import createWait

from .Missile import Missile

from STG.Regulation.Hidamari.Regular.Stage1.Yuno import Phase1_2 as Regulation

class MissileHolder:
	def __init__(self, core, rank = 1):
		self.core = core
		self.rank = rank
		self.main = Coroutine(self._main)
		
		self.regulation = Regulation.Missile(rank)
	
	def update(self):
		if self.main.alive:
			self.main.resume()
	def _main(self):
		repeatNum = int(self.regulation.launchNum)
		for i in range(repeatNum):
			if((self.core.sideL.valid and i % 2 == 0) or 
			(self.core.sideR.valid and i % 2 == 1)):
				pos = self._getPos(i % 2 == 0)
				missile = Missile(
					pos, self.core.resource, self.rank)
				Ctrl.Actor.registerEnemy(missile)
				self.core.subEnemyObjList.append(missile)
				
				wait = createWait(self.regulation.launchInterval)
				while wait(): yield
	
	def _getPos(self, left):
		basePos = self.core.locator.position
		offsetX = 165
		offsetY = 70
		if left:
			return basePos + Std.Vector2DF(offsetX, offsetY)
		else:
			return basePos + Std.Vector2DF(-offsetX, offsetY)
	
	@property
	def end(self):
		return not self.main.alive