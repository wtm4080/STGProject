'''
Created on 2010/11/10

@author: t
'''

import Std
import STG.Ctrl as Ctrl
from STG.MyShip.TestShip.Laser import Laser
from STG.MyShip.TestShip.SpLaser import SpLaser
from STG.MyShip.TestShip.SpShortLaser import SpShortLaser

class Option:
	SIZE = Std.Vector2DF(32, 32)
	
	def __init__(self, position, ship):
		self.ship = ship
		self.spShot = False
		
		self.locator = Std.Locator.TraceF(180)
		self.locator.tracing = True
		self.locator.position = position
		self.locator.speed.setUnitVector(90)
		self.locator.speed *= 8
		
		self.drawParam = Std.Sprite.DrawParam()
		self.drawParam.texture = ship.resource.optionTexture
		self.drawParam.src = Std.RectF(0, 0, 256, 256)
		self.drawParam.dst = self.position.makeRect(self.SIZE, True)
		self.drawParam.priority = Ctrl.DrawPriority.myShipOption
	
	@property
	def position(self):
		return self.locator.position
	@position.setter
	def position(self, position):
		self.locator.position = position
	
	def update(self):
		self.locator.update()
		self.drawParam.dst = self.position.makeRect(self.SIZE, True)
	def draw(self):
		Std.Sprite.draw(self.drawParam)
	
	def launch(self, angle):
		basePos = self.locator.position
		
		if self.spShot:
			if self.ship.slow:
				Ctrl.Actor.registerMyShot(
					SpShortLaser(self.ship, 
						basePos + Std.Vector2DF(-4, 0)))
				Ctrl.Actor.registerMyShot(
					SpShortLaser(self.ship, 
						basePos + Std.Vector2DF(4, 0)))
			else:
				Ctrl.Actor.registerMyShot(
					SpLaser(basePos + Std.Vector2DF(-4, 0), 
						angle, self.ship.resource))
				Ctrl.Actor.registerMyShot(
					SpLaser(basePos + Std.Vector2DF(4, 0), 
						angle, self.ship.resource))
		else:
			Ctrl.Actor.registerMyShot(
				Laser(basePos + Std.Vector2DF(-4, 0), angle))
			Ctrl.Actor.registerMyShot(
				Laser(basePos + Std.Vector2DF(4, 0), angle))

class Manager:
	POSITION_TABLE_1 = (
		(),
		(Std.Vector2DF(0, 48),),
		(Std.Vector2DF(-48, 12), Std.Vector2DF(48, 12)),
		(Std.Vector2DF(0, 48), Std.Vector2DF(-48, 12), Std.Vector2DF(48, 12)),
		(Std.Vector2DF(-20, 48), Std.Vector2DF(20, 48), Std.Vector2DF(-48, 12), Std.Vector2DF(48, 12)))
	POSITION_TABLE_2 = (
		(),
		(Std.Vector2DF(0, 36),),
		(Std.Vector2DF(-32, 0), Std.Vector2DF(32, 0)),
		(Std.Vector2DF(0, 36), Std.Vector2DF(-32, 0), Std.Vector2DF(32, 0)),
		(Std.Vector2DF(-48, 36), Std.Vector2DF(48, 36), Std.Vector2DF(-32, 0), Std.Vector2DF(32, 0)))
	LAUNCH_ANGLE_TABLE = (
		(),
		(-90,),
		(-90 - 30, -90 + 30),
		(-90, -90 - 30, -90 + 30),
		(-90 - 20, -90 + 20, -90 - 30, -90 + 30))
	INIT_INTERVAL = 4
	SPSHORT_INTERVAL = 2
	SP_INTERVAL = 2.5
	INTERVAL_DEC_RATE = 0.2
	
	def __init__(self, ship):
		self.ship = ship
		self.optionList = []
		self.repCounter = Std.RepeatCounter()
		self._spShot = False
		self.rotDegree = 0
		self.power = ship.powerCount
	
	@property
	def power(self):
		return self._power
	@power.setter
	def power(self, power):
		self._power = power
		
		self.repCounter.interval = (
			self.INIT_INTERVAL - self.INTERVAL_DEC_RATE * power)
		self.repCounter.reset()
		
		self.optionList = []
		if power > 0:
			for i in range(power):
				option = Option(self.ship.position, self.ship)
				option.spShot = self.spShot
				option.drawParam.rotDegree = self.rotDegree
				self.optionList.append(option)
				self._setTargetPos(i)
	def _setTargetPos(self, index):
		basePos = self.ship.position
		targetPos = Std.Vector2DF()
		if not self.ship.slow:
			targetPos = (
				basePos + self.POSITION_TABLE_1[self.power][index])
		else:
			targetPos = (
				basePos + self.POSITION_TABLE_2[self.power][index])
		self.optionList[index].locator.targetPosition = targetPos
	
	@property
	def spShot(self):
		return self._spShot
	@spShot.setter
	def spShot(self, spShot):
		self._spShot = spShot
		for option in self.optionList:
			option.spShot = spShot
	
	def update(self):
		if self.power > 0:
			for i in range(self.power):
				self._setTargetPos(i)
				self.optionList[i].update()
		
		if self.spShot and self.ship.slow:
			self.repCounter.interval = self.SPSHORT_INTERVAL
		elif self.spShot and not self.ship.slow:
			self.repCounter.interval = self.SP_INTERVAL
		else:
			self.repCounter.interval = self.INIT_INTERVAL
		self.repCounter.update()
		
		self.rotDegree += 1
		if self.rotDegree >= 360:
			self.rotDegree -= 360
		for option in self.optionList:
			option.drawParam.rotDegree = self.rotDegree
	def draw(self):
		for option in self.optionList:
			option.draw()
	
	def launch(self):
		for _ in range(self.repCounter.repeatCount):
			for j in range(len(self.optionList)):
				angle = 0
				if not self.ship.slow:
					angle = self.LAUNCH_ANGLE_TABLE[self.power][j]
				else:
					targetPos = self.ship.position + Std.Vector2DF(0, -480)
					angle = self.optionList[j].position.getAngle(targetPos)
				self.optionList[j].launch(angle)