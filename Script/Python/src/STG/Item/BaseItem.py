'''
Created on 2010/10/23

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Actor.BaseActor as BaseActor

class Base(BaseActor.Base):
	INIT_HIT_RADIUS = 16
	INIT_MAX_CIRCLING_ANGLE = 90
	INIT_ITEM_SIZE = Std.Vector2DI(32, 32)
	INIT_SPEED = 1.5
	
	def __init__(self, pos, angle):
		self.locator = Std.Locator.TraceF(self.INIT_MAX_CIRCLING_ANGLE)
		self.locator.tracing = False
		self.locator.position = pos
		self.locator.speed.setUnitVector(angle)
		self.locator.speed *= self.INIT_SPEED
		super().__init__(
			Std.Hit.RectI(pos, self.INIT_ITEM_SIZE, True))
		self.hitCircle = Std.Hit.CircleI(pos, self.INIT_HIT_RADIUS)
	
	@property
	def position(self):
		return self.locator.position
	@position.setter
	def position(self, position):
		self.locator.position = position
	
	@property
	def hitRadius(self):
		return self.hitCircle.radius
	@hitRadius.setter
	def hitRadius(self, radius):
		self.hitCircle.radius = radius
	
	def applyExternalForce(self, vec):
		return self.locator.applyExternalForce(vec)
	
	def isHit(self, circle):
		return self.hitCircle.isHit(circle)
	
	def updateMiddle(self):
		myShip = Ctrl.Actor.myShip
		
		if not myShip.disappeared:
			self.locator.targetPosition = myShip.position
		self.locator.update()
		
		self.hitCircle.center = self.locator.position
		
		if myShip.isHit_GetItem(self.hitCircle):
			self.effect()
			self.valid = False
		
		if not self.locator.tracing:
			if self.locator.speed.y >= 3.0:
				self.locator.speed.setXY(self.locator.speed.x, 3.0)
			else:
				self.locator.applyExternalForce(Std.Vector2DF(0, 0.03))
			
			if (not myShip.disappeared and 
					self.locator.speed.y >= 0 and 
				myShip.isHit_ItemRetrieve(self.hitCircle)):
				self.locator.tracing = True
		else:
			if not myShip.disappeared:
				if self.locator.speed.getAbs() < 10.0:
					angle = self.locator.position.getAngle(self.locator.targetPosition)
					self.locator.accel.setUnitVector(angle)
					self.locator.accel *= 1.0
				else:
					self.locator.speed.normalize()
					self.locator.speed *= 10.0
					self.locator.accel *= 0
			else:
				self.locator.tracing = False
				self.locator.accel *= 0
				self.locator.speed *= 0
	
	
	def effect(self):
		raise Exception("BaseItem.Base.effect is not implemented.")