'''
Created on 2011/12/05

@author: t
'''

import Std
import STG.Ctrl as Ctrl
from Util.Coroutine import Coroutine
from Util.Coroutine import createWait

from ...Common.BaseLauncher import BaseLauncher
from . import Shot

import STG.Regulation.Hidamari.MyShip.Nori as Regulation

class Option(BaseLauncher):
	NORMAL_SHOT_ITV_LIST = Regulation.normalOptionShotInterval
	NORMAL_SHOT_DAMAGE_LIST = Regulation.normalOptionShotBaseDamage
	
	LOCK_SHOT_ITV_LIST = Regulation.lockOptionShotInterval
	LOCK_SHOT_DAMAGE_LIST = Regulation.lockOptionShotBaseDamage
	
	SHOT_NUM_LIST = Regulation.optionShotNum
	FIRE_SIZE_LIST = (24, 32, 48, 48, 48)
	
	NORMAL_PA_DAMAGE = Regulation.normalShotPABaseDamage
	LOCK_PA_DAMAGE = Regulation.lockOptionShotPABaseDamage
	
	SHOT_HP = Regulation.lockOptionShotAttenuationResistance
	OPTION_LEVEL_EFFECT_RATE = Regulation.optionNumEffectRate_Option
	
	SP_FIRE_SIZE = 64
	
	SP_NORMAL_ITV = Regulation.spNormalOptionShotInterval
	SP_NORMAL_DAMAGE = Regulation.spNormalOptionShotBaseDamage
	SP_NORMAL_PA_DAMAGE = Regulation.spNormalOptionShotPABaseDamage
	SP_NORMAL_DAMAGE_TO_BULLET = Regulation.spNormalOptionShotDamageToBullet
	SP_NORMAL_HP = Regulation.spNormalOptionShotAttenuationResistance
	
	SP_LOCK_ITV = Regulation.spLockOptionShotInterval
	SP_LOCK_DAMAGE = Regulation.spLockOptionShotBaseDamage
	SP_LOCK_PA_DAMAGE = Regulation.spLockOptionShotPABaseDamage
	SP_LOCK_DAMAGE_TO_BULLET = Regulation.spLockOptionShotDamageToBullet
	SP_LOCK_HP = Regulation.spLockOptionShotAttenuationResistance
	
	def __init__(self, option):
		super().__init__()
		self.option = option
		
		def launchTask():
			core = option.core
			def getValue(value, rate = 1):
				return value + (
					value*core.relationalOptionLevel*self.OPTION_LEVEL_EFFECT_RATE*rate)
			def createOptionFire(texture, spAttack = False):
				drawParam = Std.Sprite.DrawParam()
				drawParam.texture = texture
				drawParam.src = Std.RectF(0, 0, 128, 128)
				drawParam.priority = Ctrl.DrawPriority.myShipB1
				drawParam.rotDegree = option.angle + 90
				if spAttack:
					drawParam.alphaBlend = Std.Sprite.AlphaBlend.Add
					size = Std.Vector2DF(self.SP_FIRE_SIZE, self.SP_FIRE_SIZE)
				else:
					size = Std.Vector2DF(
						self.FIRE_SIZE_LIST[core.power], self.FIRE_SIZE_LIST[core.power])
				self.createFire(
					Std.Vector2DF(), 
					size, 
					option.angle, 
					drawParam, 
					0.5, 
					angleCorrection = 90)
			
			while True:
				if not core.isSpAttacking:
					if not core.slow:
						self.calcRotatedLine(
							Std.Vector2DF(), 
							self.SHOT_NUM_LIST[core.power], 
							8, 
							option.angle, 
							lambda pos: Shot.createNormalShot(core, pos, option.angle, 
								getValue(self.NORMAL_SHOT_DAMAGE_LIST[core.power]), 
								max(getValue(self.NORMAL_PA_DAMAGE), self.NORMAL_PA_DAMAGE), 
								max(getValue(self.SHOT_HP, 2), self.SHOT_HP)))
						createOptionFire(core.resource.normalFire)
						
						interval = self.NORMAL_SHOT_ITV_LIST[core.power]
						wait = createWait(
							min(interval + core.relationalOptionLevel, interval))
						while wait(): yield
					else:
						self.calcRotatedLine(
							Std.Vector2DF(), 
							self.SHOT_NUM_LIST[core.power], 
							8, 
							option.angle, 
							lambda pos: Shot.createLockOptionShot(core, pos, option.angle, 
								getValue(self.LOCK_SHOT_DAMAGE_LIST[core.power]), 
								max(getValue(self.LOCK_PA_DAMAGE), self.LOCK_PA_DAMAGE), 
								max(getValue(self.SHOT_HP, 2), self.SHOT_HP)))
						createOptionFire(core.resource.lockOptionFire)
						
						interval = self.LOCK_SHOT_ITV_LIST[core.power]
						wait = createWait(
							min(interval + core.relationalOptionLevel, interval))
						while wait(): yield
				else:
					if not core.slow:
						self.calcRotatedLine(
							Std.Vector2DF(), 
							1, 
							8, 
							option.angle, 
							lambda pos: Shot.createSpNormalShot(core, pos, option.angle, 
								getValue(self.SP_NORMAL_DAMAGE), 
								max(getValue(self.SP_NORMAL_PA_DAMAGE), self.SP_NORMAL_PA_DAMAGE), 
								max(getValue(self.SP_NORMAL_DAMAGE_TO_BULLET), self.SP_NORMAL_DAMAGE_TO_BULLET), 
								max(getValue(self.SP_NORMAL_HP, 2), self.SP_NORMAL_HP)))
						createOptionFire(core.resource.normalFire)
						
						interval = self.SP_NORMAL_ITV
						wait = createWait(
							min(interval + core.relationalOptionLevel, interval))
						while wait(): yield
					else:
						self.calcRotatedLine(
							Std.Vector2DF(), 
							1, 
							8, 
							option.angle, 
							lambda pos: Shot.createSpLockOptionShot(core, pos, option.angle, 
								getValue(self.SP_LOCK_DAMAGE), 
								max(getValue(self.SP_LOCK_PA_DAMAGE), self.SP_LOCK_PA_DAMAGE),
								max(getValue(self.SP_LOCK_DAMAGE_TO_BULLET), self.SP_LOCK_DAMAGE_TO_BULLET),  
								max(getValue(self.SP_LOCK_HP, 2), self.SP_LOCK_HP)))
						createOptionFire(core.resource.lockOptionFire)
						
						interval = self.SP_LOCK_ITV
						wait = createWait(
							min(interval + core.relationalOptionLevel, interval))
						while wait(): yield
		self._launchTask = Coroutine(launchTask)
	
	@property
	def position(self):
		return self.option.nozzlePos
	@property
	def angle(self):
		return self.option.angle
	
	def launch(self):
		if self._launchTask.alive:
			self._launchTask.resume()