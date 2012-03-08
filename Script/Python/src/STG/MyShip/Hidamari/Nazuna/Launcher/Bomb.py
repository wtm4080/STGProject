'''
Created on 2011/10/25

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Auxs as Auxs
from STG.MyShot.BaseMyShot import Base
from Util.Sprite.Animation import createSequenceAnimation
from Util.Sprite.Animation import updateDst

import STG.Regulation.Hidamari.MyShip.Nazuna as Regulation

class PlasmaBall(Base):
	RADIUS = Regulation.plasmaBallRadius
	SIZE = Std.Vector2DF(RADIUS*2, RADIUS*2)
	SPEED = Regulation.plasmaBallSpeed
	BASE_DAMAGE = Regulation.plasmaBallBaseDamage
	DAMAGE_RATE_DEC = Regulation.plasmaBallDamageRateDecrease
	DAMAGE_RATE_MIN = Regulation.plasmaBallDamageRateMin
	VALID_AREA = Std.Hit.RectI(0, 0, 
		Std.Consts.ScreenSize.x - Std.Consts.StgInfAreaSize.x, 
		Std.Consts.ScreenSize.y, False)
	
	def __init__(self, core, position, angle):
		super().__init__(position, self.RADIUS, self.BASE_DAMAGE)
		self.noDamage = True
		self.core = core
		self.prevValidArea = self.isHitRect(self.VALID_AREA)
		
		self.locator = Std.Locator.LinearF(position)
		self.locator.speed.setUnitVector(angle)
		self.locator.speed *= self.SPEED
		
		self.damageRateDec = self.DAMAGE_RATE_DEC
		self.damageRateMin = self.DAMAGE_RATE_MIN
		
		self.blast = PlasmaBlast(self.core, self.position)
		self.blasted = False
		
		drawParam = Std.Sprite.DrawParam()
		drawParam.src = Std.RectF(0, 0, 64, 64)
		drawParam.dst = position.makeRect(self.SIZE, True)
		drawParam.priority = Ctrl.DrawPriority.myShot
		self.animation = createSequenceAnimation(
			core.resource.plasmaBallTexList, drawParam)
		rand = Ctrl.getRandom()
		self.animation.play(
			rand.getInt(0, self.animation.frameHolder.frameNum - 1))
		
		self.se_PlasmaBlast = core.resource.se_PlasmaBlast
	
	@property
	def position(self):
		return self.locator.position
	def applyExternalForce(self, vec):
		return Std.Vector2DF()
	
	def onUpdate(self):
		self.locator.update()
		
		inValidArea = self.isHitRect(self.VALID_AREA)
		if self.prevValidArea and not inValidArea:
			self.createBlast()
		self.prevValidArea = inValidArea
		
		if not self.animation.playing:
			self.animation.play()
		self.animation.update()
		updateDst(self.animation, self.position, self.SIZE)
	def createBlast(self):
		self.destruct()
		self.blast.position = self.position
		Ctrl.Actor.registerMyShot(self.blast)
		self.blasted = True
		self.se_PlasmaBlast.play()
	def applyDamageToEnemy(self):
		Auxs.destructBullets(self.hitCircle)
		damageSum = Auxs.applyDamageToEnemies(self.hitRect, self.damage)
		if damageSum != 0:
			self.createBlast()
	def onDraw(self):
		self.animation.draw()
	
	def onErase(self):
		Auxs.createFadeOut(self.animation.frameHolder.drawParameter)
	def onDestructed(self):
		self.onErase()
	def onDamaged(self, damage):
		pass
	def onDestructedByDamage(self, damage):
		self.onErase()

class PlasmaBlast(Base):
	RADIUS = Regulation.plasmaBlastRadius
	SIZE = Std.Vector2DF(RADIUS*2, RADIUS*2)
	BASE_DAMAGE = Regulation.plasmaBlastBaseDamage
	PA_BASE_DAMAGE = Regulation.plasmaBlastPABaseDamage
	LONGEVITY = Regulation.plasmaBlastLongevity
	
	def __init__(self, core, position):
		super().__init__(position, self.RADIUS, self.BASE_DAMAGE)
		self.noDamage = True
		self.locator = Std.Locator.LinearF(position)
		self.paBaseDamage = self.PA_BASE_DAMAGE
		self.forcibleForPA = True
		self.frameCounnt = self.LONGEVITY
		
		drawParam = Std.Sprite.DrawParam()
		drawParam.src = Std.RectF(0, 0, 128, 128)
		drawParam.dst = position.makeRect(self.SIZE, True)
		drawParam.priority = Ctrl.DrawPriority.myShot
		self.animation = createSequenceAnimation(
			core.resource.plasmaBlastTexList, drawParam)
		rand = Ctrl.getRandom()
		self.animation.play(
			rand.getInt(0, self.animation.frameHolder.frameNum - 1))
	
	@property
	def position(self):
		return self.locator.position
	@position.setter
	def position(self, value):
		self.locator.position = value
	def applyExternalForce(self, vec):
		return Std.Vector2DF()
	
	def onUpdate(self):
		self.locator.update()
		
		if self.frameCounnt <= 0:
			drawParam = self.animation.frameHolder.drawParameter
			if drawParam.color.a > 0:
				self.baseDamage = 0
				drawParam.color.a -= 0.1
				self.animation.frameHolder.drawParameter = drawParam
			else:
				self.valid = False
		else:
			self.frameCounnt -= 1
		
		if not self.animation.playing:
			self.animation.play()
		self.animation.update()
		updateDst(self.animation, self.position, self.SIZE)
	def applyDamageToEnemy(self):
		if self.baseDamage > 0:
			Auxs.applyDamageToEnemies(self.hitRect, self.damage)
			Auxs.applyDamageToBullets(self.hitCircle, self.damage)
	def onDraw(self):
		self.animation.draw()
	
	def onErase(self):
		Auxs.createFadeOut(self.animation.frameHolder.drawParameter)
	def onDestructed(self):
		self.onErase()
	def onDamaged(self, damage):
		pass
	def onDestructedByDamage(self, damage):
		self.onErase()