'''
Created on 2011/08/14

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Resource.Common as Resource
from Util.Misc import Enum
from Util.Coroutine import Coroutine

from .GamePad import GamePad
from .ScreenMode import ScreenMode
from .Volume import Volume

enum = Enum(
	"screenMode", 
	"volume", 
	"gamePad", 
	"default", 
	)

class Top:
	def __init__(self, core, initPos = enum.screenMode):
		controller = Std.Input.getController()
		
		def selectTask():
			arrow = Std.ArrowLocator(
				initPos, enum.screenMode, enum.default)
			def drawTask():
				basePos = Std.Point2DF(100, 200)
				color = Std.ColorF()
				while True:
					font = Resource.getFont(
						"font32", Ctrl.DrawPriority.pauseStr, False, 32)
					for i in range(enum.default + 1):
						dst = Std.Point2DF(basePos.x, basePos.y + font.size*i)
						if i == enum.screenMode:
							font.draw(dst, color, "ScreenMode")
						elif i == enum.volume:
							font.draw(dst, color, "Volume")
						elif i == enum.gamePad:
							font.draw(dst, color, "GamePad")
						elif i == enum.default:
							font.draw(dst, color, "Default")
					dst = Std.Point2DF(
						basePos.x - font.size, 
						basePos.y + font.size*arrow.position)
					font.draw(dst, color, "→")
					yield
			self.drawTask = Coroutine(drawTask)
			
			while True:
				arrow.update()
				
				if controller.isPush(Std.Input.KeyId.X):
					Ctrl.Conf.writeSetting()
					from ..Top import Top as PauseTop
					from ..Top import enum as pauseTopEnum
					core.view = PauseTop(core, pauseTopEnum.option)
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
									action()
									break
								elif confArrow.position == no:
									break
							yield
						self.drawTask = Coroutine(drawTask)
					if arrow.position == enum.screenMode:
						core.view = ScreenMode(core)
					elif arrow.position == enum.volume:
						core.view = Volume(core)
					elif arrow.position == enum.gamePad:
						core.view = GamePad(core)
					elif arrow.position == enum.default:
						confTask = Coroutine(confirmTask)
						yield
						while confTask.alive:
							confTask.resume(lambda : Ctrl.Conf.setDefaultSetting())
							yield
				yield
		self.task = Coroutine(selectTask)
		self.drawTask = None
	
	def update(self):
		if self.task.alive:
			self.task.resume()
	def draw(self):
		if not self.drawTask is None and self.drawTask.alive:
			self.drawTask.resume()