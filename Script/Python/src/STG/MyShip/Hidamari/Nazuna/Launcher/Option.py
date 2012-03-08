'''
Created on 2011/09/17

@author: t
'''

import Std
import STG.Ctrl as Ctrl
from Util.Coroutine import Coroutine
from Util.Coroutine import createWait

from ...Common.BaseLauncher import BaseLauncher
from . import Shot
from .Bomb import PlasmaBall

import STG.Regulation.Hidamari.MyShip.Nazuna as Regulation

class Option(BaseLauncher):
	NORMAL_SHOT_ITV_LIST = Regulation.normalOptionShotInterval
	LOCK_SHOT_ITV_LIST = Regulation.lockOptionShotInterval
	SHOT_NUM_LIST = Regulation.optionShotNum
	FIRE_SIZE_LIST = (24, 24, 32, 48, 48)
	
	def __init__(self, option):
		super().__init__()
		self.option = option
		self.launchTask = Coroutine(self._launchTask)
		self.se_LaunchPlasma = option.core.resource.se_LaunchPlasma
	
	@property
	def position(self):
		return self.option.nozzlePos
	@property
	def angle(self):
		return self.option.angle
	
	def launch(self):
		if self.launchTask.alive:
			self.launchTask.resume()
	def _launchTask(self):
		core = self.option.core
		def createOptionFire(texture):
			drawParam = Std.Sprite.DrawParam()
			drawParam.texture = texture
			drawParam.src = Std.RectF(0, 0, 128, 128)
			drawParam.priority = Ctrl.DrawPriority.myShipB1
			drawParam.rotDegree = self.option.angle + 90
			self.createFire(
				Std.Vector2DF(12, 0), 
				Std.Vector2DF(self.FIRE_SIZE_LIST[core.power], 
					self.FIRE_SIZE_LIST[core.power]), 
				self.option.angle, 
				drawParam, 
				0.5, 
				angleCorrection = 90)
		
		while True:
			if not core.slow:
				self.calcRotatedLine(
					Std.Vector2DF(), 
					self.SHOT_NUM_LIST[core.power], 
					8, 
					self.option.angle, 
					lambda pos: Shot.createNormalShot(core, pos, self.option.angle))
				createOptionFire(core.resource.normalFire)
				
				wait = createWait(self.NORMAL_SHOT_ITV_LIST[core.power])
				while wait(): yield
			else:
				self.calcRotatedLine(
					Std.Vector2DF(), 
					self.SHOT_NUM_LIST[core.power], 
					8, 
					self.option.angle, 
					lambda pos: Shot.createLockOptionShot(core, pos, self.option.angle))
				createOptionFire(core.resource.lockOptionFire)
				
				wait = createWait(self.LOCK_SHOT_ITV_LIST[core.power])
				while wait(): yield
	
	def launchBomb(self):
		plasmaBall = PlasmaBall(
			self.option.core, self.option.nozzlePos, self.option.angle)
		Ctrl.Actor.registerMyShot(plasmaBall)
		self.se_LaunchPlasma.play()
		return plasmaBall