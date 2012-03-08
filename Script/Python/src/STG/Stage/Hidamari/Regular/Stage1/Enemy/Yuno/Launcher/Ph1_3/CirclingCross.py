'''
Created on 2011/04/16

@author: t
'''

import Std
import STG.Auxs as Auxs
from Util.Coroutine import Coroutine
from Util.Coroutine import createWait
import Util.NWay as NWay

from ...BaseCross import BaseCross

from STG.Regulation.Hidamari.Regular.Stage1.Yuno import Phase1_3 as Regulation

class CirclingCross(BaseCross):
	SIZE = Std.Vector2DF(64, 64)
	ROT_SPEED = 2
	
	def __init__(self, resource, center, radius, angle, rank):
		self.locator = Std.Locator.RotateF()
		self.locator.center = center
		self.locator.radius = radius
		self.locator.angle = angle
		
		super().__init__(resource, self.locator.position, 
			self.SIZE, self.ROT_SPEED)
		
		self.launch = Coroutine(self._launch)
		
		self.regulation = Regulation.CrossCircle(rank)
	
	@property
	def position(self):
		return self.locator.position
	def applyExternalForce(self, vec):
		return Std.Vector2DF()
	
	def onUpdate(self):
		self.locator.update()
		
		super().onUpdate()
		
		if self.launch.alive:
			self.launch.resume()
	
	def _launch(self):
		while True:
			wait = createWait(self.regulation.launchWait)
			while wait(): yield
			
			for _ in range(int(self.regulation.launchRepeat)):
				pos = self.locator.position
				drawParam = Auxs.createBulletBlueDrawParam(
					pos, Std.Vector2DF(24, 8))
				NWay.launchLinear(
					pos, 
					self.locator.angle + 180, 
					self.regulation.angleInterval, 
					self.regulation.wayNum, 
					int(drawParam.dst.w/4), 
					drawParam, 
					self.regulation.bulletSpeed)
				
				wait = createWait(self.regulation.launchInterval)
				while wait(): yield