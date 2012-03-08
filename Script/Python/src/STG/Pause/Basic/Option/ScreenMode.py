'''
Created on 2011/08/14

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Resource.Common as Resource
from Util.Misc import Enum
from Util.Coroutine import Coroutine

enum = Enum(
	"full", 
	"window", 
	)

class ScreenMode:
	def __init__(self, core):
		controller = Std.Input.getController()
		
		def selectTask():
			arrow = Std.ArrowLocator(
				enum.full, enum.full, enum.window)
			def drawTask():
				basePos = Std.Point2DF(100, 200)
				color = Std.ColorF()
				while True:
					font = Resource.getFont(
						"font32", Ctrl.DrawPriority.pauseStr, False, 32)
					for i in range(enum.window + 1):
						dst = Std.Point2DF(basePos.x, basePos.y + font.size*i)
						if i == enum.full:
							font.draw(dst, color, "FullScreen")
						elif i == enum.window:
							font.draw(dst, color, "Window")
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
					core.view = Top(core, topEnum.screenMode)
				elif controller.isPush(Std.Input.KeyId.Z):
					if arrow.position == enum.full:
						Ctrl.Conf.fullScreen = True
					elif arrow.position == enum.window:
						Ctrl.Conf.fullScreen = False
				yield
		self.task = Coroutine(selectTask)
		self.drawTask = None
	
	def update(self):
		if self.task.alive:
			self.task.resume()
	def draw(self):
		if not self.drawTask is None and self.drawTask.alive:
			self.drawTask.resume()