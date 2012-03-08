'''
Created on 2011/12/22

@author: t
'''

import Std

from .DrawPriority import drawPriority

class Background:
	FADE_ALPHA = 0.4
	
	def __init__(self, core):
		self.valid = False
		
		self.drawParam = Std.Sprite.DrawParam()
		self.drawParam.texture = core.resource.titleBack
		self.drawParam.src = Std.RectF(0, 0, 640, 480)
		self.drawParam.dst = Std.RectF(0, 0, 640, 480)
		self.drawParam.priority = drawPriority.back
		
		self.fading = False
		self.blackRectDrawParam = Std.Sprite.DrawParam()
		self.blackRectDrawParam.dst = Std.RectF(0, 0, 640, 480)
		self.blackRectDrawParam.priority = drawPriority.backFade
		self.blackRectDrawParam.color = Std.ColorF(0, 0, 0, 0)
	
	def update(self):
		if self.fading and self.blackRectDrawParam.color.a < self.FADE_ALPHA:
			self.blackRectDrawParam.color.a += self.FADE_ALPHA / 20
		elif self.fading and self.blackRectDrawParam.color.a > self.FADE_ALPHA:
			self.blackRectDrawParam.color.a = self.FADE_ALPHA
	def draw(self):
		if self.valid:
			Std.Sprite.draw(self.drawParam)
			Std.Sprite.draw(self.blackRectDrawParam)
	
	def fade(self, immediate = False):
		self.fading = True
		if not immediate:
			self.blackRectDrawParam.color.a = 0
		else:
			self.blackRectDrawParam.color.a = self.FADE_ALPHA
	@property
	def faded(self):
		return self.fading and self.blackRectDrawParam.color.a >= self.FADE_ALPHA