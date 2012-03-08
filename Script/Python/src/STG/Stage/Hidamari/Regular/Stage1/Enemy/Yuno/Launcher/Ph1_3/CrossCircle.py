'''
Created on 2011/04/16

@author: t
'''

import Std
import STG.Ctrl as Ctrl
from Util.Coroutine import Coroutine
from Util.Coroutine import createWait

from .CirclingCross import CirclingCross

from STG.Regulation.Hidamari.Regular.Stage1.Yuno import Phase1_3 as Regulation

class CrossCircle:
	def __init__(self, core, rank = 1):
		self.core = core
		self.rank = rank
		self.main = Coroutine(self._main)
		self.rightCrossList = []
		self.leftCrossList = []
		self._created = False
		
		self.regulation = Regulation.CrossCircle(rank)
	
	def update(self):
		for cross in self.rightCrossList:
			if not cross.valid:
				self.rightCrossList.remove(cross)
		for cross in self.leftCrossList:
			if not cross.valid:
				self.leftCrossList.remove(cross)
		
		if self.main.alive:
			self.main.resume()
	def _main(self):
		crossNum = self.regulation.num
		circleRadius = self.regulation.initialRadius
		appearWait = self.regulation.createWait
		angleSpeed = self.regulation.angleSpeed
		
		class CrossControl:
			def __init__(self, core, rank, right, crossList):
				self.core = core
				self.rank = rank
				self.right = right
				self.crossList = crossList
			def _getPos(self, left):
				basePos = self.core.locator.position
				offsetX = 103
				offsetY = -40
				if left:
					return basePos + Std.Vector2DF(offsetX, offsetY)
				else:
					return basePos + Std.Vector2DF(-offsetX, offsetY)
			
			def controlCross(self):
				self.core.face.strain()
				pos = self._getPos(self.right)
				angle = 0
				
				for _ in range(int(crossNum)):
					cross = CirclingCross(self.core.resource, 
						pos, circleRadius, angle, self.rank)
					Ctrl.Actor.registerBullet(cross)
					self.crossList.append(cross)
					
					angle += 360 / crossNum
					
					wait = createWait(appearWait)
					while wait(): yield
				
				for cross in self.crossList:
					cross.locator.radiusSpeed = -2
					cross.locator.radiusAccel = 0.05
				
				rSpeed = 0.35
				while(len(self.crossList) > 0 and 
					self.crossList[0].locator.radiusSpeed < rSpeed):
					yield
				
				for cross in self.crossList:
					cross.locator.radiusSpeed = rSpeed
					cross.locator.radiusAccel = 0
					cross.locator.angleSpeed = angleSpeed
					if self.right:
						cross.locator.angleSpeed *= -1
					if not self.right:
						cross.locator.centerSpeed.setUnitVector(15)
					else:
						cross.locator.centerSpeed.setUnitVector(165)
					cross.locator.centerSpeed *= 0.5
		
		rightControl = CrossControl(self.core, self.rank, 
								True, self.rightCrossList)
		controlRight = Coroutine(rightControl.controlCross)
		
		wait = createWait(90)
		while wait() or controlRight.alive:
			if controlRight.alive:
				controlRight.resume()
			yield
		
		leftControl = CrossControl(self.core, self.rank, 
								False, self.leftCrossList)
		controlLeft = Coroutine(leftControl.controlCross)
		self._created = True
		
		while controlRight.alive or controlLeft.alive:
			if controlRight.alive:
				controlRight.resume()
			if controlLeft.alive:
				controlLeft.resume()
			yield
	
	@property
	def end(self):
		return self._created and not self.rightCrossList and not self.leftCrossList