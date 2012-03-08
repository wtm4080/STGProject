'''
Created on 2010/11/10

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Auxs as Auxs
from STG.MyShot.BaseMyShot import Base

class SpLaser(Base):
	RADIUS = 10
	SIZE = Std.Vector2DF(80, RADIUS*2)
	SPEED = 28
	BASE_DAMAGE = 4
	DAMAGE_RATE_DEC = 0.06
	DAMAGE_RATE_MIN = 0.7
	BASE_BULLET_DAMAGE = 4
	FORCE_TO_BULLET = 0.01
	
	def __init__(self, position, angle, resource):
		super().__init__(position, self.RADIUS, self.BASE_DAMAGE)
		
		self.locator = Std.Locator.LinearF(position)
		self.locator.speed.setUnitVector(angle)
		self.locator.speed *= self.SPEED
		
		self.damageRateDec = self.DAMAGE_RATE_DEC
		self.damageRateMin = self.DAMAGE_RATE_MIN
		self.bulletDamage = self.BASE_BULLET_DAMAGE
		
		self.drawParam = Std.Sprite.DrawParam()
		self.drawParam.texture = resource.spShotTexture
		self.drawParam.src = Std.RectF(0, 0, 64, 64)
		self.drawParam.dst = self.locator.position.makeRect(self.SIZE, True)
		self.drawParam.priority = Ctrl.DrawPriority.myShot
		self.drawParam.rotDegree = angle
	
	@property
	def position(self):
		return self.locator.position
	def applyExternalForce(self, vec):
		return self.locator.applyExternalForce(vec)
	
	def onUpdate(self):
		self.locator.update()
		self.drawParam.dst = self.locator.position.makeRect(self.SIZE, True)
		self.drawParam.rotDegree = self.locator.speed.getAngle()
		
		force = Std.Vector2DF()
		force.setUnitVector(self.locator.speed.getAngle())
		force *= self.FORCE_TO_BULLET
		
		self.bulletDamage = self.BASE_BULLET_DAMAGE * self.damageRate
		damageSum = Auxs.applyDamageToBullets(
			self.hitRect, self.bulletDamage)
		self.applyDamage(damageSum * 2)
		rebound = Auxs.applyExForceToBullets(
			self.hitRect, force)
		self.applyExternalForce(rebound * 60)
		
		if self.locator.speed.getAbs() < 10:
			self.erase()
	def onDraw(self):
		Std.Sprite.draw(self.drawParam)
	
	def onErase(self):
		Auxs.createFadeOut(self.drawParam, 10)
	def onDestructed(self):
		pass
	def onDamaged(self, damage):
		pass
	def onDestructedByDamage(self, damage):
		self.onErase()