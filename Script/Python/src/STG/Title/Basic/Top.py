'''
Created on 2011/09/09

@author: t
'''

import Std
import STG.Resource.Common as Resource
from Util.Misc import Enum
from Util.Coroutine import Coroutine

from .DrawPriority import drawPriority
from .SelectStageSet import SelectStageSet
from .Option.Top import Top as OptionTop

enum = Enum(
	"gameStart", 
	"option", 
	"exit", 
	)

class Top:
	def __init__(self, core, initPos = enum.gameStart, fadeIn = True):
		controller = Std.Input.getController()
		
		def selectTask():
			arrow = Std.ArrowLocator(
				initPos, enum.gameStart, enum.exit)
			def drawTask():
				basePos = Std.Point2DF(420, 260)
				color = Std.ColorF()
				while True:
					font = Resource.getFont(
						"font32", drawPriority.str, False, 32)
					for i in range(enum.exit + 1):
						dst = Std.Point2DF(basePos.x, basePos.y + font.size*i)
						if i == enum.gameStart:
							font.draw(dst, color, "GameStart")
						elif i == enum.option:
							font.draw(dst, color, "Option")
						elif i == enum.exit:
							font.draw(dst, color, "Exit")
					dst = Std.Point2DF(
						basePos.x - font.size, 
						basePos.y + font.size*arrow.position)
					font.draw(dst, color, "→")
					yield
			self.drawTask = Coroutine(drawTask)
			
			if fadeIn:
				core.fadeIn(30, drawPriority.fadeEffect, lambda : ())
			
			while True:
				arrow.update()
				
				if controller.isPush(Std.Input.KeyId.X):
					arrow.position = enum.exit
				elif controller.isPush(Std.Input.KeyId.Z):
					if arrow.position == enum.gameStart:
						core.view = SelectStageSet(core)
					elif arrow.position == enum.option:
						core.view = OptionTop(core)
					elif arrow.position == enum.exit:
						def action(): Std.Scene.end = True
						core.fadeOut(30, drawPriority.fadeEffect, action)
				yield
		self.task = Coroutine(selectTask)
		self.drawTask = None
	
	def update(self):
		if self.task.alive:
			self.task.resume()
	def draw(self):
		if not self.drawTask is None and self.drawTask.alive:
			self.drawTask.resume()