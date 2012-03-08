'''
Created on 2011/04/16

@author: t
'''

import Std
import STG.Ctrl as Ctrl
from Util.Coroutine import Coroutine
from Util.Coroutine import createWait
import Util.NWay as NWay

from STG.Regulation.Hidamari.Regular.Stage1.Yuno import Phase2_2 as Regulation

class CrossLauncher:
	def __init__(self, core, rank):
		self.core = core
		self.launch = Coroutine(self._launch)
		self.shooting = False
		
		self.regulation = Regulation.Cross(rank)
	
	def update(self):
		if self.launch.alive:
			self.launch.resume()
	
	def _launch(self):
		baseAngle = 0
		rotSpeed = self.regulation.launchAngleRotateSpeed
		launchNum = self.regulation.launchRepeat
		launchWaitNum = self.regulation.launchInterval
		def getPos(left):
			basePos = self.core.locator.position
			offsetX = 103
			offsetY = -40
			if left:
				return basePos + Std.Vector2DF(offsetX, offsetY)
			else:
				return basePos + Std.Vector2DF(-offsetX, offsetY)
		
		while True:
			self.shooting = True
			for _ in range(launchNum):
				angleList = NWay.getCircleAngleList(baseAngle, self.regulation.wayNum)
				for angle in angleList:
					leftCross = _LinearCross(
						self.core.resource, getPos(True), -angle, self.regulation.speed)
					Ctrl.Actor.registerBullet(leftCross)
					rightCross = _LinearCross(
						self.core.resource, getPos(False), angle, self.regulation.speed)
					Ctrl.Actor.registerBullet(rightCross)
				
				baseAngle += rotSpeed
				launchWait = createWait(launchWaitNum)
				while launchWait(): yield
			self.shooting = False
			
			interval = createWait(launchWaitNum * launchNum)
			while interval():
				baseAngle += rotSpeed
				yield

from ...BaseCross import BaseCross

class _LinearCross(BaseCross):
	SIZE = Std.Vector2DF(48, 48)
	ROT_SPEED = 6
	
	def __init__(self, resource, pos, angle, speed):
		self.locator = Std.Locator.LinearF()
		self.locator.position = pos
		self.locator.speed.setUnitVector(angle)
		self.locator.speed *= speed
		
		super().__init__(resource, self.locator.position, 
			self.SIZE, self.ROT_SPEED)
		self.particleRepCounter.interval = 15
	
	@property
	def position(self):
		return self.locator.position
	def applyExternalForce(self, vec):
		return self.locator.applyExternalForce(vec)
	
	def onUpdate(self):
		self.locator.update()
		super().onUpdate()
	
	def createInitialParticle(self):
		self.createParticle(3, Ctrl.DrawPriority.enemyBullet2)