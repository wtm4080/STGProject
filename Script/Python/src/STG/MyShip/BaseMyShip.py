'''
Created on 2010/10/23

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Auxs as Auxs

class Base:
	INIT_REMAINDER_NUM = 3
	INIT_POSITION = Std.Vector2DF(
		(Std.Consts.ScreenSize.x - Std.Consts.StgInfAreaSize.x) / 2.0, 
		Std.Consts.ScreenSize.y * 0.8)
	INIT_DISAPPEAR_FRAME_NUM = 60
	INIT_BARRIER_FRAME_NUM = 120
	INIT_HIT_RADIUS = 1
	INIT_HIT_RADIUS_ITEM_RETRIEVE = 64
	INIT_HIT_RADIUS_ITEM = 16
	
	def __init__(self):
		self.locator = Std.Locator.LinearF(self.INIT_POSITION)
		self.hitCircle = Std.Hit.CircleI(
			self.INIT_POSITION, self.INIT_HIT_RADIUS)
		self.itemRetrieveHitCircle = Std.Hit.CircleI(
			self.INIT_POSITION, self.INIT_HIT_RADIUS_ITEM_RETRIEVE)
		self.itemHitCircle = Std.Hit.CircleI(
			self.INIT_POSITION, self.INIT_HIT_RADIUS_ITEM)
		self.initRemainder = self.INIT_REMAINDER_NUM
		self.remainder = self.INIT_REMAINDER_NUM
		self.barrierCount = 0
		self.disappearCount = 0
		self.moveForbidFlag = False
		self.shotForbidFlag = False
		self.specialAttackForbidFlag = False
	
	def update(self):
		if not self.disappeared:
			bulletCount = Auxs.destructBullets(self.hitCircle)
			if bulletCount > 0:
				self.destruct()
		
		if self.disappeared:
			self.disappearCount -= 1
			
			if not self.disappeared:
				if self.remainder > 0:
					self.locator.position = self.INIT_POSITION
					self.onRevival()
				else:
					self.disappearCount += 1
		elif self.barriered:
			self.barrierCount -= 1
		
		self._input()
		
		self.hitCircle.center = self.locator.position
		self.itemRetrieveHitCircle.center = self.locator.position
		self.itemHitCircle.center = self.locator.position
		if self.barriered:
			self.hitCircle.radius = self.barrierRadius
		else:
			self.hitCircle.radius = self.INIT_HIT_RADIUS
		self.itemRetrieveHitCircle.radius = self.itemRetrieveRadius
		
		self.onUpdate()
	def _input(self):
		controller = Ctrl.getController()
		
		if not self.disappeared:
			if not self.moveForbidFlag:
				self.locator.speed = controller.direction * self.moveSpeed
				self.locator.update()
				
				pos = self.locator.position
				size = self.shipSize
				rightBorder = Std.Consts.ScreenSize.x - Std.Consts.StgInfAreaSize.x
				bottomBorder = Std.Consts.ScreenSize.y
				if pos.x - size.x/2 < 0:
					pos.x = size.x/2
				elif pos.x + size.x/2 > rightBorder:
					pos.x = rightBorder - size.x/2
				if pos.y - size.y/2 < 0:
					pos.y = size.y/2
				elif pos.y + size.y/2 > bottomBorder:
					pos.y = bottomBorder - size.y/2
				self.locator.position = pos
			if(not self.shotForbidFlag and 
			controller.isHold(Std.Input.KeyId.Z)):
				self.shot()
			if(not self.specialAttackForbidFlag and 
			controller.isPush(Std.Input.KeyId.X)):
				self.specialAttack()
	
	def draw(self):
		if not self.disappeared:
			self.onDraw()
	
	def isHit(self, bulletHit):
		if not self.disappeared:
			return self.hitCircle.isHit(bulletHit)
		return False
	def isHit_ItemRetrieve(self, itemHit):
		if not self.disappeared:
			return self.itemRetrieveHitCircle.isHit(itemHit)
		return False
	def isHit_GetItem(self, itemHit):
		if not self.disappeared:
			return self.itemHitCircle.isHit(itemHit)
		return False
	
	def destruct(self):
		if not self.disappeared and not self.barriered:
			self.remainder -= 1
			self.disappearCount = self.INIT_DISAPPEAR_FRAME_NUM
			self.barrierCount = self.INIT_BARRIER_FRAME_NUM
			self.onDestruction()
	
	@property
	def barriered(self):
		return self.barrierCount > 0
	def setBarrier(self, frameNum):
		self.barrierCount = frameNum
	@property
	def disappeared(self):
		return self.disappearCount > 0
	
	@property
	def position(self):
		return self.locator.position
	@position.setter
	def position(self, value):
		self.locator.position = value
	def applyExternalForce(self, vec):
		if not self.disappeared:
			return self.locator.applyExternalForce(vec)
		return Std.Vector2DF()
	
	def addRemainder(self, num):
		self.remainder += num
	def setInitRemainder(self, num):
		assert num > 0
		
		self.initRemainder = num
		self.remainder = num
	
	def doContinue(self):
		self.remainder = self.initRemainder
		self.onContinue()
	
	def setMoveForbidFlag(self, flag):
		self.moveForbidFlag = flag
	def setShotForbidFlag(self, flag):
		self.shotForbidFlag = flag
	def setSpecialAttackForbidFlag(self, flag):
		self.specialAttackForbidFlag = flag
	
	
	def onUpdate(self):
		raise Exception("BaseMyShip.Base.onUpdate is not implemented.")
	def onDraw(self):
		raise Exception("BaseMyShip.Base.onDraw is not implemented.")
	def drawInfArea(self, basePos):
		raise Exception("BaseMyShip.Base.drawInfArea is not implemented.")
	@property
	def power(self):
		raise Exception("BaseMyShip.Base.power is not implemented.")
	def supplyPower(self):
		raise Exception("BaseMyShip.Base.supplyPower is not implemented.")
	@property
	def spAttack(self):
		raise Exception("BaseMyShip.Base.spAttack is not implemented.")
	def supplySpAttack(self):
		raise Exception("BaseMyShip.Base.supplySpAttack is not implemented.")
	def onDestruction(self):
		raise Exception("BaseMyShip.Base.onDestruction is not implemented.")
	def onRevival(self):
		raise Exception("BaseMyShip.Base.onRevival is not implemented.")
	def onContinue(self):
		raise Exception("BaseMyShip.Base.onContinue is not implemented.")
	@property
	def shipSize(self):
		raise Exception("BaseMyShip.Base.shipSize is not implemented.")
	@property
	def moveSpeed(self):
		raise Exception("BaseMyShip.Base.moveSpeed is not implemented.")
	@property
	def barrierRadius(self):
		raise Exception("BaseMyShip.Base.barrierRadius is not implemented.")
	@property
	def itemRetrieveRadius(self):
		raise Exception("BaseMyShip.Base.itemRetrieveRadius is not implemented.")
	def shot(self):
		raise Exception("BaseMyShip.Base.shot is not implemented.")
	def specialAttack(self):
		raise Exception("BaseMyShip.Base.specialAttack is not implemented.")