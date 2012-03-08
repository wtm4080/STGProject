'''
Created on 2010/11/10

@author: t
'''

import Std
import STG.Ctrl as Ctrl
from STG.MyShip.TestShip.Laser import Laser
from STG.MyShip.TestShip.SpLaser import SpLaser
from STG.MyShip.TestShip.SpShortLaser import SpShortLaser

class ShipLauncher:
	INIT_INTERVAL = 4
	SPSHORT_INTERVAL = 2
	SP_INTERVAL = 2.5
	INTERVAL_DEC_RATE = 0.2
	LAUNCH_POSITION_TABLE = (
		Std.Vector2DF(-4, -10), Std.Vector2DF(4, -10), 
		Std.Vector2DF(-14, 6), Std.Vector2DF(14, 6), 
		Std.Vector2DF(-24, 14), Std.Vector2DF(24, 14), 
		)
	LAUNCH_ANGLE_TABLE = (
		-90-2, -90+2, 
		-90-6, -90+6, 
		-90-12, -90+12, 
		)
	
	def __init__(self, ship):
		self.ship = ship
		self.repCounter = Std.RepeatCounter()
		self.power = ship.powerCount
		self.spShot = False
	
	@property
	def power(self):
		return self._power
	@power.setter
	def power(self, power):
		self._power = power
		self.repCounter.interval = (
			self.INIT_INTERVAL - self.INTERVAL_DEC_RATE*power)
		self.repCounter.reset()
	
	def update(self):
		if self.spShot and self.ship.slow:
			self.repCounter.interval = self.SPSHORT_INTERVAL
		elif self.spShot and not self.ship.slow:
			self.repCounter.interval = self.SP_INTERVAL
		else:
			self.repCounter.interval = self.INIT_INTERVAL
		self.repCounter.update()
	
	def launch(self):
		for i in range(self.repCounter.repeatCount):
			basePos = self.ship.locator.position
			targetPos = basePos + Std.Vector2DF(0, -480)
			slow = self.ship.slow
			
			for i in range(len(self.LAUNCH_POSITION_TABLE)):
				pos = basePos + self.LAUNCH_POSITION_TABLE[i]
				angle = 0
				if not slow:
					angle = self.LAUNCH_ANGLE_TABLE[i]
				else:
					angle = pos.getAngle(targetPos)
				
				if self.spShot:
					if self.ship.slow:
						Ctrl.Actor.registerMyShot(
							SpShortLaser(self.ship, pos))
					else:
						Ctrl.Actor.registerMyShot(
							SpLaser(pos, angle, self.ship.resource))
				else:
					Ctrl.Actor.registerMyShot(
						Laser(pos, angle))