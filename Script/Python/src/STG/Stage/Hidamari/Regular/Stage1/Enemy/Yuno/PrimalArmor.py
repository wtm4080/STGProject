'''
Created on 2011/11/06

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Auxs as Auxs
from Util.Sprite.Animation import createSequenceAnimation
from Util.Sprite.Animation import updateDst

from STG.Regulation.Hidamari.Regular.Stage1.Yuno import PrimalArmor as Regulation

class PrimalArmor:
	RADIUS = Regulation.radius
	SIZE = Std.Vector2DF(RADIUS*2, RADIUS*2)
	CAPACITY = Regulation.capacity
	SUPPLY = Regulation.supply
	GENERATE_THRESHOLD = Regulation.generateThreshold
	LINEAR_ATTENUATION = Regulation.linearAttenuation
	QUADRATIC_ATTENUATION = Regulation.quadraticAttenuation
	FORCE_TO_MYSHIP = Regulation.forceToMyShip
	FORCE_TO_MYSHOT = Regulation.forceToMyShot
	DAMAGE_TO_MYSHOT = Regulation.damageToMyShot
	EFFECT_RATE_MIN = Regulation.effectRateMin
	DAMAGED_EFFECT_MAX_NUM = 10
	DAMAGED_EFFECT_MAX_NUM_PER_FRAME = DAMAGED_EFFECT_MAX_NUM / 3
	DAMAGED_EFFECT_ALPHA = 0.4
	DAMAGED_EFFECT_ALPHA_FALLOFF = 0.2
	
	def __init__(self, core):
		self.core = core
		self._enabled = True
		self.amount = self.CAPACITY
		self.generated = True
		self.hitCircle = Std.Hit.CircleI(core.position, self.RADIUS)
		
		self.damagedDrawParamList = []
		self.damagedEffectCount = 0
		
		drawParam = Std.Sprite.DrawParam()
		drawParam.src = Std.RectF(0, 0, 128, 128)
		drawParam.priority = Ctrl.DrawPriority.paEffect
		drawParam.alphaBlend = Std.Sprite.AlphaBlend.Add
		self.generatedAnimation = createSequenceAnimation(
			core.resource.paGeneratedTexList, drawParam)
		
		drawParam = Std.Sprite.DrawParam(drawParam)
		self.vanishedAnimation = createSequenceAnimation(
			core.resource.paVanishedTexList, drawParam)
		
		self.se_generate = core.resource.se_GeneratePA
	
	@property
	def enabled(self):
		return self._enabled
	@enabled.setter
	def enabled(self, value):
		self._enabled = value
		if not value:
			self.amount = 0
	@property
	def maxAmount(self):
		return self.CAPACITY
	
	def _getEffectRate(self):
		return 1 - (1 - self.EFFECT_RATE_MIN) * (1 - self.amount/self.CAPACITY)
	
	def update(self):
		self.damagedEffectCount = 0
		if self.enabled:
			for drawParam in self.damagedDrawParamList:
				drawParam.dst = self.core.position.makeRect(self.SIZE, True)
				drawParam.color.a -= self.DAMAGED_EFFECT_ALPHA_FALLOFF * self._getEffectRate()
			self.damagedDrawParamList = [
				drawParam for drawParam in self.damagedDrawParamList 
				if drawParam.color.a > 0]
			
			self.hitCircle.center = self.core.position
			if self.generated:
				def createDamagedEffect(obj):
					angle = self.core.position.getAngle(obj.position)
					self._createDamagedDrawParam(angle)
				damage = Auxs.affectMyShotsByPA(
					self.hitCircle, 
					self.FORCE_TO_MYSHOT * self._getEffectRate(), 
					self.DAMAGE_TO_MYSHOT * self._getEffectRate(), 
					self.LINEAR_ATTENUATION, self.QUADRATIC_ATTENUATION, 
					createDamagedEffect)
				self.amount -= damage * self._getEffectRate()
				
				Auxs.applyExRadialForceToMyShip(
					self.hitCircle, 
					self.FORCE_TO_MYSHIP * self._getEffectRate(), 
					self.LINEAR_ATTENUATION, self.QUADRATIC_ATTENUATION)
				myShip = Ctrl.Actor.myShip
				if myShip.isHit(self.hitCircle):
					createDamagedEffect(myShip)
			else:
				damage = Auxs.getMyShotsForcibleDamageForPA(self.hitCircle)
				self.amount -= damage * self._getEffectRate()
			
			if self.generated and self.amount <= 0:
				self.generated = False
				self.vanishedAnimation.play()
				self.core.destructBullets()
			
			self.amount += self.SUPPLY
			if self.amount > self.CAPACITY:
				self.amount = self.CAPACITY
			
			if(not self.generated and 
			(self.amount >= self.GENERATE_THRESHOLD or 
			self.amount >= self.CAPACITY)):
				self.generated = True
				self.generatedAnimation.play()
				self.se_generate.play()
			
			if self.generatedAnimation.playing:
				self.generatedAnimation.update()
				updateDst(self.generatedAnimation, self.core.position, self.SIZE)
			if self.vanishedAnimation.playing:
				self.vanishedAnimation.update()
				updateDst(self.vanishedAnimation, self.core.position, self.SIZE)
	def draw(self):
		if self.enabled:
			for drawParam in self.damagedDrawParamList:
				Std.Sprite.draw(drawParam)
			
			if self.generatedAnimation.playing:
				self.generatedAnimation.draw()
			if self.vanishedAnimation.playing:
				self.vanishedAnimation.draw()
	
	def _createDamagedDrawParam(self, angle):
		if(len(self.damagedDrawParamList) < self.DAMAGED_EFFECT_MAX_NUM and
		self.damagedEffectCount < self.DAMAGED_EFFECT_MAX_NUM_PER_FRAME):
			drawParam = Std.Sprite.DrawParam()
			drawParam.texture = self.core.resource.paDamaged
			drawParam.src = Std.RectF(0, 0, 128, 128)
			drawParam.dst = self.core.position.makeRect(self.SIZE, True)
			drawParam.priority = Ctrl.DrawPriority.paEffect
			drawParam.color.a = self.DAMAGED_EFFECT_ALPHA * self._getEffectRate()
			drawParam.rotDegree = angle - 90
			self.damagedDrawParamList.append(drawParam)
			self.damagedEffectCount += 1