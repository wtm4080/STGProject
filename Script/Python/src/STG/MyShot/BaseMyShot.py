'''
Created on 2010/10/23

@author: t
'''

import Std
import STG.Auxs as Auxs
import STG.Actor.BaseActor as BaseActor

class Base(BaseActor.Base):
	DEFAULT_HP = 100
	
	def __init__(self, position, radius, baseDamage, hp = DEFAULT_HP):
		super().__init__(
			Std.Hit.RectI(position, radius*2, radius*2, True))
		self.hitCircle = Std.Hit.CircleI(position, radius)
		self.hitRect = Std.Hit.RectI(position, radius*2, radius*2, True)
		
		self.maxHP = hp
		self.hp = hp
		
		self.noDamage = False
		self.baseDamage = baseDamage
		self.paBaseDamage = baseDamage
		self._forcibleForPA = False
		self.damageRate = 1.0
		self.damageRateDec = 0.0
		self.damageRateMin = 1.0
	
	def updateMiddle(self):
		pos = self.position
		self.hitCircle.center = pos
		self.hitRect.center = pos
		
		if self.hp <= 0:
			self.destruct()
		else:
			if self.damageRate > self.damageRateMin:
				self.damageRate -= self.damageRateDec
			else:
				self.damageRate = self.damageRateMin
			
			self.applyDamageToEnemy()
	def applyDamageToEnemy(self):
		damageSum = Auxs.applyDamageToEnemies(self.hitRect, self.damage)
		if damageSum != 0:
			self.destruct()
	
	def isHitCircle(self, hit):
		return self.hitCircle.isHit(hit)
	def isHitRect(self, hit):
		return self.hitRect.isHit(hit)
	
	@property
	def hitRadius(self):
		return self.hitCircle.radius
	@hitRadius.setter
	def hitRadius(self, radius):
		self.hitCircle.radius = radius
		self.hitRect.size = Std.Vector2DI(radius*2, radius*2)
	
	@property
	def damage(self):
		return self.baseDamage * self.hp/self.maxHP * self.damageRate
	@property
	def paDamage(self):
		return self.paBaseDamage * self.damageRate
	@property
	def forcibleForPA(self):
		return self._forcibleForPA
	@forcibleForPA.setter
	def forcibleForPA(self, value):
		self._forcibleForPA = value
	
	def destruct(self):
		if self.valid:
			self.valid = False
			self.onDestructed()
	def applyDamage(self, damage):
		if self.valid:
			if not self.noDamage:
				self.hp -= damage
			self.onDamaged(damage)
			if self.hp <= 0:
				self.valid = False
				self.onDestructedByDamage(damage)
	
	
	def onDestructed(self):
		raise Exception("BaseMyShot.Base.onDestructed is not implemented.")
	def onDamaged(self, damage):
		raise Exception("BaseMyShot.Base.onDamaged is not implemented.")
	def onDestructedByDamage(self, damage):
		raise Exception("BaseMyShot.Base.onDestructedByDamage is not implemented.")