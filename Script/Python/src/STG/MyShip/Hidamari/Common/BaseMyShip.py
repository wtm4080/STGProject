'''
Created on 2011/11/28

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Auxs as Auxs
import Util.Misc as Misc
import Util.NWay as NWay
from STG.MyShip.BaseMyShip import Base

class BaseMyShip(Base):
	SHIP_SIZE = Std.Vector2DF(64, 64)
	
	def __init__(self, resource, initialSpAttackNum = 3):
		super().__init__()
		self.slow = False
		self._power = 0
		self.initialSpAttackNum = initialSpAttackNum
		self.spAttackNum = initialSpAttackNum
		self.resource = resource
	
	@property
	def power(self):
		return self._power
	@power.setter
	def power(self, value):
		if value < 0:
			self._power = 0
		elif value > 4:
			self._power = 4
		else:
			self._power = value
	@property
	def spAttack(self):
		return self.spAttackNum
	
	def onUpdate(self):
		if not self.moveForbidFlag:
			self.slow = Ctrl.getController().isHold(Std.Input.KeyId.LShift)
		else:
			self.slow = False
	
	def supplyPower(self):
		prev = self.power
		self.power += 1
		if self.power > prev:
			self.resource.se_PowerUp.play()
			return True
		else:
			self.resource.se_Item.play()
			return False
	def supplySpAttack(self):
		prev = self.spAttackNum
		self.spAttackNum += 1
		if self.spAttackNum > prev:
			self.resource.se_Bomber.play()
			return True
		else:
			self.resource.se_Item.play()
			return False
	
	def onDestruction(self):
		Misc.createExplosion(
			Ctrl.DrawPriority.myShip, 
			5, 
			self.locator.position, 
			self.SHIP_SIZE.getAbs() * 2, 
			1.5, 
			Std.Vector2DF(16, 16)
			)
		self.resource.se_Destruction.play()
		
		if self.power <= 2:
			itemNum = 2
		elif self.power <= 4:
			itemNum = self.power
		angleList = NWay.getAngleList(-90, 20, itemNum)
		for angle in angleList:
			item = Auxs.Item.PowerUp(self.position, angle)
			Ctrl.Actor.registerItem(item)
		
		self.power = 0
	def onRevival(self):
		self.spAttackNum = self.initialSpAttackNum
		self.setBarrier(240)
	
	@property
	def shipSize(self):
		return self.SHIP_SIZE
	@property
	def barrierRadius(self):
		return 32
	@property
	def itemRetrieveRadius(self):
		return 96