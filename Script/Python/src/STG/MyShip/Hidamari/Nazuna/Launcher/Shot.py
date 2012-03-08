'''
Created on 2010/11/10

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Auxs as Auxs
from Util.Sprite.Animation import createSequenceAnimation

from ...Common.BaseShot import createSimpleShot, LockMainShotBase

import STG.Regulation.Hidamari.MyShip.Nazuna as Regulation

def createNormalShot(core, pos, angle):
	speed = Regulation.normalShotSpeed
	radius = 8
	
	drawParam = Std.Sprite.DrawParam()
	drawParam.texture = core.resource.normalShot
	drawParam.src = Std.RectF(0, 0, 28, 80)
	drawParam.dst = pos.makeRect(radius*2, 80, True)
	drawParam.priority = Ctrl.DrawPriority.myShot
	drawParam.rotDegree = angle + 90
	
	baseDamage = Regulation.normalShotBaseDamage
	damageRateDec = Regulation.normalShotDamageRateDecrease
	damageRateMin = Regulation.normalShotDamageRateMin
	paBaseDamage = Regulation.normalShotPABaseDamage
	
	vanishDrawParam = Std.Sprite.DrawParam()
	vanishDrawParam.src = Std.RectF(0, 0, 128, 128)
	vanishDrawParam.dst = pos.makeRect(48, 96, True)
	vanishDrawParam.priority = Ctrl.DrawPriority.myShot
	vanishAnimation = createSequenceAnimation(
		core.resource.normalShotParticleTexList, vanishDrawParam)
	
	shot = createSimpleShot(
		pos, angle, speed, radius, 
		baseDamage, damageRateDec, damageRateMin, paBaseDamage, 
		drawParam, 90, vanishAnimation, 
		core.resource.se_ShotHit)
	shot.hp = Regulation.normalShotAttenuationResistance

def createLockOptionShot(core, pos, angle):
	speed = Regulation.lockOptionShotSpeed
	radius = 8
	
	drawParam = Std.Sprite.DrawParam()
	drawParam.texture = core.resource.lockOptionShot
	drawParam.src = Std.RectF(0, 0, 28, 80)
	drawParam.dst = pos.makeRect(radius*2, 80, True)
	drawParam.priority = Ctrl.DrawPriority.myShot
	drawParam.rotDegree = angle + 90
	
	baseDamage = Regulation.lockOptionShotBaseDamage
	damageRateDec = Regulation.lockOptionShotDamageRateDecrease
	damageRateMin = Regulation.lockOptionShotDamageRateMin
	paBaseDamage = Regulation.lockOptionShotPABaseDamage
	
	vanishDrawParam = Std.Sprite.DrawParam()
	vanishDrawParam.src = Std.RectF(0, 0, 128, 128)
	vanishDrawParam.dst = pos.makeRect(48, 96, True)
	vanishDrawParam.priority = Ctrl.DrawPriority.myShot
	vanishAnimation = createSequenceAnimation(
		core.resource.lockOptionShotParticleTexList, vanishDrawParam)
	
	shot = createSimpleShot(
		pos, angle, speed, radius, 
		baseDamage, damageRateDec, damageRateMin, paBaseDamage, 
		drawParam, 90, vanishAnimation, 
		core.resource.se_ShotHit)
	shot.hp = Regulation.lockOptionShotAttenuationResistance

class LockMainShot(LockMainShotBase):
	SPEED = Regulation.lockMainShotSpeed
	DAMAGE_RATE_DEC = Regulation.lockMainShotDamageRateDecrease
	DAMAGE_RATE_MIN = Regulation.lockMainShotDamageRateMin
	LOCK_SPEED = Regulation.lockMainShotLockSpeed
	
	def __init__(self, core, pos, angle, toggle, radius = 24, baseDamage = 8):
		size = Std.Vector2DF(radius * 2, 96)
		drawParam = Std.Sprite.DrawParam()
		super().__init__(core, pos, angle, radius, size, self.SPEED, 
			baseDamage, self.DAMAGE_RATE_DEC, self.DAMAGE_RATE_MIN, 
			self.LOCK_SPEED, 
			drawParam, 90, core.resource.se_ShotHit)
		
		self.hp = Regulation.lockMainShotAttenuationResistance
		
		self.toggle = toggle
		self.particleSize = Std.Vector2DF(radius * 6, radius * 6)
		
		if toggle:
			drawParam.texture = core.resource.lockMainShot_1
		else:
			drawParam.texture = core.resource.lockMainShot_2
		drawParam.src = Std.RectF(0, 0, 128, 200)
		drawParam.dst = self.locator.position.makeRect(size, True)
		drawParam.priority = Ctrl.DrawPriority.myShot
		drawParam.rotDegree = angle + 90
		drawParam.color.a = 0.8
	
	def onErase(self):
		dst = self.position.makeRect(self.particleSize, True)
		drawParam = Std.Sprite.DrawParam()
		drawParam.src = Std.RectF(0, 0, 128, 128)
		drawParam.dst = dst
		drawParam.priority = Ctrl.DrawPriority.myShot
		drawParam.rotDegree = self.drawParam.rotDegree
		if self.toggle:
			texList = self.core.resource.lockMainParticleTexList_1
		else:
			texList = self.core.resource.lockMainParticleTexList_2
		animation = createSequenceAnimation(texList, drawParam)
		animation.frameInterval = 0.6
		animeObj = Auxs.Animation(Std.Hit.RectI(dst), animation)
		Ctrl.Actor.registerActor(animeObj)
	def onDestructed(self):
		self.onErase()