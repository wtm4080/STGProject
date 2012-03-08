'''
Created on 2011/08/14

@author: t
'''

import Std
import STG.Ctrl as Ctrl
from Util.Coroutine import Coroutine

class Background:
	ALPHA = 0.6
	FADE_FRAME_NUM = 8
	
	def __init__(self):
		self.finishedFadeIn = False
		self.end = False
		
		self.drawParam = Std.Sprite.DrawParam()
		self.drawParam.dst = Std.RectF(
			0, 0, Std.Consts.ScreenSize.x, Std.Consts.ScreenSize.y)
		self.drawParam.priority = Ctrl.DrawPriority.pauseBackB3
		self.drawParam.color = Std.ColorF(0, 0, 0, 0)
		self.drawParam.shakable = False
		
		def task():
			while self.drawParam.color.a < self.ALPHA:
				self.drawParam.color.a += self.ALPHA / self.FADE_FRAME_NUM
				yield
			
			self.drawParam.color.a = self.ALPHA
			self.finishedFadeIn = True
			while not self.end:
				yield
			
			while self.drawParam.color.a > 0:
				self.drawParam.color.a -= self.ALPHA / self.FADE_FRAME_NUM
				yield
		self.task = Coroutine(task)
	
	def update(self):
		if self.task.alive:
			self.task.resume()
		return self.task.alive
	def draw(self):
		Std.Sprite.draw(self.drawParam)