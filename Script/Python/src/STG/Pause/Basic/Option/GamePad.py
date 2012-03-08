'''
Created on 2011/08/14

@author: t
'''

import Std
import STG.Ctrl as Ctrl
import STG.Resource.Common as Resource
from Util.Misc import Enum
from Util.Coroutine import Coroutine
from Util.Coroutine import createWait

enum = Enum(
	"shot", 
	"special", 
	"spare", 
	"slow", 
	"pause", 
	"direction", 
	"returnTop", 
	)

class GamePad:
	def __init__(self, core):
		controller = Std.Input.getController()
		
		def selectTask():
			arrow = Std.ArrowLocator(
				enum.shot, enum.shot, enum.returnTop)
			def drawTask():
				basePos = Std.Point2DF(100, 200)
				color = Std.ColorF()
				while True:
					font = Resource.getFont(
						"font32", Ctrl.DrawPriority.pauseStr, False, 32)
					for i in range(enum.returnTop + 1):
						dst = Std.Point2DF(
							basePos.x, basePos.y + font.size*i)
						dstVKey = Std.Point2DF(
							basePos.x + 260, basePos.y + font.size*i)
						if i == enum.shot:
							font.draw(dst, color, "決定/ショット")
							font.draw(dstVKey, color, 
								str(Ctrl.Conf.getButtonVirtualKey(Std.Input.KeyId.Z)))
						elif i == enum.special:
							font.draw(dst, color, "取消/特殊攻撃")
							font.draw(dstVKey, color, 
								str(Ctrl.Conf.getButtonVirtualKey(Std.Input.KeyId.X)))
						elif i == enum.spare:
							font.draw(dst, color, "KEY_C（予備）")
							font.draw(dstVKey, color, 
								str(Ctrl.Conf.getButtonVirtualKey(Std.Input.KeyId.C)))
						elif i == enum.slow:
							font.draw(dst, color, "低速移動")
							font.draw(dstVKey, color, 
								str(Ctrl.Conf.getButtonVirtualKey(Std.Input.KeyId.LShift)))
						elif i == enum.pause:
							font.draw(dst, color, "ポーズ")
							font.draw(dstVKey, color, 
								str(Ctrl.Conf.getButtonVirtualKey(Std.Input.KeyId.Space)))
						elif i == enum.direction:
							font.draw(dst, color, "方向入力設定")
						elif i == enum.returnTop:
							font.draw(dst, color, "戻る")
					dst = Std.Point2DF(
						basePos.x - font.size, 
						basePos.y + font.size*arrow.position)
					font.draw(dst, color, "→")
					yield
			self.drawTask = Coroutine(drawTask)
			
			while True:
				arrow.update()
				
				def returnToTop():
					from .Top import Top
					from .Top import enum as topEnum
					core.view = Top(core, topEnum.gamePad)
				if(controller.isPush(Std.Input.KeyId.X) and 
				(arrow.position == enum.direction or 
				arrow.position == enum.returnTop)):
					returnToTop()
				elif controller.isPush(Std.Input.KeyId.Z):
					if arrow.position == enum.direction:
						def dirConfigTask():
							message = ""
							def dirConfigDrawTask():
								color = Std.ColorF()
								dst = Std.Point2DF(120, 220)
								while True:
									font = Resource.getFont(
										"font32", Ctrl.DrawPriority.pauseStr, False, 32)
									font.draw(dst, color, message)
									yield
							self.drawTask = Coroutine(dirConfigDrawTask)
							
							wait = createWait(30)
							while wait(): yield
							while True:
								if Ctrl.Conf.attachControllerAxis(
									Std.Input.AxisId.XMinus):
									message = ""
									break
								message = "左を入力してください"
								yield
							wait = createWait(30)
							while wait(): yield
							while True:
								if Ctrl.Conf.attachControllerAxis(
									Std.Input.AxisId.XPlus):
									message = ""
									break
								message = "右を入力してください"
								yield
							wait = createWait(30)
							while wait(): yield
							while True:
								if Ctrl.Conf.attachControllerAxis(
									Std.Input.AxisId.YMinus):
									message = ""
									break
								message = "上を入力してください"
								yield
							wait = createWait(30)
							while wait(): yield
							while True:
								if Ctrl.Conf.attachControllerAxis(
									Std.Input.AxisId.YPlus):
									message = ""
									break
								message = "下を入力してください"
								yield
							wait = createWait(30)
							while wait(): yield
							self.drawTask = Coroutine(drawTask)
						dirConfTask = Coroutine(dirConfigTask)
						yield
						while dirConfTask.alive:
							dirConfTask.resume()
							yield
					elif arrow.position == enum.returnTop:
						returnToTop()
				else:
					if arrow.position == enum.shot:
						Ctrl.Conf.attachControllerButton(Std.Input.KeyId.Z)
					elif arrow.position == enum.special:
						Ctrl.Conf.attachControllerButton(Std.Input.KeyId.X)
					elif arrow.position == enum.spare:
						Ctrl.Conf.attachControllerButton(Std.Input.KeyId.C)
					elif arrow.position == enum.slow:
						Ctrl.Conf.attachControllerButton(Std.Input.KeyId.LShift)
					elif arrow.position == enum.pause:
						Ctrl.Conf.attachControllerButton(Std.Input.KeyId.Space)
				yield
		self.task = Coroutine(selectTask)
		self.drawTask = None
	
	def update(self):
		if self.task.alive:
			self.task.resume()
	def draw(self):
		if not self.drawTask is None and self.drawTask.alive:
			self.drawTask.resume()