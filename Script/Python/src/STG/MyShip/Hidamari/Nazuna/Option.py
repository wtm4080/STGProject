'''
Created on 2011/01/08

@author: t
'''

import Std
import STG.Ctrl as Ctrl
from Util.Sprite.Animation import createSequenceAnimation

from ..Common.BaseOption import BaseOption
from .Launcher.Option import Option as Launcher

class Option(BaseOption):
	SIZE = Std.Vector2DF(48, 48)
	
	def __init__(self, core, pos, target):
		super().__init__(core, pos, target)
		
		self.launcher = Launcher(self)
		self.launchable = False
		
		drawParam = Std.Sprite.DrawParam()
		drawParam.src = Std.RectF(0, 0, 48, 48)
		drawParam.dst = self.pos.makeRect(self.SIZE, True)
		drawParam.priority = Ctrl.DrawPriority.myShipOption
		drawParam.rotDegree = self.circling.angle + 90
		self.animation = createSequenceAnimation(
			core.resource.optionTexList, drawParam)
	
	def onUpdate(self):
		self.launcher.update()
		
		if not self.animation.playing:
			self.animation.play()
		else:
			self.animation.update()
		drawParam = self.animation.frameHolder.drawParameter
		drawParam.dst = (
			self.pos.makeRect(self.SIZE, True))
		drawParam.rotDegree = self.circling.angle + 90
		self.animation.frameHolder.drawParameter = drawParam
	def onDraw(self):
		self.animation.draw()
		self.launcher.draw()
	
	def launch(self):
		if self.launchable:
			self.launcher.launch()
	def launchBomb(self):
		return self.launcher.launchBomb()

from ..Common.BaseOption import BaseManager

import STG.Regulation.Hidamari.MyShip.Nazuna as Regulation

class Manager(BaseManager):
	REL_POS = (
		Std.Vector2DF(*Regulation.optionRelativePosition[0]), 
		Std.Vector2DF(*Regulation.optionRelativePosition[1]), 
		Std.Vector2DF(*Regulation.optionRelativePosition[2])
		)
	REL_POS_AIMING = (
		Std.Vector2DF(*Regulation.optionRelativePosition_Slow[0]), 
		Std.Vector2DF(*Regulation.optionRelativePosition_Slow[1]), 
		Std.Vector2DF(*Regulation.optionRelativePosition_Slow[2])
		)
	ANGLE = Regulation.optionAngle
	LEVEL_LIST = (1, 2, 3, 3, 3)
	
	def __init__(self, core):
		super().__init__(
			core, self.REL_POS, self.REL_POS_AIMING, self.ANGLE, 
			Option, lambda index: core.lockManager.getLockedEnemy(index), 2)
		self.bombList = []
	
	def onUpdate(self):
		if self.level != self.LEVEL_LIST[self.core.power]:
			self.level = self.LEVEL_LIST[self.core.power]
		
		self.bombList = [bomb for bomb in self.bombList 
			if (bomb.valid and not bomb.blasted) or 
			(bomb.blasted and bomb.blast.valid)]
	def onDraw(self):
		pass
	
	def launch(self):
		for option in self.optionList:
			option.launch()
	def launchBomb(self):
		if not self.bombList:
			for option in self.optionList:
				self.bombList.append(option.launchBomb())
			return True
		else:
			return False