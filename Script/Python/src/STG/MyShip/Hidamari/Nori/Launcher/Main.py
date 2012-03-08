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

class Main(BaseLauncher):
	NORMAL_SHOT_ITV_LIST = Regulation.normalMainShotInterval
	NORMAL_SHOT_NUM_LIST = Regulation.normalMainShotNum
	NORMAL_SHOT_DAMAGE_LIST = Regulation.normalMainShotBaseDamage
	FIRE_SIZE_LIST = (48, 56, 64, 64, 64)
	
	LOCK_SHOT_RADIUS_LIST = (16, 24, 24, 24, 24)
	LOCK_SHOT_DAMAGE_LIST = Regulation.lockMainShotDamage
	LOCK_FIRE_SIZE_LIST = (72, 96, 96, 96, 96)
	
	NORMAL_PA_DAMAGE = Regulation.normalShotPABaseDamage
	LOCK_PA_DAMAGE = Regulation.lockMainShotPABaseDamage
	
	SHOT_HP = Regulation.normalShotAttenuationResistance
	OPTION_LEVEL_EFFECT_RATE = Regulation.optionNumEffectRate_Main
	
	SP_NORMAL_ITV = Regulation.spNormalMainShotInterval
	SP_NORMAL_DAMAGE = Regulation.spNormalMainShotBaseDamage
	SP_NORMAL_PA_DAMAGE = Regulation.spNormalMainShotPABaseDamage
	SP_NORMAL_DAMAGE_TO_BULLET = Regulation.spNormalMainShotDamageToBullet
	SP_NORMAL_FIRE_SIZE = 64
	SP_NORMAL_HP = Regulation.spNormalMainShotAttenuationResistance
	
	SP_LOCK_DAMAGE = Regulation.spLockMainShotBaseDamage
	SP_LOCK_PA_DAMAGE = Regulation.spLockMainShotPABaseDamage
	SP_LOCK_RADIUS = 48
	SP_LOCK_FIRE_SIZE = 96
	SP_LOCK_HP = Regulation.spLockMainShotAttenuationResistance
	
	def __init__(self, core):
		super().__init__()
		self.core = core
		self.lockShotToggle = True
		
		def launchTask():
			def getValue(value, rate = 1):
				return value + (
					value*core.relationalOptionLevel*self.OPTION_LEVEL_EFFECT_RATE*rate)
			
			while True:
				if not core.isSpAttacking:
					if not core.slow:
						self.calcRotatedLine(
							Std.Vector2DF(20, 0), 
							self.NORMAL_SHOT_NUM_LIST[core.power], 
							10, 
							-90, 
							lambda pos: Shot.createNormalShot(core, pos, -90, 
								getValue(self.NORMAL_SHOT_DAMAGE_LIST[core.power]), 
								max(getValue(self.NORMAL_PA_DAMAGE), self.NORMAL_PA_DAMAGE), 
								max(getValue(self.SHOT_HP, 2), self.SHOT_HP)), 
							30)
						
						drawParam = Std.Sprite.DrawParam()
						drawParam.texture = core.resource.normalFire
						drawParam.src = Std.RectF(0, 0, 128, 128)
						drawParam.priority = Ctrl.DrawPriority.myShipB1
						drawParam.rotDegree = 0
						size = self.FIRE_SIZE_LIST[core.power]
						self.createFire(
							Std.Vector2DF(20, 0), 
							Std.Vector2DF(size, size), 
							-90, 
							drawParam, 
							0.5, 
							2, 
							20, 
							angleCorrection = 90)
						
						core.resource.se_NormalShot.play()
						
						interval = self.NORMAL_SHOT_ITV_LIST[core.power]
						wait = createWait(
							min(interval + core.relationalOptionLevel, interval))
						while wait(): yield
					else:
						pos = core.position + Std.Vector2DF(0, -20)
						shot = Shot.LockMainShot(core, pos, -90, self.lockShotToggle, 
							self.LOCK_SHOT_RADIUS_LIST[core.power], 
							getValue(self.LOCK_SHOT_DAMAGE_LIST[core.power]))
						shot.paBaseDamage = max(
							getValue(self.LOCK_PA_DAMAGE), self.LOCK_PA_DAMAGE)
						shot.hp = max(getValue(self.SHOT_HP, 2), self.SHOT_HP)
						Ctrl.Actor.registerMyShot(shot)
						
						drawParam = Std.Sprite.DrawParam()
						if self.lockShotToggle:
							drawParam.texture = core.resource.lockMainFire_1
						else:
							drawParam.texture = core.resource.lockMainFire_2
						drawParam.src = Std.RectF(0, 0, 128, 128)
						drawParam.priority = Ctrl.DrawPriority.myShipB1
						drawParam.rotDegree = 0
						size = self.LOCK_FIRE_SIZE_LIST[core.power]
						self.createFire(
							Std.Vector2DF(20, 0), 
							Std.Vector2DF(size, size), 
							-90, 
							drawParam, 
							0.5, 
							angleCorrection = 90)
						
						core.resource.se_LockShot.play()
						
						self.lockShotToggle = not self.lockShotToggle
						
						wait = createWait(2)
						while wait(): yield
				else:
					if not core.slow:
						self.calcRotatedLine(
							Std.Vector2DF(20, 0), 
							4, 
							10, 
							-90, 
							lambda pos: Shot.createSpNormalShot(core, pos, -90, 
								getValue(self.SP_NORMAL_DAMAGE), 
								max(getValue(self.SP_NORMAL_PA_DAMAGE), self.SP_NORMAL_PA_DAMAGE), 
								max(getValue(self.SP_NORMAL_DAMAGE_TO_BULLET), self.SP_NORMAL_DAMAGE_TO_BULLET), 
								max(getValue(self.SP_NORMAL_HP, 2), self.SP_NORMAL_HP)), 
							30)
						
						drawParam = Std.Sprite.DrawParam()
						drawParam.texture = core.resource.normalFire
						drawParam.src = Std.RectF(0, 0, 128, 128)
						drawParam.priority = Ctrl.DrawPriority.myShipB1
						drawParam.rotDegree = 0
						drawParam.alphaBlend = Std.Sprite.AlphaBlend.Add
						size = self.SP_NORMAL_FIRE_SIZE
						self.createFire(
							Std.Vector2DF(20, 0), 
							Std.Vector2DF(size, size), 
							-90, 
							drawParam, 
							0.5, 
							2, 
							20, 
							angleCorrection = 90)
						
						core.resource.se_NormalShot.play()
						
						interval = self.SP_NORMAL_ITV
						wait = createWait(
							min(interval + core.relationalOptionLevel, interval))
						while wait(): yield
					else:
						pos = core.position + Std.Vector2DF(0, -20)
						shot = Shot.LockMainShot(core, pos, -90, self.lockShotToggle, 
							self.SP_LOCK_RADIUS, 
							getValue(self.SP_LOCK_DAMAGE), 
							True)
						shot.paBaseDamage = max(
							getValue(self.SP_LOCK_PA_DAMAGE), self.SP_LOCK_PA_DAMAGE)
						shot.hp = max(getValue(self.SP_LOCK_HP, 2), self.SP_LOCK_HP)
						Ctrl.Actor.registerMyShot(shot)
						
						drawParam = Std.Sprite.DrawParam()
						if self.lockShotToggle:
							drawParam.texture = core.resource.lockMainFire_1
						else:
							drawParam.texture = core.resource.lockMainFire_2
						drawParam.src = Std.RectF(0, 0, 128, 128)
						drawParam.priority = Ctrl.DrawPriority.myShipB1
						drawParam.rotDegree = 0
						drawParam.alphaBlend = Std.Sprite.AlphaBlend.Add
						size = self.SP_LOCK_FIRE_SIZE
						self.createFire(
							Std.Vector2DF(20, 0), 
							Std.Vector2DF(size, size), 
							-90, 
							drawParam, 
							0.5, 
							angleCorrection = 90)
						
						core.resource.se_LockShot.play()
						
						self.lockShotToggle = not self.lockShotToggle
						
						wait = createWait(2)
						while wait(): yield
		self._launchTask = Coroutine(launchTask)
	
	@property
	def position(self):
		return self.core.position
	@property
	def angle(self):
		return -90
	
	def launch(self):
		if self._launchTask.alive:
			self._launchTask.resume()