'''
Created on 2011/12/05

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Auxs as Auxs
from STG.MyShot.BaseMyShot import Base

def createSimpleShot(pos, angle, speed, radius, 
			baseDamage, damageRateDec, damageRateMin, paBaseDamage, 
			drawParam, rotDegreeCorrection, vanishAnimation, se_ShotHit):
	locator = Std.Locator.LinearF(pos)
	locator.speed.setUnitVector(angle)
	locator.speed *= speed
	
	shot = Auxs.MyShot.Linear(
		locator, radius, drawParam, baseDamage, vanishAnimation)
	shot.rotDegreeCorrection = rotDegreeCorrection
	shot.damageRateDec = damageRateDec
	shot.damageRateMin = damageRateMin
	shot.paBaseDamage = paBaseDamage
	shot.setDestructionCallback(lambda: se_ShotHit.play())
	Ctrl.Actor.registerMyShot(shot)
	
	return shot

class BaseShot(Base):
	def __init__(self, pos, angle, radius, size, speed, baseDamage,  
				drawParam, rotDegreeCorrection = 0):
		super().__init__(pos, radius, baseDamage)
		
		self.radius = radius
		self.size = size
		self.speed = speed
		
		self.locator = Std.Locator.LinearF(pos)
		self.locator.speed.setUnitVector(angle)
		self.locator.speed *= speed
		
		self.drawParam = drawParam
		self.rotDegreeCorrection = rotDegreeCorrection
	
	@property
	def position(self):
		return self.locator.position
	def applyExternalForce(self, vec):
		return self.locator.applyExternalForce(vec)
	
	def onUpdate(self):
		self.locator.update()
		self.drawParam.dst = self.locator.position.makeRect(self.size, True)
		if self.locator.speed.getAbs() > 0:
			self.drawParam.rotDegree = self.locator.speed.getAngle() + self.rotDegreeCorrection
		
		if self.locator.speed.getAbs() < self.speed:
			self.locator.speed.normalize()
			self.locator.speed *= self.speed
	def onDraw(self):
		Std.Sprite.draw(self.drawParam)
	
	def onErase(self):
		pass
	def onDestructed(self):
		pass
	def onDamaged(self, damage):
		pass
	def onDestructedByDamage(self, damage):
		Auxs.createFadeOut(self.drawParam)

class LockMainShotBase(BaseShot):
	def __init__(self, core, pos, angle, radius, size, speed, 
				baseDamage, damageRateDec, damageRateMin, 
				lockSpeed, 
				drawParam, rotDegreeCorrection, se_ShotHit):
		super().__init__(pos, angle, radius, size, speed, 
			baseDamage, drawParam, rotDegreeCorrection)
		
		self.core = core
		
		self.damageRateDec = damageRateDec
		self.damageRateMin = damageRateMin
		
		self.lockValue = lockSpeed
		
		self.se_ShotHit = se_ShotHit
	
	def applyExternalForce(self, vec):
		return vec
	
	def applyDamageToEnemy(self):
		enemy = Auxs.applyDamageAndGetEnemy(self.hitRect, self.damage)
		if not enemy is None:
			self.core.lockManager.addLock(enemy, self.lockValue * self.damageRate)
			self.destruct()
			self.se_ShotHit.play()