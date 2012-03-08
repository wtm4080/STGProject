'''
Created on 2011/01/07

@author: t
'''

import Std
import STG.Auxs as Auxs

from ..Common.BaseMyShip import BaseMyShip
from ..Common.LockManager import LockManager
from . import Option
from .Draw.Manager import Manager as DrawManager
from .Launcher.Main import Main as MainLauncher
from .Resource import Resource

import STG.Regulation.Hidamari.MyShip.Nori as Regulation

class Core(BaseMyShip):
	BASE_SPEED = Regulation.baseSpeed
	SPEEDRATE_SLOW = Regulation.speedRate_Slow
	BASE_OPTIONLEVEL = 2
	SPEEDRATE_OPTIONLEVEL = Regulation.speedRate_OptionNum
	SPATTACK_FRAME_NUM = Regulation.spAttackFrameNum
	SPBARRIER_FRAME_NUM = Regulation.spAttackBarrierFrameNum
	SPFINISHED_FORCE_FRAME_NUM = 60 * 1
	SP_BULLET_DESTRUCTION_FRAME_NUM = Regulation.spAttackBulletDestructionFrameNum
	
	def __init__(self, _):
		super().__init__(Resource())
		self.drawManager = DrawManager(self)
		self.optionManager = Option.Manager(self)
		self.mainLauncher = MainLauncher(self)
		self.lockManager = LockManager(self, 
			Regulation.lockThresHold, Regulation.lockParalellLoad)
		self.spFrameCount = 0
		self.spFinishedForceFrameCount = 0
		self.spBulletDestructionFrameCount = 0
	
	def onUpdate(self):
		super().onUpdate()
		self.mainLauncher.update()
		self.optionManager.update()
		self.lockManager.update()
		self.drawManager.update()
		
		if self.isSpAttacking:
			self.spFrameCount -= 1
			if not self.isSpAttacking:
				self._spFinished()
			elif self.spFrameCount == 60:
				self.drawManager.spFinishing()
		
		if self.spFinishedForceFrameCount > 0:
			circle = Std.Hit.CircleI(self.position, 400)
			Auxs.applyExRadialForceToBullets(circle, 0.3)
			self.spFinishedForceFrameCount -= 1
			if self.spFinishedForceFrameCount == 0:
				self.spBulletDestructionFrameCount = self.SP_BULLET_DESTRUCTION_FRAME_NUM
		if self.spBulletDestructionFrameCount > 0:
			Auxs.destructBullets()
			self.spBulletDestructionFrameCount -= 1
	def onDraw(self):
		self.drawManager.draw()
		self.optionManager.draw()
		self.lockManager.draw()
		self.mainLauncher.draw()
	def drawInfArea(self, basePos):
		self.drawManager.drawInfArea(basePos)
	
	def onDestruction(self):
		super().onDestruction()
		self.lockManager.reset()
		self.spFrameCount = 0
		self.drawManager.spStop()
	def onRevival(self):
		super().onRevival()
		self.optionManager.resetPos()
	def onContinue(self):
		pass
	
	@property
	def relationalOptionLevel(self):
		return self.optionManager.level - self.BASE_OPTIONLEVEL
	@property
	def moveSpeed(self):
		speed = self.BASE_SPEED * (
			1 + self.SPEEDRATE_OPTIONLEVEL*-self.relationalOptionLevel)
		if self.slow:
			return speed * self.SPEEDRATE_SLOW
		else:
			return speed
	
	def shot(self):
		self.mainLauncher.launch()
		self.optionManager.launch()
	
	@property
	def isSpAttacking(self):
		return self.spFrameCount > 0
	def specialAttack(self):
		if self.spAttackNum > 0 and not self.isSpAttacking:
			self.spAttackNum -= 1
			self.spFrameCount = self.SPATTACK_FRAME_NUM
			self.barrierCount = self.SPBARRIER_FRAME_NUM
			self.drawManager.spBegin(self.SPATTACK_FRAME_NUM)
			self.resource.se_SpAttack.play()
		elif self.spFrameCount > 0:
			self._spFinished()
	def _spFinished(self):
		self.barrierCount = self.SPBARRIER_FRAME_NUM
		self.spFrameCount = 0
		self.spFinishedForceFrameCount = self.SPFINISHED_FORCE_FRAME_NUM
		self.drawManager.spFinish()