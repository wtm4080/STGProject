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

class LaunchTracingCross:
	def __init__(self, core, clockwise, rank):
		self.core = core
		self.clockwise = clockwise
		self.rank = rank
		
		self.regulation = Regulation.BitTask2_LaunchTracingCross(rank)
	
	def task(self, bit):
		rotSpeed = 15
		if not self.clockwise:
			rotSpeed *= -1
		rotSum = 0
		while abs(rotSum) < 360:
			bit.angle += rotSpeed
			rotSum += rotSpeed
			yield
		
		bit.circling.circling = True
		bit.circling.circlingAngle = 15
		
		wait = createWait(self.regulation.aimingFrameNum)
		rand = Ctrl.getRandom()
		angleError = rand.getFloat(*self.regulation.angleError)
		while wait():
			targetAngle = bit.locator.position.getAngle(
				Ctrl.Actor.myShip.position) + angleError
			bit.circling.targetAngle = targetAngle
			yield
		
		bit.circling.circling = False
		bit.circling.circlingAngle = bit.CIRCLING_ANGLE
		
		if self.clockwise:
			crossLaunchAngle = bit.angle - 90
		else:
			crossLaunchAngle = bit.angle + 90
		cross = _TracingCross(
			self.core.resource, 
			bit.nozzlePos, 
			crossLaunchAngle, 
			self.rank, 
			self.clockwise)
		Ctrl.Actor.registerBullet(cross)
		
		drawParam = Auxs.createBulletRedDrawParam(
				bit.nozzlePos, Std.Vector2DF(16, 8))
		for i in range(int(self.regulation.launchRepeat)):
			NWay.launchLinear(
				bit.nozzlePos, 
				bit.angle, 
				self.regulation.angleInterval, 
				self.regulation.wayNum, 
				int(drawParam.dst.w/2), 
				drawParam, 
				self.regulation.speed(i), 
				self.regulation.accel(i))
			
			wait = createWait(self.regulation.launchInterval)
			while wait(): yield
		
		wait = createWait(self.regulation.endWait)
		while wait(): yield

from .....BaseCross import BaseCross

class _TracingCross(BaseCross):
	SIZE = Std.Vector2DF(64, 64)
	ROT_SPEED = 15
	VALID_AREA = Std.Hit.RectI(0, 0, 
		Std.Consts.ScreenSize.x - Std.Consts.StgInfAreaSize.x, 
		Std.Consts.ScreenSize.y, False)
	
	def __init__(self, resource, pos, angle, rank, clockwise):
		self.regulation = Regulation.BitTask2_LaunchTracingCross.TracingCross(rank)
		
		self.locator = Std.Locator.TraceF(self.regulation.circlingAngle)
		self.locator.tracing = False
		self.locator.position = pos
		self.locator.speed.setUnitVector(angle)
		self.locator.speed *= 4
		self.locator.accel.setUnitVector(angle + 180)
		self.locator.accel *= 0.1
		
		rotSpeed = self.ROT_SPEED
		if not clockwise:
			rotSpeed *= -1
		super().__init__(resource, self.locator.position, 
			self.SIZE, rotSpeed)
		
		self.main = Coroutine(self._main)
	
	@property
	def position(self):
		return self.locator.position
	def applyExternalForce(self, vec):
		return self.locator.applyExternalForce(vec)
	
	def onUpdate(self):
		if self.isHitRect(self.VALID_AREA):
			self.locator.update()
			super().onUpdate()
			if self.main.alive:
				self.main.resume()
		else:
			self.valid = False
	def _main(self):
		while self.locator.speed.getAbs() > 0.1:
			yield
		
		frameCount = 0
		myShip = Ctrl.Actor.myShip
		while(frameCount < self.regulation.tracingFrameNum and 
		self.position.getDistance(myShip.position) > self.regulation.tracingEndDistance):
			self.locator.tracing = True
			self.locator.targetPosition = myShip.position
			self.locator.accel.setUnitVector(
				self.locator.speed.getAngle())
			self.locator.accel *= self.regulation.tracingAccel
			
			frameCount += 1
			yield
		
		while True:
			self.locator.tracing = False
			self.locator.accel.setUnitVector(
				self.locator.speed.getAngle())
			self.locator.accel *= self.regulation.afterTracingAccel
			yield