'''
Created on 2010/10/23

@author: t
'''

import math
import Std
import STG.Actor.BaseActor as BaseActor

class Base(BaseActor.Base):
	INIT_VALID_AREA_MARGIN = 300
	INIT_DAMAGED_AREA = Std.Hit.RectI(0, 0, 
		Std.Consts.ScreenSize.x - Std.Consts.StgInfAreaSize.x, 
		Std.Consts.ScreenSize.y, False)
	
	def __init__(self, hit, hp):
		super().__init__(hit)
		self.hp = hp
		self.maxHp = hp
		self.hitRect = hit
		self.frameCounting = False
		self.setValidAreaMargin(self.INIT_VALID_AREA_MARGIN)
		self.damagedArea = self.INIT_DAMAGED_AREA
	
	@property
	def hitRadius(self):
		return math.sqrt(
			self.hitRect.size.x*self.hitRect.size.x + 
			self.hitRect.size.y*self.hitRect.size.y) / 2
	
	@property
	def paGenerated(self):
		return False
	@property
	def maxPAAmount(self):
		return 0.0
	@property
	def paAmount(self):
		return 0.0
	
	def updateMiddle(self):
		self.hitRect.center = self.position
		
		if self.hp <= 0:
			self.destruct()
	
	def isHit(self, hit):
		return self.hitRect.isHit(hit)
	
	def destruct(self):
		if self.hp > 0:
			self.valid = False
			self.onDestructed()
	def applyDamage(self, damage):
		if self.hp > 0 and self.hitRect.isHit(self.damagedArea):
			self.hp -= damage
			self.onDamaged(damage)
			
			if self.hp <= 0:
				self.valid = False
				self.onDestructedByDamage(damage)
			elif self.hp > self.maxHp:
				self.hp = self.maxHp
	
	
	def onDestructed(self):
		raise Exception("BaseEnemy.Base.onDestructed is not implemented.")
	def onDamaged(self, damage):
		raise Exception("BaseEnemy.Base.onDamaged is not implemented.")
	def onDestructedByDamage(self, damage):
		raise Exception("BaseEnemy.Base.onDestructedByDamage is not implemented.")