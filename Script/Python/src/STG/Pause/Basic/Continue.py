'''
Created on 2011/08/14

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Resource.Common as Resource
from Util.Coroutine import Coroutine

class Continue:
	def __init__(self, core):
		controller = Ctrl.getController()
		
		def task():
			yes = 0; no = 1
			arrow = Std.ArrowLocator(yes, yes, no)
			arrow.controller = controller
			def drawTask():
				basePos = Std.Point2DF(100, 200)
				color = Std.ColorF()
				while True:
					font = Resource.getFont(
						"font32", Ctrl.DrawPriority.pauseStr, False, 32)
					font.draw(basePos, color, "コンティニューしますか？")
					for i in range(no + 1):
						dst = Std.Point2DF(
							basePos.x, basePos.y + font.size*(i + 1))
						if i == yes:
							font.draw(dst, color, "はい")
						elif i == no:
							font.draw(dst, color, "いいえ")
					dst = Std.Point2DF(
						basePos.x - font.size, 
						basePos.y + font.size*(arrow.position + 1))
					font.draw(dst, color, "→")
					yield
			self.drawTask = Coroutine(drawTask)
			
			while True:
				arrow.update()
				if controller.isPush(Std.Input.KeyId.Z):
					if arrow.position == yes:
						core.end = True
						self.drawTask = None
					elif arrow.position == no:
						core.fadeOut(
							30, lambda : Std.Scene.changeToSTGTitle())
				yield
		self.task = Coroutine(task)
		self.drawTask = None
	
	def update(self):
		if self.task.alive:
			self.task.resume()
	def draw(self):
		if not self.drawTask is None and self.drawTask.alive:
			self.drawTask.resume()