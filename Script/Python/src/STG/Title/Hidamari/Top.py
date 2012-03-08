'''
Created on 2011/09/09

@author: t
'''

import Std
from Util.Misc import Enum
from Util.Coroutine import Coroutine, createWait

from .DrawPriority import drawPriority
from .SelectMyShip import SelectMyShip
from .Option.Top import Top as OptionTop

enum = Enum(
	"gameStart", 
	"option", 
	"exit", 
	)

_first = True

class Top:
	def __init__(self, core, initPos = enum.gameStart, fadeIn = True):
		controller = Std.Input.getController()
		
		def selectTask():
			if fadeIn:
				global _first
				if _first:
					_first = False
				else:
					wait = createWait(60)
					while wait(): yield
				
				core.resource.se_TitleAppear.play()
				core.fadeIn(60, drawPriority.fadeEffect, lambda : ())
				core.background.valid = True
				
				def firstDrawTask():
					font = core.resource.font_Common32
					font.setPriority(drawPriority.str)
					font.shakable = False
					alpha = 0
					offset = Std.Point2DF()
					rect = Std.RectF(0, 380, 640, 32)
					message = "Please Press Z Key..."
					
					while True:
						while alpha < 1:
							color = Std.ColorF(1, 1, 1, alpha)
							font.drawCenter(rect, offset, color, message)
							alpha += 1 / 60
							yield
						alpha = 1
						
						while alpha > 0:
							color = Std.ColorF(1, 1, 1, alpha)
							font.drawCenter(rect, offset, color, message)
							alpha -= 1 / 60
							yield
						alpha = 0
				self.drawTask = Coroutine(firstDrawTask)
				
				while True:
					if controller.isPush(Std.Input.KeyId.Z):
						core.resource.se_Enter.play()
						self.drawTask = None
						break
					yield
				
				core.background.fade()
				while not core.background.faded:
					yield
			else:
				core.background.fade(True)
			yield
			
			arrow = Std.ArrowLocator(
				initPos, enum.gameStart, enum.exit)
			arrow.setMoveCallback(lambda: core.resource.se_Select1.play())
			def drawTask():
				basePos = Std.Point2DF(420, 260)
				color = Std.ColorF()
				while True:
					font = core.resource.font_Common32
					font.setPriority(drawPriority.str)
					font.shakable = False
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
			
			while True:
				arrow.update()
				
				if controller.isPush(Std.Input.KeyId.X):
					core.resource.se_Cancel.play()
					arrow.position = enum.exit
				elif controller.isPush(Std.Input.KeyId.Z):
					if arrow.position == enum.gameStart:
						core.resource.se_Select3.play()
						core.view = SelectMyShip(core)
					elif arrow.position == enum.option:
						core.resource.se_Select2.play()
						core.view = OptionTop(core)
					elif arrow.position == enum.exit:
						core.resource.se_Select3.play()
						def action(): Std.Scene.end = True
						core.fadeOut(60, drawPriority.fadeEffect, action)
				yield
		self.task = Coroutine(selectTask)
		self.drawTask = None
	
	def update(self):
		if self.task.alive:
			self.task.resume()
	def draw(self):
		if not self.drawTask is None and self.drawTask.alive:
			self.drawTask.resume()