'''
Created on 2011/01/23

@author: t
'''

import Std
import STG.Ctrl as Ctrl

class Move:
	MAX_CIRCLING_ANGLE = 6
	BASE_SPEED = 0.6
	CHANGE_TARGET_FREQUENCY = 40
	MOVE_AREA_SIZE = Std.Vector2DF(10, 10)
	SPEED_CORRECTION_AMOUNT = 0.2
	
	def __init__(self, core):
		self.core = core
		
		self.basePos = Std.Vector2DF(core.locator.position)
		self.baseSpeed = self.BASE_SPEED
		core.locator.maxCirclingAngle = self.MAX_CIRCLING_ANGLE
		core.locator.targetPosition = self.basePos
		core.locator.tracing = True
		core.locator.speed.setUnitVector(90)
		core.locator.speed *= self.baseSpeed
		
		self.changeTargetCount = self.CHANGE_TARGET_FREQUENCY
		
		self.controlFlag = True
	
	def update(self):
		if self.controlFlag:
			targetDistance = self.core.locator.position.getDistance(
				self.core.locator.targetPosition)
			if(self.changeTargetCount == self.CHANGE_TARGET_FREQUENCY
			or targetDistance <= self.baseSpeed):
				random = Ctrl.getRandom()
				
				nextTargetPos = Std.Vector2DF()
				while True:
					randX = random.getFloat(0, self.MOVE_AREA_SIZE.x)
					randX -= self.MOVE_AREA_SIZE.x / 2
					randY = random.getFloat(0, self.MOVE_AREA_SIZE.y)
					randY -= self.MOVE_AREA_SIZE.y / 2
					
					nextTargetPos = Std.Vector2DF(
						self.basePos.x + randX, self.basePos.y + randY)
					nextTargetDistance = self.core.locator.position.getDistance(nextTargetPos)
					if nextTargetDistance > self.baseSpeed:
						break
				
				self.core.locator.targetPosition = nextTargetPos
				
				self.changeTargetCount = 0
			else:
				self.changeTargetCount += 1
		
		self.core.locator.update()
		
		if self.controlFlag:
			currentSpeed = self.core.locator.speed.getAbs()
			speedDir = self.core.locator.speed.getAngle()
			self.core.locator.speed.setUnitVector(speedDir)
			if currentSpeed > self.baseSpeed:
				if currentSpeed - self.SPEED_CORRECTION_AMOUNT < self.baseSpeed:
					self.core.locator.speed *= self.baseSpeed
				else:
					self.core.locator.speed *= currentSpeed - self.SPEED_CORRECTION_AMOUNT
			elif currentSpeed < self.baseSpeed:
				if currentSpeed + self.SPEED_CORRECTION_AMOUNT > self.baseSpeed:
					self.core.locator.speed *= self.baseSpeed
				else:
					self.core.locator.speed *= currentSpeed + self.SPEED_CORRECTION_AMOUNT
	
	def addSpeed(self, vector):
		self.core.locator.speed += vector
	def resetBaseSpeed(self):
		self.baseSpeed = self.BASE_SPEED