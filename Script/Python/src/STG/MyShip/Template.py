'''
Created on 2011/03/04

@author: t
'''

import Std
from STG.MyShip.BaseMyShip import Base

class Core(Base):
	SHIP_SIZE = Std.Vector2DF(64, 64)
	
	def __init__(self):
		super().__init__()
		self.slow = False
	
	def onUpdate(self):
		pass
	def onDraw(self):
		pass
	def drawInfArea(self, basePos):
		pass
	
	def supplyPower(self):
		pass
	def supplySpAttack(self):
		pass
	
	def onDestruction(self):
		pass
	def onRevival(self):
		pass
	def onContinue(self):
		pass
	
	@property
	def shipSize(self):
		return self.SHIP_SIZE
	@property
	def moveSpeed(self):
		if self.slow:
			return 2
		else:
			return 4
	@property
	def barrierRadius(self):
		return 32
	@property
	def itemRetrieveRadius(self):
		return 96
	
	def shot(self):
		pass
	def specialAttack(self):
		pass