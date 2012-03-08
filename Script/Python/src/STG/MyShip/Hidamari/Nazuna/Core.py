'''
Created on 2011/01/07

@author: t
'''

from ..Common.BaseMyShip import BaseMyShip
from ..Common.LockManager import LockManager
from . import Option
from .Draw.Manager import Manager as DrawManager
from .Launcher.Main import Main as MainLauncher
from .Resource import Resource

import STG.Regulation.Hidamari.MyShip.Nazuna as Regulation

class Core(BaseMyShip):
	def __init__(self, _):
		super().__init__(Resource())
		self.drawManager = DrawManager(self)
		self.optionManager = Option.Manager(self)
		self.mainLauncher = MainLauncher(self)
		self.lockManager = LockManager(self, 
			Regulation.lockThresHold, Regulation.lockParalellLoad)
	
	def onUpdate(self):
		super().onUpdate()
		self.optionManager.update()
		self.drawManager.update()
		self.mainLauncher.update()
		self.lockManager.update()
	def onDraw(self):
		self.drawManager.draw()
		self.optionManager.draw()
		self.mainLauncher.draw()
		self.lockManager.draw()
	def drawInfArea(self, basePos):
		self.drawManager.drawInfArea(basePos)
	
	def onDestruction(self):
		super().onDestruction()
		self.lockManager.reset()
	def onRevival(self):
		super().onRevival()
		self.optionManager.resetPos()
	def onContinue(self):
		pass
	
	@property
	def moveSpeed(self):
		if self.slow:
			return Regulation.moveSpeed_Slow
		else:
			return Regulation.moveSpeed
	
	def shot(self):
		self.mainLauncher.launch()
		self.optionManager.launch()
	def specialAttack(self):
		if self.spAttackNum > 0 and self.optionManager.launchBomb():
			self.setBarrier(Regulation.spAttackBarrierFrameNum)
			self.spAttackNum -= 1