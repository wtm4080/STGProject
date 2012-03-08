'''
Created on 2011/08/14

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Resource.Common as Resource
from Util.Misc import Enum
from Util.Coroutine import Coroutine

from .Option.Top import Top as OptionTop

enum = Enum(
	"returnToGame", 
	"restart", 
	"returnToTitle", 
	"option", 
	)

class Top:
	def __init__(self, core, initPos = enum.returnToGame):
		controller = Std.Input.getController()
		
		def selectTask():
			arrow = Std.ArrowLocator(
				initPos, enum.returnToGame, enum.option)
			def drawTask():
				basePos = Std.Point2DF(100, 200)
				color = Std.ColorF()
				while True:
					font = Resource.getFont(
						"font32", Ctrl.DrawPriority.pauseStr, False, 32)
					for i in range(enum.option + 1):
						dst = Std.Point2DF(basePos.x, basePos.y + font.size*i)
						if i == enum.returnToGame:
							font.draw(dst, color, "ゲームに戻る")
						elif i == enum.restart:
							font.draw(dst, color, "最初から始める")
						elif i == enum.returnToTitle:
							font.draw(dst, color, "タイトル画面へ")
						elif i == enum.option:
							font.draw(dst, color, "オプション")
					dst = Std.Point2DF(
						basePos.x - font.size, 
						basePos.y + font.size*arrow.position)
					font.draw(dst, color, "→")
					yield
			self.drawTask = Coroutine(drawTask)
			
			while True:
				arrow.update()
				
				if(controller.isPush(Std.Input.KeyId.Space) or 
				controller.isPush(Std.Input.KeyId.X)):
					core.end = True
					self.drawTask = None
				elif controller.isPush(Std.Input.KeyId.Z):
					def confirmTask(action):
						yes = 0; no = 1
						confArrow = Std.ArrowLocator(no, yes, no)
						def confDrawTask():
							basePos = Std.Point2DF(100, 200)
							color = Std.ColorF()
							while True:
								font = Resource.getFont(
									"font32", Ctrl.DrawPriority.pauseStr, False, 32)
								font.draw(basePos, color, "本当に？")
								for i in range(no + 1):
									dst = Std.Point2DF(
										basePos.x, basePos.y + font.size*(i + 1))
									if i == yes:
										font.draw(dst, color, "はい")
									elif i == no:
										font.draw(dst, color, "いいえ")
								dst = Std.Point2DF(
									basePos.x - font.size, 
									basePos.y + font.size*(confArrow.position + 1))
								font.draw(dst, color, "→")
								yield
						self.drawTask = Coroutine(confDrawTask)
						
						while True:
							confArrow.update()
							if controller.isPush(Std.Input.KeyId.X):
								break
							elif controller.isPush(Std.Input.KeyId.Z):
								if confArrow.position == yes:
									core.fadeOut(30, action)
								elif confArrow.position == no:
									break
							yield
						self.drawTask = Coroutine(drawTask)
					if arrow.position == enum.returnToGame:
						core.end = True
						self.drawTask = None
					elif arrow.position == enum.restart:
						confTask = Coroutine(confirmTask)
						yield
						while confTask.alive:
							confTask.resume(lambda : Ctrl.restart())
							yield
					elif arrow.position == enum.returnToTitle:
						confTask = Coroutine(confirmTask)
						yield
						while confTask.alive:
							confTask.resume(lambda : Std.Scene.changeToSTGTitle())
							yield
					elif arrow.position == enum.option:
						core.view = OptionTop(core)
				yield
		self.task = Coroutine(selectTask)
		self.drawTask = None
	
	def update(self):
		if self.task.alive:
			self.task.resume()
	def draw(self):
		if not self.drawTask is None and self.drawTask.alive:
			self.drawTask.resume()