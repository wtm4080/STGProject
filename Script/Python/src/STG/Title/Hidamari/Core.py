'''
Created on 2011/09/08

@author: t
'''

import Std
from Util.Coroutine import Coroutine

from .Resource import Resource
from .Top import Top
from .Background import Background

class Core:
	def __init__(self):
		self.view = Top(self)
		self.fadeEffectDrawParam = None
		self.resource = Resource()
		self.background = Background(self)
	
	def update(self):
		if self.fadeEffectDrawParam is None:
			self.view.update()
		else:
			self.fadeEffectTask.resume()
		
		self.background.update()
	def draw(self):
		if not self.view is None:
			self.view.draw()
		if not self.fadeEffectDrawParam is None:
			Std.Sprite.draw(self.fadeEffectDrawParam)
		
		self.background.draw()
	
	def fadeIn(self, frameNum, drawPriority, action):
		self._setFadeEffectDrawParam(drawPriority, 1)
		def fadeInTask():
			while self.fadeEffectDrawParam.color.a > 0:
				self.fadeEffectDrawParam.color.a -= 1 / frameNum
				yield
			action()
			self.fadeEffectDrawParam = None
		self.fadeEffectTask = Coroutine(fadeInTask)
	def fadeOut(self, frameNum, drawPriority, action):
		self._setFadeEffectDrawParam(drawPriority, 0)
		def fadeOutTask():
			while self.fadeEffectDrawParam.color.a < 1:
				self.fadeEffectDrawParam.color.a += 1 / frameNum
				yield
			action()
		self.fadeEffectTask = Coroutine(fadeOutTask)
	def _setFadeEffectDrawParam(self, drawPriority, alpha):
		self.fadeEffectDrawParam = Std.Sprite.DrawParam()
		self.fadeEffectDrawParam.dst = Std.RectF(
			0, 0, Std.Consts.ScreenSize.x, Std.Consts.ScreenSize.y)
		self.fadeEffectDrawParam.priority = drawPriority
		self.fadeEffectDrawParam.shakable = False
		self.fadeEffectDrawParam.color = Std.ColorF(0, 0, 0, alpha)