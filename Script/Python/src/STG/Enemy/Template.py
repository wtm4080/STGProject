'''
Created on 2011/03/04

@author: t
'''

import Std
from STG.Enemy.BaseEnemy import Base

class Template(Base):
	SIZE = Std.Vector2DF(128, 128)
	MAX_HP = 1000
	
	def __init__(self, pos):
		super().__init__(
			Std.Hit.RectI(pos, self.SIZE, True), self.MAX_HP)
		self.locator = Std.Locator.LinearF(pos)
	
	@property
	def position(self):
		return self.locator.position
	def applyExternalForce(self, vec):
		return self.locator.applyExternalForce(vec)
	
	def onUpdate(self):
		self.locator.update()
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