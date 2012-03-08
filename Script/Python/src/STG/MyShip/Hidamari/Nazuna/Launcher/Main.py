'''
Created on 2011/09/12

@author: t
'''

import Std
import STG.Ctrl as Ctrl
from Util.Coroutine import Coroutine
from Util.Coroutine import createWait

from ...Common.BaseLauncher import BaseLauncher
from . import Shot

import STG.Regulation.Hidamari.MyShip.Nazuna as Regulation

class Main(BaseLauncher):
	NORMAL_SHOT_ITV_LIST = Regulation.normalMainShotInterval
	NORMAL_SHOT_NUM_LIST = Regulation.normalMainShotNum
	FIRE_SIZE_LIST = (48, 48, 48, 56, 64)
	LOCK_SHOT_RADIUS_LIST = (16, 16, 24, 24, 24)
	LOCK_SHOT_DAMAGE_LIST = Regulation.lockMainShotDamage
	LOCK_FIRE_SIZE_LIST = (72, 72, 96, 96, 96)
	
	def __init__(self, core):
		super().__init__()
		self.core = core
		self.launchTask = Coroutine(self._launchTask)
		self.lockShotToggle = True
		self.se_NormalShot = core.resource.se_NormalShot
		self.se_LockShot = core.resource.se_LockShot
	
	@property
	def position(self):
		return self.core.position
	@property
	def angle(self):
		return -90
	
	def launch(self):
		if self.launchTask.alive:
			self.launchTask.resume()
	def _launchTask(self):
		while True:
			if not self.core.slow:
				self.calcRotatedLine(
					Std.Vector2DF(20, 0), 
					self.NORMAL_SHOT_NUM_LIST[self.core.power], 
					10, 
					-90, 
					lambda pos: Shot.createNormalShot(self.core, pos, -90), 
					30)
				
				drawParam = Std.Sprite.DrawParam()
				drawParam.texture = self.core.resource.normalFire
				drawParam.src = Std.RectF(0, 0, 128, 128)
				drawParam.priority = Ctrl.DrawPriority.myShipB1
				drawParam.rotDegree = 0
				size = self.FIRE_SIZE_LIST[self.core.power]
				self.createFire(
					Std.Vector2DF(20, 0), 
					Std.Vector2DF(size, size), 
					-90, 
					drawParam, 
					0.5, 
					2, 
					20, 
					angleCorrection = 90)
				
				self.se_NormalShot.play()
				
				wait = createWait(self.NORMAL_SHOT_ITV_LIST[self.core.power])
				while wait(): yield
			else:
				pos = self.core.position + Std.Vector2DF(0, -20)
				shot = Shot.LockMainShot(self.core, pos, -90, self.lockShotToggle, 
					self.LOCK_SHOT_RADIUS_LIST[self.core.power], 
					self.LOCK_SHOT_DAMAGE_LIST[self.core.power])
				Ctrl.Actor.registerMyShot(shot)
				
				drawParam = Std.Sprite.DrawParam()
				if self.lockShotToggle:
					drawParam.texture = self.core.resource.lockMainFire_1
				else:
					drawParam.texture = self.core.resource.lockMainFire_2
				drawParam.src = Std.RectF(0, 0, 128, 128)
				drawParam.priority = Ctrl.DrawPriority.myShipB1
				drawParam.rotDegree = 0
				size = self.LOCK_FIRE_SIZE_LIST[self.core.power]
				self.createFire(
					Std.Vector2DF(20, 0), 
					Std.Vector2DF(size, size), 
					-90, 
					drawParam, 
					0.5, 
					angleCorrection = 90)
				
				self.se_LockShot.play()
				
				self.lockShotToggle = not self.lockShotToggle
				
				wait = createWait(2)
				while wait(): yield