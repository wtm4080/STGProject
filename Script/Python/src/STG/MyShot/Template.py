'''
Created on 2011/03/04

@author: t
'''

import Std
from STG.MyShot.BaseMyShot import Base

class Template(Base):
	RADIUS = 3
	SIZE = Std.Vector2DF(32, RADIUS*2)
	SPEED = 30
	BASE_DAMAGE = 4
	DAMAGE_RAGE_DEC = 0.06
	DAMAGE_RAGE_MIN = 0.5
	
	def __init__(self, position, angle):
		super().__init__(position, self.RADIUS)
		
		self.locator = Std.Locator.LinearF(position)
		self.locator.speed.setUnitVector(angle)
		self.locator.speed *= self.SPEED
		
		self.baseDamage = self.BASE_DAMAGE
		self.damageRate = 1
	
	@property
	def position(self):
		return self.locator.position
	def applyExternalForce(self, vec):
		return self.locator.applyExternalForce(vec)
	
	def onUpdate(self):
		self.locator.update()
		
		if self.damageRate > self.DAMAGE_RAGE_MIN:
			self.damageRate -= self.DAMAGE_RAGE_DEC
		else:
			self.damageRate = self.DAMAGE_RAGE_MIN
			self.baseDamage = self.BASE_DAMAGE * self.damageRate
	def onDraw(self):
		pass
	
	def onErase(self):
		pass
	def onDestructed(self):
		pass
	def onDamaged(self, damage):
		pass
	def onDestructedByDamage(self, damage):
		pass
	@property
	def damage(self):
		return self.baseDamage