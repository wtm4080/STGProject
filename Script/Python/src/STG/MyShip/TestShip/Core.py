'''
Created on 2010/10/30

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Auxs as Auxs
from STG.MyShip.BaseMyShip import Base
from STG.MyShip.TestShip.Drawing import Drawing
import STG.MyShip.TestShip.Option as Option
from STG.MyShip.TestShip.Resource import Resource
from STG.MyShip.TestShip.ShipLauncher import ShipLauncher

class Core(Base):
	SHIP_SIZE = Std.Vector2DF(64, 64)
	EXPLOSION_SIZE = Std.Vector2DF(96*3, 96*3)
	MAX_POWER = 4
	INIT_SPATTACK_COUNT = 2
	SPATTACK_FRAME_NUM = 60 * 8
	SPBARRIER_FRAME_NUM = 60 * 2
	SPFINISHED_FORCE_FRAME_NUM = 60 * 1
	
	def __init__(self, _):
		super().__init__()
		self.slow = False
		self.powerCount = 0
		self.spFrameCount = 0
		self.spFinishedForceFrameCount = 0
		self.spAttackCount = self.INIT_SPATTACK_COUNT
		self.resource = Resource()
		self.drawing = Drawing(self)
		self.shipLauncher = ShipLauncher(self)
		self.optionManager = Option.Manager(self)
	
	def onUpdate(self):
		self.slow = Ctrl.getController().isHold(Std.Input.KeyId.LShift)
		self.drawing.update()
		
		self.shipLauncher.update()
		self.optionManager.update()
		
		if self.spFrameCount > 0:
			self.spFrameCount -= 1
			if self.spFrameCount <= 0:
				self.spFinished()
			elif self.spFrameCount == 60:
				self.drawing.spFinishingAnimation.play()
		
		if self.spFinishedForceFrameCount > 0:
			self.applySpFinishedForce()
			self.spFinishedForceFrameCount -= 1
	def onDraw(self):
		self.drawing.draw()
		self.optionManager.draw()
	def drawInfArea(self, basePos):
		self.drawing.drawInfArea(basePos)
	
	@property
	def power(self):
		return self.powerCount
	def supplyPower(self):
		if(not self.disappeared and 
				self.powerCount < self.MAX_POWER):
			self.powerCount += 1
			self.shipLauncher.power = self.powerCount
			self.optionManager.power = self.powerCount
			
			return True
		else:
			return False
	@property
	def spAttack(self):
		return self.spAttackCount
	def supplySpAttack(self):
		if not self.disappeared:
			self.spAttackCount += 1
			
			return True
		else:
			return False
	
	def onDestruction(self):
		Auxs.createExplosion(
			self.position, self.EXPLOSION_SIZE)
		
		itemNum = 0
		if self.powerCount <= 2:
			itemNum = 2
		elif self.powerCount <= self.MAX_POWER:
			itemNum = self.powerCount
		else:
			assert False, "invalid power count"
		for i in range(itemNum):
			angle = -180/(itemNum + 1) * (i + 1)
			item = Auxs.Item.PowerUp(self.position, angle)
			Ctrl.Actor.registerItem(item)
		
		self.powerCount = 0
		self.shipLauncher.power = self.powerCount
		self.optionManager.power = self.powerCount
		self.spFrameCount = 0
		self.shipLauncher.spShot = False
		self.optionManager.spShot = False
		self.drawing.spGaugeAnimation.stop()
	def onRevival(self):
		self.spAttackCount += self.INIT_SPATTACK_COUNT
	def onContinue(self):
		self.spAttackCount = 0
	
	@property
	def shipSize(self):
		return self.SHIP_SIZE
	@property
	def moveSpeed(self):
		if self.slow:
			return 2.5
		else:
			return 6.5
	@property
	def barrierRadius(self):
		return 32
	@property
	def itemRetrieveRadius(self):
		return 96
	
	def shot(self):
		self.shipLauncher.launch()
		self.optionManager.launch()
	
	def specialAttack(self):
		if self.spAttackCount > 0 and self.spFrameCount <= 0:
			self.shipLauncher.spShot = True
			self.optionManager.spShot = True
			self.spAttackCount -= 1
			self.spFrameCount = self.SPATTACK_FRAME_NUM
			self.barrierCount = self.SPBARRIER_FRAME_NUM
			
			self.drawing.spBeginAnimation.play()
			self.drawing.spGaugeAnimation.play()
		elif self.spFrameCount > 0:
			self.spFinished()
	def spFinished(self):
		self.shipLauncher.spShot = False
		self.optionManager.spShot = False
		self.barrierCount = self.SPBARRIER_FRAME_NUM
		self.spFrameCount = 0
		self.spFinishedForceFrameCount = self.SPFINISHED_FORCE_FRAME_NUM
		
		self.drawing.spFinishAnimation.play()
		self.drawing.spGaugeAnimation.stop()
	def applySpFinishedForce(self):
		circle = Std.Hit.CircleI(self.position, 400)
		Auxs.applyExRadialForceToBullets(circle, 0.3)