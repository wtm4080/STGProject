'''
Created on 2011/03/04

@author: t
'''

import Std
from STG.Actor.BaseActor import Base

class Template(Base):
	VALID_SIZE = Std.Vector2DF(32, 32)
	
	def __init__(self, pos):
		super().__init__(
			Std.Hit.RectI(pos, self.VALID_SIZE, True))
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