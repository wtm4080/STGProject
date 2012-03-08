'''
Created on 2011/09/09

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Resource.Common as Resource
from Util.Coroutine import Coroutine

from .DrawPriority import drawPriority
from .SelectMyShip import SelectMyShip

class SelectStageSet:
	def __init__(self, core, initPos = 0):
		controller = Std.Input.getController()
		infoList = Ctrl.Conf.getStageSetInfoList()
		
		def selectTask():
			arrow = Std.ArrowLocator(initPos, 0, len(infoList) - 1)
			def drawTask():
				basePos = Std.Point2DF(420, 260)
				color = Std.ColorF()
				while True:
					font = Resource.getFont(
						"font32", drawPriority.str, False, 32)
					for i in range(len(infoList)):
						dst = Std.Point2DF(basePos.x, basePos.y + font.size*i)
						font.draw(dst, color, infoList[i][1])
					dst = Std.Point2DF(
						basePos.x - font.size, 
						basePos.y + font.size*arrow.position)
					font.draw(dst, color, "→")
					yield
			self.drawTask = Coroutine(drawTask)
			
			while True:
				arrow.update()
				
				if controller.isPush(Std.Input.KeyId.X):
					from .Top import Top
					from .Top import enum as topEnum
					core.view = Top(core, topEnum.gameStart, False)
				elif controller.isPush(Std.Input.KeyId.Z):
					core.view = SelectMyShip(
						core, infoList[arrow.position][0], arrow.position)
				yield
		self.task = Coroutine(selectTask)
		self.drawTask = None
	
	def update(self):
		if self.task.alive:
			self.task.resume()
	def draw(self):
		if not self.drawTask is None and self.drawTask.alive:
			self.drawTask.resume()