'''
Created on 2011/12/05

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Auxs as Auxs
from Util.Sprite.Animation import createSequenceAnimation

from ...Common.BaseShot import createSimpleShot, LockMainShotBase

import STG.Regulation.Hidamari.MyShip.Nori as Regulation

def createNormalShot(core, pos, angle, damage, paDamage, shotHp):
	speed = Regulation.normalShotSpeed
	radius = 8
	damageRateDec = Regulation.normalShotDamageRateDecrease
	damageRateMin = Regulation.normalShotDamageRateMin
	
	drawParam = Std.Sprite.DrawParam()
	drawParam.texture = core.resource.normalShot
	drawParam.src = Std.RectF(0, 0, 28, 80)
	drawParam.dst = pos.makeRect(radius*2, 80, True)
	drawParam.priority = Ctrl.DrawPriority.myShot
	drawParam.rotDegree = angle + 90
	
	vanishDrawParam = Std.Sprite.DrawParam()
	vanishDrawParam.src = Std.RectF(0, 0, 128, 128)
	vanishDrawParam.dst = pos.makeRect(48, 96, True)
	vanishDrawParam.priority = Ctrl.DrawPriority.myShot
	vanishAnimation = createSequenceAnimation(
		core.resource.normalShotParticleTexList, vanishDrawParam)
	
	shot = createSimpleShot(
		pos, angle, speed, radius, 
		damage, damageRateDec, damageRateMin, paDamage, 
		drawParam, 90, vanishAnimation, 
		core.resource.se_ShotHit)
	shot.hp = shotHp

def createLockOptionShot(core, pos, angle, damage, paDamage, shotHp):
	speed = Regulation.lockOptionShotSpeed
	radius = 8
	damageRateDec = Regulation.lockOptionShotDamageRateDecrease
	damageRateMin = Regulation.lockOptionShotDamageRateMin
	
	drawParam = Std.Sprite.DrawParam()
	drawParam.texture = core.resource.lockOptionShot
	drawParam.src = Std.RectF(0, 0, 28, 80)
	drawParam.dst = pos.makeRect(radius*2, 80, True)
	drawParam.priority = Ctrl.DrawPriority.myShot
	drawParam.rotDegree = angle + 90
	
	vanishDrawParam = Std.Sprite.DrawParam()
	vanishDrawParam.src = Std.RectF(0, 0, 128, 128)
	vanishDrawParam.dst = pos.makeRect(48, 96, True)
	vanishDrawParam.priority = Ctrl.DrawPriority.myShot
	vanishAnimation = createSequenceAnimation(
		core.resource.lockOptionShotParticleTexList, vanishDrawParam)
	
	shot = createSimpleShot(
		pos, angle, speed, radius, 
		damage, damageRateDec, damageRateMin, paDamage, 
		drawParam, 90, vanishAnimation, 
		core.resource.se_ShotHit)
	shot.hp = shotHp

def createSpNormalShot(core, pos, angle, 
					damage, paDamage, damageToBullet, shotHp, 
					damageKickbackRateToBullet = 1.0):
	speed = Regulation.spNormalShotSpeed
	radius = 32
	damageRateDec = Regulation.spNormalShotDamageRateDecrease
	damageRateMin = Regulation.spNormalShotDamageRateMin
	
	rand = Ctrl.getRandom()
	drawParam = Std.Sprite.DrawParam()
	drawParam.texture = core.resource.spNormalShot
	drawParam.src = Std.RectF(0, 0, 128, 256)
	drawParam.dst = pos.makeRect(radius*2, 96, True)
	drawParam.priority = Ctrl.DrawPriority.myShot
	drawParam.rotDegree = angle + 90
	drawParam.alphaBlend = Std.Sprite.AlphaBlend.Add
	drawParam.color.a = 0.6
	if rand.getBool():
		drawParam.flipX()
	
	particleSize = Std.Vector2DF(radius*6, radius*6)
	vanishDrawParam = Std.Sprite.DrawParam()
	vanishDrawParam.src = Std.RectF(0, 0, 128, 128)
	vanishDrawParam.dst = pos.makeRect(particleSize, True)
	vanishDrawParam.priority = Ctrl.DrawPriority.myShot
	vanishDrawParam.alphaBlend = Std.Sprite.AlphaBlend.Add
	vanishDrawParam.color.a = 0.3
	if rand.getBool():
		vanishDrawParam.flipX()
	vanishAnimation = createSequenceAnimation(
		core.resource.spNormalParticleTexList, vanishDrawParam)
	vanishAnimation.frameInterval = 0.4
	
	shot = createSimpleShot(
		pos, angle, speed, radius, 
		damage, damageRateDec, damageRateMin, paDamage, 
		drawParam, 90, vanishAnimation, 
		core.resource.se_ShotHit)
	shot.hp = shotHp
	
	shot.damageToBullet = damageToBullet
	shot.damageKickbackRateToBullet = damageKickbackRateToBullet
	def damageToBulletCallback(locator):
		drawParam = Std.Sprite.DrawParam(vanishDrawParam)
		drawParam.rotDegree = locator.speed.getAngle() + 90
		drawParam.alphaBlend = Std.Sprite.AlphaBlend.Add
		drawParam.color.a = 0.3
		if rand.getBool():
			drawParam.flipX()
		animation = createSequenceAnimation(
			core.resource.spNormalParticleTexList, drawParam)
		animation.frameInterval = 0.4
		
		rect = Std.Hit.RectI(locator.position, particleSize, True)
		animeObj = Auxs.Animation(rect, animation)
		Ctrl.Actor.registerActor(animeObj)
	shot.setDamageToBulletCallback(damageToBulletCallback)

def createSpLockOptionShot(core, pos, angle, 
					damage, paDamage, damageToBullet, shotHp, 
					damageKickbackRateToBullet = 1.0):
	speed = Regulation.spLockShotSpeed
	radius = 32
	damageRateDec = Regulation.spLockShotDamageRateDecrease
	damageRateMin = Regulation.spLockShotDamageRateMin
	
	rand = Ctrl.getRandom()
	drawParam = Std.Sprite.DrawParam()
	drawParam.texture = core.resource.spLockOptionShot
	drawParam.src = Std.RectF(0, 0, 128, 256)
	drawParam.dst = pos.makeRect(radius*2, 96, True)
	drawParam.priority = Ctrl.DrawPriority.myShot
	drawParam.rotDegree = angle + 90
	drawParam.alphaBlend = Std.Sprite.AlphaBlend.Add
	drawParam.color.a = 0.6
	if rand.getBool():
		drawParam.flipX()
	
	particleSize = Std.Vector2DF(radius*6, radius*6)
	vanishDrawParam = Std.Sprite.DrawParam()
	vanishDrawParam.src = Std.RectF(0, 0, 128, 128)
	vanishDrawParam.dst = pos.makeRect(particleSize, True)
	vanishDrawParam.priority = Ctrl.DrawPriority.myShot
	vanishDrawParam.alphaBlend = Std.Sprite.AlphaBlend.Add
	vanishDrawParam.color.a = 0.3
	if rand.getBool():
		vanishDrawParam.flipX()
	vanishAnimation = createSequenceAnimation(
		core.resource.spLockOptionParticleTexList, vanishDrawParam)
	vanishAnimation.frameInterval = 0.4
	
	shot = createSimpleShot(
		pos, angle, speed, radius, 
		damage, damageRateDec, damageRateMin, paDamage, 
		drawParam, 90, vanishAnimation, 
		core.resource.se_ShotHit)
	shot.hp = shotHp
	
	shot.damageToBullet = damageToBullet
	shot.damageKickbackRateToBullet = damageKickbackRateToBullet
	def damageToBulletCallback(locator):
		drawParam = Std.Sprite.DrawParam(vanishDrawParam)
		drawParam.rotDegree = locator.speed.getAngle() + 90
		drawParam.alphaBlend = Std.Sprite.AlphaBlend.Add
		drawParam.color.a = 0.3
		if rand.getBool():
			drawParam.flipX()
		animation = createSequenceAnimation(
			core.resource.spLockOptionParticleTexList, drawParam)
		animation.frameInterval = 0.4
		
		rect = Std.Hit.RectI(locator.position, particleSize, True)
		animeObj = Auxs.Animation(rect, animation)
		Ctrl.Actor.registerActor(animeObj)
	shot.setDamageToBulletCallback(damageToBulletCallback)

class LockMainShot(LockMainShotBase):
	SPEED = Regulation.lockMainShotSpeed
	DAMAGE_RATE_DEC = Regulation.lockMainShotDamageRateDecrease
	DAMAGE_RATE_MIN = Regulation.lockMainShotDamageRateMin
	LOCK_SPEED = Regulation.lockMainShotLockSpeed
	
	def __init__(self, core, pos, angle, toggle, radius, baseDamage, spAttack = False):
		if not spAttack:
			size = Std.Vector2DF(radius * 2, 96)
		else:
			size = Std.Vector2DF(radius * 2, 128)
		drawParam = Std.Sprite.DrawParam()
		super().__init__(core, pos, angle, radius, size, self.SPEED, 
			baseDamage, self.DAMAGE_RATE_DEC, self.DAMAGE_RATE_MIN, 
			self.LOCK_SPEED, 
			drawParam, 90, core.resource.se_ShotHit)
		
		self.hp = Regulation.lockMainShotAttenuationResistance
		
		self.toggle = toggle
		self.particleSize = Std.Vector2DF(radius * 6, radius * 6)
		
		if not spAttack:
			drawParam.color.a = 0.8
			if toggle:
				drawParam.texture = core.resource.lockMainShot_1
			else:
				drawParam.texture = core.resource.lockMainShot_2
		else:
			drawParam.alphaBlend = Std.Sprite.AlphaBlend.Add
			drawParam.color.a = 0.6
			if Ctrl.getRandom().getBool():
				drawParam.flipX()
			if toggle:
				drawParam.texture = core.resource.spLockMainShot_1
			else:
				drawParam.texture = core.resource.spLockMainShot_2
		drawParam.src = Std.RectF(0, 0, 128, 256)
		drawParam.dst = self.locator.position.makeRect(size, True)
		drawParam.priority = Ctrl.DrawPriority.myShot
		drawParam.rotDegree = angle + 90
	
	def onErase(self):
		dst = self.position.makeRect(self.particleSize, True)
		drawParam = Std.Sprite.DrawParam()
		drawParam.src = Std.RectF(0, 0, 128, 128)
		drawParam.dst = dst
		drawParam.priority = Ctrl.DrawPriority.myShot
		drawParam.rotDegree = self.drawParam.rotDegree
		if Ctrl.getRandom().getBool():
			drawParam.flipX()
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