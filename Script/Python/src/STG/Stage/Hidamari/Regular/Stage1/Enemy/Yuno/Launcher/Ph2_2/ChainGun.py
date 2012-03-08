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

from STG.Regulation.Hidamari.Regular.Stage1.Yuno import Phase2_2 as Regulation

class ChainGun:
	def __init__(self, core, rank):
		self.core = core
		self.launch = Coroutine(self._launch)
		
		self.regulation = Regulation.ChainGun(rank)
	
	def update(self):
		if self.launch.alive:
			self.launch.resume()
	
	def _launch(self):
		for i in range(int(self.regulation.launchSetNum)):
			wait = createWait(self.regulation.setInterval)
			while wait(): yield
			
			for _ in range(int(self.regulation.launchRepeat(i))):
				pos = self.core.locator.position + Std.Vector2DF(0, 110)
				targetAngle = pos.getAngle(
					Ctrl.Actor.myShip.position)
				drawParam = Auxs.createBulletRedDrawParam(
					pos, Std.Vector2DF(24, 24*0.3))
				
				NWay.launchLinear(
					pos, 
					targetAngle, 
					self.regulation.outerAngleInterval, 
					self.regulation.outerWayNum, 
					int(drawParam.dst.h), 
					drawParam, 
					self.regulation.outerSpeed)
				NWay.launchLinear(
					pos, 
					targetAngle, 
					self.regulation.innerAngleInterval, 
					self.regulation.innerWayNum, 
					int(drawParam.dst.h), 
					drawParam, 
					self.regulation.innerSpeed)
				
				launchWait = createWait(self.regulation.launchInterval)
				while launchWait(): yield
		
		wait = createWait(self.regulation.endWait)
		while wait(): yield
	
	@property
	def end(self):
		return not self.launch.alive