'''
Created on 2011/08/14

@author: t
'''

import Std
import STG.Ctrl as Ctrl
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
			arrow.setMoveCallback(lambda: core.resource.se_Select1.play())
			def drawTask():
				basePos = Std.Point2DF(100, 200)
				color = Std.ColorF()
				while True:
					font = core.resource.font_Common32
					font.setPriority(Ctrl.DrawPriority.pauseStr)
					font.shakable = False
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
					core.resource.se_Cancel.play()
					from .Top import Top
					from .Top import enum as topEnum
					core.view = Top(core, topEnum.screenMode)
				elif controller.isPush(Std.Input.KeyId.Z):
					core.resource.se_Select2.play()
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