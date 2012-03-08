'''
Created on 2011/08/13

@author: t
'''

import Std
import STG.Ctrl as Ctrl
from Util.Coroutine import Coroutine

import STG.Resource.Hidamari as Resource
from .Background import Background
from .Continue import Continue
from .Top import Top

class Core:
	def __init__(self, _):
		self.resource = Resource.getResource()
		self.background = Background()
		self.view = None
		self.fadeOutDrawParam = None
	
	def update(self):
		if self.fadeOutDrawParam is None:
			backStatus = self.background.update()
			if self.view is None:
				self.resource.se_Select2.play()
				self.view = Top(self)
			if self.background.finishedFadeIn:
				self.view.update()
			return backStatus
		else:
			self.fadeOutTask.resume()
			return True
	def draw(self):
		self.background.draw()
		if not self.view is None:
			self.view.draw()
		if not self.fadeOutDrawParam is None:
			Std.Sprite.draw(self.fadeOutDrawParam)
	
	def update_Continue(self):
		if self.fadeOutDrawParam is None:
			backStatus = self.background.update()
			if self.view is None:
				self.view = Continue(self)
			if self.background.finishedFadeIn:
				self.view.update()
			return backStatus
		else:
			self.fadeOutTask.resume()
			return True
	def draw_Continue(self):
		self.background.draw()
		if not self.view is None:
			self.view.draw()
		if not self.fadeOutDrawParam is None:
			Std.Sprite.draw(self.fadeOutDrawParam)
	
	@property
	def end(self):
		return self.background.end
	@end.setter
	def end(self, value):
		self.background.end = value
	
	def fadeOut(self, frameNum, action):
		self.fadeOutDrawParam = Std.Sprite.DrawParam()
		self.fadeOutDrawParam.dst = Std.RectF(
			0, 0, Std.Consts.ScreenSize.x, Std.Consts.ScreenSize.y)
		self.fadeOutDrawParam.priority = Ctrl.DrawPriority.fadeEffect
		self.fadeOutDrawParam.shakable = False
		self.fadeOutDrawParam.color = Std.ColorF(0, 0, 0, 0)
		
		def fadeOutTask():
			while self.fadeOutDrawParam.color.a < 1:
				self.fadeOutDrawParam.color.a += 1 / frameNum
				yield
			action()
		self.fadeOutTask = Coroutine(fadeOutTask)