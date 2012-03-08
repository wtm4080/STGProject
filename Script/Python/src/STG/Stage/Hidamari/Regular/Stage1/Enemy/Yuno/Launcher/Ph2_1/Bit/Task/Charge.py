'''
Created on 2011/04/16

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Auxs as Auxs
from Util.Coroutine import Coroutine
from Util.Coroutine import createWait

from STG.Bullet.BaseBullet import Base as BaseBullet

from STG.Regulation.Hidamari.Regular.Stage1.Yuno import Phase2_1 as Regulation

class Charge:
	def __init__(self, rank):
		self.regulation = Regulation.BitTask3_Charge(rank)
	
	def task(self, bit):
		wait = createWait(self.regulation.moveWait)
		while wait(): yield
		
		bit.locator.tracing = True
		bit.locator.maxCirclingAngle = self.regulation.circlingAngle
		targetPos = Ctrl.Actor.myShip.position
		bit.locator.targetPosition = targetPos
		bit.locator.speed.setUnitVector(bit.angle)
		bit.locator.speed *= self.regulation.initialBitSpeed
		bit.locator.accel.setUnitVector(bit.angle)
		bit.locator.accel *= self.regulation.bitAccel
		
		class TracingBullet(BaseBullet):
			SIZE = Std.Vector2DF(18, 18)
			
			def __init__(self, pos, speed, accel, regulation):
				super().__init__(pos, self.SIZE.x / 4)
				
				self.regulation = regulation
				
				self.locator = Std.Locator.TraceF(self.regulation.bulletCirclingAngle)
				self.locator.tracing = True
				self.locator.targetPosition = Ctrl.Actor.myShip.position
				self.locator.position = pos
				self.locator.speed = speed
				self.locator.accel = accel
				
				self.drawParam = Auxs.createBulletRedDrawParam(
					pos, self.SIZE)
			
			@property
			def position(self):
				return self.locator.position
			def applyExternalForce(self, vec):
				return self.locator.applyExternalForce(vec)
			
			def onUpdate(self):
				self.locator.update()
				self.locator.targetPosition = Ctrl.Actor.myShip.position
				
				accel = self.locator.accel.getAbs()
				self.locator.accel.setUnitVector(
					self.locator.speed.getAngle())
				self.locator.accel *= accel
				
				if(self.frameCount >= self.regulation.bulletTracingFrameNum or 
				self.position.getDistance(self.locator.targetPosition) < self.regulation.bulletTracingEndDistance):
					self.locator.tracing = False
				
				self.drawParam.dst = self.position.makeRect(
					self.SIZE, True)
			def onDraw(self):
				Std.Sprite.draw(self.drawParam)
			
			def onErase(self):
				Auxs.createFadeOut(self.drawParam)
			def onDestructed(self):
				Auxs.createParticle(self.drawParam)
			def onDamaged(self, damage):
				pass
			def onDestructedByDamage(self, damage):
				self.onErase()
		def launch():
			while True:
				speedVector = Std.Vector2DF()
				speedVector.setUnitVector(bit.circling.angle)
				speedVector *= self.regulation.initialBulletSpeed
				accelVector = Std.Vector2DF()
				accelVector.setUnitVector(bit.circling.angle)
				accelVector *= self.regulation.bulletAccel
				bullet = TracingBullet(
					bit.backNozzlePos, speedVector, accelVector, 
					self.regulation)
				Ctrl.Actor.registerBullet(bullet)
				
				launchWait = createWait(self.regulation.launchInterval)
				while launchWait(): yield
		launcher = None
		tracing = createWait(self.regulation.tracingFrameNum)
		while tracing():
			targetPos = Ctrl.Actor.myShip.position
			bit.locator.targetPosition = targetPos
			
			if bit.locator.position.getDistance(targetPos) < self.regulation.tracingEndDistance:
				break
			
			bit.locator.accel.setUnitVector(bit.locator.speed.getAngle())
			bit.locator.accel *= self.regulation.bitAccel
			bit.angle = bit.locator.speed.getAngle()
			
			if launcher is None:
				launcher = Coroutine(launch)
			if launcher.alive:
				launcher.resume()
			yield
		
		bit.locator.tracing = False
		bit.angle = bit.locator.speed.getAngle()
		while True:
			if launcher is None:
				launcher = Coroutine(launch)
			if launcher.alive:
				launcher.resume()
			yield