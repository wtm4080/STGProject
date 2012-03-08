'''
Created on 2011/08/14

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Resource.Common as Resource
from Util.Misc import Enum
from Util.Coroutine import Coroutine

from ..DrawPriority import drawPriority

enum = Enum(
	"bgm", 
	"se", 
	)

class Volume:
	def __init__(self, core):
		controller = Std.Input.getController()
		
		def selectTask():
			select = Std.ArrowLocator(
				enum.bgm, enum.bgm, enum.se)
			select.horizontal = True
			bgmValue = Std.ArrowLocator(
				-Ctrl.Conf.bgmVolume, -100, 0, False)
			bgmValue.repeatInterval = 2
			seValue = Std.ArrowLocator(
				-Ctrl.Conf.seVolume, -100, 0, False)
			seValue.repeatInterval = 2
			def drawTask():
				basePos = Std.Point2DF(400, 260)
				def drawValue(name, dst, value, selected):
					font = Resource.getFont(
						"font32", drawPriority.str, False, 32)
					color = Std.ColorF()
					if not selected:
						color.a = 0.5
					dst = Std.Point2DF(dst)
					
					font.draw(dst, color, name)
					dst.y += 32
					if value < 100:
						font.draw(dst, color, "↑")
					dst.y += 32
					if value > 0:
						font.draw(dst, color, "↓")
					dst.x += 32
					dst.y -= 32 / 2
					font.draw(dst, color, str(int(value)))
				while True:
					dst = Std.Point2DF(basePos)
					drawValue("BGM", dst, -bgmValue.position, 
						select.position == enum.bgm)
					dst.x += 100
					drawValue("SE", dst, -seValue.position, 
						select.position == enum.se)
					yield
			self.drawTask = Coroutine(drawTask)
			
			while True:
				select.update()
				if select.position == enum.bgm:
					bgmValue.update()
				elif select.position == enum.se:
					seValue.update()
				
				Ctrl.Conf.bgmVolume = -bgmValue.position
				Ctrl.Conf.seVolume = -seValue.position
				
				if controller.isPush(Std.Input.KeyId.X):
					from .Top import Top
					from .Top import enum as topEnum
					core.view = Top(core, topEnum.volume)
				yield
		self.task = Coroutine(selectTask)
		self.drawTask = None
	
	def update(self):
		if self.task.alive:
			self.task.resume()
	def draw(self):
		if not self.drawTask is None and self.drawTask.alive:
			self.drawTask.resume()