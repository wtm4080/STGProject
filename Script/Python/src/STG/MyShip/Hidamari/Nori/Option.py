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
	SIZE = Std.Vector2DF(48, 48) * 0.8
	
	def __init__(self, core, pos, target, flip):
		super().__init__(core, pos, target)
		
		self.launcher = Launcher(self)
		self.launchable = False
		
		drawParam = Std.Sprite.DrawParam()
		drawParam.src = Std.RectF(0, 0, 48, 48)
		drawParam.dst = self.pos.makeRect(self.SIZE, True)
		drawParam.priority = Ctrl.DrawPriority.myShipOption
		drawParam.rotDegree = self.circling.angle + 90
		if flip:
			drawParam.flipX()
		self.animation = createSequenceAnimation(
			core.resource.optionTexList, drawParam)
	
	def onUpdate(self):
		self.launcher.update()
		
		if not self.animation.playing:
			self.animation.play()
		else:
			self.animation.update()
		drawParam = self.animation.frameHolder.drawParameter
		drawParam.dst = self.pos.makeRect(self.SIZE, True)
		drawParam.rotDegree = self.circling.angle + 90
		self.animation.frameHolder.drawParameter = drawParam
	def onDraw(self):
		self.animation.draw()
		self.launcher.draw()
	
	def launch(self):
		if self.launchable:
			self.launcher.launch()

from ..Common.BaseOption import BaseManager

import STG.Regulation.Hidamari.MyShip.Nori as Regulation

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
	
	def __init__(self, core):
		super().__init__(
			core, self.REL_POS, self.REL_POS_AIMING, self.ANGLE, 
			Option, lambda index: core.lockManager.getLockedEnemy(index), 2)
		self.levelChangeWaitCount = 0
	
	def onUpdate(self):
		if self.levelChangeWaitCount > 0:
			self.levelChangeWaitCount -= 1
		controller = Ctrl.getController()
		if(controller.isHold(Std.Input.KeyId.C) and 
		self.levelChangeWaitCount == 0):
			def change(level):
				self.level += level
				self.levelChangeWaitCount = 60
				self.core.lockManager.adjust()
				self.core.resource.se_ChangeOption.play()
			dirY = controller.direction.y
			if dirY < -0.3 and self.level < self.maxLevel:
				change(1)
			elif dirY > 0.3 and self.level > 1:
				change(-1)
	def onDraw(self):
		pass
	
	def _createOption(self, index, pos):
		return self.optionClass(self.core, pos, pos, index % 2 == 1)
	
	def launch(self):
		for option in self.optionList:
			option.launch()